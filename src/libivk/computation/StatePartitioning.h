#ifndef STATECONTRACTIONOPTIMAL_H_
#define STATECONTRACTIONOPTIMAL_H_

#include "AbstractComputation.hpp"
#include "AbstractDiscreteSSMPModeler.h"
#include "data/Trace.h"
#include "data/SSMProcess.h"
#include "utility/RVectorUtils.h"
#include "intvector.hpp"
#include "rmatrix.hpp"

using cxsc::real;
using cxsc::intvector;
using cxsc::rmatrix;
using std::pair;
using std::vector;

namespace ivk{
	class StatePartitioning : public AbstractComputation<SSMProcess, SSMProcess>{

	typedef pair< int , int > range;

	public:
		static const char * PARAM_NUMCONTRACTIONS;

		StatePartitioning(const SSMProcess* data, const ComputationParameters &parameters);
		virtual ~StatePartitioning();

		virtual void setParameters(const ComputationParameters &parameters);

		void setNumContractions(const int value);
		int getNumContractions() const;

		SSMProcess* compute();

	private:
		int numContractions;
		vector< range > ranges;
		vector< range > finalRanges;
		real accErr;

		SSMProcess sortByExpectation();
		real autocorrelationError( int startIndex , int endIndex );
		void recursionInit();
		void recursion( int m , int k , int parts );
		void calculateRangeValue();
		SSMProcess applyRanges();
		SSMProcess contractStates(const SSMProcess &model , int receivingState, const intvector &states);
	};
}


#endif /* STATECONTRACTIONOPTIMAL_H_ */
