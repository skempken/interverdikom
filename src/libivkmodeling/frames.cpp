#include "frames.hpp"

namespace IvkModeling{
	Frames::Frames(){
		this->inhalt = new vector<double>;
	}
	Frames::~Frames(){
		delete this->inhalt;
		delete this->gop;
	}

	double* Frames::getGop(){ return this->gop; }
	double  Frames::getMin(){ return this->min; }
	double  Frames::getMax(){ return this->max; }

	void Frames::frames_zu_gop(int gop_groesse){
		this->gop_anz = (int) ceil((double) this->inhalt->size()/ (double) gop_groesse);
		
		this->gop = new double[this->gop_anz];
		double sigma = 0;
		bool initiat = true;
		
		for(int gops = 0;gops < this->gop_anz;gops++){
			unsigned int vergl;
			for(int i = 0; i < gop_groesse; i++){
				sigma += (*this->inhalt)[(gops*gop_groesse+i)];
				vergl = gops*gop_groesse+i;
				if(vergl >= this->inhalt->size()-1) { break; }
			}
			this->gop[gops] = sigma;
			
			if(initiat == true){
				this->min = sigma;
				this->max = sigma;
				initiat = false;
			}
			else{
				if(this->min > sigma){ this->min = sigma; }
				if(this->max < sigma){ this->max = sigma; }
			}
			sigma=0;
		}
	}
}
