#include "sfmt/SFMT.h"
#include "fileProcess.h"
#include "ComputeBurnin_tmp.h"
#include <sstream>
#include <map>
#include <algorithm>
#include <cmath>

int F(int Age)
{
	if(Age >= 10 && Age <= 25)
		return 1 ;
	else 
		return 0 ;
}

string iTostr(int a, int b)
{
	stringstream ss;
	string s;
	ss << a << b;
	ss >> s;
	return s;
}

vector<int> S(vector<vector<int> > &graph, int lastNode, int curNode, map<string,vector<int> > &bMap)
{
	vector<int> s = graph[curNode];

	string key = iTostr(lastNode, curNode);
	map<string, vector<int> >::iterator it = bMap.find(key);
	if(it == bMap.end())
	{
		vector<int> a ;	
		bMap[key] = a;
		return s ;	
	}

	for(int i=0; i<(int)(it->second).size(); i++)
		s.erase(remove(s.begin(), s.end(), (it->second)[i]), s.end()); 	
	return s ;
}

int main(int argn, char **argv)
{
	int N ; //the nodes of graph 
	int tmpID, tmpUser, tmp ;
	double weight_tmp, weight_f = 0.0, weight_f1 = 0.0 ;
	map<string,vector<int> > bMap ;

	int interation = 25000;

	sfmt_t sfmtSeed ;
	sfmt_init_gen_rand(&sfmtSeed, 1234567*(unsigned)time(NULL)) ;

	string path, ID ;                            
        for(int i=0; i<argn; i++)
        {                       
                if(argv[i] == string("-dataset")) path = string(argv[i+1]) ;
                if(argv[i] == string("-ID")) ID = string(argv[i+1]);       
        }                                                                 
        if(path == "")                                                   
                cout<< "dataset path missing" <<endl ; 

	vector<vector<int> > graph = readFile(path.c_str(), N) ; 

	int ttmp ;
	vector<int> age ;
	FILE *fp1 = fopen("./Flickr_Age.txt", "r");
	while(fscanf(fp1,"%d",&ttmp) == 1)
		age.push_back(ttmp) ;
	fclose(fp1) ;

	vector<int> Product ;
	FILE *fp2 = fopen("./Product_A.txt", "r") ;
	while(fscanf(fp2,"%d",&ttmp) == 1)
		Product.push_back(ttmp) ;
	fclose(fp2) ;

	int *flag = new int[N]();
	int flag_count = 0 ;
	int *Q = new int[interation]();

	int startUser = 5000;
	Q[0] = startUser ;
		
	tmpID = sfmt_genrand_uint32(&sfmtSeed) % graph[startUser].size() ;
	tmpUser = graph[startUser][tmpID] ;
	Q[1] = tmpUser ;

	for(int i=2; i<interation; i++)
	{
		vector<int> s = S(graph, startUser, tmpUser, bMap);
		if(s.empty() == false)
		{
			tmpID = sfmt_genrand_uint32(&sfmtSeed) % s.size() ;
			tmp = s[tmpID] ;		
			bMap[iTostr(startUser,tmpUser)].push_back(tmp) ;
		}
		else
		{
			tmpID = sfmt_genrand_uint32(&sfmtSeed) % graph[tmpUser].size() ;
			tmp = graph[tmpUser][tmpID] ;		
			bMap[iTostr(startUser, tmpUser)].clear() ;
		}
		Q[i] = tmp ;
		startUser = tmpUser ;
		tmpUser = tmp ;
	}
	int burnin = 5653;
	for(int j=0; j<burnin; j++)
		if(flag[Q[j]] == 0)
		{
			flag[Q[j]] = 1;
			flag_count += 1;
		}

	int count = burnin;
	int qc = flag_count ;
	while(flag_count <= qc+1200)
	{
		int node = Q[count++] ;
		weight_tmp = 1.0 / graph[node].size() ;
		weight_f += F(age[node]) * Product[node] * weight_tmp ;
		weight_f1 += Product[node] * weight_tmp ;
		if(flag[node] == 0)
		{
			flag[node] = 1;
			flag_count += 1;
		}
	}
	FILE *fp = fopen("./qc1.txt", "a+");
	double estimator = weight_f / weight_f1 ;
	double relatedError = abs(estimator - 0.410178) / 0.410178;
	fprintf(fp, "%d %f\n", flag_count, relatedError);
	fclose(fp);
	return 0 ;
}
