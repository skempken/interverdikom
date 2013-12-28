#include "SMPWienerHopf.h"

#include <imatrix.hpp>
#include <interval.hpp>
#include <assert.h>

#include "utility/types/MatrixAccu.hpp"
#include "utility/RMatrixUtils.h"
#include "utility/IMatrixUtils.h"

#include "utility/Logging.hpp"


using namespace cxsc;

namespace ivk
{

const char* SMPWienerHopf::PARAM_EPSILON = "epsilon";
const char* SMPWienerHopf::PARAM_NUMITERATIONS = "numIterations";
const char* SMPWienerHopf::PARAM_RELAXATIONSTEPS = "relaxationSteps";

SMPWienerHopf::SMPWienerHopf(const SSMProcess* data, const ComputationParameters &parameters)
: AbstractComputation<SSMProcess, ISMPWHFactors>(data, parameters)
{
	setQueue(data);
	setParameters(parameters);

	// Default values
	m_relaxationSteps = 0;

	// No iterations so far.
	m_reqIterations_approximation = 0;
	m_reqIterations_verification = 0;
	m_verification_successful = false;
}

void SMPWienerHopf::setParameters(const ComputationParameters &parameters)
{
	setEpsilon(parameters.getReal(PARAM_EPSILON));
	setNumIterations(parameters.getInt(PARAM_NUMITERATIONS));
	setRelaxationSteps(parameters.getInt(PARAM_RELAXATIONSTEPS));
}

SMPWienerHopf::~SMPWienerHopf()
{
}

void SMPWienerHopf::setEpsilon(const real &_epsilon)
{
	this->m_epsilon = _epsilon;
}

void SMPWienerHopf::setNumIterations(const int &_numIterations)
{
	this->m_numIterations = _numIterations;
}

void SMPWienerHopf::setRelaxationSteps(const int &relaxationSteps)
{
	if(relaxationSteps < 0)
		throw new std::invalid_argument("Number of relaxation steps must be 0 or positive.");
	this->m_relaxationSteps = relaxationSteps;
}

ISMPWHFactors* SMPWienerHopf::compute()
{
	// Compute approximations
	grassmannJainIteration();

	// Perform verification
	real currentDelta = m_epsilon;
	setProgressText("Verification");
	const int numVerificationIterations = -(int)std::log10(_double(currentDelta));
	setProgressMax(numVerificationIterations);

	int iterationCount = 1;
	while(currentDelta <=1.0)
	{
		try
		{
			setProgressValue(iterationCount++);
			verification(currentDelta);

			// Check number of states
			imatrix test = m_v_int[1];

			break;
		}
		catch(IterationLimitException &ex)
		{
			// Verification failed. Let's try a larger Delta.
			currentDelta *= 10.0;
		}
	}
	setProgressValue(numVerificationIterations);

	if(currentDelta > 1.0)
	{
		m_verification_successful = false;
		copyUnverifiedValues();
	}
	else
	{
		m_verification_successful = true;
	}
	// Done.
	return new ISMPWHFactors(m_l_int, m_v_int);
}

void SMPWienerHopf::setQueue(const SSMProcess *queue)
{
	imatrix diff = queue->getDistributions();
	imatrix p = queue->getTransitionMatrix();

	const int negDiff = - Lb(diff,2);
	const int posDiff = Ub(diff,2);
	const int sizeDiffDist = negDiff + posDiff + 1;
	const int m = queue->getNumStates();

	this->m_u_int = IMatrixPolynomial(sizeDiffDist-1);
	this->m_u = RMatrixPolynomial(sizeDiffDist-1);

	for (int k = -negDiff; k <= posDiff; k++)
	{
		this->m_u_int[k+negDiff] = imatrix(1,m,1,m);
		this->m_u[k+negDiff] = rmatrix(1,m,1,m);

		for (int i = 1; i <= m; i++)
		{
		    for (int j = 1; j <= m; j++)
		    {
	        	// Array assertions
	        	assert(i >= Lb(diff,1));
	        	assert(i <= Ub(diff,1));
	        	assert(k >= Lb(diff,2));
	        	assert(k <= Ub(diff,2));

	        	assert(i >= Lb(p,1));
	        	assert(i <= Ub(p,1));
	        	assert(j >= Lb(p,2));
	        	assert(j <= Ub(p,2));

	            m_u_int[k+negDiff][i][j] = diff[i][k]*p[i][j];
	         	m_u[k+negDiff][i][j] = mid(m_u_int[k+negDiff][i][j]);
		    }
		}
	}
}


void SMPWienerHopf::grassmannJainIteration()
{
	const imatrix diff = m_ptrData->getDistributions();
	const int g = - Lb(diff,2);
	const int h = Ub(diff,2);

	const int m = m_ptrData->getNumStates();

	// Allocate space.
	RMatrixPolynomial l = allocateRMatrixPolynomial(g,m,m);
	RMatrixPolynomial v = allocateRMatrixPolynomial(h,m,m);

	// Progress notification
	setProgressText("Grassmann-Jain iteration");
	setProgressMax(m_numIterations);


	// Iteration
	real dist = m_epsilon + 1.0; // must be bigger than epsilon for following abort condition.
	int iterationCount = 1;

	// Relaxation parameters
	m_wv = 1.0;
	m_wl = 1.0;
	RMatrixPolynomial v_veryold = v;
	RMatrixPolynomial l_veryold = l;
	for(; ((iterationCount<=m_numIterations) && (dist>m_epsilon)); ++iterationCount)
	{
		setProgressValue(iterationCount);
		RMatrixPolynomial v_old = v;
		RMatrixPolynomial l_old = l;


		// Compute iteration step, propagate error if encountered.
		grassmannJainStep(v, l, this->m_u);



		// Re-estimate relaxation parameters
		if(m_relaxationSteps && (iterationCount % m_relaxationSteps == 0))
		{
			/**
			 * v,l : Step n+1
			 * v_old, l_old: Step n
			 * v_veryold, l_veryold: Step n-1
			 */
			m_wv = estimateRelaxationParameter(v_veryold, v_old, v, m_wv);
			m_wl = estimateRelaxationParameter(l_veryold, l_old, l, m_wl);
		}

		// Compute difference.
		dist = 0.0;
		for(int n = 0; n<=h; ++n)
			dist = std::max<real>(dist, distance(v[n], v_old[n]));
		for(int n = 1; n<=g; ++n)
			dist = std::max<real>(dist, distance(l[n], l_old[n]));
		Logging::log(Logging::Debug, "Change this step", dist );

		v_veryold = v_old;
		l_veryold = l_old;
    }
	setProgressValue(m_numIterations);

	// Converged?
	if(dist>=m_epsilon)
	{
		throw IterationLimitException();
	}

	// Development output
	m_reqIterations_approximation = iterationCount;
	/*
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
	*/

	Logging::log(Logging::Info, "Grassmann-Jain Iteration completed. Iterations", iterationCount);

	// copy values.
    this->m_v = v;
    this->m_l = l;
}

real SMPWienerHopf::estimateRelaxationParameter(const RMatrixPolynomial &x_1, const RMatrixPolynomial &x0, const RMatrixPolynomial &x1, const real &w)
{
	real q(0.0);
	real ret(w);
	for(int n = 0; n<=x0.degree(); ++n)
		q = std::max<real>(q, distance(x1.at(n), x0.at(n))/distance(x0.at(n), x_1.at(n)));
	if(q<1.0)
	{
		q = std::max<real>(q, w - 1.0);
		real tmp = (q+w-1.0)/w;
		tmp *= tmp;
		ret = 2.0 / ( 1.0 + sqrt(1.0 - tmp / q));
	}

	// Test
	// ret = (1.0 + ret)/2.0;
	return ret;
}

real SMPWienerHopf::grassmannJainStep(IMatrixPolynomial &v, IMatrixPolynomial &l, IMatrixPolynomial u)
{
	// Aliases for bounds
	const int m = Ub(v[0],1);
	const int g = l.degree();
	const int h = v.degree();

	// Compute inverse to resolve implicity
	imatrix inverse = IMatrixUtils::invert(IMatrixUtils::identity(1,m) - v[0]);

	// Return value: Maximum diameter of the intervals
	real max_diam = 0.0;

	// Compute new l
    for (int n = g; n >= 1; n--)
    {
		imatrixaccu sum(1,m,1,m);
        int minimum = std::min<int>(g - n, h);
        for (int mm = 1; mm <= minimum; mm++)
        {
        	assert(n+mm <= l.degree());
        	assert(mm <= v.degree());
        	sum.accumulate(v[mm], l[mm+n]);
        }
        assert(g-n>=0);
        assert(g-n<=u.degree());
        imatrixaccu sum2(1,m,1,m);
        sum2.accumulate(inverse, u[g-n]);
        sum2.accumulate(inverse, sum.rnd());
        l[n] = sum2.rnd();
        max_diam = std::max<real>(max_diam, IMatrixUtils::maxDiam(l[n]));
    }
	// Compute new v
	for (int n = h; n >= 0; n--)
	{
		imatrixaccu sum(1,m,1,m);
		int minimum = std::min<int>(h - n, g);
        for (int mm = 1; mm <= minimum; mm++)
        {
        	assert(n+mm <= v.degree());
        	assert(mm <= l.degree());
            sum.accumulate(v[n + mm], l[mm]);
        }
        v[n] = (u[n+g] + sum.rnd());
        max_diam = std::max<real>(max_diam, IMatrixUtils::maxDiam(v[n]));
	}
	return max_diam;
}

void SMPWienerHopf::verification(const real &delta)
{
	// Create aliases for v, l
	RMatrixPolynomial &v = m_v;
	RMatrixPolynomial &l = m_l;

	const int g = l.degree();
	const int h = v.degree();
	const int m = Ub(v[0],1);

	IMatrixPolynomial v_int(h);
	IMatrixPolynomial v_old(h);
	IMatrixPolynomial l_int(g);

	// Initialize interval matrix polynomials v and l
	// enclose values for v in small intervals
	for(int k=0; k<=h; ++k)
	{
		v_int[k] = imatrix(1,m,1,m);
		v_old[k] = imatrix(1,m,1,m);
		for(int row=Lb(v[k],1); row<=Ub(v[k],1); ++row)
			for(int col=Lb(v[k],2); col<=Ub(v[k],2); ++col)
			{
				if(v[k][row][col] > 0.0)
					v_old[k][row][col] = v_int[k][row][col] = interval(v[k][row][col]*(1.0 - delta), v[k][row][col]*(1.0 + delta));
				else
					v_old[k][row][col] = v_int[k][row][col] = interval(v[k][row][col]*(1.0 + delta), v[k][row][col]*(1.0 - delta));
			}
	}
	for(int k=0; k<=g; ++k)
	{
		l_int[k] = IMatrixUtils::zeros(1,m,1,m);
	}

	// Perform the Grassmann-Jain algorithm in interval arithmetic
	// Flags and variables
	int contained = false;
	int iteration = 1;
	real max_diam = 0.0;
	real old_max_diam = 1.0;

	// Verification loop
	for(; (!contained) 				// if contained, verification is successful
	&& (max_diam <= 1.0)			// Interval width grows out of range
	&& (max_diam < old_max_diam) 	// No further improvement due to precision of computation
	; ++iteration)
	{
		old_max_diam = max_diam;
		max_diam = grassmannJainStep(v_int, l_int, m_u_int);
		/** Check inclusion.
		 * Note: Only a verification for v is needed, since
		 * the l values are not needed to determine the workload.
		 */
		contained = checkInclusion(v_old, v_int);
		Logging::log(Logging::Debug, "Maximum diameter: ", max_diam);
	}
	// If convergence was not achieved, the loop was exited due to the iteration limit.
	if(!contained) throw IterationLimitException();

	Logging::log(Logging::Info, "Result verified.");
	// Further reduction of the intervals possible?
	IMatrixPolynomial v_verified = v_int;
	IMatrixPolynomial l_verified = l_int;
	max_diam = 0.0;
	old_max_diam = 1.0;
	while(contained && (max_diam < old_max_diam))
	{
		old_max_diam = max_diam;
		max_diam = grassmannJainStep(v_int, l_int, m_u_int);
		contained = checkInclusion(v_verified, v_int);
		if(contained)
		{
			Logging::log(Logging::Info, "Result improved.");
			v_verified = v_int;
			l_verified = l_int;
		}
	}



	// Set information variables.
	m_reqIterations_verification = iteration;

	// Done. Copy values.
	this->m_v_int = v_verified;
	this->m_l_int = l_verified;
}

void SMPWienerHopf::grassmannJainStep(RMatrixPolynomial &v, RMatrixPolynomial &l, RMatrixPolynomial u)
{

	// Aliases for bounds.
	const int g = l.degree();
	const int h = v.degree();
	const int m = Ub(v[0],1);

	// Compute new v
	for (int n = h; n >= 0; n--)
	{
		rmatrixaccu sum(1,m,1,m);
		int minimum = std::min<int>(h - n, g);
        for (int mu = 1; mu <= minimum; mu++)
        {
        	assert(n+mu <= v.degree());
        	assert(mu <= l.degree());
            sum.accumulate(v[n + mu],l[mu]);
        }
        v[n] = v[n] + m_wv * ((u[n+g] + sum.rnd()) - v[n]);
	}

	// Compute inverse
	rmatrix inverse = RMatrixUtils::invert(RMatrixUtils::identity(1,m) - v[0]);

	// Compute new l
    for (int n = g; n >= 1; n--)
    {
		rmatrixaccu sum(1,m,1,m);
        int minimum = std::min<int>(g - n, h);
        for (int mu = 1; mu <= minimum; mu++)
        {
        	assert(n+mu <= l.degree());
        	assert(mu <= v.degree());
        	sum.accumulate(v[mu], l[mu+n]);
        }
        l[n] = l[n] + m_wl * ( (inverse * (u[g-n] + sum.rnd())) - l[n]);
    }
}

RMatrixPolynomial SMPWienerHopf::allocateRMatrixPolynomial(const int max_k, const int max_i, const int max_j)
{
	RMatrixPolynomial l(max_k);
	for(int k = 0; k<=max_k; k++)
		l[k] = RMatrixUtils::zeros(1,max_i, 1,max_j);
	return l;
}

real SMPWienerHopf::distance( const rmatrix &x, const rmatrix &y )
{
    real ergebnis = 0.0;
    for ( int i = Lb(x,1); i <= Ub(x,1); i++ )
    {
        for (int j = Lb(x,2); j <= Ub(x,2); j++)
        {
            ergebnis = std::max<cxsc::real>( ergebnis, abs( x[i][j] - y[i][j] ) );
        }
    }
    return ergebnis;
}

void SMPWienerHopf::copyUnverifiedValues()
{
	RMatrixPolynomial &v = m_v;
	RMatrixPolynomial &l = m_l;

	const int g = l.degree();
	const int h = v.degree();
	const int m = Ub(v[0],1);

	IMatrixPolynomial v_int(h);
	IMatrixPolynomial v_old(h);
	IMatrixPolynomial l_int(g);

	for(int k = 0; k<=h; ++k)
		v_int[k] = imatrix(1,m,1,m);
	for(int k = 0; k<=g; ++k)
		l_int[k] = imatrix(1,m,1,m);

	for(int i = 1; i<=m; ++i)
	{
		for(int j=1; j<=m; ++j)
		{
			for(int k = 0; k<=h; ++k)
				v_int[k][i][j] = interval(v[k][i][j], v[k][i][j]);
			for(int k = 0; k<=g; ++k)
				l_int[k][i][j] = interval(l[k][i][j], l[k][i][j]);
		}
	}

	this->m_v_int = v_int;
	this->m_l_int = l_int;

}

}

