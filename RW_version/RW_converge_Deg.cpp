#include "sfmt/SFMT.h"
#include "fileProcess.h"
#include "ComputeBurnin_tmp.h"
#include "memoryusage.h"
#include <cmath>
#include <time.h>

int main(int argn, char **argv)
{
	vector<double> x ;
	vector<double> lcf ;
	vector<vector<int> > graph ;
	sfmt_t sfmtSeed ;
	int N ;	//the nodes of graph 

	sfmt_init_gen_rand(&sfmtSeed, (unsigned)time(NULL)*1234567) ;

	int iteration = 200000;

	string path, ID ;
	for(int i=0; i<argn; i++)
	{
		if(argv[i] == string("-dataset")) path = string(argv[i+1]) ;
		if(argv[i] == string("-ID")) ID = string(argv[i+1]) ;
	}
	if(path == "")
		cout<< "argument dataset missing" <<endl ;

	graph = readFile(path.c_str(), N) ;

	int startUser = 5000;

	x.push_back((double)graph[startUser].size()) ;

	for(int i=1; i<iteration; i++)
	{
		int tmpID = sfmt_genrand_uint32(&sfmtSeed) % graph[startUser].size() ;
		int tmpUser = graph[startUser][tmpID] ;

		x.push_back((double)graph[tmpUser].size()) ;
		startUser = tmpUser ;
	}

	int burnin = computeBurnin(x, ID) ;
	cout << "burnin: " << burnin << endl ;
	return 0 ;
}
