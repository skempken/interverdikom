#ifndef BASEPROGRESSLISTENER_H_
#define BASEPROGRESSLISTENER_H_

#include <string>
#include "AbstractProgressListener.h"

using std::string;

namespace ivk
{

/// Abstract class for progress callback.
class BaseProgressListener : public AbstractProgressListener
{
private:
	int m_max;
	string m_currentTask;
	int m_eta;
	
public:

	/// Constructor.	
	BaseProgressListener();
	
	/// Destructor.
	virtual ~BaseProgressListener();
	
	/// Sets the text describing the current task.
	/**
	 * \param text Text describing the current task.
	 */
	virtual void updateProgressText(const std::string &text);
	
	/// Sets the number of steps required for the current task.
	/**
	 * \param max Number of steps required for the current task.
	 */
	virtual void updateProgressMax(const int &max);
	
	/// Sets the number of the current step of the current task.
	/**
	 * \param value Number of the current step of the current task.
	 */
	virtual void updateProgressValue(const int &value);
	
	virtual void updateProgressETA(const int &eta);
};

}

#endif /*BASEPROGRESSLISTENER_H_*/
