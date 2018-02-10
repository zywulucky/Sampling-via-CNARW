#ifndef FileProcess_H
#define FileProcess_H

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std ;

vector<vector<int> > readFile(string path, int &N)
{
	FILE *fp ;
	vector<vector<int> > graph ;

	fp = fopen(path.c_str(), "r") ;
	if(fp == false)
	{
		cout << "Error : read file" << endl ;
		exit(0) ;
	}

	int a, b, count=0 ;
	int n, m ;

	int redCount = fscanf(fp, "%d%d", &n, &m) ;
	if(redCount != 2)
	    cout << "Error : read file, n, m" + path << endl ;
		
	N = n ;

	for(int i=0; i<n; i++)
		graph.push_back(vector<int>()) ;

	while(fscanf(fp, "%d%d", &a, &b) == 2)
	{
		graph[a].push_back(b) ;
		count++ ;
	}

	if(count != m)
		cout << "m not equal to the number of edges in file" + path << endl ;

	fclose(fp) ;

	return graph ;
}

double Jaccard(vector<vector<int> > &graph, int u, int v)
{
        vector<int> u_NebSet = graph[u] ;
        vector<int> v_NebSet = graph[v] ;
        vector<int> w(80000) ;
        int comNode, unionNode ;

        sort(u_NebSet.begin(), u_NebSet.end()) ;
        sort(v_NebSet.begin(), v_NebSet.end()) ;
        vector<int>:: iterator it = set_intersection(u_NebSet.begin(), u_NebSet.end(), v_NebSet.begin(), v_NebSet.end(), w.begin());
        w.resize(it - w.begin()) ;
        comNode = w.size() ;
        unionNode = u_NebSet.size() + v_NebSet.size() - comNode ;

        return (comNode * 1.0) / unionNode ;
}

#endif
