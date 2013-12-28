//============================================================================
//  - Changed by D. Fausten
//  - Altered by A. Mika
//  File based on: ilinsys.hpp
//
//  Changes (ilinsys.hpp):
//      Instead of a real matrix and a real right-hand side use interval
//      matrix and right hand side in the system Ax=b.
//
//  Changes to CILinSys.hpp:
//      A wrapping class was created
//
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
//
//
// see the "Disclaimer / Legal Matters" of the book (page iv).
//
//============================================================================





//----------------------------------------------------------------------------
// Purpose: Computation of a verified solution of a square linear system of
//    equations A*x = b with full interval matrix A and interval right-hand
//    side b.
// Method: Transformation of A*x = b to fixed-point form and applying an
//    interval residual iteration.
// Global functions:
//    ILinSolve()      : to get a verified enclosure of the solution (two
//                       versions)
//    ILinSolveErrMsg(): to get an error message text
//----------------------------------------------------------------------------
// In the comments below the notations #*(...) and ##(...) are used to indi-
// cate the evaluation of the expression specified in round brackets using
// the exact scalar product. I.e. each component of the result is computed
// with only one final rounding. The symbol #* holds for rounding to nearest
// whereas ## holds for rounding to the smallest enclosing interval. An exact
// scalar product may be implemented using dotprecision accumulators.
//----------------------------------------------------------------------------

#include <cstring>
#include <mvi_util.hpp>     // Interval matrix/vector utility functions
#include <cimatrix.hpp>

#include "ILinSys.hpp"       // solver declaraiton


using namespace cxsc;
using namespace std;

namespace ivk {

//----------------------------------------------------------------------------
// Error codes used in this module.
//----------------------------------------------------------------------------

#define NOERROR       0   // No error occurred
#define NOTSQUARE     1   // System to be solved is not square
#define DIMENSIONERR  2   // Dimensions of A and b are not compatible
#define INVFAILED     3   // System is probably singular
#define VERIVFAILED   4   // Verification failed, system is probably
                          // ill-conditioned

//----------------------------------------------------------------------------
// Error messages depending on the error code.
//----------------------------------------------------------------------------
char* ILinSys::ILinSolveErrMsg ( int Err )
{
	static char Msg[80] = "";

	if (Err != NOERROR)
	{
		char Hlp[60];

		switch (Err)
		{
			case NOTSQUARE:
				strcpy(Hlp,"System to be solved is not square"); break;
			case DIMENSIONERR:
				strcpy(Hlp,"Dimensions of A and b are not compatible"); break;
			case INVFAILED:
				strcpy(Hlp,"System is probably singular"); break;
			case VERIVFAILED:
				strcpy(Hlp,"Verification failed, system is probably ill-conditioned");
			break;
			default:
				strcpy(Hlp,"Code not defined");
		}

		sprintf(Msg,"Error: %s!",Hlp);
	}

	return(Msg);
} // ILinSolveErrMsg



//----------------------------------------------------------------------------
// Purpose: The function 'ILinSolve()' computes a verified solution of a
//    square linear system of equations A*x=b without returning a condition
//    number estimate.
// Parameters:
//    In : 'A'  : matrix of the system, passed as reference
//                parameter to save time for copying it
//         'b'  : right-hand side of the system, passed as
//                reference parameter to save time for copying it
//    Out: 'xx' : enclosure of the unique solution
//         'Err': error code
// Description: Calls 'ILinSolveMain()' for solving the linear system with the
//    flag 'ComputeCond' not set.
//----------------------------------------------------------------------------
void ILinSys::ILinSolve ( const imatrix& A, const ivector& b, ivector& xx, int& Err )
{
	real DummyCond;         // Dummy parameter for call of 'ILinSolveMain()'
	ILinSolveMain( A, b, xx, DummyCond, 0, Err);
}







//----------------------------------------------------------------------------
// Purpose: The function 'ILinSolve()' computes a verified solution of a
//    square linear system of equations A*x=b and returns a condition
//    number estimate.
// Parameters:
//    In : 'A'   : matrix of the system, passed as reference
//                 parameter to save time for copying it
//         'b'   : right-hand side of the system, passed as
//                 reference parameter to save time for copying it
//    Out: 'xx'  : enclosure of the unique solution
//         'Cond': condition number estimate
//         'Err' : error code
// Description: Calls 'ILinSolveMain()' for solving the linear system with the
//    flag 'ComputeCond' set.
//----------------------------------------------------------------------------
void ILinSys::ILinSolve ( const imatrix& A, const ivector& b, ivector& xx, real& Cond, int& Err )
{
	ILinSolveMain( A, b, xx, Cond, 1, Err);
}







//----------------------------------------------------------------------------
// Purpose: The function 'CILinSolvedirekt()' computes a verified solution of
//    a square linear complex interval system of equations A*x=b without
//    returning a condition number estimate.
// Parameters:
//    In : 'AC' : matrix of the system, passed as reference
//                parameter to save time for copying it
//         'bc' : right-hand side of the system, passed as
//                reference parameter to save time for copying it
//    Out: 'xxc': enclosure of the unique solution
//         'Err': error code
// Description: Transforms the system Ax = b into A'x = b', the corresponding
//    system with real intervals. Calls 'ILinSolveMain()' for solving the
//    linear system with the flag 'ComputeCond' not set.
//----------------------------------------------------------------------------
void ILinSys::CILinSolveIndirekt ( const cimatrix& AC, const civector& bc,
                                    civector& xxc, int& Err )
{
	real DummyCond;         // Dummy parameter for call of 'ILinSolveMain()'
	int     n;                 // Length of the columns of 'AC'
	int     m;                 // Length of the rows of 'AC'
	int     k;                 // Length of the vector 'bc'
	int     ic = 1;
	imatrix A_Re, A_Im;
	ivector b_Re, b_Im, x_Re, x_Im;

	A_Re = cxsc::Re(AC);
	A_Im = cxsc::Im(AC);

	n = ColLen(A_Re);
	m = RowLen(A_Re);
	k = m;

	Resize(b_Re, k);
	Resize(b_Im, k);
	Resize(x_Re, k);
	Resize(x_Im, k);

	for (int i = 1; i <= k; i++)
	{
		b_Re[i] = Re(bc[i]);
		b_Im[i] = Im(bc[i]);
	}

	imatrix A(2*n,2*m);
	ivector b(2*k), xx(2*k);

	for (int i = 1; i <= 2*n; i++)
	{
		for (int j = 1; j <= 2*m; j++)
		{
			if (i % 2 == 1)
				if (j % 2 == 1)
				  A[i][j] = A_Re[i/2+1][j/2+1];
				else
				  A[i][j] = -A_Im[i/2+1][j/2];
			else
				if (j % 2 == 1)
					A[i][j] = A_Im[i/2][j/2+1];
				else
					A[i][j] = A_Re[i/2][j/2];
		}
	}

	for (int i = 1; i <= 2*k; i++)
	{
		if (i % 2 == 1)
		{
			xx[i] = x_Re[i/2+1];
			b[i] = b_Re[i/2+1];
		}
		else
		{
			xx[i] = x_Im[i/2];
			b[i] = b_Im[i/2];
		}
	}

	ILinSolveMain(A,b,xx,DummyCond,0,Err);

	if (!Err)
	{
		ic = 1;
		for (int i = 1; i <= 2*k; i++)
		{
			if (i % 2 == 1)
			Re(xxc[ic]) = xx[i];
			else
			{
				Im(xxc[ic]) = xx[i];
				ic++;
			}
		}
	}

}





//----------------------------------------------------------------------------
// Purpose: The function 'CILinSolve()' computes a verified solution of a
//    square linear complex interval system of equations A*x=b and returns a
//    condition number estimate.
// Parameters:
//    In : 'A'   : matrix of the system, passed as reference
//                 parameter to save time for copying it
//         'b'   : right-hand side of the system, passed as
//                 reference parameter to save time for copying it
//    Out: 'xx'  : enclosure of the unique solution
//         'Cond': condition number estimate
//         'Err' : error code
// Description: Transforms the system Ax = b into A'x = b', the corresponding
//    system with real intervals. Calls 'ILinSolveMain()' for solving the
//    linear system with the flag 'ComputeCond' set.
//----------------------------------------------------------------------------
void ILinSys::CILinSolveIndirekt ( const cimatrix& AC, const civector& bc, civector& xxc,
                          real& Cond, int& Err )
{
	int     n;                 // Length of the columns of 'AC'
	int     m;                 // Length of the rows of 'AC'
	int     k;                 // Length of the vector 'bc'
	int     ic = 1;
	imatrix A_Re, A_Im;
	ivector b_Re, b_Im, x_Re, x_Im;

	A_Re = Re(AC);
	A_Im = Im(AC);

	n = ColLen(A_Re);
	m = RowLen(A_Re);
	k = m;

	Resize(b_Re, k);
	Resize(b_Im, k);
	Resize(x_Re, k);
	Resize(x_Im, k);

	for (int i = 1; i <= k; i++)
	{
		b_Re[i] = Re(bc[i]);
		b_Im[i] = Im(bc[i]);
	}

	imatrix A(2*n,2*m);
	ivector b(2*k), xx(2*k);

	for (int i = 1; i <= 2*n; i++)
	{
		for (int j = 1; j <= 2*m; j++)
		{
			if (i % 2 == 1)
			if (j % 2 == 1)
				A[i][j] = A_Re[i/2+1][j/2+1];
			else
				A[i][j] = -A_Im[i/2+1][j/2];
			else
				if (j % 2 == 1)
					A[i][j] = A_Im[i/2][j/2+1];
				else
					A[i][j] = A_Re[i/2][j/2];
		}
	}


	for (int i = 1; i <= 2*k; i++)
	{
		if (i % 2 == 1)
		{
			xx[i] = x_Re[i/2+1];
			b[i] = b_Re[i/2+1];
		}
		else
		{
			xx[i] = x_Im[i/2];
			b[i] = b_Im[i/2];
		}
	}

	ILinSolveMain(A,b,xx,Cond,1,Err);

	if (!Err)
	{
		ic = 1;
		for (int i = 1; i <= 2*k; i++)
		{
			if (i % 2 == 1)
				Re(xxc[ic]) = xx[i];
			else
			{
				Im(xxc[ic]) = xx[i];
				ic++;
			}
		}
	}

}





//----------------------------------------------------------------------------
// Computes an upper bound for the maximum norm of a real matrix 'M'.
//----------------------------------------------------------------------------
/*static*/ real ILinSys::MaxNorm ( const rmatrix& M )
{
	int          i, j;
	real         Max, Tmp;
	dotprecision Accu;

	Max = 0.0;
	for (i = Lb(M,1); i <= Ub(M,1); i++)
	{
		// Compute Tmp = #>( sum(j=1(1)n,|M_ij|) )
		//----------------------------------------
		Accu = 0.0;
		for (j = Lb(M,2); j <= Ub(M,2); j++)
			Accu += abs(M[i][j]);
		Tmp = rnd(Accu,RND_UP);
		if (Tmp > Max) Max = Tmp;
	}
	return Max;
} // MaxNorm





//----------------------------------------------------------------------------
// The vectors x and y are successive approximations for the solution of a
// linear system of equations computed by iterative refinement. If a compo-
// nent of y is diminished by more than 'Factor', it is a good candidate for
// a zero entry. Thus, it is set to zero.
//----------------------------------------------------------------------------
/*static*/ void ILinSys::CheckForZeros ( rvector& x, rvector& y )
{
	const real Factor = 1E+5;
	int i;

	for (i = Lb(y); i <= Ub(y); i++)
		if ( abs(y[i])*Factor < abs(x[i]) ) y[i] = 0.0;
}



//----------------------------------------------------------------------------
// The vectors x and y are successive iterates. The function returns true if
// the relative error of all components x_i and y_i is <= 10^(-12), i.e. y_i
// has about 12 correct decimals. If x_i or y_i vanishes, the relative error
// is implicitly set to zero.
//----------------------------------------------------------------------------
/*static*/ int ILinSys::Accurate( rvector& x, rvector& y )
{
	const real Delta = 1E-12;					// Relative error bound (5E-8)
	int        i, n, ok;						//, signx, signy;
	real       abs_yi;

	i = Lb(y);
	n = Ub(y);

	do
	{
		if (sign(x[i])*sign(y[i]) <= 0)			// Relative error set to 0
			ok = 1;
		else
		{
			abs_yi = abs(y[i]);					// Relative error > Delta ?
			ok = (abs(y[i] - x[i]) <= Delta * abs_yi );
		}
		i++;
	} while (ok && (i <= n));

	return ok;
} // Accurate





//----------------------------------------------------------------------------
// This function 'VerificationStep()' performs the iteration
// [y] = Blow([x],Eps), [x] = [z] + [C]*[y] for k = 1,2,... until the new
// iterate [x] lies in the interior of [y] or until the maximum number of
// iterations is exceeded. The flag 'IsVerified' is set if an inclusion in
// the interior could be established.
//----------------------------------------------------------------------------
/*static*/ void ILinSys::VerificationStep ( ivector& xx, ivector& zz,
                               imatrix& C,  int& IsVerified )
{
	const int  MaxIter = 3;          // Maximal number of iteration steps
	const real Epsilon = 1000.0;     // Factor for the epsilon inflation

	int     p;
	ivector yy(Lb(xx),Ub(xx));

	xx = zz; p = 0;                      // Initialize:  [x] = [z]

	do
	{
		yy = Blow(xx,Epsilon);             // Epsilon inflation
		xx = zz + C*yy;                    // New iterate: [x] = [z]+[C]*[y]
		IsVerified = in(xx,yy);            // Inclusion in the interior?
		p++;
	} while (!IsVerified && (p < MaxIter));

}


//----------------------------------------------------------------------------
// Purpose: The function 'ILinSolveMain()' computes a verified solution of a
//    square linear system of equations A*x=b.
// Parameters:
//    In : 'A'          : matrix of the system, passed as reference
//                        parameter to save time for copying it
//         'b'          : right-hand side of the system, passed as
//                        reference parameter to save time for copying it
//         'ComputeCond': flag signalling whether a condition number
//                        estimate is to be computed
//    Out: 'xx'         : enclosure of the unique solution, resized to
//                        standard index range with lower index bound 1
//         'Cond'       : condition number estimate
//         'Err'        : error code
// Description: An approximate inverse 'R' of 'mid(A)' is computed by calling
//   function 'MatInv()'. Then an approximate solution 'x' is computed
//   applying a conventional real residual iteration. For the final verifica-
//   tion, an interval residual iteration is performed. An enclosure of the
//   unique solution is returned in the interval vector 'xx'. The function
//   also returns a condition number estimate 'Cond' if the flag 'ComputeCond'
//   is set. 'Cond' is initialized by -1. A negative value for 'Cond' signals
//   that an estimate could not be computed.
//----------------------------------------------------------------------------
/*static*/ void ILinSys::ILinSolveMain ( imatrix  A, ivector b, ivector& xx,
                                       real& Cond, int ComputeCond, int& Err )
{
	const int MaxResCorr = 10;			// Maximal number of real residual corrections

	int     n = ColLen(A);              // Length of the columns of 'A'
	int     m = RowLen(A);              // Length of the rows of 'A'
	int     IsVerified, i, j, k;
	int     bLow, ARowLow, AColLow;     // Lower index bounds od 'A' and 'b'
	rmatrix R;                          // To store the inverse of mid('A')

	Cond = -1.0;                        // Initial value for the condition

	if (n != m)                         // Error: 'A' is not square
	{
		Err = NOTSQUARE;
		return;
	}

	if (n != VecLen(b))                 // Error: Dimensions of 'A' and 'b'
	{
		Err = DIMENSIONERR;
		return;
	}									// are not compatible

	MatInv( mid(A),R,Err );

	if ( Err != NOERROR )               // Error: Inversion failed
    {
		Err = INVFAILED;
		return;
	}

	// Start algorithm
	//----------------
	rvector       x(n), y(n), d(n);     // Allocate dynamic arrays
	ivector       yy(n), zz(n), dd(n);
	imatrix       C(n,n);
	dotprecision Accu;                  // Allocate accumulators
	idotprecision IAccu;

	if (ComputeCond)                    // Compute condition number
		Cond = mulu(MaxNorm(mid(A)),MaxNorm(R)); //-------------------------

	// Normalize index range of 'A', 'R' and 'b' to standard range 1..n
	// and resize 'xx' to length 'n'. Save lower bounds of 'b' and 'A'
	// to restore them before leaving 'ILinSolveMain()'.
	//-----------------------------------------------------------------
	Resize(xx,n);
	bLow = Lb(b); SetLb(b,1);
	ARowLow = Lb(A,ROW); SetLb(A,ROW,1);
	AColLow = Lb(A,COL); SetLb(A,COL,1);
	SetLb(R,ROW,1); SetLb(R,COL,1);

	x = R*mid(b); k = 0;				// Real residual iteration
	do
	{									//------------------------
		y = x;
		for (i = 1; i <= n; i++)		// Compute: d = #*(b-A*y)
		{
			Accu = mid(b[i]);			//-----------------------
			accumulate(Accu,-mid(A)[i],y);
			d[i] = rnd(Accu);
		}
		for (i = 1; i <= n; i++)		// Compute: x = #*(y+R*d)
		{
			Accu = y[i];				//-----------------------
			accumulate(Accu,R[i],d);
			x[i] = rnd(Accu);
		}
//      CILinSys _ls;
		/*_ls.*/CheckForZeros(y,x);
		k++;
	} while (!Accurate(y,x) && (k < MaxResCorr));

  // Prepare verification step, i.e. compute enclosures [C]
  // and [z] of C = (I - R*A) and z = R*(b - A*x).
  //-------------------------------------------------------
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)		// Compute [C] = ##(I-R*A)
		{
			IAccu = (i == j) ? 1.0 : 0.0;
			accumulate(IAccu,-R[i],A[Col(j)]);
			rnd(IAccu,C[i][j]);
		}

	for (i = 1; i <= n; i++)			// Compute: d = #*(b-A*x)
	{
		IAccu = b[i];					//-----------------------
		accumulate(IAccu,-A[i],x);
		dd[i] = rnd(IAccu);
	}
	for (i = 1; i <= n; i++)			// Compute: [y] = ##(b-A*x-d)
	{
		IAccu = b[i];					//---------------------------
		accumulate(IAccu,-A[i],x);
		IAccu -= dd[i];
		rnd(IAccu,yy[i]);
	}

	// Now b-A*x lies in d+[y]. Thus R*(b-A*x) lies in [z] = ##(R*d+R*[y])
	//--------------------------------------------------------------------
	for (i = 1; i <= n; i++)
	{
		IAccu = 0.0;
		accumulate(IAccu,R[i],dd);
		accumulate(IAccu,R[i],yy);
		zz[i] = rnd(IAccu);
	}

	// If R*(b-A*x) = 0 then x is an exact solution else try to find a
	// verified enclosure [x] for the absolute error of x.
	//----------------------------------------------------------------
	if (Zero(zz))
		xx = x;
	else
	{
		VerificationStep(xx,zz,C,IsVerified);   // Attempt to compute [x]
		if ( !IsVerified )
			Err = VERIVFAILED;
		else
			xx = x + xx;                          // The exact solution lies x+[x]
	}

	// Restore lower index bounds of 'A' and 'b'
	//------------------------------------------
	SetLb(b,bLow);
	SetLb(A,ROW,ARowLow); SetLb(A,COL,AColLow);

} //ILinSolveMain

}
