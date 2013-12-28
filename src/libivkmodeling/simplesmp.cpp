#include "simplesmp.hpp"

namespace IvkModeling{
	SimpleSMP::SimpleSMP(const char* filename,int states, int gopSize){
		this->ssmp = new SSMP::SSMP(filename);
		this->setStates(states);
		this->setGopSize(gopSize);
	}

	SimpleSMP::SimpleSMP(vector<double>* data,int states, int gopSize){
		this->ssmp = new SSMP::SSMP(data);
		this->setStates(states);
		this->setGopSize(gopSize);
	}
	
	SimpleSMP::SimpleSMP(vector<int>* data,int states, int gopSize){
		this->ssmp = new SSMP::SSMP(data);
		this->setStates(states);
		this->setGopSize(gopSize);
	}	
	
	SimpleSMP::SimpleSMP(cxsc::intvector* data,int states, int gopSize){
		this->ssmp = new SSMP::SSMP(data);
		this->setStates(states);
		this->setGopSize(gopSize);
	}
	
	void SimpleSMP::setStates(int m)					{ this->states = m; }
	void SimpleSMP::setGopSize(int size)			{ this->gopSize = size; }
	
	double SimpleSMP::getMin()						{ return this->ssmp->datenreihe->min; }
	double SimpleSMP::getMax()						{ return this->ssmp->datenreihe->max; }
	int SimpleSMP::getState(double gop)			{ return this->ssmp->zustand_testen(gop); }
	int SimpleSMP::getStates()			 			{ return this->states; }
	int SimpleSMP::getGopSize()		 			{ return this->gopSize; }
	int SimpleSMP::getGopAnz()						{ return this->ssmp->datenreihe->gop_anz; }
	rmatrix SimpleSMP::getTransitionMatrix() 	{ return this->ssmp->get_umatrix(); }
	double* SimpleSMP::getGops()					{ return this->ssmp->datenreihe->gop; }
	
	void SimpleSMP::compute(){
		this->ssmp->datenreihe->frames_zu_gop(this->gopSize);
		this->ssmp->zustaende_berechnen(this->states);
		this->ssmp->umatrix_erstellen();
	}
	
	void SimpleSMP::exportToXML(const char* filename){
		//~ IvkModeling::BasicIO::BasicIO::exportToFile(filename,this->getTransitionMatrix(),this);
	}
}
