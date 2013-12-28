#ifndef SMPROCESS_H_
#define SMPROCESS_H_

#include <rmatrix.hpp>
#include <imatrix.hpp>

#include "utility/MatrixPolynomial.hpp"

using namespace cxsc;

namespace ivk
{

/// Represents a semi-Markov process
class SMProcess
{
public:
	SMProcess();
	SMProcess(const rmatrix &_transition, const RMatrixPolynomial &dists);
	SMProcess(const imatrix &_transition, const IMatrixPolynomial &dists);
	virtual ~SMProcess() {};
	
	virtual void setTransitionMatrix(const rmatrix &_transition);
	virtual void setTransitionMatrix(const imatrix &_transition);
	virtual imatrix getTransitionMatrix() const;
	
	virtual ivector getDistribution(const int stateFrom, const int stateTo) const;
	
	virtual int getNumStates() const { return Ub(m_transition,1)-Lb(m_transition,1)+1;}
	virtual rvector getStationaryProbabilities() const;

protected:
	imatrix m_transition;
	SMProcess(const rmatrix &_transition);
	SMProcess(const imatrix &_transition);

private:
	IMatrixPolynomial m_dists;
};

}

#endif /*SMPROCESS_H_*/
