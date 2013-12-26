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
#include "mvci_util.hpp"

using namespace cxsc;
using namespace std;

namespace cxscx {

int in ( const civector& x, const civector& y )          // Inner inclusion for two civectors
{                                          //---------------------------------
  int i = Lb(x), n = Ub(x), ok = 1;

  while (ok && i <= n) { ok = in(x[i],y[i]); i++; }
  return ok;
}
/*
int in ( int x, civector& y )     // Inner inclusion of an integer in a civector
{                                //-------------------------------------------
  int    i = Lb(y), n = Ub(y), ok = 1;
  double d = x;

  while (ok && i <= n) { ok = in(d,y[i]); i++; }
  return ok;
}
*/
civector Blow ( const civector& x, real eps )                     // Epsilon deflation
{                                                         //------------------
  int     i;
  civector h(Lb(x),Ub(x));

  for (i = Lb(x); i <= Ub(x); i++) h[i] = Blow(x[i],eps);
  return h;
}
/*
int Disjoint ( civector& a, civector& b )             // Test for disjointedness
{                                                   //------------------------
  int al = Lb(a), au = Ub(a), bl = Lb(b);
  int disjointed, i, d;

  d = bl - al;

  i = al;
  disjointed = 0;
  do {
    if (Disjoint(a[i],b[i+d]))
      disjointed = 1;
    else
      i++;
  } while ( !(disjointed || i > au) );
  return disjointed;
}
*/
/*imatrix Id ( imatrix& A )                          // Interval identity matrix
{                                                  //-------------------------
  int i,j;
  int lbi = Lb(A,1), ubi = Ub(A,1);
  int lbj = Lb(A,2), ubj = Ub(A,2);
  imatrix B(lbi,ubi,lbj,ubj);

  for (i = lbi; i <= ubi; i++)
    for (j = lbj; j <= ubj; j++)
      B[i][j] = _interval( (i==j) ? 1.0 : 0.0 );
  return B;
}*/

int Zero ( civector& x )                               // Check for zero vector
{                                                     //----------------------
  int i, ok;
  for (i = Lb(x), ok = 1; i <= Ub(x) && ok; i++) ok = (x[i] == 0.0);
  return ok;
}

cvector mid ( civector& v )                              // Vector of midpoints
{                                                       //--------------------
  int i;
  int l = Lb(v), u = Ub(v);
  cvector w(l,u);

  for (i = l; i <= u; i++) w[i] = mid(v[i]);
  return w;
}

cmatrix mid ( cimatrix& A )                              // Matrix of midpoints
{                                                       //--------------------
  int i,j;
  int lbi = Lb(A,1), ubi = Ub(A,1);
  int lbj = Lb(A,2), ubj = Ub(A,2);
  cmatrix B(lbi,ubi,lbj,ubj);

  for (i = lbi; i <= ubi; i++)
    for (j = lbj; j <= ubj; j++)
      B[i][j] = mid(A[i][j]);
  return B;
}
/*
real MaxRelDiam ( const ivector& v )                    // Maximum relative diameter
{                                                 //--------------------------
  real r;
  int  i, l=Lb(v), u=Ub(v);

  r = 0.0;
  for (i = l; i <= u; i++)
    if (RelDiam(v[i]) > r) r = RelDiam(v[i]);
  return r;
}

real MaxRelDiam ( const ivector_slice& v )                    // Maximum relative diameter
{                                                 //--------------------------
  real r;
  int  i, l=Lb(v), u=Ub(v);

  r = 0.0;
  for (i = l; i <= u; i++)
    if (RelDiam(v[i]) > r) r = RelDiam(v[i]);
  return r;
}

real MaxRelDiam ( const imatrix_subv& v )                    // Maximum relative diameter
{                                                 //--------------------------
  real r;
  int  i, l=Lb(v), u=Ub(v);

  r = 0.0;
  for (i = l; i <= u; i++)
    if (RelDiam(v[i]) > r) r = RelDiam(v[i]);
  return r;
}

//----------------------------------------------------------------------------
// Checks if the diameter of the interval vector 'v' is less or equal to 'n'
// ulps. Ulp is an abbreviation for: units in the last place of the mantissa.
//----------------------------------------------------------------------------
int UlpAcc ( ivector& v, int n )
{
  int k, upper;

  for (k = Lb(v), upper = Ub(v); (k < upper) && UlpAcc(v[k],n); k++);
  return UlpAcc(v[k],n);
}
*/
int VecLen ( civector& v )                       // Length of a interval vector
  { return Ub(v)-Lb(v)+1; }                     //----------------------------

int RowLen ( cimatrix& A )           // Length of the rows of a interval matrix
  { return Ub(A,2)-Lb(A,2)+1; }     //----------------------------------------

int ColLen ( cimatrix& A )        // Length of the columns of a interval matrix
  { return Ub(A,1)-Lb(A,1)+1; }  //-------------------------------------------

// The 'DoubleSize' functions double the number of rows of a matrix
// or double the length of a vector preserving existing components.
//------------------------------------------------------------------
void DoubleSize ( civector& x )
{
  int n = Lb(x);
  Resize(x,n,2*Ub(x)-n+1);
}

void DoubleSize ( cimatrix& A )
{
  int n = Lb(A,1);
  Resize(A,n,2*Ub(A,1)-n+1,Lb(A,2),Ub(A,2));
}

}
