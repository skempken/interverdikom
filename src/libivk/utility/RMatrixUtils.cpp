#include "RMatrixUtils.h"

#include <matinv.hpp>
#include <vector>
#include <stdexcept>
#include <cvector.hpp>
#include "FFT.h"
#include <iostream>
#include <sstream>
#include "Logging.hpp"

using std::vector;
using std::invalid_argument;

namespace ivk
{

rmatrix RMatrixUtils::identity(const int lb, const int ub)
{
	rmatrix B(lb, ub, lb, ub);
	const real one = real(1.0);
	const real zero = real(0.0);
	
	for(int r = Lb(B,1); r<=Ub(B,1); ++r)
	{
		for(int c = Lb(B,2); c <=Ub(B,2); ++c)
		{
			B[r][c] = (r==c)?one:zero;
		}
	}
	return B;
}

rmatrix RMatrixUtils::zeros(const int lb1, const int ub1, const int lb2, const int ub2)
{
	rmatrix B(lb1, ub1, lb2, ub2);
	const real zero = real(0.0);
	
	for(int r = Lb(B,1); r<=Ub(B,1); ++r)
	{
		for(int c = Lb(B,2); c <=Ub(B,2); ++c)
		{
			B[r][c] = zero;
		}
	}
	return B;
}

rmatrix RMatrixUtils::ones(const int lb1, const int ub1, const int lb2, const int ub2)
{
	rmatrix B(lb1, ub1, lb2, ub2);
	const real one = real(1.0);
	
	for(int r = Lb(B,1); r<=Ub(B,1); ++r)
	{
		for(int c = Lb(B,2); c <=Ub(B,2); ++c)
		{
			B[r][c] = one;
		}
	}
	return B;
}



rmatrix RMatrixUtils::invert(const rmatrix &a)
{
	rmatrix inverse;
	int Err = 0;
	MatInv(a, inverse, Err);
	if(Err) throw MatrixInversionException();
	return inverse;
}

rmatrix RMatrixUtils::sortRows(const rmatrix &matrix)
{
	// sort rows in ascending order
	rmatrix ret(Lb(matrix,1), Ub(matrix,1), Lb(matrix,2), Ub(matrix,2));
	for(int row=Lb(matrix,1); row<=Ub(matrix,1); ++row)
	{
		vector<real> rowValues(Ub(matrix,2)-Lb(matrix,2)+1);
		for(int col = Lb(matrix,2); col<=Ub(matrix,2); ++col)
			rowValues.push_back(matrix[row][col]);
		std::sort(rowValues.begin(), rowValues.end());
		for(int col = Lb(matrix,2); col<=Ub(matrix,2); ++col)
			ret[row][col] = rowValues[col];
	}
	return ret;
}

rvector RMatrixUtils::solveCircular(rvector _circular, rvector _right)
{
	if((Lb(_circular) != Lb(_right)) || (Ub(_circular) != Ub(_right)))
		throw std::invalid_argument("Vectors do not have same indices.");
	const int lower = Lb(_circular);
	SetLb(_circular, 0);
	SetLb(_right, 0);
	
	// transpose circular 
	// 0-element stays the same
	rvector tmp(_circular);
	for(int i = 1; i<=Ub(_circular); ++i)
		_circular[Ub(_circular)-i+1] = tmp[i];
	
	cvector c = FFT::fft((cvector) _circular);
	cvector b = FFT::fft((cvector) _right);
	cvector ret(Lb(c), Ub(c));
	for(int i = Lb(c); i<=Ub(c); ++i)
	{
		ret[i] = b[i]/c[i];
	}
	ret = FFT::ifft(ret);
	SetLb(ret, lower);
	return Re(ret);
}

string RMatrixUtils::exportMatlab( rmatrix a ){
	stringstream ss( stringstream::in | stringstream::out );
	ss << cxsc::SetPrecision(17,16);
	ss << Scientific;
	
	string ret;
	for(int i = Lb( a,ROW ); i <= Ub( a,ROW ); i++){
		for(int c = Lb( a,COL ); c <= Ub( a, COL);c++){
			ss << "   ";
			ss << a[i][c];
		}
		ss << "\n";
	}
	
	ret = ss.str();
	size_t found = -1;
	while(found != -2){
		found = ret.find('E');
		if(found != -1){
			ret.replace(found,3,"e-");
			found = -1;
		}
		else{
			found = -2;
		}
	}
	
	return ret;
}

rvector RMatrixUtils::solveToeplitz(rvector t, rvector y)
{
	// TODO: check parameters!
	
	const int N = Ub(y) - Lb(y) +1;
	Logging::log(Logging::Trace, "N", N);
	
	// Backward vectors
	vector<rvector> bs;
	
	// init f1, b1
	rvector f(1,1);
	rvector b(1,1);
	b[1] = f[1] = 1 / t[0];
	//Logging::log(Logging::Trace, "f(1)", f);
	bs.push_back(rvector(b));
	
	// find n-step forward and backward vectors
	for(int n = 2; n<=N ; ++n)
	{
		// compute e_f^n
		dotprecision efn_accu(0.0);
		for(int i = Lb(f); i<=Ub(f); ++i)
			accumulate(efn_accu, f[i], t[n-i]);
		real efn = rnd(efn_accu); 
		Logging::log(Logging::Trace, "efn", efn);
	
		// compute e_b^n
		dotprecision ebn_accu(0.0);
		for(int i = Lb(f); i<=Ub(f); ++i)
			accumulate(ebn_accu, b[i], t[-i]);
		real ebn = rnd(ebn_accu);
		Logging::log(Logging::Trace, "ebn", ebn); 
		
		// compute denominator
		const real denom = 1 - efn*ebn;
		
		// resize vectors
		Resize(f, 1,n);
		SetUb(b,n); Resize(b, 1,n);
		
		rvector f_tmp(f);
		// compute new forward and backward vectors
		f = (1 / denom) * f + (efn / denom) * b;
		b = (1 / denom) * b + (efn / denom) * f_tmp; 
		bs.push_back(rvector(b));
	}
	
	// find solution
	rvector x(1,1);
	x[1] = y[1] / t[0];
	for(int n = 2; n<=N; ++n)
	{
		// compute e_x^n
		dotprecision exn_accu(0.0);
		for(int i = Lb(f); i<=Ub(f); ++i)
			accumulate(exn_accu, x[i], t[n-i]);
		real exn = rnd(exn_accu); 
		
		// resize vectors
		Resize(x,1,n);
		x = x + (y[n] - exn)*bs[n-1];	
	}
	
	return x;
}

	rmatrix RMatrixUtils::splitLR( const rmatrix& A ){
		
		int n = Ub(A,ROW)-Lb(A,ROW);
		rmatrix ret(A);
		
		for(int i = Lb(ret,ROW); i <= n; i++){
			for(int j = i; j <= n; j++){
				for(int k = Lb(ret,ROW); k < i; k++){
					ret[i][j] -= ret[i][k]*ret[k][j];
				}
			}
			for(int j = i+1; j <= n; j++){
				for(int k = Lb(ret,ROW); k < i; k++){
					ret[j][i] -= ret[j][k]*ret[k][i];
				}
				ret[j][i] /= ret[i][i];
			}
		}
		return ret;
	}
		
	rvector RMatrixUtils::eigLR(const rmatrix &A, const real &epsilon){
		rmatrix a(A);
		rmatrix b(A);
		cout << Scientific;
		
		bool run = true;
		real check1 = 2.0;
		real check2 = 0.0;
		
		while(run){
			rmatrix lrmatrix(splitLR(a));
			rmatrix lmat(lrmatrix);
			for(int i = Lb(lmat,ROW); i <= Ub(lmat,ROW); i++){
				for(int j = Lb(lmat,ROW); j <= Ub(lmat,ROW); j++){
					lmat[i][j] = ( i == j ) ? 1 : lmat[i][j];
					lmat[i][j] = ( j > i ) ? 0 : lmat[i][j];
				}
			}
			
			rmatrix rmat(lrmatrix);
			for(int i = Lb(rmat,ROW); i <= Ub(rmat,ROW); i++){
				for(int j = Lb(rmat,ROW); j <= Ub(rmat,ROW); j++){
					rmat[i][j] = ( j < i ) ? 0 : rmat[i][j];
				}
			}
			
			a = rmat*lmat;
			check2 = check1;
			check1 = 0.0;
			
			for(int i = Lb(a,ROW); i <= Ub(a,ROW); i++){
				check1 = ( check1 < abs(a[i][i]-b[i][i]) ) ? abs(a[i][i]-b[i][i]) : check1;
			}
			
			run = ( check1 < epsilon || check1 < check2) ? false : true;
			
			b = a;
		}
		
		rvector ret(Lb(a,ROW),Ub(a,ROW));
		
		for(int i = Lb(a,ROW); i <= Ub(a,ROW); i++){
			ret[i] = a[i][i];
		}
		
		return ret;
	}
	
	rvector RMatrixUtils::eigLR(const rmatrix &A){
		return eigLR(A,RealUtils::getMachEps());
	}
	
	rmatrix RMatrixUtils::invertVandermonde(rvector alpha){
		assert(Lb(alpha) == 0);
		int n = Ub(alpha);
		rvector a(0,Ub(alpha)+1);
		a[0] = -1 * alpha[0];
		a[1] = 1;
		for(int k = 1 ; k <= n ; k++){
			a[k+1] = 1;
			for(int j = k; j >= 1 ; j--){
				a[j] = a[j-1] - alpha[k]* a[j];
			}
			a[0] = -1* alpha[k] * a[0];
		}
		
		rmatrix w( 0 , Ub(alpha) , 0 , Ub(alpha) );
		
		for(int i = 0; i <= Ub(alpha); i++){
			w[i][n] = 1;
			real s = 1;
			
			for(int j = n -1; j >= 0; j--){
				w[i][j] = a[j+1] + alpha[i] * w[i][j+1];
				s = alpha[i]*s + w[i][j];
			}
			
			for(int j = 0; j <= Ub(alpha); j++){
				w[i][j] /= s;
			}
		}
		
		return w;
	}
	
	rvector RMatrixUtils::solveVandermonde(rvector alpha, rvector b){
		rmatrix ret(RMatrixUtils::invertVandermonde( alpha ));
		return ( ret * b);
	}
}
