#include "SMPGrassmannJain3.h"

#include "utility/Logging.hpp"

namespace ivk
{

SMPGrassmannJain3::SMPGrassmannJain3(const SSMProcess* data, const ComputationParameters &parameters)
: SMPGrassmannJain2(data, parameters)
{
}

SMPGrassmannJain3::~SMPGrassmannJain3()
{
}

void SMPGrassmannJain3::grassmannJainIteration()
{
	const imatrix diff = m_ptrData->getDistributions();
	const int g = - Lb(diff,2);
	const int h = Ub(diff,2);
	
	const int m = m_ptrData->getNumStates();
	
	// Allocate space.
	RMatrixPolynomial l = allocateRMatrixPolynomial(g,m,m);
	RMatrixPolynomial v = allocateRMatrixPolynomial(h,m,m);

	// Progress notification
	setProgressText("Grassmann-Jain iteration (Algorithm 3)");
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
		for(int n = 1; n<=g; ++n)
			dist = std::max<real>(dist, distance(l[n], l_old[n]));
		Logging::log(Logging::Debug, "Remaining distance" , dist );
    }
	setProgressValue(m_numIterations);
	
	// Converged?
	if(dist>=m_epsilon)
	{
		throw IterationLimitException();
	}
	
	// transform results.
	const rmatrix S = RMatrixUtils::identity(1,m) - l[0];
	const rmatrix Si = RMatrixUtils::invert(S);
	for(int i = 1; i<=g; ++i)
	{
		l[i] = Si * l[i];
	}
	l[0] = RMatrixUtils::zeros(1,m,1,m);
	
	for(int i = 0; i<=h; ++i)
	{
		v[i] = v[i] * S;
	}
	
	// Development output
	m_reqIterations_approximation = iterationCount;
	real vsum = 0.0;
	real lsum = 0.0;
	real usum = 0.0;
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

void SMPGrassmannJain3::grassmannJainStep(RMatrixPolynomial &v, RMatrixPolynomial &l, RMatrixPolynomial u)
{
	const int g = l.degree();
	const int h = v.degree();
	const int m = Ub(v[0],1);
	
	// Compute new l
    for (int n = g; n >= 0; n--)
    {
		rmatrix sum = RMatrixUtils::zeros(1,m,1,m);

        int minimum = std::min<int>(g - n, h);
        for (int mu = 1; mu <= minimum; mu++)
        {
        	assert(n+mu <= l.degree());
        	assert(mu <= v.degree());
        	sum += v[mu] * l[mu+n];
        }
        l[n] = u[g-n] + sum;
    }	
    
    // Compute S, inverse
    // XXX: Method works only for SMP(1)
    rmatrix S = RMatrixUtils::identity(1,m) - l[0];
    if(m==1)
    {
    	for(int i = 1; i<=g; ++i)
    		S += l[i];
    	
    	for(int i = Lb(S, 1); i<=Ub(S,1); ++i)
    		for(int j = Lb(S, 2); j<=Ub(S,2); ++j)
    			S[i][j] /= 2.0;
    }
    rmatrix Si = RMatrixUtils::invert(S);
	
	// Compute new v
	for (int n = h; n >= 0; n--)
	{
		// Allocate space for sum variable
		rmatrix sum = RMatrixUtils::zeros(1,m,1,m);
		
		// compute convolution
		int minimum = std::min<int>(h - n, g);
        for (int mu = 1; mu <= minimum; mu++)
        {
        	assert(n+mu <= v.degree());
        	assert(mu <= l.degree());
            sum += v[n + mu] * l[mu];
        }
        v[n] = (u[n+g] + sum) * Si;
	}

	Logging::log(Logging::Debug, "LSum:", RMatrixUtils::sum(l.sum()));
	Logging::log(Logging::Debug, "VSum:", RMatrixUtils::sum(v.sum()));
}

}
