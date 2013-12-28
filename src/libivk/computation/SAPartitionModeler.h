#ifndef SAPARTITIONMODELER_H_
#define SAPARTITIONMODELER_H_

#include "PartitionModeler.h"
#include <intvector.hpp>
#include "data/SSMProcess.h"

namespace ivk
{

class SAPartitionModeler : public PartitionModeler
{
public:
	static const char* PARAM_AUTOCORRELATION;
	static const char* PARAM_INITTEMP;
	static const char* PARAM_ABORTTEMP;
	static const char* PARAM_ALPHA;
	SAPartitionModeler(const Trace *data, const ComputationParameters &parameters);
	virtual ~SAPartitionModeler();
	
	virtual SSMProcess* compute();

	void setParameters(ComputationParameters parameters);
	ComputationParameters getParameters();
	
	void setInitTemp(real value);
	void setAbortTemp(real value);
	void setAlpha(real value);
	void setAutoc(int value);

	real getInitTemp();
	real getAbortTemp();
	real getAlpha();
	int getAutoc();
	
	intvector getInitialSolution(const rvector &R) const;
	static intvector findNeighbor(const intvector &lengths);
	static real squareError(const rvector &a, const rvector &b);
	SSMProcess constructSSMProcess(const rvector &R, const intvector &lengths) const;
private:
	real initTemp;
	real abortTemp;
	real alpha;
	int autoc;
};

}

#endif /*SAPARTITIONMODELER_H_*/
