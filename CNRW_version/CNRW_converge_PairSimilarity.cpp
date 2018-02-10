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
		bMap[key] = a ; 
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
	map<string,vector<int> > bMap ;

	int interation = 200001;

	sfmt_t sfmtSeed ;
	sfmt_init_gen_rand(&sfmtSeed, (unsigned)time(NULL)*1234567);

	string path, ID ;                            
        for(int i=0; i<argn; i++)
        {                       
                if(argv[i] == string("-dataset")) path = string(argv[i+1]) ;
                if(argv[i] == string("-ID")) ID = string(argv[i+1]);       
        }                                                                 
        if(path == "")                                                   
                cout<< "dataset path missing" <<endl ; 

	vector<vector<int> > graph = readFile(path.c_str(), N) ; 

	vector<double> x ;
	int startUser = 5000;

	tmpID = sfmt_genrand_uint32(&sfmtSeed) % graph[startUser].size() ;
	tmpUser = graph[startUser][tmpID] ;
	x.push_back(Jaccard(graph, startUser, tmpUser)) ;

	for(int i=2; i<interation; i++)
	{
		vector<int> s = S(graph, startUser, tmpUser, bMap);
		if(s.empty() == false)
		{
			tmpID = sfmt_genrand_uint32(&sfmtSeed) % s.size() ;
			tmp = s[tmpID] ;		
		}
		else
		{
			tmpID = sfmt_genrand_uint32(&sfmtSeed) % graph[tmpUser].size() ;
			tmp = graph[tmpUser][tmpID] ;		
			bMap[iTostr(startUser, tmpUser)].clear() ;
		}
		bMap[iTostr(startUser,tmpUser)].push_back(tmp) ;
		x.push_back(Jaccard(graph, tmpUser, tmp)) ;

		startUser = tmpUser ;
		tmpUser = tmp ;
	}

	int burnin = computeBurnin(x, ID) ;
	cout<< "average burn-in period: " << burnin << endl ;

	return 0 ;
}
