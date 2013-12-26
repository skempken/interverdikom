#include "SMPGrassmannJain1.h"

#include "utility/Logging.hpp"

namespace ivk
{

SMPGrassmannJain1::SMPGrassmannJain1(const SSMProcess* data, const ComputationParameters &parameters)
: SMPWienerHopf(data, parameters)
{
}

SMPGrassmannJain1::~SMPGrassmannJain1()
{
}

void SMPGrassmannJain1::grassmannJainIteration()
{
	const imatrix diff = m_ptrData->getDistributions();
	const int g = - Lb(diff,2);
	const int h = Ub(diff,2);
	
	const int m = m_ptrData->getNumStates();
	
	// Allocate space.
	RMatrixPolynomial l = allocateRMatrixPolynomial(g,m,m);
	RMatrixPolynomial v = allocateRMatrixPolynomial(h,m,m);
	
	// Progress notification
	setProgressText("Grassmann-Jain iteration (Algorithm 1) ");
	setProgressMax(m_numIterations);
	
	
	// Iteration
	real dist = m_epsilon + 1.0; // must be bigger than epsilon for following abort condition.
	int iterationCount = 1;
	for(; ((iterationCount<=m_numIterations) && (dist>m_epsilon)); ++iterationCount)
	{
		setProgressValue(iterationCount);
		RMatrixPolynomial v_old = v;
		RMatrixPolynomial l_old = l;
		
		// Compute iteration step, propagate error if encountered.
		grassmannJainStep(v, l, this->m_u);
		
		// Compute difference.
		dist = 0.0;
		for(int n = 0; n<=h; ++n)
			dist = std::max<real>(dist, distance(v[n], v_old[n]));
		for(int n = 0; n<=g; ++n)
			dist = std::max<real>(dist, distance(l[n], l_old[n]));
			Logging::log(Logging::Debug, "Remaining distance", dist);
    }
	setProgressValue(m_numIterations);
	
	// Converged?
	if(dist>=m_epsilon)
	{
		throw IterationLimitException();
	}

	// Transform from a to alpha
	rmatrix inverse = RMatrixUtils::invert(RMatrixUtils::identity(1,m) - l[0]);
	for(int n = 1; n<=g; ++n)
		l[n] = inverse * l[n];
	l[0] = RMatrixUtils::zeros(1,m,1,m);
	
	Logging::log(Logging::Debug, "Inverse^2", (inverse * (RMatrixUtils::identity(1,m) - v[0])));
	
	// Development output
	m_reqIterations_approximation = iterationCount;
	real vsum = 0.0;
	real lsum = 0.0;
	real usum = 0.0;
	lsum = 0.0;
	rmatrix ls = l.sum();
	rmatrix vs = v.sum();
	rmatrix us = m_u.sum();
	for(int i=Lb(v[0],1); i<=Ub(v[0],1); ++i)
		for(int j=Lb(v[0],1); j<=Ub(v[0],1); ++j)
		{
			lsum += ls[i][j];
			vsum += vs[i][j];
			usum += us[i][j];
		}
	Logging::log(Logging::Info, "Grassmann-Jain Iteration completed.");
	
	// copy values.
    this->m_v = v;
    this->m_l = l;
}

void SMPGrassmannJain1::grassmannJainStep(RMatrixPolynomial &v, RMatrixPolynomial &l, RMatrixPolynomial u)
{
	const int g = l.degree();
	const int h = v.degree();
	const int m = Ub(v[0],1);
	
	// Compute inverse
	rmatrix inverse = RMatrixUtils::invert(RMatrixUtils::identity(1,m) - l[0]);
	
	// Compute new v
	for (int n = 0; n <= h; n++)
	{
		// Allocate space for sum variable
		rmatrix sum = RMatrixUtils::zeros(1,m,1,m);
		
		// compute convolution
		int minimum = std::min<int>(h - n, g);
        for (int mu = 1; mu <= minimum; mu++)
        {
        	assert(n+mu <= v.degree());
        	assert(mu <= l.degree());
            sum += v[n + mu] * inverse * l[mu];
        }
        v[n] = u[n+g] + sum;
	}
	Logging::log(Logging::Debug, "VSum:", RMatrixUtils::sum(v.sum()));
	
	// Compute new l
    for (int n = 0; n <= g; n++)
    {
		rmatrix sum = RMatrixUtils::zeros(1,m,1,m);

        int minimum = std::min<int>(g - n, h);
        for (int mu = 1; mu <= minimum; mu++)
        {
        	assert(n+mu <= l.degree());
        	assert(mu <= v.degree());
        	sum += v[mu] * inverse * l[mu+n];
        }
        l[n] = u[g-n] + sum;
    }	
    Logging::log(Logging::Debug, "LSum:", RMatrixUtils::sum(l.sum()));
}

}
