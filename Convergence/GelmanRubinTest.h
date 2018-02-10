#ifndef GelmanRubinTest_H
#define GelmanRubinTest_H

#include <vector>
#include "ConvergenceDiagnostic.h"

class GelmanRubinTest : public ConvergenceDiagnostic
{
	public:
		GelmanRubinTest(std::size_t n=10) ;
		double assessConvergenceMultipleChains(const std::vector<std::vector<double> > &values, const std::size_t burnin) ;

	private:
		std::size_t nBatches ;
};

#endif

