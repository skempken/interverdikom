#ifndef MATRIXINVERSIONEXCEPTION_H_
#define MATRIXINVERSIONEXCEPTION_H_

#include <stdexcept>

namespace ivk
{

/// Thrown when the inversion of a matrix fails.
class MatrixInversionException : public std::runtime_error
{
public:
	MatrixInversionException() : std::runtime_error("Matrix could not be inverted.") {}
};

}

#endif /*MATRIXINVERSIONEXCEPTION_H_*/
