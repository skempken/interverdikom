#ifndef IMATRIXUTILS_H_
#define IMATRIXUTILS_H_

#include <imatrix.hpp>
#include <ivector.hpp>
#include <interval.hpp>
#include <real.hpp>
#include <assert.h>

#include "exception/MatrixInversionException.h"
#include "utility/MatrixUtils.hpp"

using cxsc::imatrix;
using cxsc::ivector;
using cxsc::interval;
using cxsc::real;

namespace ivk
{

/// Utility methods for interval matrices.
class IMatrixUtils : public MatrixUtils<imatrix, ivector, interval>
{
public:
	static imatrix identity(const int lb, const int ub);
	static imatrix zeros(const int lb1, const int ub1, const int lb2, const int ub2);
	static imatrix ones(const int lb1, const int ub1, const int lb2, const int ub2);
	
	/// Inverts 1-based square matrix.
	static imatrix invert(const imatrix &matrix);
	static cxsc::real maxDiam(const imatrix &matrix);
	static cxsc::real maxDiam(const ivector &vector);
};

}

#endif /*IMATRIXUTILS_H_*/
