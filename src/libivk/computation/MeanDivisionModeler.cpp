#include "MeanDivisionModeler.h"

namespace ivk
{

MeanDivisionModeler::MeanDivisionModeler(const Trace* ptrData,const ComputationParameters &parameters)
: AbstractDiscreteSSMPModeler(ptrData, parameters)
{
	
}

MeanDivisionModeler::~MeanDivisionModeler()
{
}

SSMProcess* MeanDivisionModeler::compute()
{
	rvector trace = m_ptrData->getTrace();
	real mean = m_ptrData->getMean();
	vector<real> means;
	const int recursions = this->getNumStates()/2;
	addLowerMeans(mean, means, recursions);
	means.push_back(mean);
	addUpperMeans(mean, means, recursions);
	
	// Generate index sequence
	intvector index(Lb(trace), Ub(trace));
	for(int i = Lb(index); i<=Ub(index); ++i)
	{
		index[i] = 0;
		for(vector<real>::iterator it = means.begin(); it != means.end(); it++)
		{
			if(trace[i] > (*it))
				index[i]++;
		}
	}
	return modelFromIndexSequence(index);
	
}

void MeanDivisionModeler::addLowerMeans(const real &bound, vector<real> &means, int recursion)
{
	if(recursion<=0) return;
	rvector trace = m_ptrData->getTrace();
	real sum = 0.0;
	int count = 0;
	for(int i = Lb(trace); i<=Ub(trace); ++i)
	{
		if(trace[i] < bound)
		{
			sum += trace[i];
			count++;
		}
	}
	sum /= count;
	addLowerMeans(sum, means, recursion-1);
	means.push_back(sum);
}

void MeanDivisionModeler::addUpperMeans(const real &bound, vector<real> &means, int recursion)
{
	if(recursion==0) return;
	rvector trace = m_ptrData->getTrace();
	real sum = 0.0;
	int count = 0;
	for(int i = Lb(trace); i<=Ub(trace); ++i)
	{
		if(trace[i] > bound)
		{
			sum += trace[i];
			count++;
		}
	}
	sum /= count;
	
	means.push_back(sum);
	addUpperMeans(sum, means, recursion-1);
}

}
