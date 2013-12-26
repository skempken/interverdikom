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
// File: cpzero (header)
// Purpose: Determination and enclosure of a root of a complex polynomial,
//    and of the coefficients of the deflated polynomial.
// Global functions:
//    CPolyZero()      : computes an enclosure for a root and for the
//                       deflated complex polynomial
//    CPolyZeroErrMsg(): delivers an error message text
//----------------------------------------------------------------------------
#ifndef __CIPZERO_HPP
#define __CIPZERO_HPP

#include <cipoly.hpp>
#include <cpoly.hpp>

using namespace cxsc;
using namespace std;

namespace cxscx {

class CIPZero
{

public:
  char* getCIPolyZeroErrMsg ( int );
  void  getCIPolyZero ( CIPolynomial, complex, CIPolynomial&, cinterval&, int& );

protected:
  real getMaxNorm( CPolynomial p );
  void doIntervalIteration( CIPolynomial, CPolynomial, complex, CIPolynomial&, cinterval&, int& );
  void doApproximation( CIPolynomial, complex&, CPolynomial&, int& );



};

}

#endif

