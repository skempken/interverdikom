/*
 * DFTTest.cpp
 *
 *  Created on: 29.07.2008
 *      Author: kempken
 */

#include "DFTTest.h"
#include <assert.h>
#include <iostream>

using namespace std;

DFTTest::DFTTest() {
	// TODO Auto-generated constructor stub

}

DFTTest::~DFTTest() {
	// TODO Auto-generated destructor stub
}

// Implementierung einer einfachen DFT
civector DFTTest::dft0(civector a)
{
	assert(Lb(a) == 0);
	const cinterval I = cinterval(interval(0.0,0.0),interval(1.0,1.0));
	const cinterval PI = cinterval(Pi(),interval(0.0,0.0));
	const int N = Ub(a)+1;
	// Vektor geht von 0 bis N-1.
	civector ret(0,N-1);
	for(int k = 0; k<N; ++k)
	{
		ret[k] = (cinterval) 0;
		for (int j = 0; j<N; ++j)
			ret[k] += exp(- 2 * PI * I * j * k / N)*a[j];
	}
	return ret;
}

civector DFTTest::dft1(civector a)
{
	assert(Lb(a) == 0);
	const interval PI = Pi();
	const int N = Ub(a)+1;

	const ivector a_r(0, N-1);
	const ivector a_i(0, N-1);
	for(int i = 0; i<N; ++i)
	{
		a_r[i] = Re(a[i]);
		a_i[i] = Im(a[i]);
	}

	// Vektor geht von 0 bis N-1.
	civector ret(0,N-1);
	for(int k = 0; k<N; ++k)
	{
		ret[k] = (cinterval) 0;
		for (int j = 0; j<N; ++j)
		{
			Re(ret[k]) += cos(- 2 * PI * j * k / N)*a_r[j]
			            - sin(- 2 * PI * j * k / N)*a_i[j];
			Im(ret[k]) += sin(- 2 * PI * j * k / N)*a_r[j]
					    + cos(- 2 * PI * j * k / N)*a_i[j];
		}
	}
	return ret;
}


civector DFTTest::dft2(civector a)
{
	assert(Lb(a) == 0);
	const interval PI = Pi();
	const int N = Ub(a)+1;

	const ivector a_r(0, N-1);
	const ivector a_i(0, N-1);
	for(int i = 0; i<N; ++i)
	{
		a_r[i] = Re(a[i]);
		a_i[i] = Im(a[i]);
	}

	// Vektor geht von 0 bis N-1.
	civector ret(0,N-1);
	for(int k = 0; k<N; ++k)
	{
		ret[k] = (cinterval) 0;
		idotprecision accu_r;
		idotprecision accu_i;
		for (int j = 0; j<N; ++j)
		{
			accumulate(accu_r, cos(- 2 * PI * j * k / N), a_r[j]);
			accumulate(accu_r, - sin(- 2 * PI * j * k / N), a_i[j]);
			accumulate(accu_i, sin(- 2 * PI * j * k / N), a_r[j]);
			accumulate(accu_r, cos(- 2 * PI * j * k / N), a_i[j]);
		}
		Re(ret[k]) = rnd(accu_r);
		Im(ret[k]) = rnd(accu_i);
	}
	return ret;
}

civector DFTTest::dft3(civector a)
{
	assert(Lb(a) == 0);
	int stagprec_old = stagprec;
	stagprec = 2;

	const l_interval PI = Pi_l_interval();
	const int N = Ub(a)+1;

	const ivector a_r(0, N-1);
	const ivector a_i(0, N-1);
	for(int i = 0; i<N; ++i)
	{
		a_r[i] = Re(a[i]);
		a_i[i] = Im(a[i]);
	}

	// Vektor geht von 0 bis N-1.
	civector ret(0,N-1);

	l_ivector roots_r(0, N-1);
	l_ivector roots_i(0, N-1);

	for(int i = 0; i<N; ++i)
	{
		roots_r[i] = cos(- 2 * PI * i / N);
		roots_i[i] = sin(- 2 * PI * i / N);
	}

	cout << "Maxdiam r:" << getMaxDiam(roots_r) << endl;
	cout << "Maxdiam i:" << getMaxDiam(roots_i) << endl;

	for(int k = 0; k<N; ++k)
	{
		ret[k] = (cinterval) 0;
		idotprecision accu_r;
		idotprecision accu_i;
		for (int j = 0; j<N; ++j)
		{
			accumulate(accu_r, roots_r[(j * k) % N], a_r[j]);
			accumulate(accu_r, - roots_i[(j * k) % N], a_i[j]);
			accumulate(accu_i, roots_i[(j * k) % N], a_r[j]);
			accumulate(accu_i, roots_r[(j * k) % N], a_i[j]);
		}
		Re(ret[k]) = rnd(accu_r);
		Im(ret[k]) = rnd(accu_i);
	}

	stagprec = stagprec_old;
	return ret;
}

civector DFTTest::idft3(civector a)
{
	assert(Lb(a) == 0);
	int stagprec_old = stagprec;
	stagprec = 2;

	const l_interval PI = Pi_l_interval();
	const int N = Ub(a)+1;

	const ivector a_r(0, N-1);
	const ivector a_i(0, N-1);
	for(int i = 0; i<N; ++i)
	{
		a_r[i] = Re(a[i]);
		a_i[i] = Im(a[i]);
	}

	// Vektor geht von 0 bis N-1.
	civector ret(0,N-1);

	l_ivector roots_r(0, N-1);
	l_ivector roots_i(0, N-1);

	for(int i = 0; i<N; ++i)
	{
		roots_r[i] = cos( 2 * PI * i / N)/(double)N;
		roots_i[i] = sin( 2 * PI * i / N)/(double)N;
	}

	cout << "Maxdiam r:" << getMaxDiam(roots_r) << endl;
	cout << "Maxdiam i:" << getMaxDiam(roots_i) << endl;

	for(int k = 0; k<N; ++k)
	{
		ret[k] = (cinterval) 0;
		idotprecision accu_r;
		idotprecision accu_i;
		for (int j = 0; j<N; ++j)
		{
			accumulate(accu_r, roots_r[(j * k) % N], a_r[j]);
			accumulate(accu_r, - roots_i[(j * k) % N], a_i[j]);
			accumulate(accu_i, roots_i[(j * k) % N], a_r[j]);
			accumulate(accu_i, roots_r[(j * k) % N], a_i[j]);
		}
		Re(ret[k]) = rnd(accu_r);
		Im(ret[k]) = rnd(accu_i);
	}

	stagprec = stagprec_old;
	return ret;
}

void DFTTest::l_dft3(civector a)
{
	assert(Lb(a) == 0);
	int stagprec_old = stagprec;
	stagprec = 2;

	const l_interval PI = Pi_l_interval();
	const int N = Ub(a)+1;

	const ivector a_r(0, N-1);
	const ivector a_i(0, N-1);
	for(int i = 0; i<N; ++i)
	{
		a_r[i] = Re(a[i]);
		a_i[i] = Im(a[i]);
	}

	// Vektor geht von 0 bis N-1.
	l_ivector ret_r(0,N-1);
	l_ivector ret_i(0,N-1);

	l_ivector roots_r(0, N-1);
	l_ivector roots_i(0, N-1);

	for(int i = 0; i<N; ++i)
	{
		roots_r[i] = cos(- 2 * PI * i / N);
		roots_i[i] = sin(- 2 * PI * i / N);
	}

	cout << "Maxdiam r:" << getMaxDiam(roots_r) << endl;
	cout << "Maxdiam i:" << getMaxDiam(roots_i) << endl;

	for(int k = 0; k<N; ++k)
	{
		ret_r[k] = (l_interval) 0;
		ret_i[k] = (l_interval) 0;
		idotprecision accu_r;
		idotprecision accu_i;
		for (int j = 0; j<N; ++j)
		{
			accumulate(accu_r, roots_r[(j * k) % N], a_r[j]);
			accumulate(accu_r, -roots_i[(j * k) % N], a_i[j]);
			accumulate(accu_i, roots_i[(j * k) % N], a_r[j]);
			accumulate(accu_i, roots_r[(j * k) % N], a_i[j]);
		}
		ret_r[k] = accu_r;
		ret_i[k] = accu_i;
	}

	cout << "Maxdiam RE:" << getMaxDiam(ret_r) << endl;
	cout << "Maxdiam IM:" << getMaxDiam(ret_i) << endl;
	stagprec = stagprec_old;

}

l_real DFTTest::getMaxDiam(const l_ivector &values)
{
	l_real maxdiam = (l_real) 0.0;
	for(int i = Lb(values); i<=Ub(values); ++i)
	{
		maxdiam = std::max<l_real>(diam(values[i]), maxdiam);
	}
	return maxdiam;
}

real DFTTest::getMaxDiam(const civector &values)
{
	real maxdiam = (real) 0.0;
	for(int i = Lb(values); i<=Ub(values); ++i)
	{
		maxdiam = std::max<real>(diam(Re(values[i])), maxdiam);
		maxdiam = std::max<real>(diam(Im(values[i])), maxdiam);
	}
	return maxdiam;
}

