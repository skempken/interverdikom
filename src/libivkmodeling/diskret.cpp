#include "diskret.hpp"
#include<iostream>
using namespace std;
namespace IvkModeling{
	Diskretisierung::Diskretisierung(int m,int gop_anz,double min, double max,double* zustaende){
		this->m = m;
		this->gop_anz = gop_anz;
		this->min = min;
		this->max = max;
		this->zustaende = new double[m];
		this->zustaende = zustaende;
	}

	Diskretisierung::~Diskretisierung(){}

	int Diskretisierung::zustand_testen(double frame){
		int x = -1;
		
		if( (frame >= this->zustaende[0]) && (frame < this->zustaende[1]) ){ x = 0; }
		if( (frame >= this->zustaende[this->m-1]) && (frame <= this->max) ) { x = this->m-1; }
		if( x == -1) { x = this->zustand_testen(frame,(this->m-1)/2,this->m-1); }
		
		return x;
	}

	int Diskretisierung::zustand_testen(double frame,int pos,int max){
		int ret;
		if ( (frame < this->zustaende[pos+1]) && (frame >= this->zustaende[pos]) ){	ret = pos; }
		else if( frame > this->zustaende[pos] ){ ret = this->zustand_testen(frame,((max-pos)/2)+pos,max); }
		else{ ret = this->zustand_testen(frame,pos/2,pos); }
		
		return ret;
	}		

	double** Diskretisierung::diskretisieren(double* gop, int schritte){
		double** disk;
		int anzahl = (int) ceil((double) (max - min)/(double) schritte);
		anzahl++;
		double s_l[anzahl];
		s_l[0] = min;
		for(int i = 1;i < anzahl-1;i++){
			s_l[i] = s_l[i-1]+schritte;
		}
		s_l[anzahl-1] = max;
		
		double s_k;
		double delta = schritte;
		disk = new double* [this->m];
		int* werte_verteilung = new int[this->m];
		for(int i = 0;i < this->m;i++){
			werte_verteilung[i] = 0;
		}
		
		for(int i = 0;i < this->gop_anz;i++){
			werte_verteilung[this->zustand_testen(gop[i])] += 1;
		}
		
		for(int i = 0;i < this->m;i++){
			int k = werte_verteilung[i];
			
			disk[i] = new double[anzahl];
			for(int n = 0;n < anzahl;n++){
				disk[i][n] = 0;
			}
			for(int n = 0;n < this->gop_anz;n++){
				if(this->zustand_testen(gop[n]) == i){
					s_k = (double) gop[n];
					for(int c = 0;c < anzahl;c++){
						double tmp = delta;
						if(c >= anzahl-2){ delta = s_l[anzahl-1] - s_l[anzahl-2]; }
						if(fabs(s_k-s_l[c]) <= delta){
							disk[i][c] += (delta-fabs(s_k-s_l[c])) / ((double) k*delta);
						}
						delta = tmp;
					}
				}
			}
		}
		
		delete werte_verteilung;
		return disk;
	}
}
