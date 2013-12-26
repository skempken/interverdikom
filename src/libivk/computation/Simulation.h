#ifndef SIMULATION_H_
#define SIMULATION_H_

#include "AbstractComputation.hpp"
#include "data/SSMProcess.h"
#include "data/DiscretizedTrace.h"
#include <stdexcept>
#include <intvector.hpp>

using cxsc::intvector;


namespace ivk
{

class Simulation : public AbstractComputation<SSMProcess, DiscretizedTrace>
{
public:
	static const char * PARAM_LENGTH;
	
	Simulation(const SSMProcess *ptrData, ComputationParameters &parameters);
	virtual ~Simulation();
	
	void setLength(const int m_length);
	int getLength() const;
	
	DiscretizedTrace* compute();
	void setParameters(const ComputationParameters &parameters);
	
	static int monteCarlo(const rvector &dist);
	
	intvector simulateTransitions(const int length);
	
private:
	int m_length;
	static int monteCarloFromCumSum(const rvector &cumsum);
};

}

#endif /*SIMULATION_H_*/
