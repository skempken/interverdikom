#include "GaussApproximation.h"

#include <rvector.hpp>
#include <math.h>
using cxsc::rvector;

GaussApproximation::GaussApproximation()
{
	m_sqrt2pi = cxsc::sqrt(M_PI * 2.0);
}

GaussApproximation::~GaussApproximation()
{
}

GIProcess GaussApproximation::approximateGaussian(const real &m, const real &std, const int numSteps)
{
	rvector dist(0, numSteps -1);
	
	// Get values on interval [0;1]
	real sum = 0.0;
	for(int i = Lb(dist); i<=Ub(dist); ++i)
	{
		real x = (real)i / (numSteps-1);
		dist[i] = (f(x-0.5, m, std) + f(x+0.5, m, std))*0.5;
		sum += dist[i];
	}
	
	// Normalize
	for(int i = Lb(dist); i<=Ub(dist); ++i)
		dist[i] = dist[i] / sum;
	
	return GIProcess(dist);
}

real GaussApproximation::f(const real x, const real m, const real s)
{
	real v= s*s;
	real tmp = x-m;
	tmp *= tmp;
	return cxsc::exp( -tmp/2*v) / (s * m_sqrt2pi);
}
