#include "sfmt/SFMT.h"
#include "fileProcess.h"
#include "ComputeBurnin_tmp.h"
#include "memoryusage.h"
#include <cmath>

int main(int argn, char **argv)
{
	vector<vector<int> > graph ;
	sfmt_t sfmtSeed ;
	int N ;	

	sfmt_init_gen_rand(&sfmtSeed, (unsigned)time(NULL)*1234567) ;

	int iteration = 100000;

	string path, ID;
	for(int i=0; i<argn; i++)
	{
		if(argv[i] == string("-dataset")) path = string(argv[i+1]) ;
		if(argv[i] == string("-ID")) ID = string(argv[i+1]) ;
	}
	if(path == "")
		cout<< "argument dataset missing" <<endl ;

	graph = readFile(path.c_str(), N) ;
	vector<int> samples ;
	double weight_tmp, weight_f=0.0, weight_sum = 0.0 ;
	int *flag = new int[N]() ;
	int flag_count = 0 ;
	FILE *fp = fopen("./qc.txt", "a+") ;

	vector<int> Q ;
	int startUser = 5000;
	Q.push_back(startUser) ;

	for(int i=1; i<iteration; i++)
	{
		int tmpID = sfmt_genrand_uint32(&sfmtSeed) % graph[startUser].size() ;
		int tmpUser = graph[startUser][tmpID] ;
		Q.push_back(tmpUser) ;
		startUser = tmpUser ;
	}

	int burnin = 20438;

	for(int j=0; j<burnin; j++)
		if(flag[Q[j]] == 0)
		{
			flag[Q[j]] = 1 ;
			flag_count += 1 ;
		}

	int j =burnin;
	int qc = flag_count ;
	while(flag_count <= qc+3300)
	{
		int lastNode = Q[j] ;
		int node = Q[++j] ;
		weight_tmp = 1.0  ;
		weight_f += Jaccard(graph, lastNode, node) * weight_tmp ;
		weight_sum += weight_tmp ;
		if(flag[lastNode] == 0)
		{
			flag[lastNode] = 1 ;
			flag_count += 1 ;
		}
	}
	double estimator = weight_f / weight_sum ;
	double rr = fabs(estimator -  0.0503892) / 0.0503892; //one should change this value according to different dataset 
	fprintf(fp, "%d %f\n", flag_count, rr);
	fclose(fp);
	return 0 ;
}
