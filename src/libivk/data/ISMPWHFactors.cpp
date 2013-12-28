#include "ISMPWHFactors.h"

namespace ivk
{

ISMPWHFactors::ISMPWHFactors(const IMatrixPolynomial &_idle, const IMatrixPolynomial &_phase)
{
	setIdleDistributions(_idle);
	setPhaseDistributions(_phase);
}

ISMPWHFactors::~ISMPWHFactors()
{
}

void ISMPWHFactors::setIdleDistributions(const IMatrixPolynomial &_idle)
{
	this->m_idle = _idle;
}

void ISMPWHFactors::setPhaseDistributions(const IMatrixPolynomial &_phase)
{
	this->m_phase = _phase;
}

}
