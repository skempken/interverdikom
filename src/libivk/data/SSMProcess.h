#ifndef SSMPROCESS_H_
#define SSMPROCESS_H_

#include "SMProcess.h"

#include "utility/MatrixPolynomial.hpp"

using namespace std;
using namespace cxsc;

namespace ivk
{

/// Represents a special-case semi-Markov process
class SSMProcess : public SMProcess
{
public:
	SSMProcess();
	
	/// Represent an SMP as an SSMP
	SSMProcess(const SMProcess& process);
	SSMProcess(const rmatrix &_transition, const rmatrix &_distributions, const int trimEmptyStates = true);
	SSMProcess(const imatrix &_transition, const imatrix &_distributions, const int trimEmptyStates = true);
	virtual ~SSMProcess();
	
	virtual ivector getDistribution(const int stateFrom, const int stateTo) const;
	
	void setDistributions(const rmatrix &_distributions);
	void setDistributions(const imatrix &_distributions);
	imatrix getDistributions() const;
	
	real getExpectationValue() const;
	rvector getStateMeans() const;
	
	rvector getAutocorrelation(const int upTo) const;
	real getVariance() const;
	real getStandardDeviation() const;
	
	void trimDistributions();
	
	friend SSMProcess operator-(const SSMProcess &a, const SSMProcess &b);
	friend SSMProcess operator+(const SSMProcess &a, const SSMProcess &b);

	static ivector subDists(const ivector &a, const ivector &b);
	static ivector addDists(const ivector &a, const ivector &b);
	static rvector subDists(const rvector &a, const rvector &b);
	static rvector addDists(const rvector &a, const rvector &b);
	
	IMatrixPolynomial getCharacteristicPolynomialMatrix() const;
	
protected:
	imatrix m_distributions;
	
	
	
};

}

#endif /*SSMPROCESS_H_*/
