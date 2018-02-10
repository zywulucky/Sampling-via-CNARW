#include "sfmt/SFMT.h"
#include "fileProcess.h"
#include "ComputeBurnin_tmp.h"
#include <sstream>
#include <map>
#include <algorithm>

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
	double weight_tmp, weight_f = 0.0, weight_sum = 0.0 ;
	map<string,vector<int> > bMap ;

	int interation = 15000;

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

	int *flag = new int[N]();
	int flag_count = 0 ;
	int *Q = new int[interation]();
	vector<double> x ;

	int startUser = 5000;
	x.push_back((double)graph[startUser].size()) ;
	Q[0] = startUser ;
		
	tmpID = sfmt_genrand_uint32(&sfmtSeed) % graph[startUser].size() ;
	tmpUser = graph[startUser][tmpID] ;
	x.push_back((double)graph[tmpUser].size()) ;
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
		x.push_back((double)graph[tmp].size()) ;
		Q[i] = tmp ;
		startUser = tmpUser ;
		tmpUser = tmp ;
	}

	int burnin = 9922;

	for(int j=0; j<burnin; j++)
		if(flag[Q[j]] == 0)
		{
			flag[Q[j]] = 1;
			flag_count += 1;
		}

	int count = burnin;
	int qc = flag_count ;
	while(flag_count <= qc+200)
	{
		int node = Q[count++] ;
		weight_tmp = 1.0 / graph[node].size() ;
		weight_f += graph[node].size() * weight_tmp ;
		weight_sum += weight_tmp ;
		if(flag[node] == 0)
		{
			flag[node] = 1;
			flag_count += 1;
		}
	}
	FILE *fp = fopen("./qc1.txt", "a+");
	double estimator = weight_f / weight_sum ;
	double relatedError = abs(estimator - 44.45) / 44.45;
	fprintf(fp, "%d %f\n", flag_count, relatedError);
	fclose(fp);
	return 0 ;
}
