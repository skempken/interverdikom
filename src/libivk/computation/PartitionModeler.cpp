#include "PartitionModeler.h"

#include "data/Trace.h"

#include <real.hpp>
#include <intvector.hpp>

#include <iostream>
#include <assert.h>

using namespace cxsc;
using namespace std;

namespace ivk
{

PartitionModeler::PartitionModeler(const Trace *data, const ComputationParameters &parameters)
: AbstractDiscreteSSMPModeler(data, parameters)
{

}

PartitionModeler::~PartitionModeler()
{
}

SSMProcess* PartitionModeler::compute()
{
	setProgressText("starting computation");
	setProgressMax(100);
	setProgressValue(1);
	const int numStates = this->getNumStates();
	const int numDSteps = this->getNumDSteps();
	rvector data = m_ptrData->getTrace();
	rvector R = m_ptrData->discretize(m_ptrData->getDiscretizationPoints(numDSteps));

	// Compute borders according to Traczinski dissertation
	intvector l(1, numStates);
	intvector n(1, numStates);
	
	for(int k = 1; k<=numStates; ++k)
	{
		real compare;
		compare = (k - 1.0)/numStates;

		l[k] = computeLN(R, numDSteps, compare,1);
		compare = ((real)k)/numStates;
		n[k] = computeLN(R, numDSteps, compare,0);
	}
	
	// Check results.
	n[Ub(n)] = numDSteps-1;
	checkLN(l,n);
	
	// compute distributions
	rmatrix dist(1, numStates, Lb(R), Ub(R));
	setProgressText("compute distributions");
	for(int state=Lb(dist,1); state<=Ub(dist,1); ++state)
	{
		real sum = 0.0;
		for(int j=l[state]; j<=n[state]; ++j)
			sum += R[j];
		for(int j = Lb(dist,2); j<=Ub(dist, 2); ++j)
		{
			if(j<l[state] || j>n[state])
				dist[state][j] = 0.0;
			else
				dist[state][j] = R[j]/sum;
		}
		setProgressValue(1 + (int) ( (double) ( 32.0 / Ub(dist,1) ) ) * state);
	}
	
	// compute transitions
	setProgressText("compute transistion");
	rmatrix count(1, numStates, 1, numStates);
	for(int i = Lb(count,1); i<=Ub(count,1); ++i)
		for(int j = Lb(count,2); j<=Ub(count,2); ++j)
			count[i][j] = 0.0;
	
	const real minValue = m_ptrData->getMinimum();
	const real maxValue = m_ptrData->getMaximum();
	
	const real Delta = (maxValue-minValue)/(numDSteps-1);
	rvector s(0,numDSteps-1);
	for(int l=Lb(s); l<=Ub(s); ++l)
		s[l] = minValue + l*Delta;
	
	intvector index(Lb(data), Ub(data));
	for(int k = Lb(l); k<=Ub(l); ++k)
	{
		for(int i = Lb(data); i<=Ub(data); ++i)
		{
			if(data[i] >= (s[l[k]]-Delta/2) && data[i] <= (s[n[k]]+Delta/2))
				index[i] = k;
		}
		setProgressValue(33 + (int)((double) ( 32.0 / Ub( l )) * k));
	}
	
	for(int i=Lb(data)+1; i<=Ub(data);++i)
		count[index[i-1]][index[i]] += 1.0;
	
	// normalize
	for(int i=Lb(count,1); i<=Ub(count,1); ++i)
	{
		real sum = 0.0;
		for(int j=Lb(count,2); j<=Ub(count,2); ++j)
		{
			sum += count[i][j];
		}
		for(int j=Lb(count,2); j<=Ub(count,2); ++j)
		{
			count[i][j]/=sum;
		}
		setProgressValue(65 + (int) ( (double) (32.0 / Ub( count, 1 )) * i));
	}
	
	// XXX: Cheat here...
	SetLb(dist, 0, 0);
	
	setProgressText("creating model");
	setProgressValue(99);
	return new SSMProcess(count, dist);
}

int PartitionModeler::checkLN(const intvector &l, const intvector &n) const
{
	// continuous indexing of discretization points
	const int numDSteps = this->getNumDSteps();
	for(int k=Lb(n); k<Ub(n); ++k)
	{
		assert(n[k]==(l[k+1]-1));
	}
	// Zero-based
	assert(l[Lb(l)] == 0);
	assert(n[Ub(n)] == numDSteps-1);
	
	return 0;
}

int PartitionModeler::computeLN(const rvector R, const int g, const real compare, const int offset) const
{
	rvector lvalue(0, g-1);
	for(int ltilde = Lb(lvalue); ltilde<=Ub(lvalue); ++ltilde)
	{
		lvalue[ltilde] = 0.0;
		for(int j = 0; j<ltilde-offset; ++j)
			lvalue[ltilde] += R[j];
		lvalue[ltilde] =abs(lvalue[ltilde]- compare);
	}
	real argvalue = DBL_MAX;
	int argindex = 0;
	for(int ltilde = Lb(lvalue); ltilde<=Ub(lvalue); ++ltilde)
	{
		if(lvalue[ltilde] < argvalue)
		{
			argvalue = lvalue[ltilde];
			argindex = ltilde;
		}
	}
	return argindex;
}

}
