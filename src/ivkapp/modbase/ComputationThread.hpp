#ifndef COMPUTATIONTHREAD_H_
#define COMPUTATIONTHREAD_H_

#include "ComputationThreadBase.h"

#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

/// Thread object for executing a specified type of computation
/**
 * This class is parameterized with the type of Computation object that it
 * manages. An instance of this class contains a pointer to a computation object
 * pointer which it manages. This is to allow the computation object to be recreated
 * with different objects at a different memory location without reinitializing the
 * associated ComputationThread each time.
 */
template<class T> class ComputationThread : public ComputationThreadBase
{
private:
	/// Pointer to pointer to managed computation object
	T **computation;

	typename T::ResultType *result;

public:
	/// Getter for computation object
	T *getComputation()
	{
		return (*this->computation);
	}

	/// Constructor, initializes attached controls and computation
	ComputationThread(T **computation, ModuleWidget *parentWidget,
			QPushButton *computeButton = 0, QProgressBar *progressBar = 0,
			QLabel *taskLabel = 0) :
		ComputationThreadBase(parentWidget, computeButton, progressBar,
				taskLabel), computation(computation), result(0)
	{
	}

	/// Destructor
	~ComputationThread()
	{
	}

	typename T::ResultType *getResult()
	{
		return result;
	}

	/// Implementation of run() for this thread object
	/**
	 * This function is called as soon as the thread is start()ed. It
	 * performs the computation and emits signals to give information
	 * about its progress. If controls were attached to the thread,
	 * these are updates as well through the previously made
	 * connections.
	 */
	void run()
	{
		(*computation)->addProgressListener(this);
		try
		{
			emit message("Starting computation...");
			result = (*computation)->compute();
			emit message("Computation finished.");
			emit computationFinished();
		}
		catch(std::exception &ex) // TODO PLACEHOLDER for exception handling!

		{
			emit error("Exception during computation.");
			QString message(ex.what());
			emit exception(message);
		}
		(*computation)->removeProgressListener(this);
	}

};

#endif /*COMPUTATIONTHREAD_H_*/
