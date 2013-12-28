/*
 * CVectorUtils.cpp
 *
 *  Created on: 28.08.2008
 *      Author: kempken
 */

#include "CPolynomialUtils.h"
#include "CppLapackUtils.h"
#include <vector>
#include <complex>

using CPPL::zgematrix;

namespace ivk {

CPolynomialUtils::CPolynomialUtils() {
	// TODO Auto-generated constructor stub

}

CPolynomialUtils::~CPolynomialUtils() {
	// TODO Auto-generated destructor stub
}

// Compute roots of polynomial, MATLAB-Style
cvector CPolynomialUtils::roots(const cvector &polynomial)
{
	// TODO: Remove roots at zero (empty coefficients)
	// Set up companion matrix
	const int n = Ub(polynomial) - Lb(polynomial) +1;

	zgematrix companion(n,n);
	for(int i = 1; i<n; ++i)
		companion(i,i-1) = std::complex<double>(1.0,0.0);

	for(int i = Lb(polynomial)+1; i<=Ub(polynomial); ++i)
	{
		cxsc::complex value = -polynomial[i] / polynomial[Lb(polynomial)];
		companion(0,i-Lb(polynomial)-1) = std::complex<double>(_double(Re(value)), _double(Im(value)));
	}

	// compute eigenvalues
	std::vector< std::complex< double > > eigenvalues;
	companion.zgeev(eigenvalues);

	// return as C-XSC type
	cvector ret(1, eigenvalues.size()-1);
	int i = Lb(ret);
	std::vector< std::complex< double > >::iterator it = eigenvalues.begin();
	it++;
	for(; it!=eigenvalues.end(); ++it)
	{
		std::complex<double> value = (*it);
		ret[i++] = cxsc::complex(value.real(), value.imag());
	}
	return ret;
}

}
