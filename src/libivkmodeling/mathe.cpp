#include<math.h>
#include "mathe.hpp"
#define p(y,x); cout<<y<<x<<endl;

using namespace std;

namespace IvkModeling{
	Hilfsklasse::Hilfsklasse(){}
	Hilfsklasse::~Hilfsklasse(){}

	double Hilfsklasse::mittelwert(int* gop,int gop_anz){
		double sigma = 0;
		for(int i = 0;i < gop_anz;i++){
			sigma += gop[i];
		}
		double ret = sigma / (double) gop_anz;
		return ret;
	}

	double Hilfsklasse::mittelwert(vector<int> gop){
		double sigma = 0;
		for(unsigned int i = 0;i < gop.size();i++){
			sigma += gop[i];
		}
		double ret = sigma / (double) gop.size();
		return ret;
	}

	double Hilfsklasse::mittelwert(double* gop,int gop_anz){
		double sigma = 0;
		for(int i = 0;i < gop_anz;i++){
			sigma += gop[i];
		}
		double ret = ((double) sigma / (double) gop_anz);
		return ret;
	}

	double Hilfsklasse::mittelwert(double* gops,int anfang,int ende){
		double sigma = 0;
		for(int i = anfang;i <= ende;i++){
			sigma += gops[i];
		}
		double ret = ((double) sigma / ((double) ende - (double) anfang + 1));
		return ret;
	}	
	
	double Hilfsklasse::mittelwert(vector<double> gops,int anfang,int ende){
		double sigma = 0;
		for(int i = anfang;i <= ende;i++){
			sigma += gops[i];
		}
		double ret = ((double) sigma / ((double) ende - (double) anfang + 1));
		return ret;
	}	
	
	double Hilfsklasse::varianz(int* gop,int gop_anz){
		double sigma = 0;
		double mw = Hilfsklasse::mittelwert(gop,gop_anz);
		for(int i = 0;i < gop_anz;i++){
			sigma += pow(mw-gop[i],2);
		}
		double ret = sigma/(gop_anz-1);
		return ret;
	}

	double Hilfsklasse::varianz(double* gop,int gop_anz){
		double sigma = 0;
		double mw = Hilfsklasse::mittelwert(gop,gop_anz);
		for(int i = 0;i < gop_anz;i++){
			sigma += pow(mw-gop[i],2);
		}
		double ret = sigma/(gop_anz-1);
		return ret;
	}

	double Hilfsklasse::varianz(double* gops,int anfang,int ende){
		double sigma = 0;
		double mw = Hilfsklasse::mittelwert(gops,anfang,ende);
		for(int i = anfang;i <= ende;i++){
			sigma += pow(mw-gops[i],2);
		}
		double ret = sigma/(ende-anfang+1);
		return ret;
	}	
	
	double Hilfsklasse::varianz(vector<double> gops,int anfang,int ende){
		double sigma = 0;
		double mw = Hilfsklasse::mittelwert(gops,anfang,ende);
		for(int i = anfang;i <= ende;i++){
			sigma += pow(mw-gops[i],2);
		}
		double ret = sigma/(ende-anfang+1);
		return ret;
	}		
	
	double Hilfsklasse::standardAbweichung(int* gop,int gop_anz){
		double ret;
		ret = sqrt(Hilfsklasse::varianz(gop,gop_anz));
		return ret;
	}

	double Hilfsklasse::standardAbweichung(double* gop,int gop_anz){
		double ret;
		ret = sqrt(Hilfsklasse::varianz(gop,gop_anz));
		return ret;
	}

	double Hilfsklasse::standardAbweichung(int anfang,int ende,double* gops){
		double ret;
		ret = sqrt(Hilfsklasse::varianz(gops,anfang,ende));
		return ret;
	}
	
	double Hilfsklasse::standardAbweichung(int anfang,int ende,vector<double>* gops){
		double ret;
		ret = sqrt(Hilfsklasse::varianz(*gops,anfang,ende));
		return ret;
	}
	
	void Hilfsklasse::zero(rvector &vec){
		for(int i = Lb(vec);i <= Ub(vec);i++){
			vec[i] = 0;
		}
	}

	void Hilfsklasse::zero(rmatrix &mat){
		for(int i = Lb(mat,COL);i <= Ub(mat,COL);i++){
			for(int n = Lb(mat,ROW); n <= Ub(mat,ROW);n++){
				mat[n][i] = 0;
			}
		}
	}

	real Hilfsklasse::fitness(rvector &basis,rvector &vergl){
		real sigma = 0;
		for(int i = 0; i <= Ub(basis);i++){
			sigma += power(basis[i] - vergl[i],2);
		}
		real fitness = 1/sigma;
		return fitness;
	}

	rvector* Hilfsklasse::zustandsfolge(int n,rmatrix umatrix){
		real x = 0.0;
		x = (real)( rand() / RAND_MAX);
		int s = rand()%(Ub(umatrix,2)+1);
		rvector* folge = new rvector(0,n-1);
		(*folge)[0] = s;

		rmatrix cumsum(umatrix);
		
		for(int row = 0;row <= Ub(umatrix,ROW);row++){
			for(int col = 1;col <= Ub(umatrix,COL);col++){
				cumsum[row][col] += cumsum[row][col-1];
			}
		}
		
		rvector tolleranz(0,Ub(umatrix,ROW));
		Hilfsklasse::zero(tolleranz);

		for(int row = 0;row <= Ub(cumsum,ROW);row++){
			if(cumsum[cxsc::Row(row)][Ub(cumsum,COL)] < 1){
				tolleranz[row] = 1-cumsum[cxsc::Row(row)][Ub(cumsum,COL)];
			}
		}
		
		rvector mindestVerteilung(0,Ub(umatrix,ROW));
		Hilfsklasse::fuellen(mindestVerteilung,2);
		mindestVerteilung[(int) cxsc::_double((*folge)[0])] -= 1;
		
		for(int i = 1;i < n;i++){
			x = (double)( rand() / RAND_MAX);
			int index = 0;
			while( (x >= cumsum[(int) cxsc::_double((*folge)[i-1])][index]) && ((cumsum[(int) cxsc::_double((*folge)[i-1])][index] + tolleranz[(int) cxsc::_double((*folge)[i-1])]) != 1) ){
				index++;
			}
			(*folge)[i] = index;
			mindestVerteilung[index] -= 1;
		}
		
		bool check;
		
		if( (((Ub(umatrix,ROW) - Lb(umatrix,ROW))+1) * 2) <= n ){	check = true; }
		else{ check = false; }
		
		while(check){
			check = false;
			for(int i = Lb(mindestVerteilung);i <= Ub(mindestVerteilung);i++){
				if(mindestVerteilung[i] > 0){
					int x = rand()%n;
					mindestVerteilung[(int) cxsc::_double((*folge)[x])] += 1;
					(*folge)[x] = i;
					mindestVerteilung[i] -= 1;
					check = true;
				}
			}
		}
		return folge;
	}

	void Hilfsklasse::fuellen(rvector &vec,int n){
		for(int i = Lb(vec);i <= Ub(vec);i++){
			vec[i] = n;
		}
	}

	void Hilfsklasse::fuellen(rmatrix &mat,int n){
		for(int i = Lb(mat,COL);i <= Ub(mat,COL);i++){
			for(int n = Lb(mat,ROW); n <= Ub(mat,ROW);n++){
				mat[n][i] = n;
			}
		}
	}

	void Hilfsklasse::testeMatrix(rmatrix &umatrix){
		real sum;
		char zeilen[(Ub(umatrix,ROW)-Lb(umatrix,ROW)+1)];
		for(int x=0;x <= Ub(umatrix,ROW);x++){
			sum = 0;
			for(int y=0;y <= Ub(umatrix,COL);y++){
				sum += umatrix[x][y];
			}
			zeilen[x] = (sum == 0) ? '0' : '1';
		}
		for(int i=0;i <= Ub(umatrix,ROW);i++){
			if(zeilen[i] == '0'){
				bool uRand,oRand = false;
				int ziel = -1;
				for(int n=0;n <= i;n++){
					uRand = (zeilen[n] == '1') ? false : true;
					if(!uRand){
						ziel = n;
						break;
					}
				}
				for(int n=Ub(umatrix,ROW);n >= i;n--){
					oRand = (zeilen[n] == '1') ? false : true;
					if(!oRand){ break; }
				}
				
				if(ziel != -1 && !oRand){
					umatrix[Row(i)] = umatrix[Row(ziel)];
					umatrix[Row(ziel)] = 0;
					umatrix[Col(i)] = umatrix[Col(ziel)];
					umatrix[Col(ziel)] = 0;				
					zeilen[i] = '1';
					zeilen[ziel] = '0';
				}
			}
		}
		rmatrix tmp(umatrix);
		int von,nach;
		for(int i=0;i <= Ub(umatrix,ROW);i++){
			if(zeilen[i] == '1'){
				von = i;
				break;
			}
		}
		
		for(int i=Ub(umatrix,ROW);i >= 0;i--){
			if(zeilen[i] == '1'){
				nach = i;
				break;
			}
		}

		cxsc::Resize(umatrix,von,nach,von,nach);
		cxsc::SetLb(umatrix,ROW,0);
		cxsc::SetLb(umatrix,COL,0);
		for(int i=0; i <= (nach-von);i++){
			umatrix[Row(i)] = tmp(von+i,von+i,von,nach);
		}	
	}
	
	rmatrix Hilfsklasse::constructSMP(rvector data, intvector index, int stepCount){
		Trace* _trace = new Trace(data);
		rmatrix* ret = new rmatrix(_trace->discretize(_trace->getDiscretizationPoints(stepCount) , index));
		delete _trace;
		return *ret;
	}
}
