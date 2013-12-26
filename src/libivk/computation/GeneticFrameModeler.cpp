#include "computation/GeneticFrameModeler.h"
#include "AbstractComputation.hpp"

namespace ivk{
	const char* GeneticFrameModeler::PARAM_FRAMELEVEL = "framelevel";

	GeneticFrameModeler::GeneticFrameModeler(const Trace *ptrData,ComputationParameters &parameters)
	: GeneticModeler(ptrData, parameters){
		this->setParameters(parameters);
	}

	GeneticFrameModeler::~GeneticFrameModeler(){}

	void GeneticFrameModeler::setParameters(const ComputationParameters &parameters){
		GeneticModeler::setParameters(parameters);
		this->setStates(parameters.getInt(GeneticFrameModeler::PARAM_NUMSTATES));
		this->setDists(parameters.getInt(GeneticFrameModeler::PARAM_NUMDSTEPS));
		this->setAutoc(parameters.getInt(GeneticFrameModeler::PARAM_AUTOC));
		this->setIter(parameters.getInt(GeneticFrameModeler::PARAM_NUMITERATIONS));
		this->setPoolSz(parameters.getInt(GeneticFrameModeler::PARAM_NUMPOOLSIZE));
		this->setMutBlock(		parameters.getReal(GeneticFrameModeler::PARAM_MUTBLOCK) );
		this->setMutInverse(	parameters.getReal(GeneticFrameModeler::PARAM_MUTINVERSE) );
		this->setMutShuffle(	parameters.getReal(GeneticFrameModeler::PARAM_MUTSHUFFLE) );
		this->setMutSwap(		parameters.getReal(GeneticFrameModeler::PARAM_MUTSWAP) );
		this->setMutCrossover(	parameters.getReal(GeneticFrameModeler::PARAM_MUTCROSSOVER) );
		this->setFramelevel( 	parameters.getInt(GeneticFrameModeler::PARAM_FRAMELEVEL ));
	}

	ComputationParameters GeneticFrameModeler::getParameters() const {
		ComputationParameters params = GeneticModeler::getParameters();
		params.setInt( GeneticFrameModeler::PARAM_FRAMELEVEL, this->framelevel);
		return params;
	}

	void GeneticFrameModeler::setFramelevel(int value){
		this->framelevel = value;
	}

	int GeneticFrameModeler::getFramelevel(){
		return this->framelevel;
	}

	SSMProcess* GeneticFrameModeler::createSMPFromIndex(intvector sequence){
		intvector indexSequence(Lb(sequence), Ub(sequence));


		//setting up the framelevel
		for(int i = Lb(indexSequence); i <= Ub(indexSequence); i++){
			int gopIndex = i % this->framelevel;
			indexSequence[i] = gopIndex * this->getStates() + indexSequence[i];
		}

		return AbstractDiscreteSSMPModeler::modelFromIndexSequence( indexSequence );
	}
}
