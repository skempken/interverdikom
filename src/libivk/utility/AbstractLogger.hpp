#ifndef ABSTRACTLOGGER_H_
#define ABSTRACTLOGGER_H_

#include <real.hpp>
#include <rvector.hpp>
#include <rmatrix.hpp>

#include <intvector.hpp>

#include <l_real.hpp>

#include <interval.hpp>
#include <ivector.hpp>
#include <intvector.hpp>
#include <imatrix.hpp>

#include <l_interval.hpp>
#include <l_imatrix.hpp>

#include <string>

using cxsc::real;
using cxsc::rvector;
using cxsc::rmatrix;

using cxsc::intvector;

using cxsc::l_real;

using cxsc::interval;
using cxsc::ivector;
using cxsc::imatrix;
using cxsc::intvector;

using cxsc::l_interval;
using cxsc::l_imatrix;

using std::string;

namespace ivk
{

class AbstractLogger
{
protected:
	AbstractLogger() {};
	virtual ~AbstractLogger() {};
	
public:
	virtual void log(const int level, const string& message) = 0;
	
	virtual void log(const int level, const string& message, const real& value) = 0;
	virtual void log(const int level, const string& message, const rvector& value) = 0;
	virtual void log(const int level, const string& message, const rmatrix& value) = 0;
	
	virtual void log(const int level, const string& message, const intvector& value) = 0;
	
	virtual void log(const int level, const string& message, const l_real& value) = 0;
	
	virtual void log(const int level, const string& message, const interval& value) = 0;
	virtual void log(const int level, const string& message, const ivector& value) = 0;
	virtual void log(const int level, const string& message, const imatrix& value) = 0;
	
	virtual void log(const int level, const string& message, const l_interval& value) = 0;
	virtual void log(const int level, const string& message, const l_imatrix& value) = 0;
	
	virtual void log(const int level, const string& message, const int &value) = 0;
};

}

#endif /*ABSTRACTLOGGER_H_*/
