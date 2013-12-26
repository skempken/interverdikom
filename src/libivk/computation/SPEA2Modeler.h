#ifndef SPEA2MODELER_H_
#define SPEA2MODELER_H_

#include "AbstractDiscreteSSMPModeler.h"

#include <stdexcept>
#include <vector>
#include <utility>
#include <intvector.hpp>
#include <intmatrix.hpp>
#include <rvector.hpp>

using namespace std;
using cxsc::rvector;
using cxsc::intmatrix;
using cxsc::intvector;

namespace ivk
{

class SPEA2Modeler : public AbstractDiscreteSSMPModeler
{
public:
	static const char* PARAM_POPSIZE;
	static const char* PARAM_ARCHIVESIZE;
	static const char* PARAM_NUMITERATIONS;
	static const char* PARAM_AUTOCORRELATION;
	static const char* PARAM_MCROSSOVER;
	static const char* PARAM_MBLOCK;
	static const char* PARAM_MINVERSE;
	static const char* PARAM_MSHUFFLE;
	static const char* PARAM_MSWAP;
		
	typedef intvector Individual;
	
	SPEA2Modeler(const Trace* data, const ComputationParameters &parameters);
	virtual ~SPEA2Modeler();
	
	SSMProcess* compute();
	
	ComputationParameters getParameters();
	void setParameters(const ComputationParameters param);
	
	void setPopSize(int value);
	int getPopSize();
	
	void setArchiveSize(int value);
	int getArchiveSize();
	
	void setNumIterations(int value);
	int getNumIterations();
	
	void setAutocorrelationLimit(int value);
	int getAutocorrelationLimit();
	
	void setMCrossover(double value);
	double getMCrossover();
	
	void setMInverse(double value);
	double getMInverse();
	
	void setMBlock(double value);
	double getMBlock();
	
	void setMShuffle(double value);
	double getMShuffle();
	
	void setMSwap(double value);
	double getMSwap();
	
	static int monteCarloFromCumSum(const rvector &cumsum);
	static int monteCarlo(const rvector &dist);
	
	static int containsIndividual(vector<Individual> &newArchive, const Individual individual);
	
private:
	Trace* m_scaledTrace;
	
	unsigned int m_popSize;
	unsigned int m_archiveSize;
	unsigned int m_numIterations;
	unsigned int m_autocorrelationLimit;
	
	double m_prob_crossover;
	double m_prob_block;
	double m_prob_inverse;
	double m_prob_shuffle;
	double m_prob_swap;
	
	enum FitnessMeasure {
		Variance = 0,
		Autocorrelation = 1
	};
	
	// reference values
	real m_trace_variance;
	real m_trace_mean;
	rvector m_trace_autocorrelation;
	
	Individual initIndividual();
	rvector computeFitness(const Individual &individual);
	intmatrix computeDominationMatrix(vector<rvector> fitnessVectors);
	rmatrix computeDistanceMatrix(vector<rvector> fitnessVectors);
	static rmatrix sortMatrix(const rmatrix &matrix);
	vector<Individual> mutate(const vector<Individual> &pool);
	Individual crossover(const vector<Individual> &pool, const int mumIndex, const int dadIndex);
	void mut_block(Individual &individual);
	void mut_inverse(Individual &individual);
	void mut_shuffle(Individual &individual);
	void mut_swap(Individual &individual);
	pair<int, int> getRandomBounds(const Individual &individual);
};

}

#endif /*SPEA2MODELER_H_*/
