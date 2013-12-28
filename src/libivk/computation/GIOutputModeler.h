#ifndef GIOUTPUTMODELER_H_
#define GIOUTPUTMODELER_H_

#include "AbstractComputation.hpp"
#include <ISMPWHFactors.h>
#include <SSMPQueue.h>
#include <SSMProcess.h>
#include <utility>

using std::pair;

namespace ivk
{
/**
 * performs a Wiener-Hopf factorization for a given GI/G/1 queue
 * and returns a SSMP(4)-model of the outgoing traffic.
 */
class GIOutputModeler : public AbstractComputation<SSMPQueue, SSMProcess>
{
public:
	GIOutputModeler(const SSMPQueue* data, const ComputationParameters &params);
	virtual ~GIOutputModeler();
	
	virtual SSMProcess* compute();
	virtual void setParameters(const ComputationParameters &params);
};

}

#endif /*GIOUTPUTMODELER_H_*/
