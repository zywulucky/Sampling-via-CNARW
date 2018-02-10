#ifndef GewekeTest_H
#define GewekeTest_H

#include <vector>
#include "ConvergenceDiagnostic.h"

class GewekeTest : public ConvergenceDiagnostic
{
	public:
		GewekeTest(double f1=0.1, double f2=0.5);
		double assessConvergenceSingleChain(const std::vector<double>& values, std::size_t burnin);
		void assessConvergenceSingleChain1(const std::vector<double>& values, std::size_t nbins);
		void setFraction1(double f1) { frac1 = f1; }
		void setFraction2(double f2) { frac2 = f2; }

	private:
		double frac1, frac2;
};

#endif
