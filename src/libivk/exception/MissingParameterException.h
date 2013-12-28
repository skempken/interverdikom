#ifndef MISSINGPARAMETEREXCEPTION_H_
#define MISSINGPARAMETEREXCEPTION_H_

#include <stdexcept>
#include <string>

using std::string;

namespace ivk
{

/// Thrown when a parameter is missing.
/**
 * The missing parameter can be named as a parameter to the exception.
 */
class MissingParameterException : public std::invalid_argument
{
public:
	MissingParameterException() : std::invalid_argument("Missing parameter.") {}
	MissingParameterException(const string &text) : std::invalid_argument(string("Missing parameter: ")+text) {}
};

}

#endif /*MISSINGPARAMETEREXCEPTION_H_*/
