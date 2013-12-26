#include "Simulation.h"

namespace ivk
{

const char * Simulation::PARAM_LENGTH = "length";

Simulation::Simulation(const SSMProcess *ptrData, ComputationParameters &parameters)
: AbstractComputation<SSMProcess, DiscretizedTrace>(ptrData, parameters)
{
	setParameters(parameters);
}

Simulation::~Simulation()
{
}

void Simulation::setParameters(const ComputationParameters &parameters)
{
	setLength(parameters.getInt(PARAM_LENGTH));
}

void Simulation::setLength(const int length)
{
	if(length > 0)
		this->m_length = length;
	else
		throw std::out_of_range("Length must be > 0");
}

int Simulation::getLength() const
{
	return this->m_length;
}

DiscretizedTrace* Simulation::compute()
{
	intvector simulatedTrace(0, m_length-1);
	intvector stateTrace = simulateTransitions(m_length);
	
	rmatrix dists = mid(m_ptrData->getDistributions());
	
	for(int i = Lb(simulatedTrace); i<=Ub(simulatedTrace); ++i)
	{
		simulatedTrace[i] = monteCarlo(dists[stateTrace[i]]);
	}
	
	return new DiscretizedTrace(simulatedTrace);
}

intvector Simulation::simulateTransitions(const int length)
{
	intvector trace(0, length-1);
	trace[0] = monteCarlo(m_ptrData->getStationaryProbabilities());
	rmatrix trans = mid(m_ptrData->getTransitionMatrix());
	for(int i = Lb(trace)+1; i<=Ub(trace); ++i)
	{
		trace[i] = monteCarlo(trans[trace[i-1]]);
	}
	return trace;
}

int Simulation::monteCarlo(const rvector &_dist)
{
	// Compute cumulative sum
	rvector cumsum(Lb(_dist), Ub(_dist));
	real sum = 0.0;
	for(int i = Lb(_dist); i<=Ub(_dist); ++i)
	{
		sum += _dist[i];
		cumsum[i] = sum;
	}
	
	return monteCarloFromCumSum(cumsum);
}

int Simulation::monteCarloFromCumSum(const rvector &cumsum)
{
	// Get random number between 0 and 1.
	real r = (double)(rand())/RAND_MAX;
	
	// Find corresponding index.
	int i = Lb(cumsum);
	while(r > cumsum[i])
	{
		++i;
	}
	return i;
}


}
