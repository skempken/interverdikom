#ifndef GENETICMODELER_H_
#define GENETICMODELER_H_

#include "AbstractDiscreteSSMPModeler.h"
#include "computation/SimpleMCModeler.h"
#include "Simulation.h"
#include "utility/Mutator.h"
#include "utility/RMatrixUtils.h"
#include "utility/IMatrixUtils.h"
#include <vector>


namespace ivk{
	/**\class GeneticModeling
	\brief GeneticModeling is used to calculate a genetic SemiMarkovProcess*/
	class GeneticModeler : public AbstractDiscreteSSMPModeler {
		public:
			static const char* PARAM_AUTOC;
			static const char* PARAM_NUMITERATIONS;
			static const char* PARAM_NUMPOOLSIZE;
			static const char* PARAM_MUTBLOCK;
			static const char* PARAM_MUTINVERSE;
			static const char* PARAM_MUTSHUFFLE;
			static const char* PARAM_MUTSWAP;
			static const char* PARAM_MUTCROSSOVER;
			
			/**Contructor for the GeneticModeler-class
			\param ptrData The trace that is used as base for the evolution algorithm
			\param parameters The parameters that are necessary to build the GeneticModel (they are: PARAM_AUTOC, PARAM_NUMITERATIONS, PARAM_NUMPOOLSIZE)*/
			GeneticModeler(const Trace *ptrData, const ComputationParameters &parameters);
			/** Destructor*/
			virtual ~GeneticModeler();
			/**Method to get the number of states*/
			int getStates();
			/**Method to get the number of discretization steps*/
			int getDists();
			/**Method to get the number of autocorrelation steps*/
			int getAutoc();
			/**Method to get the number of iterations*/
			int getIter();
			/**Method to get the number of cycles it the pool*/
			int getPoolSz();
			
			real getMutBlock();
			real getMutInverse();
			real getMutShuffle();
			real getMutSwap();
			real getMutCrossover();
			
			/**Method to set the number of states*/
			void setStates(int states);
			/**Method to set the number of discretization steps*/
			void setDists(int dists);
			/**Method to set the number of autocorrelation steps*/
			void setAutoc(int autoc);
			/**Method to set the number of iterations*/
			void setIter(int iteration);
			/**Method to set the number of cycles it the pool*/
			void setPoolSz(int poolSz);
			
			void setMutBlock(real value);
			void setMutInverse(real value);
			void setMutShuffle(real value);
			void setMutSwap(real value);
			void setMutCrossover(real value);
			
			/**Method to set the set of parameters*/
			virtual void setParameters(const ComputationParameters &parameters);
			
			virtual ComputationParameters getParameters() const;
			
			void arrangeMutations(int poolIndex);
			void mutate(int poolIndex, int lower, int upper, int mutator);
			/**Method to compute the genetic process*/
			SSMProcess* compute();

		private:
			int states;
			int dists;
			int autoc;
			int iteration;
			int poolSz;
			unsigned int best;
			real mutBlock;
			real mutInverse;
			real mutShuffle;
			real mutSwap;
			real mutCrossover;
			
			rvector eac;
			vector<intvector> pool;
			rvector compare;
			
			void generatePool();
			void initializePool();
			void mutateGenetic();
			void generateHeritage();
			int computeFittest();
			
		protected:
			virtual SSMProcess* createSMPFromIndex( intvector sequence );
	};
}
#endif
