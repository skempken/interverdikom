#ifndef SIGNALLOGGER_H_
#define SIGNALLOGGER_H_

#include <QObject>
#include "utility/AbstractLogger.hpp"

#include <sstream>
#include <string>

using namespace ivk;

using namespace std;

class SignalLogger : public QObject, public ivk::AbstractLogger
{
	Q_OBJECT
	
public:
	SignalLogger();
	virtual ~SignalLogger();
	
	virtual void log(const int level, const string& message);
	virtual void log(const int level, const string& description, const real& value);
	virtual void log(const int level, const string& description, const rvector& value);
	virtual void log(const int level, const string& description, const rmatrix& value);
	virtual void log(const int level, const string& description, const intvector& value);
	virtual void log(const int level, const string& description, const l_real& value);
	virtual void log(const int level, const string& description, const interval& value);
	virtual void log(const int level, const string& description, const ivector& value);
	virtual void log(const int level, const string& description, const imatrix& value);
	virtual void log(const int level, const string& description, const l_interval& value);
	virtual void log(const int level, const string& description, const l_imatrix& value);
	virtual void log(const int level, const string& description, const int &value);
	
signals:
	void logMessage(const QString & text);
	
	void logError(const QString & text);
	
private:
	void emitLogSignal(const int level, const QString & text);
	
	void emitLogSignal(const int level, const stringstream & textStream);
};

#endif /*SIGNALLOGGER_H_*/
