#include "GelmanRubinTest.h"
#include "DistributionNormal.h"

#include <cmath>
#include <iostream>
using namespace std ;

GelmanRubinTest::GelmanRubinTest(size_t n) : ConvergenceDiagnostic()
{
	this->nBatches = n ;
}

double GelmanRubinTest::assessConvergenceMultipleChains(const vector<vector<double> >& values, const size_t burnin)
{
	double withinBatchVariance = 0.0 ;
	double betweenBatchVariance = 0.0 ;
	size_t totalSampleSize = 0 ;
	double totalMean = 0.0 ;

	//get number of chains
	size_t nChains = values.size() ;
	
	//get a mean and standard error for each block
	vector<double> chainMeans = vector<double>(nChains, 0.0) ;
	for(size_t i=0; i<nChains; i++)
	{
		const vector<double>& chain = values.at(i) ;
		analysis.analyseMean(chain, burnin) ;
		chainMeans[i] = analysis.getMean() ;
		totalMean += chainMeans[i] ;
	}

	totalMean /= nChains ;
	size_t chainSize ;

	//iterate over all chains
	for(size_t i=0; i<nChains; i++)
	{
		const vector<double>& chain = values.at(i) ;
		chainSize = chain.size() - burnin ;
		totalSampleSize += chainSize ;

		//iterate over all samples from the chains
		for(size_t j=burnin; j<chainSize; j++)
			withinBatchVariance += (chain[j]-chainMeans[i]) * (chain[j]-chainMeans[i]) ;
	
		betweenBatchVariance += (chainMeans[i]-totalMean) * (chainMeans[i]-totalMean) ;
	}

	double psrf = (chainSize - 1.0) / chainSize + (chainSize-1.0) * (nChains+1) / (nChains-1) * (betweenBatchVariance/withinBatchVariance) ;

	return psrf ;
}
