#ifndef ABSTRACTDISCRETESSMPMODELER_H_
#define ABSTRACTDISCRETESSMPMODELER_H_

#include "AbstractComputation.hpp"
#include "../data/Trace.h"
#include "../data/SSMProcess.h"

namespace ivk
{

/// Abstract class for algorithms that create discrete semi-Markovian models for a given trace.
class AbstractDiscreteSSMPModeler : public AbstractComputation<Trace, SSMProcess>
{
public:
	/// The number of discretization steps.
	static const char* PARAM_NUMDSTEPS;
	
	/// The number of states of the semi-Markov model.
	static const char* PARAM_NUMSTATES;
	
	/// Constructor.
	/**
	 * According to the base class template, a reference to a trace and a parameter
	 * object must be provided.
	 */
	AbstractDiscreteSSMPModeler(const Trace* data, const ComputationParameters &parameters);
	
	/// Destructor.
	virtual ~AbstractDiscreteSSMPModeler();
	
	/// Sets the number of discretization steps.
	virtual void setNumDSteps(const int value);
	
	/// Returns the number of discretization steps.
	virtual int getNumDSteps() const;
	
	/// Sets the number of states of the semi-Markov model.
	virtual void setNumStates(const int value);
	
	/// Returns the number of states of the semi-Markov model.
	virtual int getNumStates() const;
	
	/// Sets the current parameter object.
	virtual void setParameters(const ComputationParameters &parameters);
	
	/// Computes a transition matrix from a given index sequence.
	static rmatrix computeTransition(const intvector &index);
	
	virtual int suggestNumStates();
	virtual int suggestNumDiscretizationSteps();
	
protected:
	/// Creates a Semi-Markov model from a given index sequence considering the original trace.
	virtual SSMProcess* modelFromIndexSequence(const intvector &index);
	
	
private:
	/// Holds the number of discretization steps.
	int m_numDSteps;
	
	/// Holds the number of states of the semi-Markov model.
	int m_numStates;
};

}

#endif /*ABSTRACTDISCRETESSMPMODELER_H_*/
