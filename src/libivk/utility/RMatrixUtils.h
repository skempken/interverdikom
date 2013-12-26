#ifndef RMATRIXUTILS_H_
#define RMATRIXUTILS_H_

#include <rmatrix.hpp>
#include <rvector.hpp>
#include <real.hpp>
#include <assert.h>
#include <string.h>

#include "exception/MatrixInversionException.h"
#include "MatrixUtils.hpp"
#include "RealUtils.h"

using cxsc::rmatrix;
using cxsc::rvector;
using cxsc::real;
using std::string;

namespace ivk
{

/// Utility methods for interval matrices.
class RMatrixUtils : public MatrixUtils<rmatrix, rvector, real>
{
public:
	static rmatrix identity(const int lb, const int ub);
	static rmatrix zeros(const int lb1, const int ub1, const int lb2, const int ub2);
	static rmatrix ones(const int lb1, const int ub1, const int lb2, const int ub2);
	
	/// Inverts 1-based square matrix.
	static rmatrix invert(const rmatrix &matrix);

	static rmatrix sortRows(const rmatrix &a);
	
	/// CircSolv
	/**
	 * circular: First row
	 * right: Right side vector
	 */
	static rvector solveCircular(rvector circular, rvector right);
	static rvector solveToeplitz(rvector toeplitz, rvector right);
	
	static string exportMatlab( rmatrix a );

	static rmatrix splitLR( const rmatrix& A );
	static rvector eigLR(const rmatrix &A, const real &epsilon);
	static rvector eigLR(const rmatrix &A);
	
	static rmatrix invertVandermonde(rvector alpha);
	static rvector solveVandermonde(rvector alpha, rvector b);
};

}

#endif /*IMATRIXUTILS_H_*/
