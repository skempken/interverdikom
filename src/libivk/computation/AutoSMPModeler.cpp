#include "AutoSMPModeler.h"

namespace ivk{	
	
	const char * AutoSMPModeler::PARAM_CONFNIVEAU = "confniveau";
	
	AutoSMPModeler::AutoSMPModeler(const Trace* data, const ComputationParameters &parameters)
	:SimpleMCModeler(data,parameters){
		this->setParameters(parameters);
	}
	AutoSMPModeler::~AutoSMPModeler(){}

	void AutoSMPModeler::setConfNiveau(const int value){
		this->confNiveau = value;
	}
	
	int AutoSMPModeler::getConfNiveau() const{
		return this->confNiveau;
	}
		
	void AutoSMPModeler::setParameters(const ComputationParameters &parameters){
		this->setConfNiveau(parameters.getInt(PARAM_CONFNIVEAU));
	}

	SSMProcess* AutoSMPModeler::computeModel(int n_states){
		const rvector &trace = m_ptrData->getTrace();
		const real minValue = m_ptrData->getMinimum();
		const real maxValue = m_ptrData->getMaximum();
		const int numStates = n_states;
		const real stepWidth = (maxValue - minValue) / real(numStates); 
		
		// construct index sequence
		intvector index(Lb(trace), Ub(trace));
		for(int i = Lb(trace); i<=Ub(trace); ++i)
		{
			const real value = trace[i];
			index[i] = (int)_double((value - minValue)/stepWidth);
			if(index[i] == 0) index[i] = numStates + 1;
		}
		this->indexSequence = index;
		return modelFromIndexSequence(index);
	}
		
	SSMProcess* AutoSMPModeler::compute(){
		int sugNum = this->getNumStates();
		int states = sugNum;
		
		bool run = true;
		bool last = false;
		while(run){
			try{
				intvector lengths(0,states-1);
				for(int x = Lb(lengths); x <= Ub(lengths); x++){
					lengths[x] = 0;
				}
				
				SSMProcess* smp = (this->computeModel(states));
				
				for(int i = 0; i <= Ub(this->indexSequence); i++){
					lengths[this->indexSequence[i]] += 1;
				}
				
				rmatrix trans(mid(smp->getTransitionMatrix()));
				
				for(int i = 0; i < states; i++){
					for(int j = 0; j < states; j++){
						if(trans[i][j] != 0.0 && trans[i][j] != 1.0){
							StatUtils::confidence(lengths[i],trans[i][j],this->confNiveau);
						}
					}
				}
				states += 1;
				last = true;
			}
			catch(std::runtime_error){
				states -= 1;
				if(last){ run = false; }
				last = false;
			}
		}
		
		SSMProcess* ret = this->computeModel(states);
		return ret;
	}
}
