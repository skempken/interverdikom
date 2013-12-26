#include "mutator.hpp"

namespace IvkModeling{
	Mutator::Mutator(int m,rmatrix& pool){
		this->mut_stat = new rmatrix(0,Ub(pool,ROW),0,4);
		Hilfsklasse::zero(*this->mut_stat);
		this->bereich = new int[2];
		this->m = m;
		this->mut_wahr = new double[5];
		this->mut_wahr[0] = 0.2;
		this->mut_wahr[1] = 0.2;
		this->mut_wahr[2] = 0.2;
		this->mut_wahr[3] = 0.2;
		this->mut_wahr[4] = 0.2;
	}
	Mutator::~Mutator(){}
		
	void Mutator::mutier(rmatrix& pool,int n){
		for(int i = 0;i < 5;i++){
			double x = (double)( rand()/ RAND_MAX);
			if(x >= this->mut_wahr[i]){
				this->benutze_mutator(i,pool,n);
			}
		}
	}

	void Mutator::benutze_mutator(int mut,rmatrix& pool,int n){
		this->berechne_bereich(pool);
		for(int i = this->bereich[0];i <= this->bereich[1];i++){
			(*this->mut_stat)[i][mut] += 1;
		}
		switch(mut){
			case 0:
				this->mut_block(pool,n);
			break;
			case 1:
				this->mut_inverse(pool,n);
			break;
			case 2:
				this->mut_shuffle(pool,n);
			break;
			case 3:
				this->mut_swap(pool,n);
			break;
			case 4:
				this->mut_crossover(pool,n);
			break;
		};
		this->testKorrektur(pool,n);
	}

	void Mutator::testKorrektur(rmatrix& pool,int folge){
		int mindestVerteilung[this->m];
		for(int i=0;i < this->m; i++){
			mindestVerteilung[i] = 2;
		}
		
		for(int i=0;i <= Ub(pool,ROW);i++){
			mindestVerteilung[(int) cxsc::_double(pool[cxsc::Col(folge)][i])] -= 1;
		}
		
		bool fehlerhaft = true;
		while(fehlerhaft){
			fehlerhaft = false;
			for(int i=0;i < this->m; i++){
				if(mindestVerteilung[i] > 0){
					for(int n=0;n < mindestVerteilung[i];n++){
						pool[cxsc::Col(folge)][rand()%Ub(pool,ROW)] = i;
						mindestVerteilung[i] -= 1;
					}
					fehlerhaft = true;
				}
			}
		}
	}
	
	void Mutator::berechne_bereich(rmatrix& pool){ // [0] = untere Grenze / [1] = obere Grenze
		int groesse = (Ub(pool,ROW)-Lb(pool,ROW))+1;
		int t1 = rand()%groesse;
		int t2 = rand()%groesse;
		this->bereich[0] = (t1 < t2) ? t1 : t2; //untere Grenze
		this->bereich[1] = (t1 > t2) ? t1 : t2; //obere Grenze
	}

	void Mutator::mut_block(rmatrix& pool,int n){
		int wert = rand()%this->m;
		for(int i = this->bereich[0];i <= this->bereich[1];i++){
			pool[i][n] = wert;
		}
	}

	void Mutator::mut_inverse(rmatrix& pool,int n){
		rvector tmp(0,cxsc::Ub(pool,ROW));
		tmp = pool[cxsc::Col(n)];
		int x = 0;
		for(int i = this->bereich[0];i<= this->bereich[1];i++){
			pool[cxsc::Col(n)][i] = tmp[this->bereich[1]-x++];
		}
	}

	void Mutator::mut_shuffle(rmatrix& pool,int n){
		rvector tmp(0,this->m-1);
		Hilfsklasse::zero(tmp);
		for(int i = this->bereich[0];i <= this->bereich[1];i++){
			tmp[(int) cxsc::_double(pool[cxsc::Col(n)][i])] += 1;
		}
		for(int i = this->bereich[0];i <= this->bereich[1];i++){
			int x = -1;
			while( true ){
				x = rand()%this->m;
				if(x != -1){
					if(tmp[x] != 0){
						break;
					}
				}
			}
			pool[cxsc::Col(n)][i] = x;
			tmp[x] -= 1;
		}
	}

	void Mutator::mut_swap(rmatrix& pool,int n){
		cxsc::real tmp = pool[cxsc::Col(n)][this->bereich[0]];
		pool[cxsc::Col(n)][this->bereich[0]] = pool[cxsc::Col(n)][this->bereich[1]];
		pool[cxsc::Col(n)][this->bereich[1]] = tmp;
	}

	void Mutator::mut_crossover(rmatrix& pool,int n){
		int x = (n != 0) ? n-1 : n+1;
		rvector tmp(0,Ub(pool,ROW));
		tmp = pool[cxsc::Col(x)];
		for(int i = this->bereich[0];i <= this->bereich[1];i++){
			pool[cxsc::Col(n)][i] = tmp[i];
		}
	}
}
