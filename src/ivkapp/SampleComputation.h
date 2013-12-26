#ifndef SAMPLECOMPUTATION_H_
#define SAMPLECOMPUTATION_H_

#if 0

#include "computation/AbstractComputation.hpp"
#include "computation/ComputationParameters.h"

#include "real.hpp"
#include <QDomElement>

/// Demonstration class to show correct implementation of ivk::Computation
class SampleComputation : public ivk::AbstractComputation<bool, bool>
{
public:
	//SampleComputation() {};
	virtual ~SampleComputation();
	
	bool* compute();
	cxsc::real getResultInt()
		{ return this->resultValue; }
	
	void setParameters(const ivk::ComputationParameters &parameters) {}
	
	QDomElement exportXml(QDomDocument document);
	
	void importXml(QDomElement domElement);

	
private:
	cxsc::real resultValue;
};

#endif

#endif /*SAMPLECOMPUTATION_H_*/
