#ifndef SMPTRANSIENT_H_
#define SMPTRANSIENT_H_

#include "AbstractComputation.hpp"
#include "../data/SSMProcess.h"
#include "../data/WorkloadVector.hpp"

using cxsc::real;

namespace ivk{

class SMPTransient: public AbstractComputation<SSMProcess, IWorkloadVector>{
public:
	static const char* PARAM_ITERATIONS;
	static const char* PARAM_THRESHOLD;
	
	SMPTransient( const SSMProcess* data, const ComputationParameters& parameters);
	
	int getIterations();
	void setIterations(int value);
	
	real getThreshold();
	void setThreshold(real value);
	
	void setParameters(const ComputationParameters& params);
	
	IWorkloadVector* compute();
	
private:
	int iterations;
	real threshold;
};

}

#endif /*SMPTRANSIENT_H_*/
