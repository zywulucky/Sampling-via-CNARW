#ifndef ComputeBurnin_H
#define ComputeBurnin_H

#include "Convergence/GewekeTest.h"
#include "Convergence/GelmanRubinTest.h"
#include <cstdio>
#include <vector>
#include <string>

using namespace std ;

int computeBurnin(vector<double>& value, string ID)
{
	GewekeTest *test = new GewekeTest() ;
	int count, tmp ;
	vector<int> logspace ;
	vector<double> tmpValue ;

	string path = "./Experiment/" RW "/" P "/zp" + ID + ".txt" ;
	printf("%s\n", path.c_str()) ;

	FILE *fp = fopen(path.c_str(), "w") ;
	FILE *fp1 = fopen("./logspac.txt", "r") ;

	while(fscanf(fp1,"%d", &tmp) == 1)
		logspace.push_back(tmp) ;

	for(int i=0; i< logspace[0]; i++)
		tmpValue.push_back(value[i]) ;

	for(count=1 ; count < (int)logspace.size(); count++)
	{
		double z = test->assessConvergenceSingleChain(tmpValue, 0);
		fprintf(fp, "%d %f\r\n", logspace[count-1] , z) ;
		for(int j = logspace[count-1]; j < logspace[count]; j++)
			tmpValue.push_back(value[j]) ;
	}

	double z = test->assessConvergenceSingleChain(tmpValue, 0);
	fprintf(fp, "%d %f\r\n", logspace[count-1] , z) ;

	fclose(fp) ;
	fclose(fp1) ;

	return 500;
}
