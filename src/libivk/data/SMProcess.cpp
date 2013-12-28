#include "SMProcess.h"

#include <solvers/ILinSys.hpp>
#include <stdexcept>
#include <IMatrixUtils.h>

#include <Logging.hpp>

namespace ivk
{
SMProcess::SMProcess(){
	setTransitionMatrix(rmatrix(1,1,1,1));
}

SMProcess::SMProcess(const rmatrix &_transition, const RMatrixPolynomial &dists)
{
	setTransitionMatrix(_transition);
	// convert distributions to point intervals
	IMatrixPolynomial iDists(dists.lowerBound(), dists.upperBound(), Lb(_transition, 1), Ub(_transition,1), Lb(_transition, 2), Ub(_transition,2));
	for(int i = dists.lowerBound(); i<= dists.upperBound(); ++i)
	{
		iDists[i] = (imatrix) dists.at(i);
	}
	m_dists = iDists;
}

SMProcess::SMProcess(const imatrix &_transition, const IMatrixPolynomial &dists)
{
	setTransitionMatrix(_transition);
	// accept distributions
	m_dists = dists;
}

SMProcess::SMProcess(const rmatrix &_transition)
{
	setTransitionMatrix(_transition);
}

SMProcess::SMProcess(const imatrix &_transition)
{
	setTransitionMatrix(_transition);
}

void SMProcess::setTransitionMatrix(const rmatrix &_transition)
{
	this->m_transition = (imatrix)_transition;
}

void SMProcess::setTransitionMatrix(const imatrix &_transition)
{
	this->m_transition = _transition;
}

imatrix SMProcess::getTransitionMatrix() const
{
	return this->m_transition;
}

ivector SMProcess::getDistribution(const int stateFrom, const int stateTo) const
{
	ivector ret(m_dists.getVectorAt(stateFrom, stateTo));
	return ret;
}

rvector SMProcess::getStationaryProbabilities() const
{
	// return fast solution if just 1 state
	if(getNumStates() == 1)
	{
		rvector ret(1,1);
		ret[1] = 1.0;
		return ret;
	}

	// Stationary probabilities for more than 1 state
	const int m = Ub(m_transition,1);
	const int m_min = Lb(m_transition,1);

	imatrix A = IMatrixUtils::zeros(m_min,m,m_min,m);
	ivector B(m_min,m);
	for(int i=m_min; i<=m; i++)
		A[m_min][i] = interval(1.0,1.0);
	B[m_min] = interval(1.0,1.0);

//	Logging::log(Logging::Debug, "Transition matrix", m_transition);

	for(int j = m_min+1; j<=m; j++)
	{
		for(int i=m_min; i<=m; i++)
		{
			A[j][i] = m_transition[i][j];
		}
		A[j][j] = A[j][j] - interval(1.0,1.0);
		B[j] = interval(0.0, 0.0);
	}

	ivector sp(B);

	int err;
	ILinSys _solver;
	Logging::log(Logging::Trace, "Stationary Probabilities");
	Logging::log(Logging::Trace, "A", A);
	Logging::log(Logging::Trace, "b", B);

	_solver.ILinSolve(A,B,sp,err);
	if(err!=0)
		throw std::runtime_error(_solver.ILinSolveErrMsg(err));


	rvector rv(Lb(sp), Ub(sp));
	for(int i=Lb(sp); i<=Ub(sp); ++i)
	{
		rv[i] = mid(sp[i]);
	}

	return rv;
}

}
