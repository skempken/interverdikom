#ifndef STATEMERGE_H_
#define STATEMERGE_H_

#include "AbstractComputation.hpp"
#include "AbstractDiscreteSSMPModeler.h"
#include "data/Trace.h"
#include "data/SSMProcess.h"
#include "utility/RMatrixUtils.h"
#include "utility/RVectorUtils.h"
#include "computation/SimpleMCModeler.h"

#include "rmatrix.hpp"

namespace ivk{
	/**\class StateContractionMultiPara
	\brief StateContractionMultiPara is used to contract multiple states to one*/
	class StateMerge : public AbstractComputation<SSMProcess, SSMProcess>{
		public:
			static const char * PARAM_CONTRACTIONVECTOR;
			static const char * PARAM_CONTRACTIONTYPE;

			static intvector generateContractionVectorStatProb(const SSMProcess* process, int numberOfContractions);
			static intvector generateContractionVectorMean(const SSMProcess* process, int numberOfContractions);

			/**Contructor to create an instance of the StateContractionMultiPara-class
			\param data is the SSMProcess in which multiple states should be contracted
			\param parameters *not used* */
			StateMerge(const SSMProcess* data, const ComputationParameters &parameters);
			virtual ~StateMerge();

			/**Method to set the set of parameters *not used* */
			virtual void setParameters(const ComputationParameters &parameters);

			void setContractionVector(const intvector value);
			intvector getContractionVector() const;

			void setContractionType(const int value);
			int getContractionType() const;

			int getNumStates();

			intvector generateContractionVector(int numberOfContractions);

			/**Method to contract multiple states to one
			\return The SSMProcess with m-n states where m is the base number of states and n the number of states that were contracted*/
			SSMProcess* compute();

		private:

			intvector contractionVector;
			int m_n;
			int m_m;
			rmatrix contractedDistribution;
			rmatrix contractedTransitionMatrix;
			int contractionType;

			virtual SSMProcess* contractStates(int receivingState, intvector states);
	};
}

#endif /*STATEMERGE_H_*/
