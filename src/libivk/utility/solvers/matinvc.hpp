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
// see the "Disclaimer / Legal Matters" of the book (page iv).
//
//============================================================================
//----------------------------------------------------------------------------
// File: matinv (header)
// Purpose: Computation of an approximate inverse of a real square matrix.
// Global functions:
//   MatInv()      : matrix inversion
//   MatInvErrMsg(): to get an error message text
//----------------------------------------------------------------------------
#ifndef __MATINVC_HPP
#define __MATINVC_HPP

#include <cmatrix.hpp>

using namespace cxsc;
using namespace std;

namespace ivk {

extern char* MatInvcErrMsg ( int );
extern void  MatInvc ( cmatrix, cmatrix&, int& );

}
#endif
