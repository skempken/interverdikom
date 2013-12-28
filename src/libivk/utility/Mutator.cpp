#include "Mutator.h"

namespace ivk{
	Mutator::Mutator(int m){
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
		
	void Mutator::mutier(int n,vector<intvector>& pool){
		double sum = this->mut_wahr[0];
		double x = (double) rand()/ (double) RAND_MAX;
		
		for(int i = 0 ; i < 5 ;i++ ){			
			if(x <= sum){ this->benutze_mutator(i,n,pool); }
			else{ sum += this->mut_wahr[i+1]; }
		}
	}

	void Mutator::benutze_mutator(int mut,int n,vector<intvector>& pool){
		this->berechne_bereich(pool);
		switch(mut){
			case 0:
				this->mut_block(n, pool);
			break;
			case 1:
				this->mut_inverse(n, pool);
			break;
			case 2:
				this->mut_shuffle(n, pool);
			break;
			case 3:
				this->mut_swap(n, pool);
			break;
			case 4:
				this->mut_crossover(n, pool);
			break;
		};
	}

	void Mutator::berechne_bereich(vector<intvector>& pool){ // [0] = untere Grenze / [1] = obere Grenze
		int t1 = rand()%pool.size();
		int t2 = rand()%pool.size();
		this->bereich[0] = (t1 < t2) ? t1 : t2; //untere Grenze
		this->bereich[1] = (t1 > t2) ? t1 : t2; //obere Grenze
	}

	void Mutator::mut_block(int n,vector<intvector>& pool){
		int wert = rand()%this->m;
		for(int i = this->bereich[0];i <= this->bereich[1];i++){
			pool[n][i] = wert;
		}
	}

	void Mutator::mut_inverse(int n,vector<intvector>& pool){
		intvector tmp(pool[n]);
		int x = 0;
		for(int i = this->bereich[0];i<= this->bereich[1];i++){
			pool[n][i] = tmp[this->bereich[1]-x++];
		}
	}

	void Mutator::mut_shuffle(int n,vector<intvector>& pool){
		rvector tmp(0,this->m-1);
		
		for(int i = this->bereich[0];i <= this->bereich[1];i++){
			tmp[pool[n][i]] += 1;
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
			pool[n][i] = x;
			tmp[x] -= 1;
		}
	}

	void Mutator::mut_swap(int n,vector<intvector>& pool){
		int tmp = pool[n][this->bereich[0]];
		pool[n][this->bereich[0]] = pool[n][this->bereich[1]];
		pool[n][this->bereich[1]] = tmp;
	}

	void Mutator::mut_crossover(int n,vector<intvector>& pool){
		int x = (n != 0) ? n-1 : n+1;
		intvector tmp(pool[x]);
		for(int i = this->bereich[0];i <= this->bereich[1];i++){
			pool[n][i] = tmp[i];
		}
	}
}
