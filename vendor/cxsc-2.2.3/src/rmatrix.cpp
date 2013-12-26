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

/* CVS $Id: rmatrix.cpp,v 1.14 2008/05/19 13:19:07 cxsc Exp $ */

#define _CXSC_CPP

#include "rmatrix.hpp"
#include "matrix.inl"
#include "rmatrix.inl"

namespace cxsc {
int RowLen ( const rmatrix& A )         // Length of the rows of a real matrix
  { return Ub(A,2)-Lb(A,2)+1; }         //------------------------------------

int ColLen ( const rmatrix& A )      // Length of the columns of a real matrix
  { return Ub(A,1)-Lb(A,1)+1; }      //---------------------------------------

rmatrix Id ( const rmatrix& A )                        // Real identity matrix
{                                                      //---------------------
  int i,j;
  int lbi = Lb(A,1), ubi = Ub(A,1);
  int lbj = Lb(A,2), ubj = Ub(A,2);
  rmatrix B(lbi,ubi,lbj,ubj);

  for (i = lbi; i <= ubi; i++)
    for (j = lbj; j <= ubj; j++)
      B[i][j] = (i==j) ? 1.0 : 0.0;
  return B;
}

rmatrix transp ( const rmatrix& A )                       // Transposed matrix
{                                                         //------------------
  int      n;
  rmatrix  res(Lb(A,2),Ub(A,2),Lb(A,1),Ub(A,1));

  for (n = Lb(A,1); n <= Ub(A,1); n++) Col(res,n) = Row(A,n);
  return res;
}

} // namespace cxsc


