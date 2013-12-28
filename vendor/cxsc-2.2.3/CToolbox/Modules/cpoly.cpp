/*
**  CXSC is a C++ library for eXtended Scientific Computing (V 2.2.3)
**
**  Copyright (C) 1990-2000 Institut fuer Angewandte Mathematik,
**                          Universitaet Karlsruhe, Germany
**            (C) 2000-2008 Wiss. Rechnen/Softwaretechnologie
**                          Universitaet Wuppertal, Germany   
**
**  This library is free software; you can redistribute it and/or
**  modify it under the terms of the GNU Library General Public
**  License as published by the Free Software Foundation; either
**  version 2 of the License, or (at your option) any later version.
**
**  This library is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
**  Library General Public License for more details.
**
**  You should have received a copy of the GNU Library General Public
**  License along with this library; if not, write to the Free
**  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/* CVS $Id: cpoly.cpp,v 1.4 2008/05/28 15:28:28 cxsc Exp $ */

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
// File: cpoly (implementation)
// Purpose: Definition of the class for the representation of a complex
//    polynomial by its coefficients.
// Class CPolynomial:
//    Deg()        : to get the degree of the polynomial
//    CPolynomial(): constructors
//    operator []  : component access
//    operator >>  : input operator for data of type CPolynomial
//    operator <<  : output operator for data of type CPolynomial
//----------------------------------------------------------------------------
#include <cpoly.hpp>

using namespace cxsc;
using namespace std;

int Deg ( const CPolynomial& p ) { return Ub(p.coeff); }

CPolynomial::CPolynomial( int n )
{
  Resize(coeff,0,n);
  coeff = 0.0;
}

CPolynomial::CPolynomial( const CPolynomial& p )
{
  Resize(coeff,0,Deg(p));
  coeff = p.coeff;
}

istream& operator>> ( istream& in, CPolynomial& p )
{
  cout << "  x^0 * ";  in >> p[0];
  for (int i = 1; i <= Deg(p); i++)
    { cout << "+ x^" << i << " * ";  in >> p[i]; }
  return in;
}

ostream& operator<< ( ostream& out, CPolynomial p )
{
  int PolyIsZero, n = Deg(p);

  PolyIsZero = 1;
  for (int i = 0; i <= n; i++) {
    if (p[i] == 0.0) continue;
    if (PolyIsZero)
      out << "  ";
    else
      out << "+ ";
    out << p[i] << " * x^" << i << endl;
    PolyIsZero = 0;
  }
  if (PolyIsZero) out << "  0 (= zero polynomial)" << endl;
  return out;
}

