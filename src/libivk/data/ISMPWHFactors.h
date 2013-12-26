#ifndef ISMPWHFACTORS_H_
#define ISMPWHFACTORS_H_

#include <imatrix.hpp>
#include "utility/MatrixPolynomial.hpp"

using namespace cxsc;

namespace ivk
{

class ISMPWHFactors
{
public:
	ISMPWHFactors(const IMatrixPolynomial &_idle, const IMatrixPolynomial &_phase);
	virtual ~ISMPWHFactors();
	
	void setPhaseDistributions(const IMatrixPolynomial &_phase);
	IMatrixPolynomial getPhaseDistributions() const { return this->m_phase; }
	
	void setIdleDistributions(const IMatrixPolynomial &_idle);
	IMatrixPolynomial getIdleDistributions() const { return this->m_idle; }
	
private:
	IMatrixPolynomial m_idle;
	IMatrixPolynomial m_phase;
};

}

#endif /*ISMPWHFACTORS_H_*/
