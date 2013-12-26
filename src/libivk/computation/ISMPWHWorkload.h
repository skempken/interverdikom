#ifndef ISMPWHWORKLOAD_H_
#define ISMPWHWORKLOAD_H_

#include "AbstractComputation.hpp"
#include "data/ISMPWHFactors.h"
#include "data/WorkloadVector.hpp"

#include <ivector.hpp>
#include <rvector.hpp>

using namespace cxsc;

namespace ivk
{

/// Computes workload vectors from given Wiener-Hopf factors of an SMP queue model.
class ISMPWHWorkload : public AbstractComputation<ISMPWHFactors, IWorkloadVector>
{
public:
	// Parameter keys.
	static const char* PARAM_UPTO;
	
	
	ISMPWHWorkload(const ISMPWHFactors *data, const ComputationParameters &parameters);
	virtual ~ISMPWHWorkload();
	
	void setUpTo(const int upTo);
	int getUpTo();
	
	// Computation interface
	virtual IWorkloadVector* compute();
	virtual void setParameters(const ComputationParameters &parameters);

	static ivector computeLI( IMatrixPolynomial ll);
	
private:
	int m_upTo;
};

}

#endif /*ISMPWHWORKLOAD_H_*/
