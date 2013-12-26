#include "SPEA2Modeler.h"

#include <math.h>
#include <algorithm>
#include <map>
#include "utility/RMatrixUtils.h"
#include "utility/IntMatrixUtils.h"

#include "utility/Logging.hpp"

namespace ivk
{
	const char* SPEA2Modeler::PARAM_POPSIZE = "popSize";
	const char* SPEA2Modeler::PARAM_ARCHIVESIZE = "archiveSize";
	const char* SPEA2Modeler::PARAM_NUMITERATIONS = "numIterations";
	const char* SPEA2Modeler::PARAM_AUTOCORRELATION = "autocorrelation";
	const char* SPEA2Modeler::PARAM_MCROSSOVER = "mCrossover";
	const char* SPEA2Modeler::PARAM_MBLOCK = "mBlock";
	const char* SPEA2Modeler::PARAM_MINVERSE = "mInverse";
	const char* SPEA2Modeler::PARAM_MSHUFFLE = "mShuffle";
	const char* SPEA2Modeler::PARAM_MSWAP = "mSwap";
	
SPEA2Modeler::SPEA2Modeler(const Trace* data, const ComputationParameters &parameters)
: AbstractDiscreteSSMPModeler(data, parameters)
{
	m_scaledTrace = 0;
	// set default values
/*	setPopSize(60);
	setArchiveSize(20);
	setNumIterations(500);
	
	m_autocorrelationLimit = 100;
	m_prob_crossover = 0.2;
	m_prob_block = 0.2;
	m_prob_inverse = 0.2;
	m_prob_shuffle = 0.2;
	m_prob_swap = 0.2;*/
	
	// Compute scaled trace
	const real minValue = m_ptrData->getMinimum();
	const real maxValue = m_ptrData->getMaximum();
	const real Delta = (maxValue-minValue)/(getNumDSteps()-1);
	rvector originalTrace = m_ptrData->getTrace();
	rvector scaledTrace(originalTrace);
	for(int i = Lb(scaledTrace); i<=Ub(scaledTrace); ++i)
	{
		scaledTrace[i] = (originalTrace[i]-minValue) / Delta;
	}
	m_scaledTrace = new Trace(scaledTrace);
}

SPEA2Modeler::~SPEA2Modeler()
{
	if(m_scaledTrace) delete m_scaledTrace;
}

ComputationParameters SPEA2Modeler::getParameters(){
	ComputationParameters param(AbstractDiscreteSSMPModeler::getParameters());
	param.setInt( SPEA2Modeler::PARAM_NUMSTATES, this->getNumStates());
	param.setInt( SPEA2Modeler::PARAM_NUMDSTEPS, this->getNumDSteps());
	param.setInt( SPEA2Modeler::PARAM_POPSIZE , this->getPopSize() ); 
	param.setInt( SPEA2Modeler::PARAM_ARCHIVESIZE , this->getArchiveSize()); 
	param.setInt( SPEA2Modeler::PARAM_NUMITERATIONS , this->getNumIterations()); 
	param.setInt( SPEA2Modeler::PARAM_AUTOCORRELATION, this->getAutocorrelationLimit());
	param.setReal( SPEA2Modeler::PARAM_MCROSSOVER, this->getMCrossover());
	param.setReal( SPEA2Modeler::PARAM_MBLOCK, this->getMBlock());
	param.setReal( SPEA2Modeler::PARAM_MINVERSE, this->getMInverse());
	param.setReal( SPEA2Modeler::PARAM_MSHUFFLE, this->getMShuffle());
	param.setReal( SPEA2Modeler::PARAM_MSWAP, this->getMSwap());
	return param;
}

void SPEA2Modeler::setParameters(const ComputationParameters param){
	AbstractDiscreteSSMPModeler::setParameters(param);
	this->setNumStates( 			param.getInt( SPEA2Modeler::PARAM_NUMSTATES) );
	this->setNumDSteps( 			param.getInt( SPEA2Modeler::PARAM_NUMDSTEPS) );
	this->setPopSize( 				param.getInt( SPEA2Modeler::PARAM_POPSIZE) );
	this->setArchiveSize( 			param.getInt( SPEA2Modeler::PARAM_ARCHIVESIZE) );
	this->setNumIterations( 		param.getInt( SPEA2Modeler::PARAM_NUMITERATIONS) );
	this->setAutocorrelationLimit( 	param.getInt( SPEA2Modeler::PARAM_AUTOCORRELATION) );
	this->setMCrossover(_double(	param.getReal(SPEA2Modeler::PARAM_MCROSSOVER)));
	this->setMBlock(_double(		param.getReal(SPEA2Modeler::PARAM_MBLOCK)));
	this->setMInverse(_double(		param.getReal(SPEA2Modeler::PARAM_MINVERSE)));
	this->setMShuffle(_double(		param.getReal(SPEA2Modeler::PARAM_MSHUFFLE)));
	this->setMSwap(_double(			param.getReal(SPEA2Modeler::PARAM_MSWAP)));
}

void SPEA2Modeler::setPopSize(int value)
{
	if(value>0)
		this->m_popSize = value;
	else
		throw std::out_of_range("Population size is out of range.");
}

int SPEA2Modeler::getPopSize(){
	return m_popSize;
}

void SPEA2Modeler::setArchiveSize(int value)
{
	if(value>0)
		m_archiveSize=value;
	else
		throw std::out_of_range("Archive size is out of range.");
}

int SPEA2Modeler::getArchiveSize()
{
	return m_archiveSize;
}

void SPEA2Modeler::setNumIterations(int value)
{
	if(value>0)
		m_numIterations=value;
	else
		throw std::out_of_range("Number of iterations is out of range.");
}

int SPEA2Modeler::getNumIterations()
{
	return m_numIterations;
}

void SPEA2Modeler::setAutocorrelationLimit(int value)
{
	if(value > 0)
		m_autocorrelationLimit = value;
	else
		throw std::out_of_range("Autocorrelation limit is out of range.");
}

int SPEA2Modeler::getAutocorrelationLimit()
{
	return m_autocorrelationLimit;
}

void SPEA2Modeler::setMCrossover(double value){ this->m_prob_crossover = value; }
double SPEA2Modeler::getMCrossover(){ return this->m_prob_crossover; }

void SPEA2Modeler::setMInverse(double value){ this->m_prob_inverse = value; }
double SPEA2Modeler::getMInverse(){ return this->m_prob_inverse; }

void SPEA2Modeler::setMBlock(double value){ this->m_prob_block = value; }
double SPEA2Modeler::getMBlock(){ return this->m_prob_block; }

void SPEA2Modeler::setMShuffle(double value){ this->m_prob_shuffle = value; }
double SPEA2Modeler::getMShuffle(){ return this->m_prob_shuffle; }

void SPEA2Modeler::setMSwap(double value){ this->m_prob_swap = value; }
double SPEA2Modeler::getMSwap(){ return this->m_prob_swap; }

SPEA2Modeler::Individual SPEA2Modeler::initIndividual()
{
	const int numStates = getNumStates();
	Individual individual(m_ptrData->getLowerBound(), m_ptrData->getUpperBound());
	for(int i = m_ptrData->getLowerBound(); i<=m_ptrData->getUpperBound(); ++i)
	{
		individual[i] = (int)(numStates * ((double)rand()/RAND_MAX));
	}
	return individual;
}

SSMProcess* SPEA2Modeler::compute()
{
	setProgressText("SPEA2 Optimization.");
	setProgressMax(m_numIterations);
	
	// Compute value k
	const int k = 1 + (int) sqrt(m_popSize + m_archiveSize);
	
	// Compute reference values
	m_trace_variance = m_scaledTrace->getVariance();
	m_trace_mean = m_scaledTrace->getMean();
	Logging::log(Logging::Debug, "Trace mean", m_trace_mean);
	m_trace_autocorrelation = m_ptrData->getAutocorrelation(m_autocorrelationLimit);
	
	// --- Initialization ---
	Logging::log(Logging::Info, "SPEA: Initialization");
	// Initialize population
	vector<Individual> population;
	for(unsigned int i = 0; i<m_popSize; ++i)
		population.push_back(initIndividual());
	
	// Initialize archive
	vector<Individual> archive;
	for(unsigned int i = 0; i<m_archiveSize; ++i)
		archive.push_back(initIndividual());
	
	// Main iteration loop
	for(unsigned int currentIteration = 1; currentIteration <=m_numIterations; ++currentIteration)
	{
		setProgressValue(currentIteration);
		Logging::log(Logging::Debug, "Starting iteration", currentIteration);
		
		// Combine population and archive
		vector<Individual> comb_0;
		for(vector<Individual>::iterator it = population.begin(); it!=population.end(); ++it)
			comb_0.push_back(*it);
		for(vector<Individual>::iterator it = archive.begin(); it!=archive.end(); ++it)
			comb_0.push_back(*it);
		
		// --- Fitness assignment ---
		Logging::log(Logging::Debug, "Fitness assignment");
		// Compute fitness values for both
		vector<rvector> fitnessVectors;
		for(vector<Individual>::iterator it = comb_0.begin(); it!=comb_0.end(); ++it)
		{
			rvector _fit = computeFitness(*it);
			fitnessVectors.push_back(_fit);
		}
			
			
		
		// Compute domination matrix
		intmatrix dominationMatrix = computeDominationMatrix(fitnessVectors);
		
		// Compute S
		intvector S = IntMatrixUtils::sumRows(dominationMatrix);
		
		// Compute R
		intvector R(0,comb_0.size()-1);
		int indexR = 0;
		for(vector<Individual>::iterator it = comb_0.begin(); it!=comb_0.end(); ++it)
		{
			R[indexR] = 0;
			for(int s=Lb(S); s<=Ub(S); ++s)
			{
				if(dominationMatrix[indexR][s])
					R[indexR] += S[s];
			}
			++indexR;
		}
		
		// Compute distance matrix
		rmatrix distanceMatrix = computeDistanceMatrix(fitnessVectors);
		
		// sorted distance matrix
		rmatrix sortedDistanceMatrix = RMatrixUtils::sortRows(distanceMatrix);
		
		// Compute density
		rvector density(0, comb_0.size()-1);
		for(int i = Lb(density); i<=Ub(density); ++i)
			density[i] = 1.0 / (sortedDistanceMatrix[i][k]+2.0);
		
		// Compute fitness values
		rvector fitness(0, comb_0.size()-1);
		for(int i = Lb(fitness); i<=Ub(fitness); ++i)
			fitness[i] = density[i] + R[i];
		
		// --- Construct new archive ---
		Logging::log(Logging::Debug, "New archive");
		vector<Individual> newArchive;
		multimap<real, Individual> additional; // Pool of additional individuals
		vector<rvector> archiveFitness; // Stores fitness vectors of archive elements.
		
		// Copy non-dominated individuals (those with fitness < 1) into new archive
		// TODO: Unique individuals
		
		int index = 0; int nonDominatedCount = 0;
		for(vector<Individual>::iterator it = comb_0.begin(); it!=comb_0.end(); ++it)
		{
			if(fitness[index] < 1.0 && !(containsIndividual(newArchive, *it)))
			{
				nonDominatedCount++;
				newArchive.push_back(*it);
				archiveFitness.push_back(fitnessVectors[index]);
			}
			else // Add to reserve
				additional.insert(pair<real, Individual>(fitness[index], (*it)));
			++index;
		}
		Logging::log(Logging::Debug, "# non-dominated individuals", nonDominatedCount);
		
		// Fill archive from reserve, if necessary
		multimap<real, Individual>::iterator additionalElement = additional.begin();
		while(newArchive.size() < m_archiveSize)
		{
			newArchive.push_back(additionalElement->second);
			additionalElement++;
		}
		
		// Truncate archive if too large
		rmatrix archiveDistanceMatrix;
		if(newArchive.size() > m_archiveSize)
		{
			// Compute distances between archive elements
			archiveDistanceMatrix = computeDistanceMatrix(archiveFitness);
		}
		while(newArchive.size() > m_archiveSize)
		{
			// Sort distances
			rmatrix sortedArchiveDistanceMatrix = RMatrixUtils::sortRows(archiveDistanceMatrix);
			
			// find unique element with minimum distance to another individual
			// multimap sorts according to key, and rvector compares element-wise
			multimap<rvector, int> distanceVectors;
			for(int i = Lb(sortedArchiveDistanceMatrix,1); i<=Ub(sortedArchiveDistanceMatrix,1); ++i)
				distanceVectors.insert(pair<rvector, int>(sortedArchiveDistanceMatrix[i], i));
			// first element is the one with the smallest distance vector in the archive
			const int elementIndex = distanceVectors.begin()->second;
			
			// remove it
			newArchive.erase(newArchive.begin()+elementIndex);
			// remove also from distance matrix.
			archiveDistanceMatrix = RMatrixUtils::rmRow(archiveDistanceMatrix, elementIndex);
			archiveDistanceMatrix = RMatrixUtils::rmCol(archiveDistanceMatrix, elementIndex);
		}
		archive = newArchive;
		
		// --- abort condition ---
		// is achieved through enclosing for loop
		
		Logging::log(Logging::Debug, "Mutation");
		// --- create new population ---
		population = mutate(archive);
	}
	// individuals on the pareto front are given in the archive.
	Logging::log(Logging::Info, "End of SPEA2");
	// return median of archive, ordered by a specific criterion
	
	multimap<real, Individual> orderedArchive;
	for(vector<Individual>::iterator it = archive.begin(); it!=archive.end(); ++it)
	{
		rvector fitnessVector = computeFitness(*it);
		orderedArchive.insert(make_pair<real, Individual>(fitnessVector[Autocorrelation], *it));
	}
	return modelFromIndexSequence(orderedArchive.begin()->second);
	/*
	const int medianIndex = orderedArchive.size()/2;
	int count = 0;
	for(multimap<real, Individual>::iterator it = orderedArchive.begin(); it !=orderedArchive.end(); ++it)
	{
		if(count++ == medianIndex)
			return modelFromIndexSequence(it->second);
	}
	DBG("Uh-oh. This should not happen.");
	return modelFromIndexSequence(orderedArchive.begin()->second);
	*/
}

int SPEA2Modeler::containsIndividual(vector<Individual> &newArchive, const Individual individual)
{
	for(vector<Individual>::iterator it = newArchive.begin(); it!=newArchive.end(); ++it)
	{
		Individual &comp = (*it);
		int equals = 1;
		// compare by value
		for(int i = Lb(individual); i<=Ub(individual); ++i)
		{
			if(!(comp[i] == individual[i]))
			{
				equals = 0;
				break;
			}
		}
		if(equals) return 1;
	}
	return 0;
}

vector<SPEA2Modeler::Individual> SPEA2Modeler::mutate(const vector<SPEA2Modeler::Individual> &pool)
{
	const int sexual = pool.size() / 2;
	const int asexual = pool.size() - sexual;
	vector<SPEA2Modeler::Individual> nextPool;
	
	// TODO: Make fitness-proportional
	// Sexual reproduction
	for(int poolCount = 0; poolCount<sexual; ++poolCount)
	{
		double s = 0.0;
		s = (double) rand()/ (double) RAND_MAX;
		int randomIndexA = (int)(s * pool.size());
		s = (double) rand()/ (double) RAND_MAX;
		int randomIndexB = (int)(s * pool.size()); 
		// Mating: 2-point crossover
		nextPool.push_back(crossover(pool, randomIndexA, randomIndexB));
	}
	// Asexual reproduction
	for(int poolCount = 0; poolCount<asexual; ++poolCount)
	{
		double s = 0.0;
		s = (double) rand()/ (double) RAND_MAX;
		int randomIndex = (int)(s * pool.size());
		Individual mutated = pool[randomIndex]; 
		// Mutation: Block
		int r = 0;
		r = rand() % 4;
		switch(r)
		{
		case 0:
			mut_block(mutated);
			break;
		case 1:
			mut_inverse(mutated);
			break;
		case 2:
			mut_shuffle(mutated);
			break;
		case 3:
			mut_swap(mutated);
			break;
		default:
			Logging::log(Logging::Warning, "Invalid mutation operator selected.");
		}
		nextPool.push_back(mutated);
	}
	return nextPool;
}

SPEA2Modeler::Individual SPEA2Modeler::crossover(const vector<SPEA2Modeler::Individual> &pool, const int mumIndex, const int dadIndex)
{
	// Determine bounds
	pair<int,int> bounds = getRandomBounds(pool[mumIndex]);
	
	// Copy Mum's genetic code
	Individual ret(pool[mumIndex]);
	
	// Insert Dad's genetic code
	const Individual &dad = pool[dadIndex];
	for(int i = bounds.first; i<=bounds.second; ++i)
		ret[i] = dad[i];
	
	// Return child
	return ret;
}

void SPEA2Modeler::mut_block(Individual &individual)
{
	const int state = (int)(getNumStates() * (double) rand()/ (double) RAND_MAX);
	pair<int, int> bounds = getRandomBounds(individual);
	for(int i = bounds.first; i<=bounds.second; ++i)
		individual[i] = state;
}

void SPEA2Modeler::mut_inverse(Individual &individual)
{
	pair<int, int> bounds = getRandomBounds(individual);
	intvector tmp(bounds.first, bounds.second);
	for(int i = bounds.first; i<=bounds.second; ++i)
		tmp[i] = individual[i];
	for(int i = bounds.first; i<=bounds.second; ++i)
		individual[i] = tmp[bounds.second - (i - bounds.first)];
}

void SPEA2Modeler::mut_shuffle(Individual &individual)
{
	pair<int, int> bounds = getRandomBounds(individual);
	// copy 
	vector<int> tmp;
	for(int i = bounds.first; i<=bounds.second; ++i)
		tmp.push_back(individual[i]);
	random_shuffle(tmp.begin(), tmp.end());
	for(int i = bounds.first; i<=bounds.second; ++i)
		individual[i] = tmp[i-bounds.first];
}

void SPEA2Modeler::mut_swap(Individual &individual)
{
	pair<int, int> bounds = getRandomBounds(individual);
	int swap = individual[bounds.first];
	individual[bounds.first] = individual[bounds.second];
	individual[bounds.first] = swap;
}

pair<int, int> SPEA2Modeler::getRandomBounds(const Individual &individual)
{
	int t1 = Lb(individual) + rand()%VecLen(individual);
	int t2 = Lb(individual) + rand()%VecLen(individual);
	if(t1>t2)
		return make_pair<int,int>(t2, t1);
	else
		return make_pair<int,int>(t1, t2);
}

rvector SPEA2Modeler::computeFitness(const Individual &individual)
{
	SSMProcess* process = modelFromIndexSequence(individual);
	rvector fitnessValues(0,1);
	real tmp;
	
	// Variance
	tmp = process->getVariance() - m_trace_variance;
	fitnessValues[Variance] = tmp*tmp;
	
	// Mean values
	//tmp = process.getExpectationValue() - m_trace_mean;
	//fitnessValues[Mean] = tmp*tmp;
	
	// Autocorrelation
	rvector model_autocorrelation = process->getAutocorrelation(m_autocorrelationLimit);
	tmp = 0.0;
	for(int i = Lb(model_autocorrelation); i<=Ub(model_autocorrelation); ++i)
	{
		real tmp2 = model_autocorrelation[i] - m_trace_autocorrelation[i];
		tmp += tmp2*tmp2;
	}
	fitnessValues[Autocorrelation] = tmp;
	
	delete process;
	
	return fitnessValues;
}

intmatrix SPEA2Modeler::computeDominationMatrix(vector<rvector> fitnessVectors)
{
	const int size = fitnessVectors.size();
	const int ub = size-1;
	intmatrix ret(0, ub, 0, ub);
	const int fitnessVectorUb = Ub(fitnessVectors[0]);
	
	// Iterate rows
	for(int yz = 0; yz < size; ++yz)
	{
		// Iterate columns
		for(int ys = 0; ys < size; ++ys)
		{
			ret[yz][ys] = 0;
			// Compare all entries in fitness vector
			for(int f = 0; f<=fitnessVectorUb; ++f)
			{
				// Row dominates Column
				if(fitnessVectors[yz][f] > fitnessVectors[ys][f])
					ret[yz][ys] = 1;
				// Row does not dominate Column
				else if(fitnessVectors[yz][f] < fitnessVectors[ys][f])
				{
					ret[yz][ys] = 0;
					// Abort, since row is not dominating.
					break;
				}
			}
		}
	}
	return ret;
}

rmatrix SPEA2Modeler::computeDistanceMatrix(vector<rvector> fitnessVectors)
{
	const int size = fitnessVectors.size();
	const int ub = size-1;
	rmatrix ret(0, ub, 0, ub);
	const int fitnessVectorUb = Ub(fitnessVectors[0]);
	
	// TODO: Make use of symmetry for speedup.
	// Iterate rows
	for(int yz = 0; yz < size; ++yz)
	{
		// Iterate columns
		for(int ys = 0; ys < size; ++ys)
		{
			real distance = 0;
			// Compare all entries in fitness vector
			for(int f = 0; f<=fitnessVectorUb; ++f)
			{
				real tmp = fitnessVectors[yz][f] - fitnessVectors[ys][f];
				distance += tmp*tmp;
			}
			ret[yz][ys] = sqrt(distance);
		}
	}
	return ret;
}

int SPEA2Modeler::monteCarlo(const rvector &_dist)
{
	// Compute cumulative sum
	rvector cumsum(Lb(_dist), Ub(_dist));
	real sum = 0.0;
	for(int i = Lb(_dist); i<=Ub(_dist); ++i)
	{
		sum += _dist[i];
		cumsum[i] = sum;
	}
	
	return monteCarloFromCumSum(cumsum);
}

int SPEA2Modeler::monteCarloFromCumSum(const rvector &cumsum)
{
	// Get random number between 0 and 1.
	real r = (double)(rand())/RAND_MAX;
	
	// Find corresponding index.
	int i = Lb(cumsum);
	while(r > cumsum[i])
	{
		++i;
	}
	return i;
}


}
