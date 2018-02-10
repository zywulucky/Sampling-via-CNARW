#include "fileProcess.h"
#include "ComputeBurnin_tmp.h"
#include "sfmt/SFMT.h"
#include "memoryusage.h"
#include <string.h>
#include <vector>
#include <queue>
#include <time.h>
#include <map>
#include <algorithm>
#include <math.h>

sfmt_t sfmtSeed ;

double min(double a, double b)
{
	return a<b?a:b ;
}

vector<int> getUnion(vector<vector<int> > &graph, queue<int> myQueue)
{
	vector<int> v ;
	vector<int> tmp ;
	int size = myQueue.size() ;

	for(int i=0; i<size; i++)
	{
		vector<int> w(80000) ;
		int curNode = myQueue.front() ;
		myQueue.pop() ;
		tmp = graph[curNode] ;

		sort(v.begin(), v.end()) ;	
		sort(tmp.begin(), tmp.end()) ;
		vector<int>::iterator it = set_union(v.begin(), v.end(), tmp.begin(), tmp.end(), w.begin()) ;
		w.resize(it-w.begin()) ;
		v.clear() ;
		for(int j=0; j<w.size(); j++)
			v.push_back(w.at(j));
		myQueue.push(curNode);
	}
	return v ;
}

int commSize(vector<vector<int> > &graph, vector<int> v, int nextNode)
{
	vector<int> curNode_tmp = v ;
	vector<int> nextNode_tmp = graph[nextNode] ;
	vector<int> w(80000) ;
	int comNode ;

	sort(curNode_tmp.begin(), curNode_tmp.end()) ;
	sort(nextNode_tmp.begin(), nextNode_tmp.end()) ;
	vector<int>:: iterator it = set_intersection(curNode_tmp.begin(), curNode_tmp.end(), nextNode_tmp.begin(), nextNode_tmp.end(), w.begin()) ;
	w.resize(it-w.begin()) ;
	
	if(H_INT == 1)
		comNode = w.size() ;
	else
		comNode = w.size()-1 ;

	return comNode ; 
} 

int nextStep(vector<vector<int> > &graph, queue<int> myQueue)
{
	int nextNode, id ;
	double prb, p ;

	int curNode = myQueue.back() ;
	vector<int> v = getUnion(graph, myQueue) ;
	
	do
	{
		if(graph[curNode].size() == 1)
		{
			id = sfmt_genrand_uint32(&sfmtSeed) % v.size() ;
			nextNode =v[id] ;

			break ;
		}
		else
		{
			id = sfmt_genrand_uint32(&sfmtSeed) % graph[curNode].size() ;
			nextNode = graph[curNode][id] ;

			int comNode = commSize(graph, v, nextNode) ;
			prb = 1.0 - comNode / min(v.size()*1.0, graph[nextNode].size()) ;
			p = sfmt_genrand_real1(&sfmtSeed) ;
		}
	}while(p > prb);

	return nextNode ;
}

int main(int argn, char **argv)
{
	vector<double> x ;
	vector<vector<int> > graph ;
	int N ;
	int count=1, tmpNextNode, startNode,multcount = 0 ;
	queue<int> myQueue ;
	
	int interation = 200000;
	
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

	int *flag = new int[N]() ;
	int flag_count = 0 ;

	startNode = 5000;
	x.push_back((double)graph[startNode].size()) ;
	myQueue.push(startNode) ;

	while(count < H_INT)
	{
		int tmpID = sfmt_genrand_uint32(&sfmtSeed) % graph[startNode].size() ;
		int tmpCurNode = graph[startNode][tmpID] ;
		x.push_back((double)graph[tmpCurNode].size()) ;
		myQueue.push(tmpCurNode) ;
		startNode = tmpCurNode ;
		count++ ;
	}
	
	while(count++ < interation)
	{
		tmpNextNode = nextStep(graph, myQueue) ;	
		myQueue.pop() ;
		myQueue.push(tmpNextNode) ;
		x.push_back((double)graph[tmpNextNode].size()) ;
	}

	int burnin = computeBurnin(x, ID) ;
	cout << "burnin: " << burnin << endl ;
	return 0 ;
}
