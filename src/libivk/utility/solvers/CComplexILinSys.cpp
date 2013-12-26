//============================================================================
//  Changed by D. Fausten
//  Altered by A. Mika
//  File based on: cilinsys.cpp
//  Changes: Instead of a real matrix and a real right-hand side use complex
//           interval matrix and right hand side in the system Ax=b.
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
// Purpose: Computation of a verified solution of a square linear system of
//    equations A*x = b with full complex interval matrix A and
//    complex interval right-hand side b.
// Method: Transformation of A*x = b to fixed-point form and applying an
//    interval residual iteration.
// Global functions:
//    CILinSolve()      : to get a verified enclosure of the solution (two
//                        versions)
//    CILinSolveErrMsg(): to get an error message text
//----------------------------------------------------------------------------
// In the comments below the notations #*(...) and ##(...) are used to indi-
// cate the evaluation of the expression specified in round brackets using
// the exact scalar product. I.e. each component of the result is computed
// with only one final rounding. The symbol #* holds for rounding to nearest
// whereas ## holds for rounding to the smallest enclosing interval. An exact
// scalar product may be implemented using dotprecision accumulators.
//----------------------------------------------------------------------------

#include <cstring>
#include "mvci_util.hpp"    // Interval matrix/vector utility functions
#include "matinvc.hpp"
#include "CComplexILinSys.hpp"

using namespace cxsc;
using namespace std;

namespace ivk {

//----------------------------------------------------------------------------
// Error codes used in this module.
//----------------------------------------------------------------------------
const int
	NoError      = 0,   // No error occurred
	NotSquare    = 1,   // System to be solved is not square
	DimensionErr = 2,   // Dimensions of A and b are not compatible
	InvFailed    = 3,   // System is probably singular
	VerivFailed  = 4;   // Verification failed, system is probably
                      // ill-conditioned

//----------------------------------------------------------------------------
// Error messages depending on the error code.
//----------------------------------------------------------------------------
char* CComplexILinSys::CILinSolveErrMsg ( int Err )
{
	static char Msg[80] = "";

	if (Err != NoError)
	{
		char Hlp[60];

		switch (Err)
		{
			case NotSquare:
				strcpy(Hlp,"System to be solved is not square"); break;
			case DimensionErr:
				strcpy(Hlp,"Dimensions of A and b are not compatible"); break;
			case InvFailed:
				strcpy(Hlp,"System is probably singular"); break;
			case VerivFailed:
				strcpy(Hlp,"Verification failed, system is probably ill-conditioned");
			break;
			default:
				strcpy(Hlp,"Code not defined");
		}
		sprintf(Msg,"Error: %s!",Hlp);
	}
	return(Msg);
} // CILinSolveErrMsg





//----------------------------------------------------------------------------
// Computes an upper bound for the maximum norm of a complex matrix 'M'.
//----------------------------------------------------------------------------
real CComplexILinSys::MaxNorm ( const cmatrix& M )
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
void CComplexILinSys::CheckForZeros ( cvector& x, cvector& y )
{
	const real Factor = 1E+5;
	int        i;

	for (i = Lb(y); i <= Ub(y); i++)
		if ( abs(y[i])*Factor < abs(x[i]) ) y[i] = 0.0;
}




//----------------------------------------------------------------------------
// The vectors x and y are successive iterates. The function returns true if
// the relative error of all components x_i and y_i is <= 10^(-12), i.e. y_i
// has about 12 correct decimals.
//----------------------------------------------------------------------------
int CComplexILinSys::Accurate( cvector& x, cvector& y )
{
	const real Delta = 1E-12;   // Relative error bound (5E-8)
	int        i, n, ok; //, signx, signy;
	real       abs_yi;

	i = Lb(y); n = Ub(y);
	do
	{
		abs_yi = abs(y[i]);                // Relative error > Delta ?
		ok = (abs(y[i] - x[i]) <= Delta * abs_yi );
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
void CComplexILinSys::VerificationStep ( civector& xx, civector& zz,
                                         cimatrix& C,  int& IsVerified )
{
	const int  MaxIter = 3;          // Maximal number of iteration steps
	const real Epsilon = 1000.0;     // Factor for the epsilon inflation

	int     p;
	civector yy(Lb(xx),Ub(xx));

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
// Purpose: The function 'CILinSolveMain()' computes a verified solution of a
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
// Description: An approximate inverse 'R' of 'A' is computed by calling
//   function 'MatInv()'. Then an approximate solution 'x' is computed
//   applying a conventional real residual iteration. For the final verifica-
//   tion, an interval residual iteration is performed. An enclosure of the
//   unique solution is returned in the interval vector 'xx'. The function
//   also returns a condition number estimate 'Cond' if the flag 'ComputeCond'
//   is set. 'Cond' is initialized by -1. A negative value for 'Cond' signals
//   that an estimate could not be computed.
//----------------------------------------------------------------------------
void CComplexILinSys::CILinSolveMain ( cimatrix  AC, civector  bc, civector&  xxc,
									   real& Cond, int ComputeCond, int& Err )
{
	const int MaxResCorr = 10;							// Maximal number of real residual corrections


	int n = Ub(AC,1)-Lb(AC,1)+1;									// Length of the columns of 'AC'
	int m = Ub(AC,2)-Lb(AC,2)+1;									// Length of the rows of 'AC'
	int IsVerified, i, j, k;
	int bLow, ARowLow, AColLow;							// Lower index bounds od 'AC' and 'bc'
	cmatrix RC;											// To store the inverse of mid('AC')


	Cond = -1.0;										// Initial value for the condition

	if (n != m)											// Error: 'AC' is not square
    {
		Err = NotSquare;
		return;
	}

	if (n != VecLen(bc))								// Error: Dimensions of 'AC' and 'bc'
    {
		Err = DimensionErr;
		return;
	}													// are not compatible

	MatInvc(mid(AC),RC,Err);

	if (Err != NoError)									// Error: Inversion failed
	{
		Err = InvFailed;
		return;
	}

	// Start algorithm
	//----------------
	cvector       xc(n), yc(n), dc(n);					// Allocate dynamic arrays
	civector      yyc(n), zzc(n), ddc(n);
	cimatrix      CC(n,n);
	cdotprecision Accuc;								// Allocate accumulators
	cidotprecision IAccuc;


	if (ComputeCond)									// Compute condition number
		Cond = mulu(MaxNorm(mid(AC)),MaxNorm(RC));		//-------------------------

	// Normalize index range of 'AC', 'RC' and 'bc' to standard range 1..n
	// and resize 'xxc' to length 'n'. Save lower bounds of 'bc' and 'AC'
	// to restore them before leaving 'ILinSolveMain()'.
	//---------------------------------------------------------------------
	Resize(xxc,n);
	bLow = Lb(bc); SetLb(bc,1);
	ARowLow = Lb(AC,ROW); SetLb(AC,ROW,1);
	AColLow = Lb(AC,COL); SetLb(AC,COL,1);
	SetLb(RC,ROW,1); SetLb(RC,COL,1);

	xc = RC*mid(bc); k = 0;								// Residual iteration
	do
	{													//------------------------
		yc = xc;
		for (i = 1; i <= n; i++)						// Compute: dc = #*(bc-AC*yc)
		{
			Accuc = mid(bc[i]);							//---------------------------
			accumulate(Accuc,-mid(AC)[i],yc);
			dc[i] = rnd(Accuc);
		}
		for (i = 1; i <= n; i++)						// Compute: xc = #*(yc+RC*dc)
		{
			Accuc = yc[i];								//---------------------------
			accumulate(Accuc,RC[i],dc);
			xc[i] = rnd(Accuc);
		}
		CheckForZeros(yc,xc);
		k++;
	} while (!Accurate(yc,xc) && (k < MaxResCorr));

	// Prepare verification step, i.e. compute enclosures [CC]
	// and [zzc] of CC = (I - RC*AC) and zc = RC*(bc - AC*xc).
	//--------------------------------------------------------
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)						// Compute [CC] = ##(I-RC*AC)
		{
			IAccuc = (i == j) ? 1.0 : 0.0;				//---------------------------
			accumulate(IAccuc,-RC[i],AC[Col(j)]);
			rnd(IAccuc,CC[i][j]);
		}

	for (i = 1; i <= n; i++)							// Compute: ddc = #*(bc-AC*xc)
	{
		IAccuc = bc[i];									//----------------------------
		accumulate(IAccuc,-AC[i],xc);
		ddc[i] = rnd(IAccuc);
	}

	for (i = 1; i <= n; i++)							// Compute: [yyc] = ##(bc-AC*xc-ddc)
	{
		IAccuc = bc[i];									//----------------------------------
		accumulate(IAccuc,-AC[i],xc);
		IAccuc -= ddc[i];
		rnd(IAccuc,yyc[i]);
	}

	// Now bc-AC*xc lies in ddc+[yyc]. Thus RC*(bc-AC*xc) lies in [zzc] = ##(RC*dc+RC*[yyc])
	//-------------------------------------------------------------------------------------
	for (i = 1; i <= n; i++)
	{
		IAccuc = 0.0;
		accumulate(IAccuc,RC[i],ddc);
		accumulate(IAccuc,RC[i],yyc);
		zzc[i] = rnd(IAccuc);
	}

  // If RC*(bc-AC*xc) = 0 then xc is an exact solution else try to find a
  // verified enclosure [xc] for the absolute error of xc.
  //----------------------------------------------------------------------
	ivector tmp1 = abs(zzc);
	if (Zero(tmp1))
		xxc = xc;
	else
	{
		VerificationStep(xxc,zzc,CC,IsVerified);		// Attempt to compute [xc]
		if ( !IsVerified )
			Err = VerivFailed;
		else
			xxc = xc + xxc;								// The exact solution lies xc+[xc]
	}

	// Restore lower index bounds of 'AC' and 'bc'
	//--------------------------------------------
	SetLb(bc,bLow);
	SetLb(AC,ROW,ARowLow); SetLb(AC,COL,AColLow);
} //CILinSolveMain






//------------------------------------------------------------------------------
// Purpose: The function 'CILinSolve()' computes a verified solution of a
//    square linear system of equations A*x=b without returning a condition
//    number estimate.
// Parameters:
//    In : 'A'  : matrix of the system, passed as reference
//                parameter to save time for copying it
//         'b'  : right-hand side of the system, passed as
//                reference parameter to save time for copying it
//    Out: 'xx' : enclosure of the unique solution
//         'Err': error code
// Description: Calls 'CILinSolveMain()' for solving the linear system with the
//    flag 'ComputeCond' not set.
//------------------------------------------------------------------------------
void CComplexILinSys::CILinSolve ( const cimatrix& A, const civector& b,
                                   civector& xx, int& Err )
{
	real DummyCond;         // Dummy parameter for call of 'CILinSolveMain()'
	CILinSolveMain(A,b,xx,DummyCond,0,Err);
}





//------------------------------------------------------------------------------
// Purpose: The function 'CILinSolve()' computes a verified solution of a
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
// Description: Calls 'CIILinSolveMain()' for solving the linear system with the
//    flag 'ComputeCond' set.
//------------------------------------------------------------------------------
void CComplexILinSys::CILinSolve ( const cimatrix& A, const civector& b,
                                   civector& xx, real& Cond, int& Err )
{
	CILinSolveMain(A,b,xx,Cond,1,Err);
}

}
