#include "MMCModeler.h"

namespace ivk{

	const char* MMCModeler::PARAM_W = "w";
	const char* MMCModeler::PARAM_MS = "sampleSize";
	const char* MMCModeler::PARAM_MA = "averageSize";
	
	MMCModeler::MMCModeler(const Trace * ptrData, const ComputationParameters &parameters)
	: AbstractDiscreteSSMPModeler(ptrData, parameters)	{
		this->setXi(ptrData);
		this->setParameters(parameters);
	}

	MMCModeler::~MMCModeler(){
	}

	void MMCModeler::setXi(const Trace * ptrData){ 
		rvector tmp(ptrData->getTrace());
		this->xi = rvector(Lb(tmp),Ub(tmp));
		for(int i = Lb(tmp); i <= Ub(tmp); i++){
			this->xi[i] = (int) _double( tmp[i] );
		}
	}
	rvector MMCModeler::getXi() const { return this->xi; }
	
	void MMCModeler::setW(const int value) { this->w = value; }
	int  MMCModeler::getW() const { return this->w; }
	
	void MMCModeler::setNumMS(const int value) { this->mS = value; }
	int  MMCModeler::setNumMS() const { return this->mS; }
	
	void MMCModeler::setNumMA(const int value) { this->mA = value; }
	int  MMCModeler::setNumMA() const { return this->mA; }
	
	void MMCModeler::setParameters(const ComputationParameters &parameters){
		this->setNumDSteps(parameters.getInt(PARAM_NUMDSTEPS));
		this->setNumStates(0);
		this->setW(parameters.getInt(PARAM_W));		
		this->setNumMS(parameters.getInt(PARAM_MS));		
		this->setNumMA(parameters.getInt(PARAM_MA));
	}
	
	ComputationParameters MMCModeler::getParameters(){
		ComputationParameters* parameters = new ComputationParameters();
		parameters->setInt(MMCModeler::PARAM_NUMDSTEPS, this->getNumDSteps());
		parameters->setInt(MMCModeler::PARAM_NUMSTATES, this->getNumStates());
		parameters->setInt(MMCModeler::PARAM_W, this->w);		
		parameters->setInt(MMCModeler::PARAM_MS, this->mS);		
		parameters->setInt(MMCModeler::PARAM_MA, this->mA);
		return *parameters;
	}
	
	void MMCModeler::calcXi_(){
		setProgressText("calculate series of pairs");
		this->xi_ = rvector(Lb(this->xi),Ub(this->xi));
		for(int i = Lb( this->xi ) ; i <= Ub( this->xi ) ; i++){
			double sum = 0;
			
			if(i > this->w){
				
				for(int n=1;n <= this->w; n++){
					sum += _double(this->xi[i-n]);
				}
				this->xi_[i] = (int) ( (1/(double) this->w) * sum );
			}
			else{
				for(int n = 1; n <= i; n++){
					sum += (i == 0) ? _double(this->xi[i]) : _double(this->xi[i-n]);
				}
				this->xi_[i] = (int) ( (1/(double) i+1) * sum ); 
			}
			setProgressValue(1 + (int)( (double) (40.0 / Ub( this->xi )) * i));
		}
	}
	
	void MMCModeler::calcStateSpace(){
		setProgressText("calculate state space");
		this->mSi = intvector( Lb( this->xi ) , Ub( this->xi ) );
		this->mAi = intvector( Lb( this->xi_ ) , Ub( this->xi_ ) );
		
		Trace tXi( this->xi );
		Trace tXi_(this->xi_);
		
		for(int i = Lb( this->xi ); i <= Ub( this->xi ); i++){
			this->mSi[i] = (this->xi[i] == tXi.getMinimum()) ? 1 : (int) ceil(_double( ( this->xi[i]-tXi.getMinimum() ) / ( tXi.getMaximum() - tXi.getMinimum() ) ) * this->mS);
			setProgressValue(41 + (int) ( (double)( 20.0 / Ub( this->xi )) * i));
		}

		for(int i = Lb( this->xi_ ); i <= Ub( this->xi_ ); i++){
			this->mAi[i] = ( this->xi_[i] == tXi_.getMinimum()) ? 1 : (int) ceil(_double( ( this->xi_[i]-tXi_.getMinimum() ) / ( tXi_.getMaximum() - tXi_.getMinimum() ) ) * this->mA);
			setProgressValue(61 + (int) ( (double) ( 20.0 / Ub( this->xi_ )) * i));
		}
	}
	
	SSMProcess* MMCModeler::calcGlobalTransitionMatrix(){
		setProgressText("calculate global transition matrix");
		intvector globStates( Lb( this->mSi ) , Ub( this->mSi ) );

		for( int i = Lb( this->xi ) ; i <= Ub( this->xi ) ; i++ ){
			globStates[i] = (int) _double(( this->mSi[i]-1) * this->mA + this->mAi[i]);
			setProgressValue(81 + (int) ( (double) (19.0 / Ub( this->xi )) * i));
		}
		setProgressText("creating model");
		return this->modelFromIndexSequence(globStates);
	}	
	
	SSMProcess* MMCModeler::compute(){
		setProgressText("starting computation");
		setProgressMax(100);
		setProgressValue(1);
		this->calcXi_();
		this->calcStateSpace();
		return this->calcGlobalTransitionMatrix();
		
	}
}
