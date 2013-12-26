#ifndef VERIFYEIGPOLYFAC_H_
#define VERIFYEIGPOLYFAC_H_

#include "computation/AbstractComputation.hpp"
#include "utility/AbstractProgressListener.h"

#include "data/SSMProcess.h"
#include <civector.hpp>
#include <cimatrix.hpp>

#include "data/ISMPPFResult.h"


using namespace cxsc;


namespace ivk {

class SMPVerifyEig : public AbstractComputation<SSMProcess, ISMPPFResult>, public AbstractProgressListener
{
public:
	SMPVerifyEig(const SSMProcess * ptrData, const ComputationParameters &parameters);

	virtual ~SMPVerifyEig();

	virtual ISMPPFResult * compute();

	virtual void setParameters(const ivk::ComputationParameters&) {}

	virtual void updateProgressText(const std::string &text);

	virtual void updateProgressMax(const int &max);

	virtual void updateProgressValue(const int &value);

	virtual void updateProgressETA(const int &eta);
};

}

#endif /*VERIFYEIGPOLYFAC_H_*/
