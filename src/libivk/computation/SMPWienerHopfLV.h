#ifndef SMPWIENERHOPFLV_H_
#define SMPWIENERHOPFLV_H_

#include "SMPWienerHopf.h"

#include "utility/Polynomial.hpp"

#include <l_real.hpp>
#include <l_imatrix.hpp>

using namespace cxsc;

namespace ivk
{

/**
 * Implements Wiener-Hopf factorization with verification step in
 * multiple precision arithmetic.
 */
class SMPWienerHopfLV : public ivk::SMPWienerHopf
{
public:
	SMPWienerHopfLV(const SSMProcess* data, const ComputationParameters &parameters);
	virtual ~SMPWienerHopfLV();
	
	virtual ISMPWHFactors* compute();
	
protected:
	virtual void verification(const l_real &currentDelta);
	virtual l_real grassmannJainStep(Polynomial<l_imatrix> &v, Polynomial<l_imatrix> &l, Polynomial<l_imatrix> u);

};

}

#endif /*SMPWIENERHOPFLV_H_*/
