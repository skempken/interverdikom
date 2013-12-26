#ifndef CIMATRIXUTILS_H_
#define CIMATRIXUTILS_H_

#include <cimatrix.hpp>
#include <civector.hpp>
#include <cinterval.hpp>

#include "exception/MatrixInversionException.h"
#include "MatrixUtils.hpp"
#include "RealUtils.h"

using cxsc::cimatrix;
using cxsc::civector;
using cxsc::cinterval;

namespace ivk
{

/// Utility methods for interval matrices.
class CIMatrixUtils : public MatrixUtils<cimatrix, civector, cinterval>
{
public:
	static cimatrix invert(const cimatrix & matrix);
};

}

#endif /*CIMATRIXUTILS_H_*/
