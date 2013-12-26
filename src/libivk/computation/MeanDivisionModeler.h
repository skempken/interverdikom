#ifndef MEANDIVISIONMODELER_H_
#define MEANDIVISIONMODELER_H_

#include "AbstractDiscreteSSMPModeler.h"

#include <vector>

using std::vector;

namespace ivk
{

class MeanDivisionModeler : public AbstractDiscreteSSMPModeler
{
public:
	MeanDivisionModeler(const Trace* ptrData,const ComputationParameters &parameters);
	virtual ~MeanDivisionModeler();
	
	SSMProcess* compute();
	
private:
	void addLowerMeans(const real &bound, vector<real> &means, int recursion);
	void addUpperMeans(const real &bound, vector<real> &means, int recursion);
};

}

#endif /*MEANDIVISIONMODELER_H_*/
