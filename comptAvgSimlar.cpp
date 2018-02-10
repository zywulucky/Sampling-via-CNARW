#include "fileProcess.h"

int main(int argn, char **argv)
{
	vector<vector<int> > graph ;
	int N , M = 0;

	string path;
	for(int i=0; i<argn; i++)
		if(argv[i] == string("-dataset")) 
			path = string(argv[i+1]) ;
	if(path == "")
		cout << "argument dataset missing" << endl; 

	graph = readFile(path.c_str(), N) ;
	double jaccard = 0.0 ;

	for(int i=0; i<N; i++)
		for(int j=0; j<graph[i].size(); j++)
		{
			jaccard += Jaccard(graph, i, graph[i][j]) ;
			M += 1 ;
		}

	jaccard = jaccard / M ;

	cout << "Jaccard: " << jaccard << endl; 
	return 0 ;
}
