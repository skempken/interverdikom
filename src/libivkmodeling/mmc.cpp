#include "mmc.hpp"

namespace IvkModeling{
	MMC::MMC(rvector data){
		this->xi = new rvector(data);
	}
	
	MMC::MMC(vector<double> data){
		this->xi = new rvector(0,data.size()-1);
		
		for(unsigned int i=0; i < data.size(); i++){
			(*this->xi)[i] = data[i];
		}
	}
	
	MMC::MMC(const char* filename,int gopSize){
		Frames::Frames* f = new Frames::Frames();
		f->inhalt = BasicIO::importFromFile(filename);
		f->frames_zu_gop(gopSize);
		
		this->xi = new rvector(0,f->gop_anz-1);
		
		for(int i=0; i < f->gop_anz; i++){
			(*this->xi)[i] = f->gop[i];
		}		
	}
	
	MMC::~MMC(){
		delete this->xi;
	}
	
	void MMC::setW(int w)	{ this->w = w; }
	void MMC::setMA(int mA)	{ this->mA = mA; }
	void MMC::setMS(int mS)	{ this->mS = mS; }
	
	int MMC::getW()		{ return this->w; }
	int MMC::getMA()		{ return this->mA; }
	int MMC::getMS()		{ return this->mS; }
	rvector MMC::getXi()	{ return *this->xi; }
	rvector MMC::getXi_(){ return *this->xi_; }
	
	void MMC::calcXi_(){
		this->xi_ = new rvector(0,Ub(*this->xi));
		for(int i=0;i <= Ub(*this->xi);i++){
			if(i >= this->w){
				double sum = 0;
				for(int n=1;n <= this->w; n++){
					sum += _double((*this->xi)[i-n]);
				}
				(*this->xi_)[i] = (1/(double) this->w) * sum;
			}
		}
	}
	
	void MMC::calcStateSpace(){
		this->mSi = new rvector(0,Ub(*this->xi));
		this->mAi = new rvector(0,Ub(*this->xi_));
		
		Trace tXi(*this->xi);
		Trace tXi_(*this->xi_);
		
		for(int i=0; i <= Ub(*this->xi); i++){
			(*this->mSi)[i] = ((*this->xi)[i] == tXi.getMinimum()) ? 1 : ceil(_double( ( (*this->xi)[i]-tXi.getMinimum() ) / ( tXi.getMaximum() - tXi.getMinimum() ) ) * this->mS);
		}
		
		for(int i=0; i <= Ub(*this->xi_); i++){
			(*this->mAi)[i] = ((*this->xi_)[i] == tXi_.getMinimum()) ? 1 : ceil(_double( ( (*this->xi_)[i]-tXi_.getMinimum() ) / ( tXi_.getMaximum() - tXi_.getMinimum() ) ) * this->mA);
		}
	}

	void MMC::calcTransitionMatrix(){
		rvector globStates(0,Ub(*this->mSi)-this->w);
		for(int i=this->w;i <= Ub(*this->xi);i++){
			globStates[i-this->w] = (*this->mSi)[i]*this->mS+(*this->mAi)[i];
		}
		
		this->transMat = new rmatrix(SSMP::umatrix_erstellen(globStates,this->mS*this->mA));
		Hilfsklasse::testeMatrix(*this->transMat);
		std::cout << *this->transMat;
	}
	
	void MMC::compute(){
		this->calcXi_();
		this->calcStateSpace();
		this->calcTransitionMatrix();
	}
}
