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

/* CVS $Id: ci_util.cpp,v 1.3 2008/01/23 08:39:21 cxsc Exp $ */

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
// File: ci_util (implementation)
// Purpose: Utilities of type 'cinterval'
// Global functions:
//    in()  : Contained-in-the-interior relation for two complex intervals
//    Blow(): Epsilon inflation
//----------------------------------------------------------------------------
#include <i_util.hpp>      // Interval utility functions
#include <ci_util.hpp>

// obsolete file

/*
using namespace cxsc;
using namespace std;

int in ( cinterval& x, cinterval& y )    // Contained-in-the-interior relation
{                                        //-----------------------------------
  return ( in(Re(x),Re(y)) && in(Im(x),Im(y)) );
}

cinterval Blow ( cinterval x, const real& eps )           // Epsilon inflation
{                                                         //------------------
  return _cinterval(Blow(Re(x),eps),Blow(Im(x),eps));
}
*/

