#ifndef CONSOLELOGGER_H_
#define CONSOLELOGGER_H_

#include "AbstractLogger.hpp"
#include "utility/Logging.hpp"

namespace ivk
{

class ConsoleLogger : public ivk::AbstractLogger
{
public:
	ConsoleLogger();
	virtual ~ConsoleLogger();
	
	virtual void log(const int level, const string& message);
	
	virtual void log(const int level, const string& message, const intvector &value);
	
	virtual void log(const int level, const string& message, const real &value);
	virtual void log(const int level, const string& message, const rvector &value);
	virtual void log(const int level, const string& message, const rmatrix &value);
	
	virtual void log(const int level, const string& message, const l_real &value);
	
	virtual void log(const int level, const string& message, const interval &value);
	virtual void log(const int level, const string& message, const ivector &value);
	virtual void log(const int level, const string& message, const imatrix &value);

	virtual void log(const int level, const string& message, const l_interval &value);
	virtual void log(const int level, const string& message, const l_imatrix &value);
	
	virtual void log(const int level, const string& message, const int &value);
	
protected:
	std::string getLevelText(const int level);
};

}

#endif /*CONSOLELOGGER_H_*/
