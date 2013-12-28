#include "RepeatedStateContractions.h"
#include "utility/RealUtils.h"
#include "utility/RVectorUtils.h"
#include "utility/Logging.hpp"

namespace ivk{
	const char * RepeatedStateContractions::PARAM_NUMCONTRACTIONS = "numContractions";

	RepeatedStateContractions::RepeatedStateContractions(const SSMProcess* data, const ComputationParameters &parameters)
	:AbstractComputation<SSMProcess, SSMProcess>(data, parameters){
		this->setParameters(parameters);
		this->bestAutocorrelation = -1.0;
	}
	RepeatedStateContractions::~RepeatedStateContractions(){	}

	void RepeatedStateContractions::setParameters(const ComputationParameters &parameters){
		this->setNumContractions(parameters.getInt(RepeatedStateContractions::PARAM_NUMCONTRACTIONS));
	}

	void RepeatedStateContractions::setNumContractions(const int value){
		this->numContractions = value;
	}

	int RepeatedStateContractions::getNumContractions() const{
		return this->numContractions;
	}

	SSMProcess* RepeatedStateContractions::contractSpecificStates(int n , int m , SSMProcess tSSMProcess){
		assert(n <= this->m_ptrData->getNumStates());
		assert(m <= this->m_ptrData->getNumStates());
		assert(n != m);

		rmatrix a( mid( tSSMProcess.getDistributions() ) );
		rmatrix t( mid( tSSMProcess.getTransitionMatrix() ) );

		//setting up initial values
		rvector p(tSSMProcess.getStationaryProbabilities());
		rmatrix a_( RMatrixUtils::zeros( Lb(a,ROW) , Ub(a,ROW)-1 , Lb(a,COL) , Ub(a,COL) ) );
		rmatrix p_( RMatrixUtils::zeros( Lb(t,ROW) , Ub(t,ROW)-1 , Lb(t,COL) , Ub(t,COL)-1 ) );

		//contracting state in transitionMatrix
		for(int i = Lb(a,ROW); i <= Ub(a,ROW); i++){
			int buff = (i > n) ? -1 : 0;

			for(int x = Lb( Row(a,1) ); x <= Ub( Row(a,1) );x++){
				real value = 0.0;
				if(i != m && i != n){
					a_[i+buff][x] = a[i][x];
				}
				else if(i == m){
					a_[i+buff][x] = (p[i]*a[i][x] + p[n]*a[n][x]) / (p[n]+p[m]);
				}
			}
		}

		for(int i = 1; i < tSSMProcess.getNumStates(); i++){
			int buffI = (i > n) ? -1 : 0;

			for(int j = 1; j < tSSMProcess.getNumStates();j++){
				int buffJ = (j > n) ? -1 : 0;

				real value = 0.0;
				if(i != m && i != n && j != n && j != m){
					value = t[i][j];
				}
				else if( i != m && i != n && j == m ){
					value = t[i][m] + t[i][n];
				}
				else if( i == m && j != m && j != n){
					value = (p[m]*t[m][j] + p[n]*t[n][j]) / (p[m] + p[n]);
				}
				else if( i == m && j == m){
					value = ( (p[m]*(t[m][m]+t[m][n])) + (p[n]*(t[n][m]+t[n][n])) ) / (p[m] + p[n]);
				}

				p_[i+buffI][j+buffJ] = value;
			}
		}

		return new SSMProcess( p_ , a_ , false );
	}


	vector<pair< pair<int,int>, real> > RepeatedStateContractions::checkValue( SSMProcess *model){
		vector< pair< pair< int , int > , real > > qualitySortetContractions;

		rvector statProb( model->getStationaryProbabilities() );
		real var( model->getVariance() );
		rvector stateMeans( model->getStateMeans() );
		for( int i = 1; i < model->getNumStates() ; i++){
			for( int j = i+1 ;j <= model->getNumStates() ; j++){
				real ret = ( statProb[i] * statProb[j] ) / ( statProb[i] + statProb[j] );
				ret *= RealUtils::rPow( stateMeans[i] - stateMeans[j] , 2) / var;
				qualitySortetContractions.push_back( make_pair( make_pair( i , j ) , ret ) );
			}
		}

		std::sort( qualitySortetContractions.begin() , qualitySortetContractions.end() , RVectorUtils::test2LayerPairs );

		return qualitySortetContractions;
	}

	SSMProcess* RepeatedStateContractions::contractStates( int depth , SSMProcess* model ){
		vector< pair< pair< int , int > , real > > vec = this->checkValue( model );

		for( int i = 0; i < vec.size(); i++ ){
			if( this->bestAutocorrelation == -1.0 ){
				if( depth < this->numContractions ){
					SSMProcess* newModel = this->contractSpecificStates( vec[i].first.first , vec[i].first.second , *model );
					this->contractStates( depth +1 , newModel );
				}
				else{
					this->bestAutocorrelation = vec[i].second;
					this->bestModel = model;
				}
			}
			else{
				if( this->bestAutocorrelation > vec[i].second ){
					if( depth < this->numContractions ){
						SSMProcess* newModel = this->contractSpecificStates( vec[i].first.first , vec[i].first.second , *model );
						this->contractStates( depth +1 , newModel );
					}
					else{
						this->bestAutocorrelation = vec[i].second;
						this->bestModel = model;
					}
				}
			}
		}
	}

//	void StateContraction::contract

	SSMProcess* RepeatedStateContractions::compute(){
		this->contractStates( 0 , (SSMProcess* ) this->m_ptrData );
		return  this->bestModel;
	}
}
