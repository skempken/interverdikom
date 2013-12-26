#include "ConsoleLogger.h"

#include <iostream>
#include "utility/IMatrixUtils.h"
#include "utility/l_IMatrixUtils.h"

using std::cout;
using std::endl;

namespace ivk
{

ConsoleLogger::ConsoleLogger()
{
	//cout << cxsc::SetDotPrecision(33,32);
}

ConsoleLogger::~ConsoleLogger()
{
}

std::string ConsoleLogger::getLevelText(const int level)
{
	switch(level)
	{
	case Logging::Trace:
		return "TRACE";
	case Logging::Debug:
		return "DEBUG";
	case Logging::Info:
		return "INFO";
	case Logging::Warning:
		return "WARN";
	case Logging::Error:
		return "ERROR";
	case Logging::Fatal:
		return "FATAL";
	}
	return "<unknown>";
}

void ConsoleLogger::log(const int level, const string& message)
{
	cout << getLevelText(level) << ": " << message << endl;
}

void ConsoleLogger::log(const int level, const string& message, const real &value)
{
	cout << getLevelText(level) << ": " << message << ": " << value << endl;
}

void ConsoleLogger::log(const int level, const string& message, const rvector &value)
{
	cout << getLevelText(level) << ": " << message << ": " << endl << value << endl;
}

void ConsoleLogger::log(const int level, const string& message, const rmatrix &value)
{
	cout << getLevelText(level) << ": " << message << ": " << endl << value << endl;
}

void ConsoleLogger::log(const int level, const string& message, const l_real &value)
{
	cout << getLevelText(level) << ": " << message << ": " << value << endl;
}

void ConsoleLogger::log(const int level, const string& message, const intvector &value)
{
	cout << getLevelText(level) << ": " << message << ": " << endl << value << endl;
}

void ConsoleLogger::log(const int level, const string& message, const interval &value)
{
	cout << getLevelText(level) << ": " << message << ": " << value << " (d = " << diam(value) << ")" << endl;
}

void ConsoleLogger::log(const int level, const string& message, const ivector &value)
{
	cout << getLevelText(level) << ": " << message << ": " << endl;
	cout << value;
	cout << "(dmax = " << IMatrixUtils::maxDiam(value) << ")" << endl;
}

void ConsoleLogger::log(const int level, const string& message, const imatrix &value)
{
	cout << getLevelText(level) << ": " << message << ": " << endl;
	cout << value;
	cout << "(dmax = " << IMatrixUtils::maxDiam(value) << ")" << endl;
}

void ConsoleLogger::log(const int level, const string& message, const int &value)
{
	cout << getLevelText(level) << ": " << message << ": " << value << endl;
}

void ConsoleLogger::log(const int level, const string& message, const l_imatrix &value)
{
	cout << getLevelText(level) << ": " << message << ": " << endl;
	cout << value;
	cout << "(dmax = " << l_IMatrixUtils::maxDiam(value) << ")" << endl;
}

void ConsoleLogger::log(const int level, const string& message, const l_interval &value)
{
	cout << getLevelText(level) << ": " << message << ": " << value << " (d = " << diam(value) << ")" << endl;
}

}
