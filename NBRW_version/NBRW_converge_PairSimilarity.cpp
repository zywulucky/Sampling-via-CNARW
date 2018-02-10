#include "sfmt/SFMT.h"
#include "fileProcess.h"
#include "ComputeBurnin_tmp.h"
#include <time.h>
#include <algorithm>

int main(int argn, char **argv)
{
	int N ; //the nodes of graph 
	int tmpID, tmpUser, tmp ;
	int interation = 200001;

	sfmt_t sfmtSeed ;
	sfmt_init_gen_rand(&sfmtSeed, (unsigned)time(NULL)*1234567) ;

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
		if(graph[tmpUser].size() > 1)
		{
			graph[tmpUser].erase(remove(graph[tmpUser].begin(), graph[tmpUser].end(), startUser), graph[tmpUser].end());
			tmpID = sfmt_genrand_uint32(&sfmtSeed) % graph[tmpUser].size() ;
			tmp = graph[tmpUser][tmpID] ;		
			graph[tmpUser].push_back(startUser) ;

			x.push_back(Jaccard(graph, tmpUser, tmp)) ;
	
			startUser = tmpUser ;
			tmpUser = tmp ;
		}
		else
		{
			tmp = startUser ;
			startUser = tmpUser;			
			tmpUser = tmp ;
			x.push_back(Jaccard(graph, startUser, tmpUser)) ;
		}
	}
	int burnin = computeBurnin(x, ID) ;
	cout<< "average burn-in period: " << burnin << endl ;

	return 0 ;
}

