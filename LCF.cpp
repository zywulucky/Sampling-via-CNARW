#include "fileProcess.h"
#include <cstdio>
#include <iostream>
#include <algorithm>

double local_cluster_coefficient(vector<vector<int> > &graph, int curNode)
{
        vector<int> neighbor = graph[curNode] ;
        int size = neighbor.size();
        int count = 0 ;

        if(size == 1)
                return 0 ;

        for(int i=0; i<size; i++)
                for(int j=i+1; j<size; j++)
                {
                        int tmp = neighbor[i] ;
                        vector<int>::iterator it= find(graph[tmp].begin(), graph[tmp].end(), neighbor[j]);
                        if(it == graph[tmp].end())
                                continue;
                        count += 2 ;
                }

        return count*1.0 / (size*(size-1)) ;
}

int main(int argn, char **argv)
{
	vector<vector<int> > graph ;
	double lcf = 0 ;
	int N ;
	FILE *fp = fopen("./cluster.txt", "w") ;

	string path ;
	for(int i=0; i<argn; i++)
	{
		if(argv[i] == string("-dataset"))
			path = string(argv[i+1]) ;
	}
	if(path == "")
		cout << "argument dataset missing" << endl ;

	graph = readFile(path.c_str(), N) ;
	cout << N << endl;

	for(int i=0; i<N; i++)
	{
		lcf += local_cluster_coefficient(graph, i);
		fprintf(fp, "%d\n", (int)graph[i].size());
	}

	cout << lcf / N << endl; 

	fclose(fp) ;

	return 0 ;
}
