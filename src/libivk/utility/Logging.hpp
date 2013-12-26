#ifndef LOGGING_H_
#define LOGGING_H_

#include "AbstractLogger.hpp"

namespace ivk
{

class Logging
{
public:
	enum LogLevel
	{
		Trace = 0,
		Debug = 1,
		Info = 2,
		Warning = 3,
		Error = 4,
		Fatal = 5
	};
	
private:
	static LogLevel m_logLevel;
	static AbstractLogger* m_logger;

public:
	static void setLogLevel(const LogLevel level) { m_logLevel = level; };
	static LogLevel getLogLevel() { return m_logLevel; };
	static bool willLog(const LogLevel level) { return (m_logLevel <= level); };
	
	static void setLogger(AbstractLogger* logger) {m_logger = logger;};
	
	static void log(const LogLevel level, const string& message)
	{
		if(m_logger && (level >= m_logLevel))
			m_logger->log(level, message);
	};
	
	template <class T>
	static void log(const LogLevel level, const string& description, const T& value)
	{
		if(m_logger && (level >= m_logLevel))
			m_logger->log(level, description, value);
	};
	
};

}

#endif /*LOGGING_H_*/
