//============================================================================
//  Changed by D. Fausten
//  Altered by A. Mika
//  File based on: cilinsys.hpp
//  Changes: Instead of a real matrix and a real right-hand side use complex
//           interval matrix and right hand side in the system Ax=b.
//============================================================================



//
//
//
//                              Program/Module
//                                   from
//                 C++ TOOLBOX FOR VERIFIED COMPUTING I
//                         Basic Numerical Problems
//
//      Copyright (c) 1995   Rolf Hammer, Matthias Hocks, Dietmar Ratz
//
// This program/module is free software for non-commercial use. For details
// on theory, algorithms, and programs, see the book
//
//  R. Hammer, M. Hocks, U. Kulisch, D. Ratz:  C++ Toolbox for
//  Verified Computing I - Basic Numerical Problems. Springer-Verlag,
//  Heidelberg, New York, 1995.
//
// This program/module is distributed WITHOUT ANY WARRANTY. For details,
// see the "Disclaimer / Legal Matters" of the book (page iv).
//
//============================================================================


//----------------------------------------------------------------------------
// File: cilinsys (header)
// Purpose: Computation of a verified solution of a square linear system of
//    equations A*x = b with full complex interval matrix A and 
//    complex interval right-hand side b.
// Global functions:
//    CILinSolve()      : to get a verified enclosure of the solution (two
//                        versions)
//    CILinSolveErrMsg(): to get an error message text
//----------------------------------------------------------------------------


#ifndef __CCOMPLEXILINSYS_HPP
#define __CCOMPLEXILINSYS_HPP

#include <cimatrix.hpp>
#include <civector.hpp>

using namespace cxsc;

namespace ivk {

class CComplexILinSys
{

public:
	char* CILinSolveErrMsg ( int );
	void  CILinSolve ( const cimatrix&, const civector&, civector&, int& );
	void  CILinSolve ( const cimatrix&, const civector&, civector&, cxsc::real&, int& );

protected:
	void  CILinSolveMain ( cimatrix  AC, civector bc, civector& xxc, cxsc::real& Cond, int ComputeCond, int& Err );
	void  CheckForZeros ( cvector& x, cvector& y );
	void  VerificationStep ( civector& xx, civector& zz, cimatrix& C, int& IsVerified );
	int   Accurate ( cvector& x, cvector& y );
	cxsc::real  MaxNorm ( const cmatrix& M );

};

}

#endif //__CCOMPLEXILINSYS




