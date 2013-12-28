#ifndef SMPGRASSMANNJAIN1_H_
#define SMPGRASSMANNJAIN1_H_

#include "SMPWienerHopf.h"

namespace ivk
{

class SMPGrassmannJain1 : public ivk::SMPWienerHopf
{
public:
	SMPGrassmannJain1(const SSMProcess* data, const ComputationParameters &parameters);
	virtual ~SMPGrassmannJain1();
	
protected:
	virtual void grassmannJainIteration();
	virtual void grassmannJainStep(RMatrixPolynomial &v, RMatrixPolynomial &l, RMatrixPolynomial u);
};

}

#endif /*SMPGRASSMANNJAIN1_H_*/
