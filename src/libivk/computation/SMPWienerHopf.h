#ifndef SMPWIENERHOPF_H_
#define SMPWIENERHOPF_H_

#include "AbstractComputation.hpp"
#include "data/SSMProcess.h"
#include "data/ISMPWHFactors.h"
#include "utility/Polynomial.hpp"
#include "exception/IterationLimitException.h"
#include "utility/RMatrixUtils.h"

namespace ivk
{

class SMPWienerHopf : public AbstractComputation<SSMProcess, ISMPWHFactors> 
{
public:
	// Parameter keys
	static const char* PARAM_EPSILON;
	static const char* PARAM_NUMITERATIONS;
	static const char* PARAM_RELAXATIONSTEPS;
	
	SMPWienerHopf(const SSMProcess* data, const ComputationParameters &parameters);
	virtual ~SMPWienerHopf();
	
	void setEpsilon(const real &_epsilon);
	real getEpsilon() const { return m_epsilon; }
	
	virtual void setNumIterations(const int &_numIterations);
	virtual int getNumIterations() const { return m_numIterations;}
	virtual void setRelaxationSteps(const int &relaxationSteps);
	virtual int getRelaxationSteps() const {return m_relaxationSteps;}
	
	// Additional info about the process
	virtual int getNumApproximationIterations() { return m_reqIterations_approximation; }
	virtual int getNumVerificationIterations() { return m_reqIterations_verification; }
	virtual bool isVerificationSuccessful() { return m_verification_successful; }
	
	// Computation interface
	virtual ISMPWHFactors* compute();
	virtual void setParameters(const ComputationParameters &parameters);
	
	// Helper functions
	static real distance( const rmatrix &x, const rmatrix &y );
	static RMatrixPolynomial allocateRMatrixPolynomial(const int k, const int i, const int j);
	
	template<class P>
	static bool checkInclusion(Polynomial<P> &container, Polynomial<P> &contained)
	{
		int ret = true;
		
		for(int k = 0; k<=container.degree(); ++k)
			for(int i=Lb(container[k],1); i<=Ub(container[k],1); ++i)
				for(int j=Lb(container[k],2); j<=Ub(container[k],2); ++j)
					ret &= (contained[k][i][j] <= container[k][i][j]);
		
		return ret;
	}

protected:
	real m_epsilon;
	int m_numIterations;
	int m_reqIterations_approximation;
	int m_reqIterations_verification;
	bool m_verification_successful;
	
	// Variables
	/// Interval difference matrices.
	IMatrixPolynomial m_u_int;
	
	/// Floating-point difference matrices.
	RMatrixPolynomial m_u;
	
	/// Interval matrices denoting idle phase distributions.
	IMatrixPolynomial m_l_int;
	
	/// Interval matrices denoting phase niveau distributions.
	IMatrixPolynomial m_v_int;
	
	/// Floating-point matrices denoting idle phase distributions.
	RMatrixPolynomial m_l;
	
	/// Floating-point matrices denoting phase niveau distributions.
	RMatrixPolynomial m_v;
	
	/// Setter method for queue object to be analyzed.
	/**
	 * \param queue Queue object to be analyzed.
	 */
	void setQueue(const SSMProcess *queue);
	
	virtual void grassmannJainIteration(); // First algorithm from Grassmann and Jain.
	virtual void grassmannJainStep(RMatrixPolynomial &v, RMatrixPolynomial &l, RMatrixPolynomial u);
	virtual real grassmannJainStep(IMatrixPolynomial &vPolynomial, IMatrixPolynomial &l, IMatrixPolynomial u);
	virtual void verification(const real &currentDelta);
	virtual void copyUnverifiedValues();
	
private:
	/// Relaxation parameter for Vl = u
	real m_wl;
	/// Relaxation parameter for Lv = u
	real m_wv;
	/// Number of steps for re-estimating the relaxation parameters
	int m_relaxationSteps;
	
	/// estimates the relaxation parameter
	static real estimateRelaxationParameter(const RMatrixPolynomial &x_1, const RMatrixPolynomial &x0, const RMatrixPolynomial &x1, const real &w);
	
};

}

#endif /*SMPWIENERHOPF_H_*/
