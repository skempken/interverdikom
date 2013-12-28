#ifndef ISMPPFRESULT_H_
#define ISMPPFRESULT_H_

#include <civector.hpp>
#include <cimatrix.hpp>

#include "data/WorkloadVector.hpp"

#include "data/SSMProcess.h"


using namespace cxsc;


namespace ivk {

class ISMPPFResult
{
public:
	ISMPPFResult();
	
	virtual ~ISMPPFResult();

	bool getVerifiedCoefficients(cimatrix & alpha, civector & beta) const;
	
	IWorkloadVector getWorkload(int upTo) const;
	
	interval getWorkloadComponent(int index) const;
	
	bool calculateGamma(const SSMProcess & process);
	
	bool success;
	
	int M;
	
	int h;
	
	cimatrix eigenVectors;
	
	civector eigenValues;
	
	civector gamma;
};

}

#endif /*ISMPPFRESULT_H_*/
