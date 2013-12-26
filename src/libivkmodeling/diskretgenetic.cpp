#include "diskretgenetic.hpp"
#include "frames.hpp"

using namespace std;

namespace IvkModeling{
	namespace Gen{
		
		Diskretisierung::Diskretisierung(){}		
		Diskretisierung::~Diskretisierung(){}
		
		rmatrix Diskretisierung::diskretisieren(rmatrix pool,int folge, int schritte,double gop[],int m,double min, double max){
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
			
			rmatrix* disk = new rmatrix(0,m-1,0,anzahl-1);
			
			int* werte_verteilung = new int[m];
			for(int i = 0;i < m;i++){
				werte_verteilung[i] = 0;
			}
			
			for(int i = 0;i <= cxsc::Ub(pool,ROW);i++){
				werte_verteilung[(int) cxsc::_double(pool[cxsc::Col(folge)][i])] += 1;
			}
			
			for(int i = 0;i < m;i++){
				int k = werte_verteilung[i];
				for(int n = 0;n < anzahl;n++){
					(*disk)[i][n] = 0;
				}
				for(int n = 0;n <= cxsc::Ub(pool,ROW);n++){
					if(((int) cxsc::_double(pool[cxsc::Col(folge)][n])) == i){
						s_k = (double) gop[n];
						for(int c = 0;c < anzahl;c++){
							double tmp = delta;
							if(c >= anzahl-2){ delta = s_l[anzahl-1] - s_l[anzahl-2]; }
							if(fabs(s_k-s_l[c]) <= delta){
								(*disk)[i][c] += (delta-fabs(s_k-s_l[c])) / ((double) k*delta);
							}
							delta = tmp;
						}
					}
				}
			}
			
			delete werte_verteilung;
			return *disk;
		}
		
		rmatrix Diskretisierung::diskretisieren(SimpleSMP* model){
			int anzahl = (int) ceil((double) (model->getMax() - model->getMin())/(double) model->getDiscreteSteps());
			anzahl++;
			double s_l[anzahl];
			s_l[0] = model->getMin();
			for(int i = 1;i < anzahl-1;i++){
				s_l[i] = s_l[i-1]+model->getDiscreteSteps();
			}
			s_l[anzahl-1] = model->getMax();
			
			double s_k;
			double delta = model->getDiscreteSteps();
			
			rmatrix* disk = new rmatrix(0,model->getStates()-1,0,anzahl-1);
			
			int* werte_verteilung = new int[model->getStates()];
			for(int i = 0;i < model->getStates();i++){
				werte_verteilung[i] = 0;
			}
			
			double* gops;
			gops = model->getGops();
			
			for(int i = 0;i <= model->getGopAnz();i++){
				werte_verteilung[model->getState(gops[i])] += 1;
			}
			
			for(int i = 0;i < model->getStates();i++){
				int k = werte_verteilung[i];
				for(int n = 0;n < anzahl;n++){
					(*disk)[i][n] = 0;
				}
				for(int n = 0;n <= model->getGopAnz();n++){
					if((model->getState(gops[n])) == i){
						s_k = gops[n];
						for(int c = 0;c < anzahl;c++){
							double tmp = delta;
							if(c >= anzahl-2){ delta = s_l[anzahl-1] - s_l[anzahl-2]; }
							if(fabs(s_k-s_l[c]) <= delta){
								(*disk)[i][c] += (delta-fabs(s_k-s_l[c])) / ((double) k*delta);
							}
							delta = tmp;
						}
					}
				}
			}
			
			delete werte_verteilung;
			return *disk;
		}		
	}
}
