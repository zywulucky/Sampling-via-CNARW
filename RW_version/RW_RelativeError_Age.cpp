#include "sfmt/SFMT.h"
#include "fileProcess.h"
#include "ComputeBurnin_tmp.h"
#include "memoryusage.h"
#include <cmath>

int F(int age)
{
	if(age >= 10 && age <= 25)
		return 1 ;
	else 
		return 0 ;
}

int main(int argn, char **argv)
{
	vector<vector<int> > graph ;
	sfmt_t sfmtSeed ;
	int N ;	//the nodes of graph 

	sfmt_init_gen_rand(&sfmtSeed, (unsigned)time(NULL)*1234567) ;

	int iteration = 25000;

	string path, ID ;
	for(int i=0; i<argn; i++)
	{
		if(argv[i] == string("-dataset")) path = string(argv[i+1]) ;
		if(argv[i] == string("-ID")) ID = string(argv[i+1]) ;
	}
	if(path == "")
		cout<< "argument dataset missing" <<endl ;

	graph = readFile(path.c_str(), N) ;

	vector<int> age ;
	int ttmp;
	FILE *fp1 = fopen("./Flickr_Age.txt","r");
	while(fscanf(fp1,"%d", &ttmp) == 1)
		age.push_back(ttmp);
	fclose(fp1);

	vector<int> Product ;
	FILE *fp2 = fopen("./Product_A.txt", "r");
	while(fscanf(fp2,"%d",&ttmp) == 1)
		Product.push_back(ttmp) ;
	fclose(fp2) ;

	vector<int> samples ;
	double weight_tmp, weight_f=0.0, weight_f1 = 0.0 ;
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

	int burnin = 6207;
	for(int j=0; j<burnin; j++)
		if(flag[Q[j]] == 0)
		{
			flag[Q[j]] = 1 ;
			flag_count += 1 ;
		}

	int j =burnin;
	int qc = flag_count ;
	while(flag_count <= qc+250)
	{
		int node = Q[j++] ;
		weight_tmp = 1.0 / graph[node].size();	
		weight_f += F(age[node]) * Product[node] * weight_tmp ;
		weight_f1 += Product[node] * weight_tmp ;
		if(flag[node] == 0)
		{
			flag[node] = 1 ;
			flag_count += 1 ;
		}
	}
	double estimator = weight_f / weight_f1 ;
	double rr = abs(estimator - 0.410178) / 0.410178 ;
	fprintf(fp, "%d %f\n", flag_count, rr);
	fclose(fp);
	return 0 ;
}
