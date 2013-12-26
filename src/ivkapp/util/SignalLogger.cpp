#include "SignalLogger.h"

#include "utility/Logging.hpp"
#include "utility/IMatrixUtils.h"
#include "utility/l_IMatrixUtils.h"

SignalLogger::SignalLogger()
{
}

SignalLogger::~SignalLogger()
{
}

void SignalLogger::emitLogSignal(const int level, const QString & text)
{
	if (level >= Logging::Error)
	{
		emit logError(text);
	}
	else
	{
		emit logMessage(text);
	}
}


void SignalLogger::emitLogSignal(const int level, const stringstream & textStream)
{
	emitLogSignal(level, QString::fromStdString(textStream.str()));
}

void SignalLogger::log(const int level, const string& message)
{
	emitLogSignal(level, QString::fromStdString(message) + "\n");
}

void SignalLogger::log(const int level, const string& description,
		const real& value)
{
	stringstream textStream;
	textStream << description << ": " << value << endl;
	emitLogSignal(level, textStream);
}

void SignalLogger::log(const int level, const string& description,
		const rvector& value)
{
	stringstream textStream;
	textStream << description << ": " << endl << value << endl;
	emitLogSignal(level, textStream);
}

void SignalLogger::log(const int level, const string& description,
		const rmatrix& value)
{
	stringstream textStream;
	textStream << description << ": " << endl << value << endl;
	emitLogSignal(level, textStream);
}

void SignalLogger::log(const int level, const string& description,
		const intvector& value)
{
	stringstream textStream;
	textStream << description << ": " << endl << value << endl;
	emitLogSignal(level, textStream);
}

void SignalLogger::log(const int level, const string& description,
		const l_real& value)
{
	stringstream textStream;
	textStream << description << ": " << value << endl;
	emitLogSignal(level, textStream);
}

void SignalLogger::log(const int level, const string& description,
		const interval& value)
{
	stringstream textStream;
	textStream << description << ": " << value << " (d = " << diam(value) << ")" << endl;
	emitLogSignal(level, textStream);
}

void SignalLogger::log(const int level, const string& description,
		const ivector& value)
{
	stringstream textStream;
	textStream << description << ": " << endl;
	textStream << value;
	textStream << "(dmax = " << IMatrixUtils::maxDiam(value) << ")" << endl;
	emitLogSignal(level, textStream);
}

void SignalLogger::log(const int level, const string& description,
		const imatrix& value)
{
	stringstream textStream;
	textStream << description << ": " << endl;
	textStream << value;
	textStream << "(dmax = " << IMatrixUtils::maxDiam(value) << ")" << endl;
	emitLogSignal(level, textStream);
}

void SignalLogger::log(const int level, const string& description,
		const int &value)
{
	stringstream textStream;
	textStream << description << ": " << value << endl;
	emitLogSignal(level, textStream);
}

void SignalLogger::log(const int level, const string& description,
		const l_imatrix& value)
{
	stringstream textStream;
	textStream << description << ": " << endl;
	textStream << value;
	textStream << "(dmax = " << l_IMatrixUtils::maxDiam(value) << ")" << endl;
	emitLogSignal(level, textStream);
}

void SignalLogger::log(const int level, const string& description,
		const l_interval& value)
{
	stringstream textStream;
	textStream << description << ": " << endl;
	textStream << value;
	emitLogSignal(level, textStream);
}
