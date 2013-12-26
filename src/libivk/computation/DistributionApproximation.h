#ifndef DISTRIBUTIONAPPROXIMATION_H_
#define DISTRIBUTIONAPPROXIMATION_H_

#include "AbstractComputation.hpp"
#include "data/SSMProcess.h"
#include "data/DiscretizedTrace.h"
#include <stdexcept>
#include "intvector.hpp"
#include "utility/RMatrixUtils.h"
#include "computation/SimpleMCModeler.h"

using cxsc::intvector;

namespace ivk{
	class DistributionApproximation: public AbstractComputation<SSMProcess, DiscretizedTrace>{
		public:
			static const char * PARAM_LENGTH;
			
			DistributionApproximation(const SSMProcess *ptrData, ComputationParameters &parameters);
			virtual ~DistributionApproximation();
			
			void setLength(const int m_length);
			int getLength() const;
			
			DiscretizedTrace* compute();
			void setParameters(const ComputationParameters &parameters);
			
			intvector simulateTransitions(const int length);
			intvector simulateDistribution(intvector indexSequence);
			
		private:
			int m_length;
	};
}

#endif
