#ifndef ITERATIONLIMITEXCEPTION_H_
#define ITERATIONLIMITEXCEPTION_H_

#include <stdexcept>

namespace ivk
{

/// Thrown when a given limit of the number of allowed iterations has been reached.
class IterationLimitException : public std::runtime_error
{
public:
	IterationLimitException() : std::runtime_error("Too many iterations.") {}
};

}

#endif /*ITERATIONLIMITEXCEPTION_H_*/
