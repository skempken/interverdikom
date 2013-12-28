#ifndef SMPGRASSMANNJAIN2_H_
#define SMPGRASSMANNJAIN2_H_

#include "SMPWienerHopf.h"

namespace ivk
{

class SMPGrassmannJain2 : public ivk::SMPWienerHopf
{
public:
	SMPGrassmannJain2(const SSMProcess* data, const ComputationParameters &parameters);
	virtual ~SMPGrassmannJain2();
	
protected:
	virtual void grassmannJainIteration();
	virtual void grassmannJainStep(RMatrixPolynomial &v, RMatrixPolynomial &l, RMatrixPolynomial u);
};

}

#endif /*SMPGRASSMANNJAIN2_H_*/
