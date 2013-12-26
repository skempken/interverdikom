#ifndef REPEATEDSTATECONTRACTIONS_H_
#define REPEATEDSTATECONTRACTIONS_H_

#include "AbstractComputation.hpp"
#include "AbstractDiscreteSSMPModeler.h"
#include "data/Trace.h"
#include "data/SSMProcess.h"
#include "utility/RMatrixUtils.h"
#include "computation/SimpleMCModeler.h"

#include "rmatrix.hpp"

// #include "utility/contractionTree.h"

using std::pair;
using std::vector;
using cxsc::real;

namespace ivk{
	/**\class StateContractionMulti
	\brief StateContractionMulti is used to contract multiple states to one*/
	class RepeatedStateContractions : public AbstractComputation<SSMProcess, SSMProcess>{
		public:
			static const char * PARAM_NUMCONTRACTIONS;
			/**Contructor to create an instance of the StateContractionMulti-class
			\param data is the SSMProcess in which multiple states should be contracted
			\param parameters *not used* */
			RepeatedStateContractions(const SSMProcess* data, const ComputationParameters &parameters);
			virtual ~RepeatedStateContractions();

			/**Method to set the set of parameters *not used* */
			virtual void setParameters(const ComputationParameters &parameters);

			void setNumContractions(const int value);
			int getNumContractions() const;

			/**Method to contract multiple states to one
			\return The SSMProcess with m-n states where m is the base number of states and n the number of states that were contracted*/
			SSMProcess* compute();

		private:

			int numContractions;
			int m_n;
			int m_m;
			vector< pair< int , int > > globalStack;
			real bestAutocorrelation;
			SSMProcess* bestModel;

			SSMProcess* contractSpecificStates(int n , int m , SSMProcess tSSMProcess);
			SSMProcess* contractStates( int depth ,  SSMProcess* model );
			vector<pair< pair<int,int>, real> > checkValue( SSMProcess* model);
	};
}

#endif /*REPEATEDSTATECONTRACTIONS_H_*/
