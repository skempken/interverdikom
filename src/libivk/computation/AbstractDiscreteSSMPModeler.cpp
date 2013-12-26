#include "AbstractDiscreteSSMPModeler.h"

#include <assert.h>
#include <climits>
#include "utility/RMatrixUtils.h"


namespace ivk
{

const char *AbstractDiscreteSSMPModeler::PARAM_NUMDSTEPS = "numDSteps";
const char *AbstractDiscreteSSMPModeler::PARAM_NUMSTATES = "numStates";

AbstractDiscreteSSMPModeler::AbstractDiscreteSSMPModeler(const Trace *data, const ComputationParameters &parameters)
: AbstractComputation<Trace, SSMProcess>(data, parameters)
{
	setParameters(parameters);
}

AbstractDiscreteSSMPModeler::~AbstractDiscreteSSMPModeler()
{
}

void AbstractDiscreteSSMPModeler::setParameters(const ComputationParameters &parameters)
{
	this->m_parameters = parameters;
	setNumDSteps(parameters.getInt(PARAM_NUMDSTEPS));
	setNumStates(parameters.getInt(PARAM_NUMSTATES));
}

void AbstractDiscreteSSMPModeler::setNumDSteps(const int value)
{
	this->m_numDSteps = value;
}

int AbstractDiscreteSSMPModeler::getNumDSteps() const
{
	return this->m_numDSteps;
}

void AbstractDiscreteSSMPModeler::setNumStates(const int value)
{
	this->m_numStates = value;
}

int AbstractDiscreteSSMPModeler::getNumStates() const
{
	return this->m_numStates;
}

int AbstractDiscreteSSMPModeler::suggestNumStates()
{
	const real maxValue = m_ptrData->getMaximum();
	const real minValue = m_ptrData->getMinimum();
	const real std = m_ptrData->getStandardDeviation();

	return (int)_double((maxValue - minValue)/std);
}


int AbstractDiscreteSSMPModeler::suggestNumDiscretizationSteps(){
	return this->suggestNumStates();
}
rmatrix AbstractDiscreteSSMPModeler::computeTransition(const intvector &index)
{
	// find minimum and maximum values
	intvector _index(index);

	int minValue = INT_MAX;
	int maxValue = -INT_MAX;
	for(int i = Lb(index); i<=Ub(index); ++i)
	{
		minValue = min<int>(minValue, index[i]);
		maxValue = max<int>(maxValue, index[i]);
	}

	if( minValue != 1){
		for( int i = Lb(index) ; i <= Ub( index ) ; i++){
			_index[i] -= minValue-1;
		}
		minValue -= minValue-1;
		maxValue -= minValue-1;
	}

	rmatrix count = RMatrixUtils::zeros(minValue, maxValue, minValue, maxValue);

	for(int i=Lb(_index)+1; i<=Ub(_index);++i)
		count[_index[i-1]][_index[i]] += 1.0;

	// normalize
	for(int i=Lb(count,1); i<=Ub(count,1); ++i)
	{
		real sum = 0.0;
		for(int j=Lb(count,2); j<=Ub(count,2); ++j)
		{
			sum += count[i][j];
		}
		for(int j=Lb(count,2); j<=Ub(count,2); ++j)
		{
			count[i][j]/=sum;
		}
	}

	cxsc::SetLb(count, ROW ,1);
	cxsc::SetLb(count, COL ,1);
	return count;
}

SSMProcess* AbstractDiscreteSSMPModeler::modelFromIndexSequence(const intvector &index)
{
	rmatrix transition = computeTransition(index);
	int numDSteps = getNumDSteps();
	rvector discP = m_ptrData->getDiscretizationPoints(numDSteps);
	rmatrix dists = m_ptrData->discretize(discP, index);
	SSMProcess* _tmp = new SSMProcess(transition, dists);
	return _tmp;
}

}
