#include "DistributionApproximation.h"

namespace ivk{

	const char * DistributionApproximation::PARAM_LENGTH = "length";

	DistributionApproximation::DistributionApproximation(const SSMProcess *ptrData, ComputationParameters &parameters)
	: AbstractComputation<SSMProcess, DiscretizedTrace>(ptrData, parameters){
		this->setParameters(parameters);
	}

	DistributionApproximation::~DistributionApproximation(){
	}

	void DistributionApproximation::setParameters(const ComputationParameters &parameters){
		this->setLength(parameters.getInt(PARAM_LENGTH));
	}

	void DistributionApproximation::setLength(const int length){
		if(length > 0)
			this->m_length = length;
		else
			throw std::out_of_range("Length must be > 0");
	}

	int DistributionApproximation::getLength() const{
		return this->m_length;
	}

	DiscretizedTrace* DistributionApproximation::compute()	{
		intvector indexSequence = simulateTransitions(this->m_length);
		intvector distSequence = simulateDistribution(indexSequence);
		return new DiscretizedTrace(distSequence);
	}

	intvector DistributionApproximation::simulateTransitions(const int length)
	{
		intvector trace(0, length-1);
		rvector p(m_ptrData->getStationaryProbabilities());
		rmatrix trans = mid(m_ptrData->getTransitionMatrix());
		double start = (double) rand() / (double) RAND_MAX;
		rmatrix numerator(RMatrixUtils::zeros(0,Ub(trans,ROW),0,Ub(trans,ROW)));
		rvector denominator(0,Ub(trans,ROW));
		
		for(int i = 0; i <= Ub(denominator); i++){
			denominator[i] = 0.0;
		}
		
		double cumsum = 0.0;
		for(int i = 0; i < this->m_ptrData->getNumStates(); i++){
			cumsum += _double(p[i]);
			if(start <= cumsum){
				trace[0] = i;
				break;
			}
		}
		
		double distCoeff = 0.0;
		double bestCoeff = 2.0;
		int nextState = 0;
		rvector tmp(0,this->m_ptrData->getNumStates()-1);
		for(int i = 1; i < length; i++){
			denominator[(int) _double(trace[i-1])] += 1;
			
			for(int c = 0; c < this->m_ptrData->getNumStates(); c++){
				tmp = numerator[(int) _double(trace[i-1])];
				tmp[c] += 1;
				
				for(int t = 0; t < this->m_ptrData->getNumStates(); t++){
					distCoeff += _double(abs(trans[(int) _double(trace[i-1])][t] - (tmp[t] / denominator[(int) _double(trace[i-1])])));
				}
				
				if(trans[(int) _double(trace[i-1])][c] != 0.0){
					if(distCoeff <= bestCoeff){
						bestCoeff = distCoeff;
						nextState = c;
					}
				}
				distCoeff = 0.0;
			}
			numerator[(int) _double(trace[i-1])][nextState] += 1;
			trace[i] = nextState;
			bestCoeff = 2.0;
		}
		
		return trace;
	}
	
	intvector DistributionApproximation::simulateDistribution(intvector indexSequence){
		rmatrix dist(cxsc::mid(this->m_ptrData->getDistributions()));
		
		intvector trace(0, this->m_length-1);
		rmatrix numerator(RMatrixUtils::zeros(0,Ub(dist,ROW),0,Ub(dist,COL)));
		rvector denominator(0,Ub(dist,ROW));
		
		for(int i = 0; i <= Ub(denominator); i++){
			denominator[i] = 0.0;
		}
		
		double distCoeff = 0.0;
		double bestCoeff = 2.0;
		int nextState = 0;
		rvector tmp(0,Ub(dist,COL));
		for(int i = 0; i < this->m_length; i++){
			denominator[indexSequence[i]] += 1;
			
			for(int c = 0; c <= Ub(dist,COL); c++){
				tmp = numerator[indexSequence[i]];
				tmp[c] += 1;
				
				for(int t = 0; t < this->m_ptrData->getNumStates(); t++){
					distCoeff += _double(abs(dist[indexSequence[i]][t] - (tmp[t] / denominator[indexSequence[i]])));
				}
				
				if(dist[indexSequence[i]][c] != 0.0){
					if(distCoeff <= bestCoeff){
						bestCoeff = distCoeff;
						nextState = c;
					}
				}
				distCoeff = 0.0;
			}
			numerator[indexSequence[i]][nextState] += 1;
			trace[i] = nextState;
			bestCoeff = 2.0;
		}
		
		return trace;	
	}
}
