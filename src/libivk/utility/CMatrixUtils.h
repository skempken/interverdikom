#ifndef CMATRIXUTILS_H_
#define CMATRIXUTILS_H_

#include <cmatrix.hpp>
#include <cvector.hpp>
#include <complex.hpp>

#include "exception/MatrixInversionException.h"
#include "utility/CIMatrixUtils.h"
#include "MatrixUtils.hpp"
#include "RealUtils.h"

using cxsc::cmatrix;
using cxsc::cvector;
using cxsc::complex;

namespace ivk
{

/// Utility methods for interval matrices.
class CMatrixUtils : public MatrixUtils<cmatrix, cvector, cxsc::complex>
{
public:
	static cmatrix invert(const cmatrix & matrix);
};

}


#endif /*CMATRIXUTILS_H_*/
