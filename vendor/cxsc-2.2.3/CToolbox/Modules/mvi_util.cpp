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

/* CVS $Id: mvi_util.cpp,v 1.3 2008/01/23 08:39:21 cxsc Exp $ */

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
// File: mvi_util (implementation)
// Purpose: Utilities of type 'ivector' and 'imatrix'.
// Global functions:
//    in()        : contained-in-the-interior relation for two interval
//                  vectors and for an integer in an interval vector
//    Blow()      : epsilon inflation for an interval vector
//    Disjoint()  : test for disjointedness of two interval vectors
//    Id()        : identity interval matrix
//    Zero()      : check for a zero interval matrix
//    mid()       : midpoint vector and matrix
//    MaxRelDiam(): to get the maximum of the relative diameters of the
//                  components of an interval vector.
//    UlpAcc()    : to check whether all components of an interval vector
//                  have width less than a certain number of ulps
//                  (ulp = unit in the last place of the mantissa).
//    VecLen()    : length of an interval vector
//    RowLen()    : length of the rows of an interval matrix
//    ColLen()    : length of the columns of an interval matrix
//    DoubleSize(): for doubling the size of an interval vector or matrix
//----------------------------------------------------------------------------
#include <mvi_util.hpp>

