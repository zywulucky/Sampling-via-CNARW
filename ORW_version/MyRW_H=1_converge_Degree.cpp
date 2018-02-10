#include "fileProcess.h"
#include "ComputeBurnin_tmp.h"
#include "sfmt/SFMT.h"
#include "memoryusage.h"
#include <string.h>
#include <vector>
#include <time.h>
#include <map>
#include <algorithm>
#include <math.h>

sfmt_t sfmtSeed ;

double min(double a, double b)
{
	return a<b?a:b ;
}

int commSize(vector<vector<int> > &graph, int curNode, int nextNode)
{
	vector<int> curNode_tmp = graph[curNode] ;
	vector<int> nextNode_tmp = graph[nextNode] ;
	vector<int> w(80000) ;

	sort(curNode_tmp.begin(), curNode_tmp.end()) ;
	sort(nextNode_tmp.begin(), nextNode_tmp.end()) ;
	vector<int>:: iterator it = set_intersection(curNode_tmp.begin(), curNode_tmp.end(), nextNode_tmp.begin(), nextNode_tmp.end(), w.begin()) ;
	w.resize(it-w.begin()) ;
	
	return w.size() ;
} 

int nextStep(vector<vector<int> > &graph, int curNode)
{
	int nextNode, id, comNode ;
	double prb, p ;
	do
	{
		if(graph[curNode].size() == 1)
		{
			nextNode =graph[curNode][0] ;
			break ;
		}
		else
		{
			id = sfmt_genrand_uint32(&sfmtSeed) % graph[curNode].size() ;
			nextNode = graph[curNode][id] ;

			comNode = commSize(graph, curNode, nextNode) ;
			prb = 1.0 - comNode / min(graph[curNode].size()*1.0, graph[nextNode].size()) ;
			p = sfmt_genrand_real1(&sfmtSeed) ;
		}
	}while(p > prb) ;

	return nextNode ;
}

int main(int argn, char **argv)
{
	vector<double> x ;
	vector<vector<int> > graph ;
	int N ;
	int count=1, tmpNextNode, startNode ;
	
	int interation =200000;
	
	string path, ID ;
	for(int i=0; i<argn; i++)
	{
		if(argv[i] == string("-dataset"))
			path = string(argv[i+1]) ;
		if(argv[i] == string("-ID"))
			ID = string(argv[i+1]) ;
	}
	if(path == "")
		cout << "argument dataset missing" << endl ;

	sfmt_init_gen_rand(&sfmtSeed, 1234567*(unsigned)time(NULL)) ;

	graph = readFile(path.c_str(), N) ;

	startNode = 5000;
	x.push_back((double)graph[startNode].size()) ;

	while(count++ < interation)
	{
		tmpNextNode = nextStep(graph, startNode) ;	
		x.push_back((double)graph[tmpNextNode].size()) ;
		startNode = tmpNextNode ;
	}

	int burnin = computeBurnin(x, ID) ;
	cout << "burnin: " << burnin << endl ;
	return 0 ;
}
