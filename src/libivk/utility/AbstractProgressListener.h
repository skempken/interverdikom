#ifndef ABSTRACTPROGRESSLISTENER_H_
#define ABSTRACTPROGRESSLISTENER_H_

#include <string>

namespace ivk
{

class AbstractProgressListener
{
protected:
	AbstractProgressListener();
	virtual ~AbstractProgressListener();

public:
	
	/// Sets the text describing the current task.
	/**
	 * \param text Text describing the current task.
	 */
	virtual void updateProgressText(const std::string &text) = 0;
	
	/// Sets the number of steps required for the current task.
	/**
	 * \param max Number of steps required for the current task.
	 */
	virtual void updateProgressMax(const int &max) = 0;
	
	/// Sets the number of the current step of the current task.
	/**
	 * \param value Number of the current step of the current task.
	 */
	virtual void updateProgressValue(const int &value) = 0;
	
	/// Sets the number of seconds remaining for the current task.
	/**
	 * \param value Number of seconds remaining.
	 */
	virtual void updateProgressETA(const int &eta) = 0;
};

}

#endif /*ABSTRACTPROGRESSLISTENER_H_*/
