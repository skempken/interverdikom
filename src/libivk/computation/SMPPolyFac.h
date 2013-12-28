#ifndef SMPPOLYFAC_H_
#define SMPPOLYFAC_H_

#include "computation/AbstractComputation.hpp"

#include "data/SSMProcess.h"
#include <civector.hpp>
#include <cimatrix.hpp>

#include "data/ISMPPFResult.h"


using namespace cxsc;


namespace ivk {

class SMPPolyFac : public AbstractComputation<SSMProcess, ISMPPFResult>
{
public:
	SMPPolyFac(const SSMProcess * ptrData, const ComputationParameters &parameters);

	virtual ~SMPPolyFac();

	virtual ISMPPFResult * compute();

	virtual void setParameters(const ivk::ComputationParameters& np) {p = np;}

	static const char * PARAM_ROOTS;

	static const char * PARAM_DETERMINANT;

	ivk::ComputationParameters p;
};

}

#endif /*SMPPOLYFAC_H_*/
