/***************************************************************************
                          CILinSys.h  -  description
                             -------------------

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

//============================================================================
//  - Changed by D. Fausten
//  - Changed by A. Mika
//  File based on: ilinsys.hpp
//
//  Changes (ilinsys.hpp):
//      Instead of a real matrix and a real right-hand side use interval
//      matrix and right hand side in the system Ax=b.
//
//  Changes to CILinSys.hpp:
//      A wrapping class was created
//
//============================================================================
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
//
// see the "Disclaimer / Legal Matters" of the book (page iv).
//
//============================================================================


#ifndef __ILINSYS_HPP
#define __ILINSYS_HPP

#include <civector.hpp>
#include <matinv.hpp>
#include <real.hpp>

using namespace cxsc;
using namespace std;

namespace ivk {



//----------------------------------------------------------------------------
// Purpose: Computation of a verified solution of a square linear system of
//    equations A*x = b with full interval matrix A and interval right-hand
//    side b.
// Global functions:
//    ILinSolve()      : to get a verified enclosure of the solution (two
//                       versions)
//    ILinSolveErrMsg(): to get an error message text
//----------------------------------------------------------------------------
class ILinSys
{

public:
  char* ILinSolveErrMsg ( int );
  void  ILinSolve          ( const imatrix&,  const ivector&,  ivector&,  int& );
  void  ILinSolve          ( const imatrix&,  const ivector&,  ivector&,  cxsc::real&, int& );
  void  CILinSolveIndirekt ( const cimatrix&, const civector&, civector&, int& );
  void  CILinSolveIndirekt ( const cimatrix&, const civector&, civector&, cxsc::real&, int& );

// internal methods
protected:
  void ILinSolveMain ( imatrix A, ivector b, ivector&  xx, cxsc::real& Cond, int ComputeCond, int& Err );
  void CheckForZeros ( rvector& x, rvector& y );
  void VerificationStep ( ivector& xx, ivector& zz, imatrix& C,  int& IsVerified );
  int Accurate ( rvector& x, rvector& y );
  cxsc::real MaxNorm ( const rmatrix& M );

};

}

#endif //__CILINSYS_HPP






















