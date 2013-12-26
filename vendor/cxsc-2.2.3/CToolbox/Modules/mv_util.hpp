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

/* CVS $Id: mv_util.hpp,v 1.4 2008/01/23 08:39:21 cxsc Exp $ */

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
// File: mv_util (implementation)
// Purpose: Utilities of type 'intvector', 'intmatrix', 'rvector', and
//    'rmatrix'.
// Global functions:
//    VecLen()    : length of an integer or real vector
//    RowLen()    : length of the rows of an integer or real matrix
//    ColLen()    : length of the columns of an integer or real matrix
//    Id()        : identity real matrix
//    transp()    : transposed of a real matrix
//    DoubleSize(): for doubling the size of an integer vector or matrix
//    operator << : output of integer vector
//----------------------------------------------------------------------------
#ifndef __MV_UTIL_HPP
#define __MV_UTIL_HPP

#include <intmatrix.hpp>     // Interval matrix/vector type
#include <rmatrix.hpp>      // Real matrix/vector arithmetic

//using namespace cxsc;
//using namespace std;

//extern int      VecLen     ( const intvector& );
//extern int      RowLen     ( const intmatrix& );
//extern int      ColLen     ( const intmatrix& );
//extern int      VecLen     ( const rvector& );
//extern int      RowLen     ( const rmatrix& );
//extern int      ColLen     ( const rmatrix& );
//extern rmatrix  Id         ( const rmatrix& );
//extern rmatrix  transp     ( rmatrix& );
//extern void     DoubleSize ( intvector& );
//extern void     DoubleSize ( intmatrix& );
//extern ostream& operator<< ( ostream&, intvector& );
#endif

