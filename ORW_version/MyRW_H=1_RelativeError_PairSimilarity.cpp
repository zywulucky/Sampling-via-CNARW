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

int commSize(vector<vector<int> > &graph, int curNode, int nextNode)
{
	vector<int> curNode_tmp = graph[curNode] ;
	vector<int> nextNode_tmp = graph[nextNode] ;
	vector<int> w(80000) ;
	int comNode ;

	sort(curNode_tmp.begin(), curNode_tmp.end()) ;
	sort(nextNode_tmp.begin(), nextNode_tmp.end()) ;
	vector<int>:: iterator it = set_intersection(curNode_tmp.begin(), curNode_tmp.end(), nextNode_tmp.begin(), nextNode_tmp.end(), w.begin()) ;
	w.resize(it-w.begin()) ;
	
	comNode = w.size() ;
	return comNode ; 
} 

int nextStep(vector<vector<int> > &graph, int curNode, int &multcount, vector<int> &M)
{
	int nextNode, id ;
	double prb, p ;

	multcount = 0 ;
	do
	{
		if(graph[curNode].size() == 1)
		{
			nextNode =graph[curNode][0] ;
			M.push_back(nextNode) ;
			multcount += 1 ;
			break ;
		}
		else
		{
			id = sfmt_genrand_uint32(&sfmtSeed) % graph[curNode].size() ;
			nextNode = graph[curNode][id] ;

			M.push_back(nextNode) ;

			int comNode = commSize(graph, curNode, nextNode) ;
			prb = 1.0 - comNode*1.0 / min(graph[curNode].size(), graph[nextNode].size()) ;
			p = sfmt_genrand_real1(&sfmtSeed) ;
			multcount += 1 ;
		}
	}while(p > prb);

	return nextNode ;
}

int main(int argn, char **argv)
{
	vector<vector<int> > graph ;
	int N ;
	int tmpNextNode,startNode,multcount = 0 ;
	double weight_tmp, weight_f = 0.0, weight_sum = 0.0 ;
	
	int interation = 35000;
	
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

	FILE *fp = fopen("./qc3.txt", "a+");

	vector<double> x ;
	vector<int> M ;
	long *indexCount = new long[interation]();
	int *Mulcount = new int[interation]() ;

	startNode = 5000;
	x.push_back((double)graph[startNode].size()) ;
	M.push_back(startNode) ;
	indexCount[0] = 0 ;
	Mulcount[0] = 0 ;

	for(int count=1; count<interation; count++)
	{
		tmpNextNode = nextStep(graph, startNode, multcount, M) ;	
		x.push_back((double)graph[tmpNextNode].size()) ;
		Mulcount[count] = multcount ;
		indexCount[count] = indexCount[count-1] + multcount ;	
		startNode = tmpNextNode ;
	}
	int burnin = 5094;
	for(int j=0; j<indexCount[burnin]; j++)
		if(flag[M[j]] == 0)
		{
			flag[M[j]] = 1;
			flag_count += 1 ;
		}

	int k = burnin + 1;
	int qc = flag_count ;
	while(flag_count <= qc + 6500)
	{
		int lastNode = M[indexCount[k-1]];
		int Node = M[indexCount[k]];

		weight_tmp = 1.0 / (1.0 - commSize(graph, lastNode, Node) * 1.0 / min(graph[lastNode].size(), graph[Node].size())) ;
		weight_f += Jaccard(graph, lastNode, Node) * weight_tmp ;
		weight_sum += weight_tmp ;
		for(int w=0; w<Mulcount[k]; w++)
		{
			int index = indexCount[k-1] + w;
			if(flag[M[index]] == 0)
			{
				flag[M[index]] = 1 ;	
				flag_count += 1 ;
			}
		}
		k = k + 1 ;
	}
	double estimator = weight_f / weight_sum ;
	double relatedError = fabs(estimator - 0.0503892) / 0.0503892;
	fprintf(fp, "%d %f\n", flag_count, relatedError) ;
	fclose(fp) ;
	delete [] Mulcount ;
	delete [] indexCount ;
	x.clear();
	M.clear();
	return 0 ;
}
