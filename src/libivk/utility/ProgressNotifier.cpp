#include "ProgressNotifier.h"

#include "utility/Logging.hpp"

using namespace std;

namespace ivk
{

ProgressNotifier::ProgressNotifier()
{
	m_lastTick = clock();
	m_max = 1;
}

ProgressNotifier::~ProgressNotifier()
{
}

void ProgressNotifier::setProgressText(const std::string &text)
{
	for(list<AbstractProgressListener*>::iterator it = m_progressListeners.begin(); it!=m_progressListeners.end(); ++it)
	{
		AbstractProgressListener* listener = *it;
		try	{listener->updateProgressText(text);}
		catch(std::exception &ex) {
			Logging::log(Logging::Error, ex.what());
		}
	}
}

void ProgressNotifier::setProgressMax(const int &max)
{
	this->m_max = max;
	for(list<AbstractProgressListener*>::iterator it = m_progressListeners.begin(); it!=m_progressListeners.end(); ++it)
	{
		AbstractProgressListener* listener = *it;
		try {listener->updateProgressMax(max);}
		catch(std::exception &ex) {
			Logging::log(Logging::Error, ex.what());
		}
	}
}

void ProgressNotifier::setProgressValue(const int &value)
{
	// Compute ETA
	clock_t now = clock();
	int secondsLeft = (now - m_lastTick)  * (m_max - value) / CLOCKS_PER_SEC;
	m_lastTick = now;

	for(list<AbstractProgressListener*>::iterator it = m_progressListeners.begin(); it!=m_progressListeners.end(); ++it)
	{
		AbstractProgressListener* listener = *it;
		try {
			listener->updateProgressETA(secondsLeft);
			listener->updateProgressValue(value);
		}
		catch(std::exception &ex) {
			Logging::log(Logging::Error, ex.what());
		}
	}
}

void ProgressNotifier::addProgressListener(AbstractProgressListener* listener)
{
	m_progressListeners.push_back(listener);
}

void ProgressNotifier::removeProgressListener(AbstractProgressListener* listener)
{
	m_progressListeners.remove(listener);
}

}
