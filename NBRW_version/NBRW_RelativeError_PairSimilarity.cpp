#include "sfmt/SFMT.h"
#include "fileProcess.h"
#include "ComputeBurnin_tmp.h"
#include <time.h>
#include <algorithm>
#include <cmath>

int main(int argn, char **argv)
{
	int N ; 
	int tmpID, tmpUser, tmp ;
	double weight_tmp, weight_f = 0.0, weight_sum = 0.0 ;
	int interation = 35000;

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

	int *flag = new int[N]() ;
	int flag_count = 0 ;

	vector<int> Q ;
	int startUser = 5000;
	tmpID = sfmt_genrand_uint32(&sfmtSeed) % graph[startUser].size() ;
	tmpUser = graph[startUser][tmpID] ;
	Q.push_back(startUser) ;
	Q.push_back(tmpUser) ;

	for(int i=2; i<interation; i++)
	{
		if(graph[tmpUser].size() > 1)
		{
			graph[tmpUser].erase(remove(graph[tmpUser].begin(), graph[tmpUser].end(),startUser), graph[tmpUser].end());
			tmpID = sfmt_genrand_uint32(&sfmtSeed) % graph[tmpUser].size() ;
			tmp = graph[tmpUser][tmpID] ;		
			graph[tmpUser].push_back(startUser) ;
			Q.push_back(tmp) ;
			startUser = tmpUser ;
			tmpUser = tmp ;
		}
		else
		{
			tmp = startUser ;
			startUser = tmpUser;			
			tmpUser = tmp ;
			Q.push_back(tmpUser) ;
		}
	}

	int burnin = 11020;
	for(int j=0; j<burnin; j++)
                if(flag[Q[j]] == 0)
                {
                        flag[Q[j]] = 1;
                        flag_count += 1 ;
                }

        FILE *fp = fopen("./qc2.txt","a+");

	int count = burnin ; 
	int qc = flag_count;
	while(flag_count < qc + 50)
	{
		int lastNode = Q[count] ;
        	int node = Q[++count] ;
		weight_tmp = 1.0 ;
		weight_f += Jaccard(graph, lastNode, node) * weight_tmp ;
		weight_sum += weight_tmp ;
		if(flag[lastNode] == 0)
		{
			flag[lastNode] = 1 ;
			flag_count += 1;
		}
	}
	double estimator = weight_f / weight_sum ;
	double relatedError = abs(estimator - 0.124318) / 0.124318;
	fprintf(fp,"%d %f\n", flag_count, relatedError);
        fclose(fp);
	return 0 ;
}

