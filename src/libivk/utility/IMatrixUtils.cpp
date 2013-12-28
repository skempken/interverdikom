#include "utility/IMatrixUtils.h"
#include "solvers/ILinSys.hpp"
#include "utility/Logging.hpp"

namespace ivk
{

imatrix IMatrixUtils::identity(const int lb, const int ub)
{
	imatrix B(lb, ub, lb, ub);
	const interval one = interval(1.0,1.0);
	const interval zero = interval(0.0,0.0);
	
	for(int r = Lb(B,1); r<=Ub(B,1); ++r)
	{
		for(int c = Lb(B,2); c <=Ub(B,2); ++c)
		{
			B[r][c] = (r==c)?one:zero;
		}
	}
	return B;
}

imatrix IMatrixUtils::zeros(const int lb1, const int ub1, const int lb2, const int ub2)
{
	imatrix B(lb1, ub1, lb2, ub2);
	
	for(int r = Lb(B,1); r<=Ub(B,1); ++r)
	{
		for(int c = Lb(B,2); c <=Ub(B,2); ++c)
		{
			B[r][c] = interval(0.0,0.0);
		}
	}
	return B;
}

imatrix IMatrixUtils::ones(const int lb1, const int ub1, const int lb2, const int ub2)
{
	imatrix B(lb1, ub1, lb2, ub2);
	const interval one = interval(1.0,1.0);
	
	for(int r = Lb(B,1); r<=Ub(B,1); ++r)
	{
		for(int c = Lb(B,2); c <=Ub(B,2); ++c)
		{
			B[r][c] = one;
		}
	}
	return B;
}

imatrix IMatrixUtils::invert(const imatrix &a)
{
	
	const int m = Ub(a,1);
    imatrix ergebnis( m, m );
    
    if(m == 1)
    {
    	Logging::log(Logging::Trace, "a", a);
    	ergebnis[1][1] = 1.0 / a[1][1];
    	Logging::log(Logging::Trace, "1/a", ergebnis);
    	return ergebnis;
    }
    
    // m = 2
    if ( m == 2 )
    {
        interval det;
                    
        det = a[1][1] * a[2][2] - a[1][2] * a[2][1];
                    
        ergebnis[1][1] = a[2][2] / det;
        ergebnis[1][2] = - a[1][2] / det;
        ergebnis[2][1] = - a[2][1] / det;
        ergebnis[2][2] = a[1][1] / det; 
        return ergebnis;
    }
    
    // m > 2
    imatrix atransp = IMatrixUtils::transpose(a);
    ivector b(m), xx(m);

    for ( int i = 1; i <= m; i++ ) 
    {
        b[i] = 0.0;
    }

    for ( int i = 1; i <= m; i++ )
    {
        b[i] = 1.0;
        if (i > 1)
           b[i-1] = 0.0;
   
        ILinSys _ls;
        int Err = 0;
        _ls.ILinSolve( atransp, b, xx, Err );
        if(Err) throw MatrixInversionException();
        ergebnis[i] = xx;
    }
    return(ergebnis); 
}

real IMatrixUtils::maxDiam(const imatrix &a)
{
	real diam = 0.0;
	for(int i = Lb(a,1); i<=Ub(a,1); ++i)
		for(int j = Lb(a,2); j<=Ub(a,2); ++j)
			diam = std::max<real>(diam, cxsc::diam(a[i][j]));
	return diam;
}

real IMatrixUtils::maxDiam(const ivector &a)
{
	real diam = 0.0;
	for(int i = Lb(a); i<=Ub(a); ++i)
		diam = std::max<real>(diam, cxsc::diam(a[i]));
	return diam;
}

}
