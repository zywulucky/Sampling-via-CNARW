#ifndef TraceAnalysis_H
#define TraceAnalysis_H

#include<vector>

#define MAX_LAG 100 

class TraceAnalysis
{
	public:
		TraceAnalysis();
		void analyseMean(const std::vector<double>& v, std::size_t begin, std::size_t end);
		void analyseMean(const std::vector<double>& v, std::size_t b);
		void analyseCorrelation(const std::vector<double>& v, std::size_t begin, std::size_t end);
		double getStdErrorOfMean() {return this->sem; } 
		double getMean(){return this->mean;}
	private:
		double mean;
		double sem;		//standard error of mean
};

#endif
