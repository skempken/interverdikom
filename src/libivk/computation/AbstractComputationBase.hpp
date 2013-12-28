#ifndef ABSTRACTCOMPUTATIONBASE_H_
#define ABSTRACTCOMPUTATIONBASE_H_

#include "computation/ComputationParameters.h"

namespace ivk
{

class AbstractComputationBase
{
public:
	AbstractComputationBase(const ComputationParameters &parameters) :
		m_parameters(parameters)
	{
	}

	virtual ~AbstractComputationBase()
	{
	}

	/// Sets the current computation parameter object.
	/**
	 * To be implemented in derived classes. The idea is to get parameters for the
	 * computation from the corresponding parameter object.
	 */
	virtual void setParameters(const ComputationParameters &parameters) = 0;

	/// Returns the current computation parameter object.
	virtual ComputationParameters getParameters() const
	{
		return this->m_parameters;
	}

protected:
	/// Holds the current computation parameter object.
	ComputationParameters m_parameters;
};

}

#endif /*ABSTRACTCOMPUTATIONBASE_H_*/
