#include "computation/SimpleMCModeler.h"
#include "utility/RealUtils.h"
namespace ivk
{

SimpleMCModeler::SimpleMCModeler(const Trace * ptrData, const ComputationParameters &parameters)
: AbstractDiscreteSSMPModeler(ptrData, parameters)
{

}

SimpleMCModeler::~SimpleMCModeler()
{
	
}

SSMProcess* SimpleMCModeler::compute()
{
	setProgressText("starting computation");
	setProgressMax(110);
	int pvalue = 1;
	setProgressValue(pvalue);
	const rvector &trace = m_ptrData->getTrace();
	const real minValue = m_ptrData->getMinimum();
	const real maxValue = m_ptrData->getMaximum();
	const int numStates = getNumStates();

	const real stepWidth = (maxValue - minValue) / real(numStates); 
	
	// construct index sequence
	intvector index(Lb(trace), Ub(trace));
	int threshold = (int) floor((Ub(trace)-Lb(trace)) / 100 );
	
	for(int i = Lb(trace); i<=Ub(trace); ++i)
	{
		const real value = trace[i];
		index[i] = (int)_double((value - minValue)/stepWidth);
		if(index[i]==0) index[i] = 1;
		if(i/threshold > pvalue){ 
			pvalue++;
			setProgressValue(pvalue);
		}
	}
	setProgressValue(105);
	setProgressText("generating Model From Index Sequence");
	return modelFromIndexSequence(index);
}



}
