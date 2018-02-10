#include "GewekeTest.h"
#include "DistributionNormal.h"

#include <cmath>
#include <cstdio>
#include <iostream>

using namespace std;

GewekeTest::GewekeTest(double f1, double f2) : ConvergenceDiagnostic()
{
	frac1 = f1 ;
	frac2 = f2 ;
}

double GewekeTest::assessConvergenceSingleChain(const std::vector<double>& values, size_t burnin)
{
	size_t valueCount = values.size() ;

	size_t sampleSize = valueCount - burnin ;

	size_t startwindow1 = burnin ;
	size_t endwindow1 = size_t(sampleSize * frac1) + burnin ;

	size_t startwindow2 = valueCount - size_t(sampleSize * frac2) ;
	size_t endwindow2 = valueCount ;

	//get mean and variance of the first window
	analysis.analyseMean(values, startwindow1, endwindow1) ;
	double meanWindow1 = analysis.getMean() ;
	analysis.analyseCorrelation(values, startwindow1, endwindow1) ;
	double varWindow1 = analysis.getStdErrorOfMean() * analysis.getStdErrorOfMean() ;

	//get mean and variance of the second window
	analysis.analyseMean(values, startwindow2, endwindow2) ;
	double meanWindow2 = analysis.getMean() ;
	analysis.analyseCorrelation(values, startwindow2, endwindow2) ;
	double varWindow2 = analysis.getStdErrorOfMean() * analysis.getStdErrorOfMean() ;

	double z = (meanWindow1 - meanWindow2) / sqrt(varWindow1 + varWindow2) ;

	return z ;

}

void GewekeTest::assessConvergenceSingleChain1(const std::vector<double>& values, size_t nbins)
{
	FILE *fp = fopen("./zp.txt","w") ;

	size_t valueCount = values.size() ;	
	size_t halfCount = size_t(valueCount * (1.0 - frac2)) ;
	size_t interval = halfCount / nbins ;

	size_t startWindow2 = halfCount ;
	size_t endWindow2 = valueCount ;
	
	analysis.analyseMean(values, startWindow2, endWindow2) ;
	double meanWindow2 = analysis.getMean() ;
	analysis.analyseCorrelation(values, startWindow2, endWindow2) ;
	double varWindow2 = analysis.getStdErrorOfMean()*analysis.getStdErrorOfMean() ;

	size_t startWindow1 = 0 ;
	size_t endWindow1 = interval ;

	while(endWindow1 <= halfCount ) 
	{
		analysis.analyseMean(values, startWindow1, endWindow1) ;
		double meanWindow1 = analysis.getMean() ;
		analysis.analyseCorrelation(values, startWindow1, endWindow1) ;
		double varWindow1 = analysis.getStdErrorOfMean()*analysis.getStdErrorOfMean() ;

		double z = (meanWindow1 - meanWindow2) / sqrt(varWindow1 + varWindow2) ;
		
		fprintf(fp,"%d %f\r\n", int(startWindow1), z) ;

		startWindow1 += interval ;
		endWindow1 += interval ;
	}
}
