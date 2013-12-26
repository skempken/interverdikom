#ifndef SMPGRASSMANNJAIN3_H_
#define SMPGRASSMANNJAIN3_H_

#include "SMPGrassmannJain2.h"

namespace ivk
{

class SMPGrassmannJain3 : public ivk::SMPGrassmannJain2
{
public:
	SMPGrassmannJain3(const SSMProcess* data, const ComputationParameters &parameters);
	virtual ~SMPGrassmannJain3();
	
protected:
	virtual void grassmannJainIteration();
	virtual void grassmannJainStep(RMatrixPolynomial &v, RMatrixPolynomial &l, RMatrixPolynomial u);
};

}

#endif /*SMPGRASSMANNJAIN3_H_*/
