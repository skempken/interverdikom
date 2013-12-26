#ifndef GENETICFRAMEMODELER_H_
#define GENETICFRAMEMODELER_H_

#include "computation/GeneticModeler.h"
#include "AbstractDiscreteSSMPModeler.h"
#include "computation/SimpleMCModeler.h"
#include "Simulation.h"
#include "utility/Mutator.h"
#include "utility/RMatrixUtils.h"
#include "utility/IMatrixUtils.h"
#include <vector>

namespace ivk{
	class GeneticFrameModeler : public GeneticModeler{
	public:
		static const char* PARAM_FRAMELEVEL;
		GeneticFrameModeler(const Trace *ptrData, ComputationParameters &parameters);
		
		virtual ~GeneticFrameModeler();
		
		void setParameters(const ComputationParameters &parameters);
		
		virtual ComputationParameters getParameters() const;
		
		void setFramelevel(int value);
		int getFramelevel();
		
	protected:
		virtual SSMProcess* createSMPFromIndex( intvector sequence );
		
	private:
		int framelevel;
	};
	
}

#endif /*GENETICFRAMEMODELER_H_*/
