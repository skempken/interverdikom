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
// Example: Automatic differentiation for Hessians
// This is an implementation of Newton's Method for computing a stationary
// point of a twice continuously differentiable multi-dimensional function.
//
//    given:      the function f(x) and the starting value x0
//    iteration:  x[n+1] := x[n] - InvHf(x[n])*Gf(x[n]) , n = 0,1,...
//
// where InvHf(x) denotes the inverse of the Hessian matrix of f(x).
// All real operations are replaced by interval operations, all function and
// derivative evaluations are calculated by differentiation arithmetic.
//----------------------------------------------------------------------------
#include <matinv.hpp>       // Matrix inversion
#include <hess_ari.hpp>     // Hessian differentiation arithmetic


using namespace cxsc;
using namespace std;


const int
  fDim = 2,
  nmax = 100;

interval  fx;
ivector   x(fDim), Gfx(fDim);
imatrix   Hfx(fDim,fDim);
rmatrix   InvHfx(fDim,fDim);
int       n, Error;

HessType f ( const HTvector& x )
{
  return 100.0*sqr(x[2] - sqr(x[1])) + sqr(x[1] - 1.0);
}

int main ( )
{
  cout << SetPrecision(23,15) << Scientific;   // Output format

  cout << "Newton-Method for finding a stationary point of Rosenbrock's"
       << endl
       << "function:  f(x) = 100*sqr(x[2] - sqr(x[1])) + sqr(x[1] - 1)"
       << endl << endl;
  cout << "Starting vector x = "; cin >> x;
  cout << endl << "Iteration:" << endl;
  fghEvalH(f,x,fx,Gfx,Hfx);
  n = 0;
  do {
    n++;
    cout << "x: " << endl << x << "Gf(x): " << endl << Gfx << endl;
    MatInv(mid(Hfx),InvHfx,Error);
    if (!Error) {
      x = x - InvHfx * Gfx;
      fghEvalH(f,x,fx,Gfx,Hfx);
    }
  } while( !( (in(0.0,Gfx[1]) && in(0.0,Gfx[2])) || (n >= nmax) || Error ) );

  if (!Error) {
    cout << endl
         << "Stationary point:  " << endl << x
         << "Gradient value:    " << endl << Gfx << endl
         << "Expected solution: " << endl
         << " 1.0 " << endl << " 1.0 " << endl;
  }
  else
    cout << MatInvErrMsg(Error) << endl;

  return 0;
}
