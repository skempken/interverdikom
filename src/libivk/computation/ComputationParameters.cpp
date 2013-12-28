#include "ComputationParameters.h"

#include <sstream>

using std::istringstream;
using std::ostringstream;

namespace ivk
{

ComputationParameters::ComputationParameters()
{
}

ComputationParameters::~ComputationParameters()
{
}

void ComputationParameters::setString(const string key, const string &value)
{
	this->m_parameters[key] = value;
}

string ComputationParameters::getString(const string key) const
{
	map<string, string>::const_iterator it = m_parameters.find(key);
	if (it == m_parameters.end())
	{
		throw MissingParameterException(string(key));
	}
	string ret((*it).second);

	return ret;
}

void ComputationParameters::setInt(const string key, const int &value)
{
	ostringstream o;
	o << value;
	setString(key, o.str());
}

int ComputationParameters::getInt(const string key) const
{
	istringstream i(getString(key));
	int value;
	i >> value;
	return value;
}

void ComputationParameters::setReal(const string key, const real &value)
{
	// TODO: Check precision issues
	ostringstream o;
	o << cxsc::SetPrecision(15, 16);
	o << value;
	setString(key, o.str());
}

real ComputationParameters::getReal(const string key) const
{
	istringstream i(getString(key));
	real value;
	i >> value;
	return value;
}

void ComputationParameters::setIntVector(const string key,
		const intvector &value)
{
	setString(key, convertIntVectorToString(value));
}

string ComputationParameters::convertIntVectorToString(const intvector &value)
{
	ostringstream o;

	for (int i = Lb(value); i <= Ub(value); i++)
	{
		o << value[i];
		if (i != Ub(value))
		{
			o << ",";
		}
	}

	return o.str();
}

intvector ComputationParameters::convertStringToIntVector(const string &str)
{
	intvector ret(0, 0);

	size_t curPos = 0;
	size_t lastPos = -1;

	do
	{
		curPos = str.find_first_of(',', lastPos+1);
		istringstream i(str.substr(lastPos+1, curPos-lastPos-1));
		
		int val;
		i >> val;
		
		if (lastPos == -1)
		{
			ret[0] = val;
		}
		else
		{
			Resize(ret, 0, Ub(ret)+1);
			ret[Ub(ret)] = val;
		}
		
		lastPos = curPos;
	} while (curPos != string::npos);

	return ret;
}

intvector ComputationParameters::getIntVector(const string key) const
{
	istringstream i(getString(key));
	string str = i.str();
	
	return convertStringToIntVector(str);
}

}
