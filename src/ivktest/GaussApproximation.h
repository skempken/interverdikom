#ifndef GAUSSAPPROXIMATION_H_
#define GAUSSAPPROXIMATION_H_

#include <real.hpp>
#include <GIProcess.h>

using cxsc::real;
using namespace ivk;

class GaussApproximation
{
private:
	real m_sqrt2pi;

public:
	GaussApproximation();
	virtual ~GaussApproximation();
	
	GIProcess approximateGaussian(const real &mean, const real &std, const int numSteps);
	real f(const real x, const real m, const real s);
	
};

#endif /*GAUSSAPPROXIMATION_H_*/
