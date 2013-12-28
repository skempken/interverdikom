#ifndef ONESTATEMODELER_H_
#define ONESTATEMODELER_H_

#include "AbstractDiscreteSSMPModeler.h"

namespace ivk
{

class RenewalModeler : public AbstractDiscreteSSMPModeler
{
public:
	RenewalModeler(const Trace * ptrData, const ComputationParameters &parameters);
	virtual ~RenewalModeler();
	
	virtual SSMProcess* compute();
};

}

#endif /*ONESTATEMODELER_H_*/
