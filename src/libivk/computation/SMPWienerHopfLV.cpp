#include "SMPWienerHopfLV.h"

#include <l_imatrix.hpp>
#include <l_interval.hpp>

#include "utility/l_IMatrixUtils.h"
#include "utility/IMatrixUtils.h"
#include "utility/Logging.hpp"

namespace ivk
{

SMPWienerHopfLV::SMPWienerHopfLV(const SSMProcess* data, const ComputationParameters &parameters)
: SMPWienerHopf(data, parameters)
{
	// Nothing else to do.
}

SMPWienerHopfLV::~SMPWienerHopfLV()
{
}

/**
 * "compute()" method from SMPWienerHopf.
 * currentDelta is a multiple precision real here.
 */
ISMPWHFactors* SMPWienerHopfLV::compute()
{
	Logging::log(Logging::Info, "Starting Wiener-Hopf LV");
	// Compute approximations
	grassmannJainIteration();

	// Perform verification
	l_real currentDelta = l_real(m_epsilon);
	currentDelta *= currentDelta;
	setProgressText("Verification");
	const int numVerificationIterations = 2 * (-(int)std::log10(_double(m_epsilon)));
	setProgressMax(numVerificationIterations);

	int iterationCount = 1;
	while(currentDelta <=1.0)
	{
		try
		{
			setProgressValue(iterationCount++);
			verification(currentDelta);
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

void SMPWienerHopfLV::verification(const l_real &delta)
{
	// Create aliases for v, l
	RMatrixPolynomial &v = m_v;
	RMatrixPolynomial &l = m_l;

	const int g = l.degree();
	const int h = v.degree();
	const int m = Ub(v[0],1);

	Polynomial<l_imatrix> v_int(h);
	Polynomial<l_imatrix> v_old(h);
	Polynomial<l_imatrix> l_int(g);

	Polynomial<l_imatrix> u_int(m_u.degree());
	l_real maxdiam(0.0);
	for(int i = 0; i<=m_u.degree(); ++i)
	{
		u_int[i] = (l_imatrix) m_u[i];
		maxdiam = std::max<l_real>(maxdiam, l_IMatrixUtils::maxDiam(u_int[i]));
	}
	Logging::log(Logging::Debug, "Maximum diameter", maxdiam);



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
					v_old[k][row][col] = v_int[k][row][col] = l_interval(((l_real)v[k][row][col])*(1.0 - delta), ((l_real)v[k][row][col])*(1.0 + delta));
				else
					v_old[k][row][col] = v_int[k][row][col] = l_interval(((l_real)v[k][row][col])*(1.0 + delta), ((l_real)v[k][row][col])*(1.0 - delta));
			}
	}
	for(int k=0; k<=g; ++k)
	{
		l_int[k] = l_IMatrixUtils::zeros(1,m,1,m);
	}

	// Perform the Grassmann-Jain algorithm in interval arithmetic
	// Flags and variables
	int contained = false;
	int iteration = 1;
	l_real max_diam(1.0);
	l_real old_max_diam(1.0);

	// Verification loop
	for(; (!contained) 				// if contained, verification is successful
	&& (max_diam <= 1.0)			// Interval width grows out of range
	&& (max_diam <= old_max_diam) 	// No further improvement due to precision of computation
	; ++iteration)
	{
		old_max_diam = max_diam;
		max_diam = grassmannJainStep(v_int, l_int, u_int);
		/** Check inclusion.
		 * Note: Only a verification for v is needed, since
		 * the l values are not needed to determine the workload.
		 */
		contained = checkInclusion(v_old, v_int);

		Logging::log(Logging::Debug, "Maximum diameter", max_diam);
		Logging::log(Logging::Debug, "OldMaxDiam", old_max_diam);
		Logging::log(Logging::Debug, "Contained", contained);
		if(iteration > 100) break;
	}
	// If convergence was not achieved, the loop was exited due to the iteration limit.
	if(!contained) throw IterationLimitException();

	Logging::log(Logging::Info, "Result verified.");

	// Further reduction of the intervals possible?
	Polynomial<l_imatrix> v_verified = v_int;
	Polynomial<l_imatrix> l_verified = l_int;
	max_diam = 0.0;
	old_max_diam = 1.0;
	while(contained && (max_diam != old_max_diam))
	{
		old_max_diam = max_diam;
		max_diam = grassmannJainStep(v_int, l_int, u_int);
		contained = checkInclusion(v_verified, v_int);
		if(contained)
		{
			Logging::log(Logging::Debug, "Result improved. Maximum diameter", max_diam);
			v_verified = v_int;
			l_verified = l_int;
		}
	}



	// Set information variables.
	m_reqIterations_verification = iteration;

	// Done. Copy values.

	// Initialise.
	this->m_v_int = IMatrixPolynomial(v_verified.degree());
	this->m_l_int = IMatrixPolynomial(l_verified.degree());
	for(int i = 0; i<=v_verified.degree(); ++i)
	{
		this->m_v_int[i] = imatrix(1,m,1,m);
	}
	for(int i = 0; i<=l_verified.degree(); ++i)
	{
		this->m_l_int[i] = imatrix(1,m,1,m);
	}

	// Copy values (cast to double precision)
	for(int j = 1; j<=m; ++j)
	{
		for(int k = 1; k<=m; ++k)
		{
			for(int i = 0; i<=v_verified.degree(); ++i)
			{
				this->m_v_int[i][j][k] = _interval(v_verified[i][j][k]);
			}
			for(int i = 0; i<=l_verified.degree(); ++i)
			{
				this->m_l_int[i][j][k] = _interval(l_verified[i][j][k]);
			}
		}
	}

}

l_real SMPWienerHopfLV::grassmannJainStep(Polynomial<l_imatrix> &v, Polynomial<l_imatrix> &l, Polynomial<l_imatrix> u)
{
	// Aliases for bounds
	const int m = Ub(v[0],1);
	const int g = l.degree();
	const int h = v.degree();

	// Return value: Maximum diameter of the intervals
	l_real max_diam(0.0);

	// Compute new l
    for (int n = g; n >= 1; n--)
    {
		l_imatrix sum = l_IMatrixUtils::zeros(1,m,1,m);
        int minimum = std::min<int>(g - n, h);
        for (int mm = 1; mm <= minimum; mm++)
        {
        	assert(n+mm <= l.degree());
        	assert(mm <= v.degree());
        	sum += v[mm] * l[mm+n];
        }
        assert(g-n>=0);
        assert(g-n<=u.degree());
        l_imatrix inverse = l_IMatrixUtils::invert(l_IMatrixUtils::identity(Lb(v[0],1), Ub(v[0],1)) - v[0]);
        l[n] = inverse * (u[g-n] + sum);
        max_diam = std::max<l_real>(max_diam, l_IMatrixUtils::maxDiam(l[n]));
    }
	// Compute new v
	for (int n = h; n >= 0; n--)
	{
		l_imatrix sum = l_IMatrixUtils::zeros(1,m,1,m);
		int minimum = std::min<int>(h - n, g);
        for (int mm = 1; mm <= minimum; mm++)
        {
        	assert(n+mm <= v.degree());
        	assert(mm <= l.degree());
            sum += v[n + mm] * l[mm];
        }
        v[n] = u[n+g] + sum;
        max_diam = std::max<l_real>(max_diam, l_IMatrixUtils::maxDiam(v[n]));
	}
	return max_diam;
}

}
