#include "GeneticModeler.h"

namespace ivk{
	const char* GeneticModeler::PARAM_AUTOC 		= "autoc";
	const char* GeneticModeler::PARAM_NUMITERATIONS = "numiter";
	const char* GeneticModeler::PARAM_NUMPOOLSIZE 	= "poolsize";
	const char* GeneticModeler::PARAM_MUTBLOCK 		= "mutblock";
	const char* GeneticModeler::PARAM_MUTINVERSE 	= "mutinverse";
	const char* GeneticModeler::PARAM_MUTSHUFFLE	= "mutshuffle";
	const char* GeneticModeler::PARAM_MUTSWAP		= "mutswap";
	const char* GeneticModeler::PARAM_MUTCROSSOVER	= "mutcrossover";

	GeneticModeler::GeneticModeler(const Trace *ptrData, const ComputationParameters &parameters)
	: AbstractDiscreteSSMPModeler(ptrData, parameters) {
		this->setParameters(parameters);
	}

	GeneticModeler::~GeneticModeler(){}

	int GeneticModeler::getStates(){	 		return this->states; }
	int GeneticModeler::getDists(){			 	return this->dists; }
	int GeneticModeler::getAutoc(){				return this->autoc; }
	int GeneticModeler::getIter(){				return this->iteration; }
	int GeneticModeler::getPoolSz(){			return this->poolSz; }
	real GeneticModeler::getMutBlock(){		return this->mutBlock; }
	real GeneticModeler::getMutInverse(){		return this->mutInverse; }
	real GeneticModeler::getMutShuffle(){		return this->mutShuffle; }
	real GeneticModeler::getMutSwap(){		return this->mutSwap; }
	real GeneticModeler::getMutCrossover(){	return this->mutCrossover; }

	void GeneticModeler::setStates(int states){			 	this->states = states; }
	void GeneticModeler::setDists(int dists){			 	this->dists = dists; }
	void GeneticModeler::setAutoc(int autoc){				this->autoc = autoc; }
	void GeneticModeler::setIter(int iteration){			this->iteration = iteration; }
	void GeneticModeler::setPoolSz(int poolSz){				this->poolSz = poolSz; }
	void GeneticModeler::setMutBlock(real value){			this->mutBlock = value;}
	void GeneticModeler::setMutInverse(real value){		this->mutInverse = value;}
	void GeneticModeler::setMutShuffle(real value){		this->mutShuffle = value;}
	void GeneticModeler::setMutSwap(real value){			this->mutSwap = value;}
	void GeneticModeler::setMutCrossover(real value){		this->mutCrossover = value;}

	void GeneticModeler::setParameters(const ComputationParameters &parameters){
		AbstractDiscreteSSMPModeler::setParameters(parameters);
		this->setStates(parameters.getInt(GeneticModeler::PARAM_NUMSTATES));
		this->setDists(parameters.getInt(GeneticModeler::PARAM_NUMDSTEPS));
		this->setAutoc(parameters.getInt(GeneticModeler::PARAM_AUTOC));
		this->setIter(parameters.getInt(GeneticModeler::PARAM_NUMITERATIONS));
		this->setPoolSz(parameters.getInt(GeneticModeler::PARAM_NUMPOOLSIZE));
		this->setMutBlock(		parameters.getReal(GeneticModeler::PARAM_MUTBLOCK) );
		this->setMutInverse(	parameters.getReal(GeneticModeler::PARAM_MUTINVERSE) );
		this->setMutShuffle(	parameters.getReal(GeneticModeler::PARAM_MUTSHUFFLE) );
		this->setMutSwap(		parameters.getReal(GeneticModeler::PARAM_MUTSWAP) );
		this->setMutCrossover(	parameters.getReal(GeneticModeler::PARAM_MUTCROSSOVER) );
	}

	ComputationParameters GeneticModeler::getParameters() const {
		ComputationParameters params = AbstractDiscreteSSMPModeler::getParameters();
		params.setInt( GeneticModeler::PARAM_NUMSTATES 		, this->states );
		params.setInt( GeneticModeler::PARAM_NUMDSTEPS 		, this->dists );
		params.setInt( GeneticModeler::PARAM_AUTOC 			, this->autoc);
		params.setInt( GeneticModeler::PARAM_NUMITERATIONS 	, this->iteration );
		params.setInt( GeneticModeler::PARAM_NUMPOOLSIZE 	, this->poolSz );
		params.setReal( GeneticModeler::PARAM_MUTBLOCK		, this->mutBlock);
		params.setReal( GeneticModeler::PARAM_MUTINVERSE	, this->mutInverse);
		params.setReal( GeneticModeler::PARAM_MUTSHUFFLE	, this->mutShuffle);
		params.setReal( GeneticModeler::PARAM_MUTSWAP		, this->mutSwap);
		params.setReal( GeneticModeler::PARAM_MUTCROSSOVER	, this->mutCrossover);
		return params;
	}

	void GeneticModeler::generatePool(){
		SimpleMCModeler _simple(this->m_ptrData, getParameters());
		const SSMProcess* initSMP = _simple.compute();

		ComputationParameters params_sim = getParameters();
		params_sim.setInt( GeneticModeler::PARAM_NUMDSTEPS , this->getNumStates());
		params_sim.setInt(Simulation::PARAM_LENGTH, this->m_ptrData->getUpperBound() - this->m_ptrData->getLowerBound()+1);
		Simulation _sim(initSMP, params_sim);

		//computing the initial pool of model to have the base for the evolution

		for(int i=0;i < this->getPoolSz();++i)
		{
			rvector indexTrace =_sim.compute()->getTrace();
			intvector indexSequence(Lb(indexTrace), Ub(indexTrace));
			for(int j = Lb(indexTrace); j<=Ub(indexTrace); ++j){
				indexSequence[j] = (int) _double(indexTrace[j]) +1;
				assert( indexSequence[j] != 0 );
			}
			pool.push_back(indexSequence);
		}
		delete initSMP;
	}

	void GeneticModeler::initializePool(){
		setProgressText("initialize pool");
		this->generatePool();
		this->compare = rvector(0,this->getPoolSz()-1);
		this->eac = rvector(this->m_ptrData->getAutocorrelation(this->getAutoc()));
		setProgressValue(5);

	}

	int GeneticModeler::computeFittest(){
		for(int i = 0 ; i < this->pool.size() ; i++){
			for(int c = Lb(this->pool[i]) ; c <= Ub(this->pool[i]); c++){
				assert( this->pool[i][c] != 0);
			}
		}
		int fittest = -1;

		//computing the fittnes of every model and comparing it to determine the best

		for(unsigned int i = 0; i < this->pool.size(); i++){
			SSMProcess* tmpProc = createSMPFromIndex(this->pool[i]);
			rvector tmpVec = tmpProc->getAutocorrelation(this->getAutoc());
			real sigma = 0.0;
			for(int n = 0;n < this->getAutoc();n++){
				real x = this->eac[n] - tmpVec[n];
				sigma += x*x;
			}
			this->compare[i] = 1.0/sigma;
			if(fittest == -1 || this->compare[fittest] < this->compare[i]) { fittest = i; }
		}

		return fittest;
	}

	void GeneticModeler::mutateGenetic(){
		for(unsigned int i = 0; i < this->pool.size(); i++){
			if(this->best != i){ this->arrangeMutations(i); }
		}
	}

	void GeneticModeler::arrangeMutations(int poolIndex){
		rvector probabilities(1,5);
		probabilities[1] = getMutBlock();
		probabilities[2] = getMutInverse();
		probabilities[3] = getMutShuffle();
		probabilities[4] = getMutSwap();
		probabilities[5] = getMutCrossover();

		//determine the mutators and the range of the data that will be mutated

		for(int i = 1 ; i <= 5; i++){
			double x = (double) rand()/ (double) RAND_MAX;
			if(x <= probabilities[i]){
				int t1 = rand()%this->m_ptrData->getUpperBound();
				int t2 = rand()%this->m_ptrData->getUpperBound();
				int lower = (t1 < t2) ? t1 : t2; //untere Grenze
				int upper = (t1 > t2) ? t1 : t2; //obere Grenze
			}
		}
	}

	void GeneticModeler::mutate(int poolIndex, int lower, int upper, int mutator){
		//using the mutator with the index on the data

		switch(mutator){
			case 1:{
				int wert = (int) rand()%this->states;
				for(int i = lower;i <= upper;i++){
					this->pool[poolIndex][i] = wert;
				}
			}
			break;

			case 2:{
				intvector tmp(this->pool[poolIndex]);
				int x = 0;
				for(int i = lower;i<= upper;i++){
					this->pool[poolIndex][i] = tmp[upper-x++];
				}
			}
			break;

			case 3:{
				rvector tmp(1,this->states);

				for(int i = lower;i <= upper;i++){
					tmp[this->pool[poolIndex][i]] += 1;
				}
				for(int i = lower;i <= upper;i++){
					int x = -1;
					while( true ){
						x = rand()%this->states;
						if(x != -1){
							if(tmp[x] != 0){
								break;
							}
						}
					}
					this->pool[poolIndex][i] = x;
					tmp[x] -= 1;
				}
			}
			break;

			case 4:{
				int tmp = this->pool[poolIndex][lower];
				this->pool[poolIndex][lower] = this->pool[poolIndex][upper];
				this->pool[poolIndex][upper] = tmp;
			}
			break;

			case 5:{
				int x = (poolIndex != 0) ? poolIndex-1 : poolIndex+1;
				intvector tmp(this->pool[x]);
				for(int i = lower;i <= upper;i++){
					this->pool[poolIndex][i] = tmp[i];
				}
			}
			break;
		}
	}

	void GeneticModeler::generateHeritage(){
		setProgressText("starting evolution");
		setProgressValue(1);

		//loop to make sure that there will be no better model after mutating the pool this->iteration times
		unsigned int x = 0;
		for(int i = 0; i < this->iteration; i++){
			stringstream buffer;
			buffer << "iteration " << i << " of " << this->iteration;
			setProgressText( buffer.str() );
			setProgressValue( (int) (100.0 / (double) this->iteration) * i  );
			x = this->computeFittest();
			if(x != this->best){
				this->best = x;
				this->mutateGenetic();
				i = 0;
			}
		}
	}
	SSMProcess* GeneticModeler::createSMPFromIndex( intvector sequence ){
		return AbstractDiscreteSSMPModeler::modelFromIndexSequence( sequence );
	}

	SSMProcess* GeneticModeler::compute(){
		setProgressText("starting computation");
		setProgressMax(100);
		setProgressValue(1);
		this->initializePool();
		this->generateHeritage();
		SSMProcess* smp = createSMPFromIndex(this->pool[this->best]);
		return smp;
	}
}
