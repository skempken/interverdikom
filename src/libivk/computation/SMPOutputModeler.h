#ifndef SMPOUTPUTMODELER_H_
#define SMPOUTPUTMODELER_H_

#include "AbstractComputation.hpp"
#include <ISMPWHFactors.h>
#include <SSMPQueue.h>
#include <SSMProcess.h>
#include <utility>

using std::pair;

namespace ivk
{
/**
 * performs a Wiener-Hopf factorization for a given SMP(M)/G/1 queue
 * and returns a SSMP(2M)-model of the outgoing traffic.
 */
class SMPOutputModeler : public AbstractComputation<SSMPQueue, SSMProcess>
{
public:
	SMPOutputModeler(const SSMPQueue* data, const ComputationParameters &params);
	virtual ~SMPOutputModeler();
	
	virtual SSMProcess* compute();
	virtual void setParameters(const ComputationParameters &params);
};

}

#endif /*SMPOUTPUTMODELER_H_*/
