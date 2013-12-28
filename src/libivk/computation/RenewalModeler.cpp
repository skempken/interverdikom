#include "RenewalModeler.h"

namespace ivk
{

RenewalModeler::RenewalModeler(const Trace * ptrData, const ComputationParameters &parameters)
: AbstractDiscreteSSMPModeler(ptrData, parameters)
{
}

RenewalModeler::~RenewalModeler()
{
}

SSMProcess* RenewalModeler::compute()
{
	setProgressText("starting computation");
	setProgressMax(100);
	setProgressValue(1);
	intvector index(m_ptrData->getLowerBound(), m_ptrData->getUpperBound());
	for(int i = Lb(index); i<=Ub(index); ++i){
		index[i] = 1;
		setProgressValue( ((double)( Ub( index ) - Lb( index ) ) / 100.0) * i );
	}
	setProgressText("generation model");
	setProgressValue(98);
	SSMProcess* _tmp = modelFromIndexSequence(index);
	return _tmp;
}

}
