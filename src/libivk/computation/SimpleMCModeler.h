#ifndef SIMPLEMCMODELER_H_
#define SIMPLEMCMODELER_H_

#include "AbstractDiscreteSSMPModeler.h"

#include <fstream>
#include <iostream>

namespace ivk
{

/// Models the given Trace as a simple Markov chain.
/**
 * Idea from Rose, 1997: Simple and Efficient Models for 
 * Variable Bit Rate MPEG Video Traffic. Performance Evaluation 30.
 */

class SimpleMCModeler : public AbstractDiscreteSSMPModeler
{
public:
	SimpleMCModeler(const Trace * ptrData, const ComputationParameters &parameters);
	virtual ~SimpleMCModeler();
	
	virtual SSMProcess* compute();
};

}

#endif /*SIMPLEMCMODELER_H_*/
