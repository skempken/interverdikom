#ifndef COMPUTATIONPARAMETERS_H_
#define COMPUTATIONPARAMETERS_H_

#include <string>
#include <map>

#include <intvector.hpp>
#include <real.hpp>

#include "exception/MissingParameterException.h"

using std::string;
using std::map;
using cxsc::real;
using cxsc::intvector;

namespace ivk
{

class ComputationParameters
{
public:
	ComputationParameters();
	
	ComputationParameters(const ComputationParameters & other) :
		m_parameters(other.m_parameters)
	{
	}
	
	void operator=(const ComputationParameters & other)
	{
		m_parameters = other.m_parameters;
	}
	
	virtual ~ComputationParameters();

	void setString(const string, const string &value);
	string getString(const string) const;

	void setInt(const string, const int &value);
	int getInt(const string) const;

	void setReal(const string, const real &value);
	real getReal(const string) const;

	void setIntVector(const string, const intvector &value);
	intvector getIntVector(const string) const;
	
	static string convertIntVectorToString(const intvector &value);
	static intvector convertStringToIntVector(const string &str);

private:
	map<string,string> m_parameters;
};

}

#endif /*COMPUTATIONPARAMETERS_H_*/
