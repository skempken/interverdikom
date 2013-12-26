#ifndef PARTITIONMODELER_H_
#define PARTITIONMODELER_H_

#include <rvector.hpp>
#include <real.hpp>
#include <rmatrix.hpp>

#include "AbstractDiscreteSSMPModeler.h"

using cxsc::rvector;
using cxsc::real;
using cxsc::rmatrix;

namespace ivk
{

class PartitionModeler : public AbstractDiscreteSSMPModeler
{
public:
	
	PartitionModeler(const Trace *data, const ComputationParameters &parameters);
	virtual ~PartitionModeler();
		
	// Computation interface
	virtual SSMProcess* compute();
	
protected:

	int computeLN(const rvector R, const int g, const real compare, const int offset) const;
	int checkLN(const intvector &l, const intvector &n) const;
};

}
#endif /*PARTITIONMODELER_H_*/
