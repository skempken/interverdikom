#include "ssmp.hpp"

using namespace std;
using cxsc::real;

namespace IvkModeling{
	SSMP::SSMP(const char* dateiname){
		srand(0);
		this->datenreihe = new Frames();
		this->datenreihe->inhalt = BasicIO::importFromFile(dateiname);
	}

	SSMP::SSMP(vector<double>* gops){
		srand(0);
		this->datenreihe = new Frames();
		this->datenreihe->inhalt = gops;
	}
	
	SSMP::SSMP(vector<int>* gops){
		srand(0);
		this->datenreihe = new Frames();
		for(unsigned int i=0; i < gops->size(); i++){
			this->datenreihe->inhalt->push_back((double) (*gops)[i]);
		}
	}
	
	SSMP::SSMP(intvector* gops){
		srand(0);
		this->datenreihe = new Frames();
		for(int i=0; i < Ub(*gops); i++){
			this->datenreihe->inhalt->push_back(cxsc::_double((*gops)[i]));
		}
	}
	
	SSMP::~SSMP(){
		delete[] zustaende;
		delete[] stationaer;
	}

	void SSMP::zustaende_berechnen(int m){
		this->m = m;
		double diff = this->datenreihe->max - this->datenreihe->min;
		this->schrittweite = (double) diff/  (double) m;
		this->zustaende = new double[m];
		
		this->zustaende[0] = this->datenreihe->min;

		for(int i = 1;i < m;i++){
			this->zustaende[i] = this->zustaende[i-1]+this->schrittweite;
		}
	}		

	int SSMP::get_Zustaende(){
		return this->m;
	}

	int SSMP::zustand_testen(double frame){
		int x = -1;
		
		if( (frame >= this->zustaende[0]) && (frame < this->zustaende[1]) ){ x = 0; }
		if( (frame >= this->zustaende[this->m-1]) && (frame <= this->datenreihe->max) ) { x = this->m-1; }
		if( x == -1) { x = this->zustand_testen(frame,(this->m-1)/2,this->m-1); }
		
		return x;
	}

	int SSMP::zustand_testen(double frame,int pos,int max){
		int ret;
		if ( (frame < this->zustaende[pos+1]) && (frame >= this->zustaende[pos]) ){	ret = pos; }
		else if( frame > this->zustaende[pos] ){ ret = this->zustand_testen(frame,((max-pos)/2)+pos,max); }
		else{ ret = this->zustand_testen(frame,pos/2,pos); }

		return ret;
	}

	void SSMP::zmittelwerte(){
		rmatrix* tmp = new rmatrix(0,this->m-1,0,1);
		Hilfsklasse::zero(*tmp);

		for(int i = 0;i < this->datenreihe->gop_anz;i++){
			(*tmp)[this->zustand_testen(this->datenreihe->gop[i])][0] += this->datenreihe->gop[i];
			(*tmp)[this->zustand_testen(this->datenreihe->gop[i])][1] += 1;
		}
		
		this->zustandsmittelwerte = new double[this->m];
		for(int i = 0;i < this->m;i++){
			this->zustandsmittelwerte[i] = cxsc::_double((*tmp)[i][0] / (*tmp)[i][1]);
		}
		delete tmp;
	}

	void SSMP::umatrix_erstellen(){
		this->umatrix = new rmatrix(0,this->m-1,0,this->m-1);
		Hilfsklasse::zero(*this->umatrix);
		
		int y,x;
		
		for(int i = 0; i < this->datenreihe->gop_anz-1; i++){
			y = this->zustand_testen(this->datenreihe->gop[i]);
			x = this->zustand_testen(this->datenreihe->gop[i+1]);
			(*this->umatrix)[y][x] += 1;
		}
		
		real y_wert;

		for(int y = 0; y < this->m; y++){
			y_wert = 0;
			for(int x = 0; x < this->m; x++){
				y_wert += (*this->umatrix)[y][x];
			}
			
			for(int x = 0; x< this->m; x++){
				(*this->umatrix)[y][x] = (y_wert != 0) ? (*this->umatrix)[y][x]/ y_wert : 0.0;
			}
		}
		
		double sum;
		for(int i = 0;i < this->m;i++){
			sum = 0.0;
			for(int n = 0;n < this->m;n++){
				sum += cxsc::_double((*this->umatrix)[n][i]);
			}
		}
	}

	rmatrix SSMP::umatrix_erstellen(rmatrix &pool,int folge,int m){
		rmatrix* retMatrix = new rmatrix(0,m-1,0,m-1);
		Hilfsklasse::zero(*retMatrix);
		
		for(int i = 0; i < Ub(pool,ROW); i++){
			(*retMatrix)[(int) cxsc::_double(pool[i][folge])][(int) cxsc::_double(pool[i+1][folge])] += 1;
		}
		
		real y_wert;

		for(int y = 0; y < m; y++){
			y_wert = 0;
			for(int x = 0; x < m; x++){
				y_wert += (*retMatrix)[y][x];
			}
			
			for(int x = 0; x< m; x++){
				(*retMatrix)[y][x] = (y_wert != 0) ? (*retMatrix)[y][x]/ y_wert : 0.0;
			}
		}
		
		double sum;
		for(int i = 0;i < m;i++){
			sum = 0.0;
			for(int n = 0;n < m;n++){
				sum += cxsc::_double((*retMatrix)[n][i]);
			}
		}
		return *retMatrix;
	}	
	
	rmatrix SSMP::umatrix_erstellen(rvector &folge,int m){
		rmatrix* retMatrix = new rmatrix(0,m-1,0,m-1);
		Hilfsklasse::zero(*retMatrix);
		
		for(int i = 0; i < Ub(folge); i++){
			(*retMatrix)[(int) cxsc::_double(folge[i])][(int) cxsc::_double(folge[i+1])] += 1;
		}
		
		real y_wert;

		for(int y = 0; y < m; y++){
			y_wert = 0;
			for(int x = 0; x < m; x++){
				y_wert += (*retMatrix)[y][x];
			}
			
			for(int x = 0; x< m; x++){
				(*retMatrix)[y][x] = (y_wert != 0) ? (*retMatrix)[y][x]/ y_wert : 0.0;
			}
		}
		
		double sum;
		for(int i = 0;i < m;i++){
			sum = 0.0;
			for(int n = 0;n < m;n++){
				sum += cxsc::_double((*retMatrix)[n][i]);
			}
		}
		return *retMatrix;
	}

	rmatrix SSMP::get_umatrix(){
		return *this->umatrix;
	}

	void SSMP::stat_wahrsch_rechnen(){
		this->stat_wahr = new rvector(1,this->m);
		(*this->stat_wahr) = QueueTools::computeStationaryProbabilities(*this->umatrix);
		SetLb(*this->stat_wahr,0);
	}

	rvector SSMP::stat_wahrsch_rechnen(rmatrix &umatrix){
		rvector* statWahr = new rvector(QueueTools::computeStationaryProbabilities(*this->umatrix));
		SetLb(*statWahr,0);
		return *statWahr;
	}

	rvector SSMP::get_stat_wahr(){
		return *this->stat_wahr;
	}

	rvector SSMP::autokorrelation_em(int n){
		double erw = Hilfsklasse::mittelwert(this->datenreihe->gop,this->datenreihe->gop_anz);
		double var = Hilfsklasse::varianz(this->datenreihe->gop,this->datenreihe->gop_anz);
		
		rvector autok(0,n-1);
		Hilfsklasse::zero(autok);
		autok[0] = 1;
		
		double* x_erw = new double[this->datenreihe->gop_anz];
		for(int i = 0;i < this->datenreihe->gop_anz;i++){
			x_erw[i] = this->datenreihe->gop[i] - erw;
		}
		
		for(int i = 1;i < n;i++){
			int hilfz = this->datenreihe->gop_anz-i;
			double* z = new double[hilfz];
			for(int c = 0;c < hilfz;c++){
				z[c] = 0;
			}
			for(int j = 0;j < hilfz;j++){
				z[j] = x_erw[j]*x_erw[j+i];
			}
			autok[i] = Hilfsklasse::mittelwert(z,hilfz) / var;
			
			delete z;
		}
		delete x_erw;
		return autok;
	}

	rvector SSMP::autokorrelation_um(int n,rmatrix &zmittelwerte,rmatrix &umatrix,rvector &statWahr,int folge){
		rvector autok(0,n-1);
		rvector p;
		
		real v = 0;
		
		rmatrix P_n(umatrix);
		
		real E_A = 0;
		for(int i = 0;i < this->m;i++){
			E_A += (real)( statWahr[i] * zmittelwerte[i][folge]);
		}
		
		for(int i = 0;i < this->m;i++){
			v += statWahr[i] * power(((real) zmittelwerte[i][folge] - E_A),2);
		}
		
		real E_A2 = power(E_A,2) / v;
		p = statWahr / v;
		
		rmatrix I(0,this->m-1,0,this->m-1);
		for(int i = 0;i < this->m;i++){
			for(int c = 0;c < this->m;c++){
				if(i == c){ I[i][c] = 1; }
				else{ I[i][c] = 0;}
			}
		}

		rvector E2(0,this->m-1);
		for(int i = 0;i < this->m;i++){
			E2[i] = power(zmittelwerte[i][folge],2);
		}
		autok[0] = (p*E2) - E_A2;
		
		for(int x = 1;x < n;x++){
			autok[x] = 0;
			for(int i = 0;i < this->m;i++){
				for(int j = 0;j < this->m;j++){
					autok[x] = autok[x] + (p[i]*zmittelwerte[i][folge]*P_n[i][j]*zmittelwerte[j][folge]);
				}
			}
			autok[x] = autok[x] - E_A2;
			P_n = P_n * umatrix;
		}
		return autok;
	}

	double SSMP::stdAbweichung(){
		double ret = Hilfsklasse::standardAbweichung(this->datenreihe->gop,this->datenreihe->gop_anz);
		return ret;
	}
}
