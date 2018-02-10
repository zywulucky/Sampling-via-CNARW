#include "RbConstants.h"
#include "TraceAnalysis.h"
#include<cmath>
#include<math.h>
#include <iostream>

using namespace std;

TraceAnalysis::TraceAnalysis()
{
	mean = RbConstants::Double::max ;
	sem = RbConstants::Double::max ;
}

void TraceAnalysis::analyseMean(const std::vector<double>& v, size_t begin, size_t end)
{
	double m =0 ;
	for (size_t i=begin; i<end; i++)
		m += v.at(i);

	this->mean = m/double(end-begin) ;
}

void TraceAnalysis::analyseMean(const std::vector<double> &values, size_t b)
{
	double m = 0 ;
	size_t size = values.size() ;
	for(size_t i=b; i<size; i++)
		m += values.at(i) ;
	mean = m/double(size-b) ;
}

void TraceAnalysis::analyseCorrelation(const std::vector<double>& v, size_t begin, size_t end)
{
	//if we have not yet calculated the mean, do this now
	if(mean == RbConstants::Double::max)
		analyseMean(v, begin, end);

	size_t samples = end -begin ;
//	size_t maxLag = (samples - 1 < MAX_LAG ? samples - 1 : MAX_LAG);
	size_t maxLag = 1 ;

	double *gammaStat = new double[maxLag];
	for(size_t i=0; i<maxLag; i++)
		gammaStat[i] = 0;

	double varStat = 0.0;

	for(size_t lag=0; lag<maxLag; lag++)
	{
		for(size_t j=0; j<samples - lag; j++)
		{
			double del1 = v.at(begin+j) - mean ;
			double del2 = v.at(begin+j+lag) - mean ;
			gammaStat[lag] += (del1 * del2) ;
		}

		gammaStat[lag] /= ((double)(samples-lag-1 )) ;

		if(lag == 0)
			varStat = gammaStat[0] ;
		else if(lag % 2 == 0)
		{
			if((gammaStat[lag - 1] + gammaStat[lag]) > 0)
				varStat += 2 * (gammaStat[lag - 1] + gammaStat[lag]) ;
			else
				maxLag = lag ;
		}
	}
	
	this->sem = sqrt(varStat) ;

	delete[] gammaStat ;
}
