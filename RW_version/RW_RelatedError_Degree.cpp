#include "sfmt/SFMT.h"
#include "fileProcess.h"
#include "ComputeBurnin_tmp.h"
#include "memoryusage.h"
#include <cmath>

int main(int argn, char **argv)
{
	vector<vector<int> > graph ;
	vector<int> samples ;
	sfmt_t sfmtSeed ;
	double weight_tmp, weight_f=0.0, weight_sum = 0.0 ;
	int N ;	//the nodes of graph 

	sfmt_init_gen_rand(&sfmtSeed, (unsigned)time(NULL)*1234567) ;

	int iteration = 50000;

	string path, ID ;
	for(int i=0; i<argn; i++)
	{
		if(argv[i] == string("-dataset")) path = string(argv[i+1]) ;
		if(argv[i] == string("-ID")) ID = string(argv[i+1]) ;
	}
	if(path == "")
		cout<< "argument dataset missing" <<endl ;

	graph = readFile(path.c_str(), N) ;

	int *flag = new int[N]() ;
	int flag_count = 0 ;
	FILE *fp = fopen("./qc.txt", "a+") ;

	vector<double> x ;
	int *Q = new int[iteration]() ;
	int startUser = 5000;
	x.push_back((double)graph[startUser].size()) ;
	Q[0] = startUser ;

	for(int i=1; i<iteration; i++)
	{
		int tmpID = sfmt_genrand_uint32(&sfmtSeed) % graph[startUser].size() ;
		int tmpUser = graph[startUser][tmpID] ;
		x.push_back((double)graph[tmpUser].size()) ;
		Q[i] = tmpUser ;
		startUser = tmpUser ;
	}

	int burnin = 30000; //burn-in period, one should reset it before run this code.

	for(int j=0; j<burnin; j++)
		if(flag[Q[j]] == 0)
		{
			flag[Q[j]] = 1 ;
			flag_count += 1 ;
		}

	int j =burnin;
	int qc = flag_count ;
	while(flag_count <= qc+650) //qc means the query cost; different query cost leads to different realtive error.
//	while(j <= burnin + 700)
	{
		int node = Q[j++] ;
		weight_tmp = 1.0 / graph[node].size();	
		weight_f += graph[node].size() * weight_tmp ;
		weight_sum += weight_tmp ;
		if(flag[node] == 0)
		{
			flag[node] = 1 ;
			flag_count += 1 ;
		}
	}
	double estimator = weight_f / weight_sum ;
	double rr = abs(estimator - 44.45033) / 44.45033; //The specific value is the average degree of the corresponding dataset.
	fprintf(fp, "%d %f\n", flag_count, rr); //write the query cost and relative error to the file "qc.txt"
	fclose(fp);
	return 0 ;
}
