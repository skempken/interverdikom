#ifndef PROGRESSNOTIFIER_H_
#define PROGRESSNOTIFIER_H_

#include "AbstractProgressListener.h"
#include <list>
#include <stdexcept>
#include <time.h>

using std::list;

namespace ivk
{

class ProgressNotifier
{
public:
	ProgressNotifier();
	virtual ~ProgressNotifier();

	virtual void addProgressListener(AbstractProgressListener* listener);
	virtual void removeProgressListener(AbstractProgressListener* listener);

private:
	list<AbstractProgressListener*> m_progressListeners;
	clock_t m_lastTick;
	int m_max;

protected:
	/// Sets the text describing the current task.
	/**
	 * \param text Text describing the current task.
	 */
	void setProgressText(const std::string &text);

	/// Sets the number of steps required for the current task.
	/**
	 * \param max Number of steps required for the current task.
	 */
	void setProgressMax(const int &max);

	/// Sets the number of the current step of the current task.
	/**
	 * \param value Number of the current step of the current task.
	 */
	void setProgressValue(const int &value);

	void logMessage(const std::string &message, const int level = 0);
};

}

#endif /*PROGRESSNOTIFIER_H_*/
