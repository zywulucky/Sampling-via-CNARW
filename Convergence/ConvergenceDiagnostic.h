#ifndef ConvergenceDiagnostic_H
#define ConvergenceDiagnostic_H

#include "TraceAnalysis.h"
#include <vector>

class ConvergenceDiagnostic
{
	public:
		ConvergenceDiagnostic();
		virtual ~ConvergenceDiagnostic(void) {}
		virtual double assessConvergenceSingleChain(const std::vector<double>& values, std::size_t burnin) { return 0.0; }
	protected:
		TraceAnalysis analysis ;
};

#endif
