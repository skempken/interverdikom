#ifndef ABSTRACTCOMPUTATION_H_
#define ABSTRACTCOMPUTATION_H_

#include "utility/ProgressNotifier.h"

#include "AbstractComputationBase.hpp"

namespace ivk
{

/**
 * Abstract class template for computations on some kind of data and producing some kind of result.
 * The actual class of the data to be computed on and the class of the result are given
 * as class template parameters:
 * D: Type of data to be computed on
 * R: Type of result.
 */
template <class D, class R>
class AbstractComputation : public AbstractComputationBase, public ProgressNotifier
{
public:
	/// The type of the data to be processed.
	typedef D DataType;
	
	/// The type of the results to be provided.
	typedef R ResultType;
	
	/// Abstract constructor.
	/**
	 * Abstract constructor. Needs to get a pointer to the data to be processed,
	 * and a set of parameters for the actual computation.
	 */
	AbstractComputation(const D * ptrData, const ComputationParameters &parameters)
	: AbstractComputationBase(parameters), m_ptrData(ptrData)
	{
		
	}
	
	/// Destructor.
	/**
	 * Nothing to be done here.
	 */
	virtual ~AbstractComputation() {};
	
	/// The main computation routine.
	/**
	 * Can be lengthy, consider running in a separate thread.
	 */
	virtual R* compute() = 0;


protected:
	/// Points to the data for this computation.
	const D* m_ptrData;
};

}

#endif /*ABSTRACTCOMPUTATION_H_*/
