#include "StatePartitioning.h"

#include "utility/RealUtils.h"
#include "utility/RMatrixUtils.h"
#include "utility/Logging.hpp"
#include <iostream>

namespace ivk{
	const char * StatePartitioning::PARAM_NUMCONTRACTIONS = "numContractions";

	StatePartitioning::StatePartitioning(const SSMProcess* data, const ComputationParameters &parameters)
	:AbstractComputation<SSMProcess, SSMProcess>(data, parameters){
		this->setParameters( parameters );
		this->accErr = cxsc::MaxReal;
	}

	StatePartitioning::~StatePartitioning(){

	}

	void StatePartitioning::setParameters(const ComputationParameters &parameters){
		this->setNumContractions(parameters.getInt(StatePartitioning::PARAM_NUMCONTRACTIONS));
	}

	void StatePartitioning::setNumContractions(const int value){
		this->numContractions = value;
	}

	int StatePartitioning::getNumContractions() const{
		return this->numContractions;
	}

	SSMProcess StatePartitioning::sortByExpectation(){
		rvector means = this->m_ptrData->getStateMeans();
		vector< pair< int , real > > sorted = RVectorUtils::sortWithIndex( means );

		rmatrix newTransition( mid( this->m_ptrData->getTransitionMatrix() ) );
		rmatrix newDistribution( mid( this->m_ptrData->getDistributions() ) );

		rmatrix transition( mid( this->m_ptrData->getTransitionMatrix() ) );
		rmatrix distribution( mid( this->m_ptrData->getDistributions() ) );

		int rowcount = 0;
		int colcount = 0;
		for( int i = Lb( newTransition , ROW ) ; i <= Ub( newTransition , ROW ) ; i++ ){
			for(int j = Lb( newTransition , COL ) ; j <= Ub( newTransition , COL ) ; j++ ){
				newTransition[i][j] = transition[ sorted[rowcount].first ][ sorted[colcount].first ];
				colcount++;
			}
			rowcount ++;
			colcount = 0;
		}

		rowcount = 0;
		for( int i = Lb( newDistribution , ROW ) ; i <= Ub( newDistribution , ROW ) ; i++ ){
			for( int j = Lb( newDistribution , COL ) ; j <= Ub( newDistribution , COL ) ; j++ ){
				newDistribution[i][j] = distribution[ sorted[rowcount].first ][j];
			}
			rowcount ++;
		}

		SSMProcess ret( newTransition , newDistribution );
		return ret;
	}

	real StatePartitioning::autocorrelationError( int startIndex , int endIndex ){
		SSMProcess sortedProcess = this->sortByExpectation();
		rvector statProbs( sortedProcess.getStationaryProbabilities() );
		rvector expect( sortedProcess.getStateMeans() );

		real e_ = 0.0;
		for( int i = startIndex ; i <= endIndex ; i++){
			e_ += statProbs[i] * expect[i];
		}

		real s_j = 0.0;
		for( int k = startIndex ; k <= endIndex ; k++ ){
			s_j += statProbs[k] * RealUtils::rPow( expect[k] , 2) - RealUtils::rPow( e_ , 2 );
		}
		s_j /= sortedProcess.getVariance();

		return s_j;
	}

	void StatePartitioning::recursionInit(){
		int x = this->m_ptrData->getNumStates() - this->numContractions;
		this->recursion( 1 , this->m_ptrData->getNumStates() , x-1 );
	}

	void StatePartitioning::recursion( int m , int k , int numParts){
		if( numParts == 1 ){
			this->ranges.push_back( make_pair( m , k ) );
			this->calculateRangeValue();
			this->ranges.pop_back();
		}
		else{
			for(int i = m+1 ; i <= k-numParts+1 ; i++){
				this->ranges.push_back( make_pair( m , i ) );
				this->recursion( i , k , numParts-1 );
				this->ranges.pop_back();
			}
		}
	}

	void StatePartitioning::calculateRangeValue(){
		vector< range > tmp = this->ranges;
		real acerr = 0.0;

		for( int i = 0 ; i < tmp.size() ; i++ ){
			acerr += this->autocorrelationError( tmp[i].first , tmp[i].second  );
		}

		if( acerr < this->accErr ){
			this->accErr = acerr;
			this->finalRanges = this->ranges;
		}
		//this->ranges.clear();
	}

	SSMProcess StatePartitioning::applyRanges(){
		SSMProcess process( *this->m_ptrData );

		for( int i = 0 ; i < this->finalRanges.size() ; i++ ){
			if( ( this->finalRanges[i].second - this->finalRanges[i].first ) > 1){
				int numContractions = this->finalRanges[i].second - this->finalRanges[i].first -1 ;
				intvector contractions( 1 , numContractions );

				for(int c = Lb( contractions ) ; c <= Ub( contractions ) ; c++ ){
					contractions[ c ] = this->finalRanges[i].first + c;
				}
				process = contractStates( process , this->finalRanges[i].first , contractions );
			}

		}

		return process;
	}

	SSMProcess StatePartitioning::contractStates(const SSMProcess &model , int receivingState, const intvector &states){
		int m = receivingState;
		rmatrix d = mid(model.getDistributions());
		rmatrix t = mid(model.getTransitionMatrix());
		rvector p = model.getStationaryProbabilities();

		rmatrix d_ = RMatrixUtils::zeros( Lb( d,ROW ) , Ub( d,ROW ) - ( VecLen( states ) ) , Lb( d,COL ) , Ub( d,COL ) );
		rmatrix t_ = RMatrixUtils::zeros( Lb( t,ROW ) , Ub( t,ROW ) - ( VecLen( states ) ) , Lb( t,ROW ) , Ub( t,ROW ) - ( VecLen( states ) ) );

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
					assert(i+buff >= Lb(d_, 1));
					d_[ i+buff ][x] = d[i][x];
				}
				else if( i == receivingState ){
					real numerator = p[receivingState] * d[receivingState][x];
					real denominator = p[receivingState];

					for( int c = Lb( states ) ; c <= Ub( states ) ; c++ ){
						assert(states[c] >= Lb(d, 1));
						assert(states[c] <= Ub(d, 1));
						numerator += p[states[c]] * d[states[c]][x];
						denominator += p[states[c]];
					}

					assert(i+buff >= Lb(d_, 1));
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
/*
		Logging::log( Logging::Debug , "d_:" , d_ );
		Logging::log( Logging::Debug , "t_:" , t_ );
*/
		return SSMProcess( t_ , d_ , false );
	}

	SSMProcess* StatePartitioning::compute(){
		this->recursionInit();
		/*this->applyRanges();
		return new SSMProcess(*this->m_ptrData);*/
		return new SSMProcess( this->applyRanges() );
	}
}

