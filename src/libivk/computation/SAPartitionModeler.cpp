#include "SAPartitionModeler.h"
#include <math.h>
#include <assert.h>
#include "utility/RMatrixUtils.h"
#include <cstdlib>
#include <ctime>

namespace ivk
{
const char* SAPartitionModeler::PARAM_AUTOCORRELATION = "autoc";
const char* SAPartitionModeler::PARAM_INITTEMP = "inittemp";
const char* SAPartitionModeler::PARAM_ABORTTEMP = "aborttemp";
const char* SAPartitionModeler::PARAM_ALPHA = "alpha";

SAPartitionModeler::SAPartitionModeler(const Trace *data, const ComputationParameters &parameters)
: PartitionModeler(data, parameters)
{
	
}

SAPartitionModeler::~SAPartitionModeler()
{

}

void SAPartitionModeler::setParameters(ComputationParameters parameters){
	AbstractDiscreteSSMPModeler::setParameters(parameters);
	this->setInitTemp( parameters.getReal( SAPartitionModeler::PARAM_INITTEMP ) );
	this->setAbortTemp( parameters.getReal( SAPartitionModeler::PARAM_ABORTTEMP ));
	this->setAlpha( parameters.getReal( SAPartitionModeler::PARAM_ALPHA ));
	this->setAutoc( parameters.getInt( SAPartitionModeler::PARAM_AUTOCORRELATION ));
}

ComputationParameters SAPartitionModeler::getParameters(){
	ComputationParameters params = PartitionModeler::getParameters();
	params.setInt( SAPartitionModeler::PARAM_AUTOCORRELATION , 	this->autoc );
	params.setReal(SAPartitionModeler::PARAM_INITTEMP , 		this->initTemp );
	params.setReal(SAPartitionModeler::PARAM_ABORTTEMP , 		this->abortTemp );
	params.setReal(SAPartitionModeler::PARAM_ALPHA ,	 		this->alpha );
	return params;
}

void SAPartitionModeler::setInitTemp(real value){ this->initTemp = value; }
void SAPartitionModeler::setAbortTemp(real value){ this->abortTemp = value; }
void SAPartitionModeler::setAlpha(real value){ this->alpha = value; }
void SAPartitionModeler::setAutoc(int value){ this->autoc = value; }

real SAPartitionModeler::getInitTemp(){ return this->initTemp; }
real SAPartitionModeler::getAbortTemp(){ return this->abortTemp; }
real SAPartitionModeler::getAlpha(){ return this->alpha; }
int SAPartitionModeler::getAutoc(){ return this->autoc; }

SSMProcess* SAPartitionModeler::compute()
{
	const int numDSteps = getNumDSteps();
	// discretization
	rvector R = m_ptrData->discretize(m_ptrData->getDiscretizationPoints(numDSteps));
	
	// Choose initial solution
	intvector current = getInitialSolution(R);
	
	SSMProcess currentModel = constructSSMProcess(R, current);
	
	// Compute reference autocorrelation
	const int autoLimit = getAutoc();
	rvector a0 = m_ptrData->getAutocorrelation(autoLimit);
	real currentFitness = squareError(a0, currentModel.getAutocorrelation(autoLimit));

	// Choose initial temperature
	const real T = getInitTemp();
	const real T_min = getAbortTemp();
	const real alpha = getAlpha();
	real currentT = T;
	
	// Iterate
	while(currentT > T_min)
	{
		// Find neighbor
		intvector neighbor = findNeighbor(current);
		
		// Construct SMP model from it
		SSMProcess neighborModel = constructSSMProcess(R, neighbor);
		
		// Compare fitness
		real neighborFitness = squareError(a0, neighborModel.getAutocorrelation(autoLimit));
		// Maybe choose
		bool choose = (neighborFitness < currentFitness);
		if(!choose)
		{
			const real prob = exp(( currentFitness - neighborFitness) / currentT);
			const real rnd = (double)(rand())/RAND_MAX;
			choose = (rnd <=prob);
		}
		
		// If chosen
		if(choose)
		{
			current = neighbor;
			currentModel = neighborModel;
			currentFitness = neighborFitness;
		}
		
		// Cooldown
		currentT *= alpha;
	}
	// done. Return result.
	
	return new SSMProcess(currentModel);
}

SSMProcess SAPartitionModeler::constructSSMProcess(const rvector &R, const intvector &lengths) const
{
	const int numDSteps = getNumDSteps();
	const int numStates = getNumStates();
	const rvector data = m_ptrData->getTrace();
	
	// check Parameters
	int lengths_sum = 0;
	for(int i = Lb(lengths); i<=Ub(lengths); ++i)
		lengths_sum += lengths[i];
	assert(lengths_sum == numDSteps);
	
	// compute l,n
	int current = Lb(data);
	intvector l(lengths);
	intvector n(lengths);
	for(int i=Lb(lengths); i<=Ub(lengths); ++i)
	{
		l[i] = current;
		n[i] = l[i] + lengths[i] -1;
		current += lengths[i];
	}
	
	// compute distributions
	rmatrix dist = RMatrixUtils::zeros(0, numStates-1, Lb(R), Ub(R));
	for(int state=Lb(dist,1); state<=Ub(dist,1); ++state)
	{
		real sum = 0.0;
		for(int j=l[state]; j<=n[state]; ++j)
			sum += R[j];
		for(int j = Lb(dist,2); j<=Ub(dist, 2); ++j)
		{
			if(j<l[state] || j>n[state])
				dist[state][j] = 0.0;
			else
				dist[state][j] = R[j]/sum;
		}
	}
	
	// compute transitions
	rmatrix count = RMatrixUtils::zeros(1, numStates, 1, numStates);
	
	const real minValue = m_ptrData->getMinimum();
	const real maxValue = m_ptrData->getMaximum();
	
	const real Delta = (maxValue-minValue)/(numDSteps-1);
	rvector s(0,numDSteps);
	for(int l=Lb(s); l<=Ub(s); ++l)
		s[l] = minValue + l*Delta;
	
	intvector index(Lb(data), Ub(data));
	for(int i=Lb(index); i<=Ub(index); ++i)
	{
		index[i] = -1;
	}
	
	for(int k = Lb(l); k<=Ub(l); ++k)
	{
		for(int i = Lb(data); i<=Ub(data); ++i)
		{
			if((data[i] >= (s[l[k]]-Delta/2)) && (data[i] <= (s[n[k]]+Delta/2)))
				index[i] = k+1;
		}	
	}
	
	for(int i=Lb(data)+1; i<=Ub(data);++i)
	{
		count[index[i-1]][index[i]] += 1.0;
	}
	
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
			if(sum>0)
				count[i][j]/=sum;
		}
	}
	SSMProcess ret(count, dist);
	return ret;
}

intvector SAPartitionModeler::getInitialSolution(const rvector &R) const
{
	const int numStates = getNumStates();
	const int numDSteps = getNumDSteps();
	// Compute borders according to Traczinski dissertation
	intvector lengths(0, numStates-1);

	intvector l(1, numStates);
	intvector n(1, numStates);
	for(int k = Lb(lengths)+1; k<=Ub(lengths)+1; ++k)
	{
		real compare;
		compare = (k - 1.0)/numStates;

		l[k] = computeLN(R, numDSteps, compare,1);
		compare = ((real)k)/numStates;
		n[k] = computeLN(R, numDSteps, compare,0);
		
		lengths[k-1] = n[k] - l[k] + 1;

	}
	if(n[numStates] != (numDSteps-1))
	{
		cerr << "n: " << n[numStates] << endl;
		lengths[Ub(lengths)] += (numDSteps-1)-n[numStates];
		n[numStates] = numDSteps-1;
		
	}
	checkLN(l,n);
	return lengths;
}

intvector SAPartitionModeler::findNeighbor(const intvector &lengths)
{
	intvector ret(lengths);
	const int lb = Lb(lengths);
	const int ub = Ub(lengths);
	const int range = ub - lb +1;
	int abort = false;
	while(!abort)
	{
		const int from = (int)(lb + (range * ((double)rand())/RAND_MAX));
		const int to = (int)(lb + (range * ((double)rand())/RAND_MAX));
		if((lengths[from]> 1) && (from != to))
		{
			ret[to] += 1;
			ret[from] -= 1;
			abort = true;
		}
	}
	return ret;
}

real SAPartitionModeler::squareError(const rvector &a, const rvector &b)
{
	assert(Lb(a)==Lb(b));
	assert(Ub(a)==Ub(b));
	real sum = 0.0;
	for(int i=Lb(a); i<=Ub(a); ++i)
	{
		real tmp = a[i]-b[i];
		sum += tmp*tmp;
	}
	return sum;
}

}
