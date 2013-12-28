#include "PronyMethod.h"

namespace ivk{
	PronyMethod::PronyMethod(SSMProcess* smp){
		this->smp_ = smp;
		this->states = smp->getNumStates();
		this->a = new rvector(smp->getAutocorrelation(this->states*2));
		this->mu = 0;
		this->imat = 0;
		this->coeff = 0;
		this->n = 0;
	}
	
	PronyMethod::~PronyMethod(){
		if(this->smp_ != 0){ delete this->smp_; }
		if(this->a != 0){ delete this->a; }
		if(this->mu != 0){ delete this->mu; }
		if(this->imat != 0){ delete this->imat; }
		if(this->coeff != 0){ delete this->coeff; }
	}
	
	void PronyMethod::setN(int n){
		this->n = n;
	}
	
	int PronyMethod::getN(){
		return this->n;
	}
	
	void PronyMethod::setMuMatrix(){
		this->mu = new rvector(RMatrixUtils::eigLR(mid(this->smp_->getTransitionMatrix()),0.000005));
		
		this->imat = new imatrix( 0, this->states-1, 0, this->states-1 );
		for(int i = Lb((*this->imat),1); i <= Ub((*this->imat),1); i++){
			for(int c = Lb((*this->imat),2); c <= Ub((*this->imat),2); c++){
				if(i==0)
					(*this->imat)[i][c] = interval(1.0,1.0);
				else
					(*this->imat)[i][c] = interval( RealUtils::rPow( (*this->mu)[c] , i ) , RealUtils::rPow( (*this->mu)[c] , i ) );
			}
		}
	}
	
	void PronyMethod::verifyResult(){
		ivector rightside(0,this->states-1);
		for(int i = Lb( rightside ); i <= Ub( rightside ); i++){
			rightside[i] = interval( (*this->a)[i], (*this->a)[i] );
		}
		
		this->coeff = new ivector(0,this->states-1);
		for(int i = Lb( (*this->coeff) ); i <= Ub( (*this->coeff) ) ; i++){
			(*this->coeff)[i] = interval( 0.0 , 0.0 );
		}
		
		ILinSys l;
		l.ILinSolve(*this->imat,rightside,*this->coeff,this->err);
	}
	
	interval PronyMethod::computeAutocorrelation(int x){
		interval ret( 0.0, 0.0 );
		for(int i = Lb( (*this->coeff) ); i <= Ub( (*this->coeff) ); i++){
			ret += (*this->coeff)[i] * RealUtils::rPow( (*this->mu)[i-1] , x) ;
		}
		return ret;
	}
	
	interval PronyMethod::compute(){
		this->setMuMatrix();
		this->verifyResult();
		return this->computeAutocorrelation( this->n );
	}
}
