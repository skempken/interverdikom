#include "StateMerge.h"
#include <vector>

namespace ivk{
	const char * StateMerge::PARAM_CONTRACTIONVECTOR = "conVector";
	const char * StateMerge::PARAM_CONTRACTIONTYPE = "conType";

	intvector StateMerge::generateContractionVectorStatProb(const SSMProcess* process, int numberOfContractions){
		rvector statProb( process->getStationaryProbabilities() );

		vector<std::pair< int , real> > sortetProb = RVectorUtils::sortWithIndex( statProb );
		intvector ret(1,numberOfContractions);

		for(int i = Lb( ret ); i <= Ub( ret ); i++ ){
			ret[i] = sortetProb[i-1].first;

		}

		return ret;
	}

	intvector StateMerge::generateContractionVectorMean(const SSMProcess* process, int numberOfContractions){
		rvector means( process->getStateMeans() );
		int states = process->getNumStates();

		intvector ret(1,numberOfContractions);

		real bestMeanBunch = -1;
		int startState = -1;

		for(int i = Lb( means ); i <= states - ( numberOfContractions - 1 ) ; i++ ){
			real sum = 0;
			for( int n = Lb( ret ); n <= Ub( ret ) -1 ; n++){
				sum += means[i+n-1] - means[i+n];
			}
			if( sum < bestMeanBunch || bestMeanBunch == -1){
				bestMeanBunch = sum;
				startState = i;
			}
		}

		assert( startState != -1);

		for(int i = Lb( ret ); i <= Ub( ret ); i++){
			ret[i] = startState + i - 1 ;
		}

		return ret;
	}

	intvector StateMerge::generateContractionVector(int numberOfContractions){
		intvector ret;
		switch(this->contractionType){
			case 1:
				ret = StateMerge::generateContractionVectorStatProb(this->m_ptrData , numberOfContractions);
				break;
			case 2:
				ret = StateMerge::generateContractionVectorMean(this->m_ptrData , numberOfContractions);
				break;
		}
		return ret;
	}

	StateMerge::StateMerge(const SSMProcess* data, const ComputationParameters &parameters)
	:AbstractComputation<SSMProcess, SSMProcess>(data, parameters){
		this->contractedDistribution = 0;
		this->contractedTransitionMatrix = 0;
		this->setParameters(parameters);
	}
	StateMerge::~StateMerge(){
	}

	void StateMerge::setParameters(const ComputationParameters &parameters){
		this->setContractionVector(parameters.getIntVector(StateMerge::PARAM_CONTRACTIONVECTOR));
		this->setContractionType(parameters.getInt(StateMerge::PARAM_CONTRACTIONTYPE));
	}

	void StateMerge::setContractionVector(const intvector value){
		this->contractionVector = value;
	}

	void StateMerge::setContractionType(const int value){
		this->contractionType = value;
	}

	int StateMerge::getContractionType() const{
		return this->contractionType;
	}

	int StateMerge::getNumStates(){
		return this->m_ptrData->getNumStates();
	}

	intvector StateMerge::getContractionVector() const{
		return this->contractionVector;
	}

	SSMProcess* StateMerge::contractStates(int receivingState, intvector states){
		int m = receivingState;
		rmatrix d(mid(this->m_ptrData->getDistributions()));
		rmatrix t(mid(this->m_ptrData->getTransitionMatrix()));
		rvector p(this->m_ptrData->getStationaryProbabilities());

		rmatrix d_(RMatrixUtils::zeros( Lb( d,ROW ) , Ub( d,ROW ) - ( VecLen( states ) ) , Lb( d,COL ) , Ub( d,COL ) ) );
		rmatrix t_(RMatrixUtils::zeros( Lb( t,ROW ) , Ub( t,ROW ) - ( VecLen( states ) ) , Lb( t,ROW ) , Ub( t,ROW ) - ( VecLen( states ) ) ) );

		for( int i = Lb( t,ROW ) ; i <= Ub( t,ROW ) ; i++ ){
			int buff = 0;
			for(int c = Lb( states ) ; c <= Ub(states);c++){
				if( states[c] <= i ){ buff -= 1; }
			}

			for( int x = Lb( d,COL ) ; x <= Ub( d,COL ) ; x++ ){

				bool check = true;
				for(int c = Lb( states ) ; c <= Ub( states ) ; c++){
					if( states[c] == i || receivingState == i ){ check = false; }
				}

				if( check ){
					d_[ i+buff ][x] = d[i][x];
				}
				else if( i == receivingState ){
					real numerator = p[receivingState] * d[receivingState][x];
					real denominator = p[receivingState];

					for( int c = Lb( states ) ; c <= Ub( states ) ; c++ ){
						numerator += p[states[c]] * d[states[c]][x];
						denominator += p[states[c]];
					}


					d_[ i+buff ][x] = numerator / denominator;
				}
			}
		}

		for( int i = Lb( t,ROW ) ; i <= Ub( t,ROW ) ; i++ ){

			bool iPull = false;
			bool iPush = false;
			int buffI = 0;

			for( int c = Lb( states ) ; c <= Ub( states ) ; c++ ){
				if(states[c] < i){ buffI -= 1; }
				if(states[c] == i){ iPush = true; }
			}

			if( receivingState == i ){ iPull = true; }

			for( int j = Lb( t,ROW ) ; j <= Ub( t,ROW ) ; j++ ){
				bool jPush = false;
				bool jPull = false;
				real numerator = 0.0;
				real denominator = 0.0;
				int buffJ = 0;

				for(int c = 0; c <= Ub(states); c++){
					if(states[c] < j){ buffJ -= 1; }
					if(states[c] == j){ jPush = true; }
				}

				if(receivingState == j){ jPull = true; }

				real value = 0.0;
				if(!iPush && !iPull && !jPush && !jPull){
					value = t[i][j];
				}
				else if( !iPush && !iPull && jPull ){
					value = t[i][receivingState];
					for(int c = Lb( states ) ; c <= Ub( states ) ; c++){
						value += t[i][states[c]];
					}
				}
				else if( iPull && !jPull && !jPush){
					numerator = p[receivingState] * t[receivingState][j];
					denominator = p[receivingState];
					for(int c = Lb( states ) ; c <= Ub( states ) ; c++){
						numerator += p[states[c]]*t[states[c]][j];
						denominator += p[states[c]];
					}
					value = numerator / denominator;

				}
				else if( iPull && jPull){
					denominator = p[receivingState];
					real tmp = t[receivingState][receivingState];
					for(int c = Lb( states ) ; c <= Ub( states ) ; c++ ){
						tmp += t[receivingState][states[c]];
						numerator += p[states[c]] * (t[states[c]][receivingState] + t[states[c]][states[c]]);
						denominator += p[states[c]];
					}
					numerator += p[receivingState] * tmp;

					value = numerator / denominator;

				}
				t_[i+buffI][j+buffJ] = value;
			}
		}

		return new SSMProcess( t_ , d_ , false );
	}

	SSMProcess* StateMerge::compute(){
		intvector conVec( Lb( this->contractionVector ) , Ub( this->contractionVector )-1 );
		for(int i = Lb( conVec ); i <= Ub( conVec ); i++){
			int x = this->contractionVector[i+1];
			conVec[i] = x;
		}

		return this->contractStates( this->contractionVector[ Lb( this->contractionVector ) ] ,conVec);
	}
}
