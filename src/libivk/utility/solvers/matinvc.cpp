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
// File: matinvc (implementation)
// Purpose: Computation of an approximate inverse of a complex square matrix.
// Method: LU decomposition applying Crout's algorithm.
// Global functions:
//   MatInvc()      : matrix inversion
//   MatInvcErrMsg(): to get an error message text
//----------------------------------------------------------------------------
// In the comments below the notations #*(...) and ##(...) are used to indi-
// cate the evaluation of the expression specified in round brackets using
// the exact scalar product. I.e. each component of the result is computed
// with only one final rounding. The symbol #* holds for rounding to nearest
// whereas ## holds for rounding to the smallest enclosing interval. An exact
// scalar product may be implemented using dotprecision accumulators.
//----------------------------------------------------------------------------
#include <cstring>
#include "matinvc.hpp"

using namespace cxsc;
using namespace std;

namespace ivk {

//----------------------------------------------------------------------------
// Error codes used in this module.
//----------------------------------------------------------------------------
const int
  NoError      = 0,     // No error occurred
  NotSquare    = 1,     // Matrix to be inverted is not square
  Singular     = 2;     // Matrix to be inverted is probably singular

//----------------------------------------------------------------------------
// Error messages depending on the error code.
//----------------------------------------------------------------------------
char* MatInvcErrMsg ( int Err )
{
  static char Msg[80] = "";

  if (Err != NoError) {
    char Hlp[60];

    switch (Err) {
      case NotSquare:
        sprintf(Hlp,"Matrix to be inverted is not square");           break;
      case Singular:
        sprintf(Hlp,"Inversion failed, matrix is probably singular"); break;
      default:
        strcpy(Hlp,"Code not defined");
    }
    sprintf(Msg,"Error: %s!",Hlp);
  }
  return(Msg);
} // MatInvErrMsg

//----------------------------------------------------------------------------
// Purpose: The function 'MatInvc()' may be used for the computation of an
//    approximate inverse of a complex square matrix.
// Parameters:
//    In : 'AC'  : matrix to be inverted
//    Out: 'R'  : approximate inverse
//         'Err': error code
// Description:
//    Inversion of a regular matrix AC stored in 'AC' using LU decomposition.
//    For LU decomposition, formally a permutation matrix P is determined so
//    that the product P*A may be decomposed into a lower-triangular matrix L
//    and an upper-triangular matrix U with P*AC = L*U. The diagonal elements
//    of L are set to 1. Using Crout's algorithm, the elements of both matri-
//    ces L and U are stored by temporary overwriting a copy of the input
//    matrix 'AC'. The permutation matrix P is not explicitly generated. The
//    indices of row interchanges are stored in the index vector 'p' instead.
//    The i-th element of P*b may be accessed indirectly using the p[i]-th
//    entry of 'b'. Accurate expressions are used to avoid cancellation
//    errors. The k-th column of the inverse R of P*AC is computed by
//    forward/backward substitution with the k-th unit vector e_k as the
//    right-hand side of the system: U*y = P*e_k ==> y, L*x = y ==> x. For
//    error codes, see above.
//----------------------------------------------------------------------------
void MatInvc ( cmatrix AC, cmatrix& R, int& Err )
{
  const real
    Tiny = 1E-200;          // A divisor less than 'Tiny' is handled like zero

  cdotprecision Accuc;                     // Long accumulator
  real    Max, Temp;
  complex Tempc;                           // Help variables
  int     p1 = Lb(AC,1), q1 = Lb(AC,2);    // Lower bounds of 'AC'.
  int     pn = Ub(AC,1), qm = Ub(AC,2);    // Upper bounds of 'AC'.
  int     n = pn-p1+1;                     // Length of the rows of 'AC'
  int     m = qm-q1+1;                     // Length of the columns of 'AC'
  int     i, j, k, l, kk;                  // For loops

  Err = NoError;                           // Initialization

  if (n != m)                              // Error: 'AC' is not square
    { Err = NotSquare; return; }

  // Normalize index range of 'AC' to standard range (1..n,1..n)
  //-----------------------------------------------------------
  SetLb(AC,ROW,1);  SetLb(AC,COL,1);
  Resize(R,p1,pn,q1,qm);                   // Resize 'R' to same shape as 'AC'

  if (n == 2) {                            // Special case: (2,2)-matrix
    Accuc = 0.0;                           // Compute the determinant of 'AC'
    accumulate(Accuc, AC[1][1],AC[2][2]);
    accumulate(Accuc,-AC[2][1],AC[1][2]);
    Tempc = rnd(Accuc);

    if (abs(Tempc) < Tiny)                  // Error: 'AC' is probably singular
      { Err = Singular; return; }

    R[p1][q1] =  AC[2][2] / Tempc;  R[p1][qm] = -AC[1][2] / Tempc;
    R[pn][q1] = -AC[2][1] / Tempc;  R[pn][qm] =  AC[1][1] / Tempc;
    return;
  }

  // Start usual case: Dimension of 'AC' > 2
  //----------------------------------------
  cvector vc(n), xc(n);        // Help vectors
  int*    p = new int [n+1];   // Dynamic array of type integer
                               // Note: p[0] not used !

  for (i = 1; i <= n; i++)  p[i] = i; // Initializing permutation vector

  // Start LU factorization
  //-----------------------
  i = 1;
  while ( (Err == NoError) && (i <= n) ) {
    // Compute the numerators of those elements of the i-th column
    // of L which are not updated so far and store them in 'vc'.
    //------------------------------------------------------------
    for (k = i; k <= n; k++) {   // vc_k = #*(AC_ki - sum(j=1(1)i-1,AC_kj*AC_ji))
      Accuc = AC[k][i];          //----------------------------------------------
      for (j = 1; j < i; j++) accumulate(Accuc,-AC[k][j],AC[j][i]);
      vc[k] = rnd(Accuc);
    }

    // Look for the column pivot
    //--------------------------
    j = i;  Max = abs(vc[i]);
    for (k = i+1; k <= n; k++)
      if ( (Temp = abs(vc[k])) > Max ) { j = k; Max = Temp; }

    // Swap rows of 'AC' and 'vc', store the permutation in 'p'
    //---------------------------------------------------------
    if (j != i) {
      xc = AC[i];     AC[i] = AC[j];  AC[j] = xc;
      k = p[i];     p[i] = p[j];  p[j] = k;
      Tempc = vc[i];  vc[i] = vc[j];  vc[j] = Tempc;
    }

    if (Max < Tiny)                   // Pivot element < 'Tiny', inversion
      { Err = Singular; return; }     // failed, matrix 'AC' assumed to be
                                      // singular
    Tempc = vc[i];
    AC[i][i] = Tempc;    // Update the diagonal element of U

    // Update U's row and L's column elements
    //---------------------------------------
    for (k = i+1; k <= n; k++) { // AC_ik = #*(AC_ik - sum(j=1(1)i-1,AC_ij*AC_jk))
      Accuc = AC[i][k];          //-----------------------------------------------
      for (j = 1; j < i; j++) accumulate(Accuc,-AC[i][j],AC[j][k]);
      AC[i][k] = rnd(Accuc);
      AC[k][i] = vc[k] / Tempc;
    }
    i++;
  } // while

  // Now 'AC' is overwritten with the subdiagonal elements of L in its
  // lower left triangle and with the elements of U in its diagonal and
  // its upper right triangle. The elements of the inverse matrix are
  // computed column by column using forward/backward substitution.
  //-------------------------------------------------------------------
  for (k = 1; k <= n; k++) {
    // Forward substitution: L*x = P*e_k, where e_k is the k-th unit
    // vector. Note: If P*e_k has m leading zeros, this results in
    // xc_i = 0 for 1,..,l-1 and xc_l = 1. Thus, forward substitution
    // starts at index l+1.
    //---------------------------------------------------------------
    l = 1;
    while (p[l] != k) { xc[l] = 0.0; l++; }
    xc[l] = 1.0;
    for (i = l+1; i <= n; i++) {    // xc_i = - #*(sum(j=1(1)i-1,AC_ij*xc_j))
      Accuc = 0.0;                  //---------------------------------------
      for (j = l; j < i; j++) accumulate(Accuc,AC[i][j],xc[j]);
      xc[i] = -rnd(Accuc);
    }

    // Backward substitution: U * xc = xc, where the right-hand side is
    // the result of the forward substitution. It will be overwritten
    // by the solution of the system, the k-th column of the inverse
    // matrix.
    //-----------------------------------------------------------------
    kk = q1+k-1;                 // Index offset for the k-th column of R
    for (i = n; i >= 1; i--) {   // xc_i = #*(xc_i-sum(j=i+1(1)n,AC_ij*xc_j)/AC_ii)
      Accuc = xc[i];             //------------------------------------------------
      for (j = i+1; j <= n; j++) accumulate(Accuc,-AC[i][j],xc[j]);
      xc[i] = rnd(Accuc) / AC[i][i];
      R[p1+i-1][kk] = xc[i];     // Remember index offset !
    }
  } // for (k = 1,...

  delete [] p;   // Free dynamically allocated memory
} // MatInvc

}

