#include "ScenePartitioner.h"

namespace ivk{
		const char* ScenePartitioner::PARAM_EPSILON = "epsilon";
		
		ScenePartitioner::ScenePartitioner(const Trace* data, const ComputationParameters &parameters)
		: AbstractComputation<Trace, vector<Trace> >(data,parameters){
			this->setParameters(parameters);
		}
		ScenePartitioner::~ScenePartitioner(){}
		
		void ScenePartitioner::setEpsilon(const real value){ this->m_epsilon = value; }
		real ScenePartitioner::getEpsilon() const{ return this->m_epsilon; }
		
		void ScenePartitioner::setParameters(const ComputationParameters &parameters){
			this->setEpsilon(parameters.getReal(ScenePartitioner::PARAM_EPSILON));
		}
		
		vector<Trace>* ScenePartitioner::compute(){
			vector<int> sceneLimits;
			sceneLimits.push_back(0);
			vector<real> vk;
			
			for(int i = 0;i <= this->m_ptrData->getUpperBound();i++){
				
				vk.push_back(this->m_ptrData->getVariationCoefficientSlice(sceneLimits.back(),i));
				int last = sceneLimits.back();
				if( (i-last) >= 1 ){
					if(((i-last+1) * abs(vk[i] - vk[i-1])) > this->m_epsilon){
						sceneLimits.push_back(i);
						vk[i] = this->m_ptrData->getVariationCoefficientSlice(sceneLimits.back(),i);
					}
				}
			}
			
			vector<Trace>* scenes = new vector<Trace>();
			for(unsigned int i=0; i < sceneLimits.size(); i++){
				int from,to;
				from = sceneLimits[i];
				to = (i < sceneLimits.size()-1) ? sceneLimits[i+1]-1 : this->m_ptrData->getUpperBound();
				rvector tmp(from,to);
				for(int n=from; n < to; n++){
					tmp[n] = this->m_ptrData->getTrace()[n];
				}
				SetLb(tmp,0);
				scenes->push_back(Trace(tmp));
			}
			return scenes;
		}
}
