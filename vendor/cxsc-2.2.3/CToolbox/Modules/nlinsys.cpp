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

/* CVS $Id: nlinsys.cpp,v 1.4 2008/01/23 08:39:21 cxsc Exp $ */

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
// File: nlinsys (implementation)
// Purpose: Computing enclosures for all solutions of systems of nonlinear
//    equations given by continuously differentiable functions.
// Method: Extended interval Newton Gauss-Seidel method.
// Global functions:
//    AllNLSS()      : computes enclosures for all solutions
//    AllNLSSErrMsg(): delivers an error message text
// Updates:
//    04.03.1996 : 'p = 0' eliminated in 'return' statements of 'NewtonStep'
//----------------------------------------------------------------------------
#include <string.h>         // String handling
#include <xi_ari.hpp>       // Extended interval arithmetic
#include <matinv.hpp>       // Matrix inversion
#include <nlinsys.hpp>

using namespace cxsc;
using namespace std;

static int MaxSoluNo;       // Maximum number of solutions to be computed

//----------------------------------------------------------------------------
// Error codes used in this module.
//----------------------------------------------------------------------------
const int
  NoError      = 0,  // No error occurred
  IllMaxSoluNo = 1,  // Illegal value for the maximum number of solutions
  NotAllSolus  = 2;  // Not all solutions computed

//----------------------------------------------------------------------------
// Error messages depending on the error code.
//----------------------------------------------------------------------------
char* AllNLSSErrMsg ( int Err )
{
  static char Msg[80] = "";

  switch (Err) {
    case NoError:
      break;  // Blank message
    case IllMaxSoluNo:
      sprintf(Msg,"Error: Parameter for maximum number of solutions "
                  "must lie in 1,...,%1d!",MaxCountNLSS); break;
    case NotAllSolus:
      sprintf(Msg,"Warning: Not all solutions found due to the user "
                  "limit of %1d solution(s)!",MaxSoluNo); break;
    default:
      strcpy(Msg,"Error: Code not defined!");
  }
  return(Msg);
}

//----------------------------------------------------------------------------
// Purpose: Execution of one single interval Newton Gauss-Seidel step for the
//    interval vector 'Y' and the function 'f'.
// Parameters:
//    In    : 'f'          : must be declared for the type 'GTvector' to
//                           enable the internal use of the differentiation
//                           arithmetic 'grad_ari'
//            'Y'          : starting interval
//            'JfY'        : Jacobian matrix of 'f(Y)', already computed
//                           outside of 'NewtonStep'
//            'Epsilon'    : desired relative accuracy
//    In/Out: 'V'          : enclosures 'V[i]' for the splittings
//                           generated by the Newton step
//            'p'          : number of non-empty interval vectors 'V[i]'
// Description:
//    'NewtonStep' executes the extended interval Newton Gauss-Seidel step
//    for 'Y' with result interval vector(s) 'V[i]' which can be empty.
//    'p' gives the number of non-empty interval vectors stored as vectors
//    'V[1]',...,'V[p]'.
//----------------------------------------------------------------------------
static void NewtonStep ( GTvector_FctPtr f,
                         ivector         Y,
                         imatrix&        JfY,
                         real            Epsilon,
                         imatrix&        V,
                         int&            p )
{
  const int     n = Ub(Y);
  rvector       c(n);
  ivector       fC(n), b(n), Y_minus_c(n);
  rmatrix       R(n,n);
  imatrix       A(n,n);
  int           i, i0, j, InvErr;
  idotprecision Accu;
  interval      h;
  ivector       z(2);

  c = mid(Y);  fEvalJ(f,_ivector(c),fC);         // Midpoint evaluation of 'f'
                                                 //---------------------------
  MatInv(mid(JfY),R,InvErr);                     // Invert the midpoint matrix
  if (InvErr) R = Id(R);                         //---------------------------

  A = R * JfY;  b = R * fC;         // Compute data for Gauss-Seidel step
  Y_minus_c = Y - c;                //-----------------------------------

  p = 0;  i0 = 0;                   // Initializations, A[i0,i0] contains zero
                                    //----------------------------------------
  for (i = 1; i <= n; i++ ) {                // Interval-Gauss-Seidel-step for
                                             // non-zero A[i,i] elements
                                             //-------------------------------
    if ( in(0.0,A[i][i]) || (RelDiam(Y[i]) <= Epsilon) ) {
      i0 = i;       // Largest i with 0 in A[i,i]
      continue;     // Next i
    }

    Accu = b[i];
    for (j = 1; j < i; j++) accumulate(Accu,A[i][j],Y_minus_c[j]);
    for (j = i+1; j <= n; j++) accumulate(Accu,A[i][j],Y_minus_c[j]);
    rnd(Accu,h);
    h = c[i] - h / A[i][i];

    if ( Disjoint(Y[i],h) ) { return; }                // No solution possible
                                                       //---------------------
    Y[i] = Y[i] & h;  Y_minus_c[i] = Y[i] - c[i];
  } // for (i...

  for (i = 1; i <= i0; i++ ) {               // Interval-Gauss-Seidel-step for
                                             // zero A[i,i] elements
                                             //-------------------------------
    if ( !in(0.0,A[i][i]) || (RelDiam(Y[i]) <= Epsilon) ) continue;  // Next i
                                                                     //-------
    Accu = b[i];
    for (j = 1; j < i; j++) accumulate(Accu,A[i][j],Y_minus_c[j]);
    for (j = i+1; j <= n; j++) accumulate(Accu,A[i][j],Y_minus_c[j]);
    rnd(Accu,h);
    z = Y[i] & (c[i] - h % A[i][i]);             // Extended interval division
                                                 //---------------------------
    if (z[1] == EmptyIntval())                // z[1] == z[2] == EmptyIntval()
      { return; }                             // i.e. no solution possible
                                              //------------------------------
    Y[i] = z[1];  Y_minus_c[i] = Y[i] - c[i];               // Compute new 'Y'
    if (z[2] != EmptyIntval())                              //----------------
      { p++; V[p] = Y;  V[p][i] = z[2]; }          // Store further splittings
  } // for (i...                                   //-------------------------

  p++;  V[p] = Y;
} // NewtonStep

//----------------------------------------------------------------------------
// Purpose: Recursive function for the execution of the extended interval
//    Newton Gauss_Seidel method for the function 'f'.
// Parameters:
//    In    : 'f'         : must be declared for the type 'GTvector' to
//                          enable the internal use of the differentiation
//                          arithmetic 'grad_ari'
//            'y'         : starting interval
//            'Epsilon'   : desired relative accuracy
//                          (interval diameter) of the result intervals
//            'yUnique'   : signals whether it is already verified that the
//                          actual interval 'y' contains a unique zero
//    Out   : 'SoluVector': enclosures for the zeros of 'f'
//            'InfoVector': corresponding information on the uniqueness of
//                          the zero in each of these enclosures
//    In/Out: 'SoluNo'    : represents the number of the zero computed last
//                          (in) and the total number of enclosures
//                          computed at the end of the recursion (out)
// Description:
//    The function 'XINewton()' is recursively called whenever the extended
//    interval Newton step results in a splitting of the actual interval 'y'
//    in two or more intervals, and the tolerance condition is not fulfilled
//    yet. Otherwise, the enclosures for the zeros of 'f' are stored in the
//    interval matrix 'SoluVector' row by row, the corresponding information
//    on the uniqueness of the zero in each of these enclosures is stored in
//    the integer vector 'InfoVector'. The number of enclosures computed is
//    returned in the variable 'SoluNo'. The maximum number of enclosures to
//    be computed is given by the value of the global variable 'MaxSoluNo'.
//----------------------------------------------------------------------------
static void XINewton ( GTvector_FctPtr f,
                       ivector         y,
                       real&           Epsilon,
                       int             yUnique,
                       imatrix&        SoluVector,
                       intvector&      InfoVector,
                       int&            SoluNo )
{
  if (SoluNo > MaxSoluNo) return;       // Stop due to user specified limit
                                        //---------------------------------
  const int  n = Ub(y);
  ivector    fy(n);
  rvector    dY(n);
  imatrix    Jfy(n,n);
  imatrix    V(n+1,n);
  int        i, p, k, l;
  real       my, supy;
  int        InnerIncl;

  fJEvalJ(f, y, fy, Jfy);               // Compute f(y) and Jf(y)
  if ( !in(0,fy) ) return;              // Start if 0 in f(y), else do nothing
                                        //------------------------------------
  NewtonStep(f,y,Jfy,Epsilon,V,p);      // Extended interval Newton step with
                                        // results V[i], i = 1,...,p
  if (p == 1) {                         //------------------------------------
    InnerIncl = in(V[1],y);             // Inner inclusion ===> uniqueness
    yUnique = yUnique || InnerIncl;     //--------------------------------
  }
  else
    InnerIncl = yUnique = 0;

  for (i = 1; i <= p; i++) {
    if (MaxRelDiam(V[i]) <= Epsilon) {     // No more Newton steps

      fEvalJ(f, V[i], fy);                 // Compute f(V[i])
      if ( in(0,fy) ) {                    // Store enclosure and info
        SoluNo++;                          //-------------------------

        if (SoluNo > MaxSoluNo) return;    // Stop due to user specified limit
                                           //---------------------------------
        if (SoluNo > Ub(SoluVector,1))
          { DoubleSize(SoluVector); DoubleSize(InfoVector); }
        SoluVector[SoluNo] = V[i];         // Store enclosure of the zero
        InfoVector[SoluNo] = yUnique;      // Store uniqueness info
      }                                    //----------------------------
    }
    else { // Recursive call of 'XINewton()' for interval 'V[i]'
      if ( !InnerIncl ) {                                    // Bisect the box
        yUnique = 0;                                         //---------------
        dY = diam(V[i]);
        l = 1;
        for (k = 2; k <= n; k++)
          if (dY[k] > dY[l]) l = k;
        my = mid(V[i][l]);               // Compute midpoint of l-th component
        supy = Sup(V[i][l]);             // Save supremum of l-th component
        SetSup(V[i][l],my);              // Set supremum to midpoint
                                         //-----------------------------------
        XINewton(f,V[i],Epsilon,yUnique,              // Call 'XINewton()' for
                 SoluVector,InfoVector,SoluNo);       // first half of 'V[i]'
                                                      //----------------------
        SetSup(V[i][l],supy);                   // Reset supremum to old value
        SetInf(V[i][l],my);                     // Set infimum to midpoint
      }                                         //----------------------------
      XINewton(f,V[i],Epsilon,yUnique,              // Call 'XINewton()' for
               SoluVector,InfoVector,SoluNo);       // (second half of) 'V[i]'
    } // else                                       //------------------------
  } // for
} // XINewton

//----------------------------------------------------------------------------
// Purpose: Execution of a verification step including the use of an epsilon
//    inflation.
// Parameters:
//    In    : 'f'      : function of type 'GTvector'
//    Out   : 'yUnique': returns 'true' if the verification is successful
//    In/Out: 'y'      : interval enclosure to be verified
// Description: This function checks the uniqueness of the zero enclosed in
//    the variable 'y' by an additional verification step including the use
//    of an epsilon inflation of the iterates.
//----------------------------------------------------------------------------
// static void VerificationStep ( GTvector_FctPtr f, ivector& y, int& yUnique )
static void VerificationStep ( GTvector_FctPtr f, const imatrix_subv& y, int& yUnique )
{
  const int kmax = 10, n = Ub(y);
  ivector   yIn(n), fY(n), yOld(n);
  imatrix   JfY(n,n);
  imatrix   V(n+1,n);
  rvector   m(n);
  int       k, p;
  real      eps;

  yIn = y;  k = 0;  eps = 0.25;                             // Initializations
  yUnique = 0;                                              //----------------
  while ( !yUnique && (k < kmax) ) {     // Do kmax loops to achieve inclusion
    yOld = Blow(y,eps);                  // Epsilon inflation of 'y'
                                         //-----------------------------------
    k++;  fJEvalJ(f, yOld, fY, JfY);     // Perform interval Newton step
    NewtonStep(f, yOld, JfY, 0.0, V, p); //-----------------------------------

    if (p != 1) break;                             // No verification possible
                                                   //-------------------------
    if (V[1] == yOld)                              // Increase 'eps'
      eps = eps * 8.0;                             //-------------------------
    else
    { for (int ii=Lb(y); ii<=Ub(y); ii++)
	y[ii] = V[1][ii];
        yUnique = in(y,yOld);
    }                                       // Inner inclusion ===> uniqueness
  }                                         //--------------------------------

  if (!yUnique)
      for (int ii=Lb(y); ii<=Ub(y); ii++)
                     y[ii] = yIn[ii];
} // VerificationStep

//----------------------------------------------------------------------------
// Purpose: Computation of enclosures for all zeros of a continuously
//    differentiable multi-dimensional, vector-valued function.
// Parameters:
//    In : 'f'               : objective function, must be declared for the
//                             'GTvector' to enable the internal use of
//                             the differentiation arithmetic 'grad_ari'.
//         'Start'           : starting interval.
//         'Epsilon'         : desired relative accuracy
//                             (interval diameter) of the result intervals.
//    Out: 'SoluVector'      : stores and returns the enclosures for the
//                             zeros of 'f'.
//         'InfoVector'      : corresponding information on the uniqueness
//                             of the zeros in each of these enclosures.
//         'NumberOfSolus'   : number of enclosures computed.
//         'Err'             : error code.
//         'MaxNumberOfSolus': maximum number of zeros to be computed
//                             (default value: 'MaxCountNLSS' = compute all)
// Description:
//    The enclosures for the zeros of 'f' are computed by calling function
//    'XINewton'. Then an additional verification step is applied to those
//    enclosures which have not been verified. If an error occurs the value
//    of 'Err' is different from 0. The output parameters 'SoluVector' and
//    'InfoVector' are automatically resized to standard index range with
//    lower index bounds 1. The result arrays 'SoluVector' and 'InfoVector'
//    are automatically resized to standard index range with lower index
//    bounds 1. The maximum number of zeros which can be computed is given by
//    'MaxNumberOfSolus'. It is bounded by 'MaxCountNLSS'. If your system can
//    handle more than 'MaxCountNLSS' zeros, you can increase its value.
//----------------------------------------------------------------------------
void AllNLSS ( GTvector_FctPtr f,
               ivector         Start,
               real            Epsilon,
               imatrix&        SoluVector,
               intvector&      InfoVector,
               int&            NumberOfSolus,
               int&            Err,
               int             MaxNumberOfSolus )
{
  int     MinSize, i, n = VecLen(Start);
  real    MinEpsilon;

  if (1 <= MaxNumberOfSolus && MaxNumberOfSolus <= MaxCountNLSS) {
    MaxSoluNo = MaxNumberOfSolus;   // Initialize global static variable

    // Set index range of the start vector to standard index range with
    // lower bound 1 and resize the result arrays to 'MinSize' components.
    //--------------------------------------------------------------------
    SetLb(Start,1);

    MinSize = (MaxNumberOfSolus == MaxCountNLSS) ? 10 : MaxNumberOfSolus;

    Resize(SoluVector,MinSize,n);
    Resize(InfoVector,MinSize);

    // Start extended interval Newton method
    //--------------------------------------
    Err = NoError;  NumberOfSolus = 0;

    MinEpsilon = succ(1.0) - 1.0;       // Relative machine accuracy (1 ulp)
    SetLb(Start,1);                     // Change to standard bounds 1..n
                                        //----------------------------------
    if (Epsilon < MinEpsilon)
      Epsilon = MinEpsilon;             // Set 'Epsilon' to 1 ulp accuracy

    XINewton(f,Start,Epsilon,0,SoluVector,InfoVector,NumberOfSolus);

    if (NumberOfSolus > MaxNumberOfSolus)
      { Err = NotAllSolus;  NumberOfSolus = MaxNumberOfSolus; }
  }
  else {
    Err = IllMaxSoluNo;
    NumberOfSolus = 0;
  }

  // Resize the result matrix and the info vector to appropriate
  // number of rows if no error has occurred. Otherwise, resize
  // them to minimum dimensions with undefined value.
  //------------------------------------------------------------
  if (NumberOfSolus > 0) {
    Resize(SoluVector,NumberOfSolus,n);
    Resize(InfoVector,NumberOfSolus);
  }
  else {
    Resize(SoluVector,1,1);     // Values undefined
    Resize(InfoVector,1);       //-----------------
  }

  for (i = 1; i <= NumberOfSolus; i++)                   // Verification step
    if (InfoVector[i] == 0)                              // for the enclosures
      VerificationStep(f,SoluVector[i],InfoVector[i]);   //-------------------
} // AllNLSS

