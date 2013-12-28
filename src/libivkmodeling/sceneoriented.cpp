#include "sceneoriented.hpp"
#include "mathe.hpp"
#include <math.h>

using IvkModeling::Hilfsklasse;
using IvkModeling::Hilfsklasse;

namespace IvkModeling{
	SceneOrientedSMPModel::SceneOrientedSMPModel(vector<int>* gops,double threshold,int discretSteps){}
		
	SceneOrientedSMPModel::SceneOrientedSMPModel(const char* filename,int gopSize,double threshold, int discretSteps){
		this->gopData = new Frames();
		this->setThreshold(threshold);
		this->setFilename(filename);
		this->setGopSize(gopSize);
		this->setDiscretSteps(discretSteps);
		

		vector<double>* tmp;
		tmp = BasicIO::importFromFile(filename);
		
		for(unsigned int i=0; i < tmp->size();i++){
			this->gopData->inhalt->push_back((*tmp)[i]);
		}
		
		this->gopData->frames_zu_gop(gopSize);
	}

	void SceneOrientedSMPModel::setGops(vector<int>* gops){			this->gops = gops; }
	void SceneOrientedSMPModel::setThreshold(double threshold){		this->threshold = threshold; }
	void SceneOrientedSMPModel::setFilename(const char* filename){ this->filename = filename; }
	void SceneOrientedSMPModel::setGopSize(int gopSize){				this->gopSize = gopSize; }
	void SceneOrientedSMPModel::setDiscretSteps(int discretSteps){	this->discretSteps = discretSteps; }
	
	int SceneOrientedSMPModel::getDiscretSteps()		{ return this->discretSteps; }
	vector<int>* SceneOrientedSMPModel::getGops()	{ return this->gops; }
	double SceneOrientedSMPModel::getThreshold()		{ return this->threshold; }
	const char* SceneOrientedSMPModel::getFilename(){ return this->filename; }
	int SceneOrientedSMPModel::getGopSize()			{ return this->gopSize; }
	rmatrix SceneOrientedSMPModel::getDiscrete()		{ return (*this->discrete); }
	
	void SceneOrientedSMPModel::captureSceneLimits(){
		this->sceneLimits = new vector<int>;
		this->sceneLimits->push_back(0);
		vector<double>* vk = new vector<double>;
		for(int i = 0;i < this->gopData->gop_anz;i++){
			vk->push_back(Hilfsklasse::standardAbweichung(this->sceneLimits->back(),i,this->gopData->gop) / Hilfsklasse::mittelwert(this->gopData->gop,this->sceneLimits->back(),i));
			int last = this->sceneLimits->back();
			if( (i-last) >= 1 ){
				if(((i-last+1) * abs((*vk)[i] - (*vk)[i-1])) > this->threshold){
					this->sceneLimits->push_back(i);
					(*vk)[i] = (Hilfsklasse::standardAbweichung(this->sceneLimits->back(),i,this->gopData->gop) / Hilfsklasse::mittelwert(this->gopData->gop,this->sceneLimits->back(),i));
				}
			}
		}
	}
	
	void SceneOrientedSMPModel::calculateClasses(){
		this->means = new vector<double>;
		double min = 0;
		double max = 0;
		
		for(unsigned int i = 0; i < this->sceneLimits->size();i++){
			int next = (i != this->sceneLimits->size()-1) ? (*this->sceneLimits)[i+1]-1 : this->gopData->gop_anz-1;
			
			this->means->push_back(Hilfsklasse::mittelwert(this->gopData->gop,(*this->sceneLimits)[i],next));
			min = ((*this->means)[i] < min || min == 0) ? (*this->means)[i] : min;
			max = ((*this->means)[i] > max) ? (*this->means)[i] : max;
		}
		this->numClasses = (int) floor((max - min) / Hilfsklasse::standardAbweichung(0,this->gopData->gop_anz-1,this->gopData->gop));
		double step = ((double)max - (double)min) / this->numClasses;
		
		this->classes = new vector< vector<int> >(this->numClasses);
		
		for(unsigned int i = 0; i < this->means->size();i++){
			if((*this->means)[i] != max){
				(*this->classes)[(int) floor(((*this->means)[i] - (double)min) / step)].push_back(i);
			}
			else{
				(*this->classes)[(int) floor(((*this->means)[i] - (double)min) / step)-1].push_back(i);
			}
		}
	}
	
	void SceneOrientedSMPModel::computeTransitionSMP(int discretSteps){
		int menge = 0;
		for(unsigned int i = 0;i < this->classes->size(); i++){
			if((*this->classes)[i].size() != 0){ menge += 1; }
		}
		
		this->SSMP = new vector< SimpleSMP::SimpleSMP* >;
		this->classData = new vector< vector <double>* >(menge);
		
		this->transitionDataClasses = new vector< int >(this->gopData->gop_anz);
		this->numStates = new int[this->numClasses];
		this->classMap = new int[this->numClasses];
		unsigned int count = 0;
		
		/*creating vectors containing:
			-simpleSMP-models for each class (this->SSMP)
			-a map that compensates the empty classes(this->classMap)
			-the specific class for each datapoint(this->transitionDataClasses)*/
		
		for(unsigned int i = 0;i < this->classes->size(); i++){
			
			if((*this->classes)[i].size() != 0){
				this->classMap[i] = i-count;
				(*this->classData)[this->classMap[i]] = new vector<double>;
				
				for(unsigned int n = 0; n < (*this->classes)[i].size(); n++){
					int ende = ((unsigned int) (*this->classes)[i][n] != this->sceneLimits->size()-1) ? ((int) (*this->sceneLimits)[((int) (*this->classes)[i][n])+1]) -1 : this->gopData->gop_anz-1;;
					for(int x = (*this->sceneLimits)[(*this->classes)[i][n]]; x <= ende; x++){
						(*this->classData)[this->classMap[i]]->push_back((double)this->gopData->gop[x]);
						(*this->transitionDataClasses)[x] = i;
					}
				}
				
				double max = 0;
				double min = 0;
				
				for(unsigned int n = 0; n < (*this->classData)[this->classMap[i]]->size();n++){
					min = (n == 0 || min > (*(*this->classData)[this->classMap[i]])[n]) ? (*(*this->classData)[this->classMap[i]])[n] : min;
					max = (max < (*(*this->classData)[this->classMap[i]])[n]) ? (*(*this->classData)[this->classMap[i]])[n] : max;
				}
				
				this->numStates[i] = (int) floor((max - min) /	Hilfsklasse::standardAbweichung(0,(*this->classData)[this->classMap[i]]->size() -1,(*this->classData)[this->classMap[i]]));
				this->SSMP->push_back(new SimpleSMP::SimpleSMP((*this->classData)[this->classMap[i]],this->numStates[i],1));
				
				this->SSMP->back()->compute();
				cout << "c(" << i<<") s("<< this->numStates[i] << ")"<<this->SSMP->back()->getMin() << " -> " << this->SSMP->back()->getMax()<<endl;
				
			}
			else{
				this->numStates[i] = 0;
				this->classMap[i] = -1;
				count++;
			}
		}
		
		/*creating vector containing states without values*/
		this->strippedStates = new vector< vector <int>* >(this->classes->size());
		
		for(unsigned int i=0; i < this->classes->size();i++){
			(*this->strippedStates)[i] = new vector<int>;
			
			if(this->classMap[i] != -1){
				rmatrix* tmp = new rmatrix((*this->SSMP)[this->classMap[i]]->getTransitionMatrix());
				
				for(int n=0;n < this->numStates[i];n++){
					real sum=0;
					for(int x=0;x < this->numStates[i];x++){
						sum += (*tmp)[cxsc::Row(n)][x];
					}
					if(((int) cxsc::_double(sum)) != 1){ (*this->strippedStates)[this->classMap[i]]->push_back(n); }
				}
				
				delete tmp;
			}
		}
		
		/*creating intvector containing states for each datapoint*/
		this->transitionDataStates = new intvector(0,this->gopData->gop_anz-1);
		
		for(int i=0; i < this->gopData->gop_anz;i++){
			int stateBuff=0;
			for(int n=0;n < (*this->transitionDataClasses)[i];n++){
				stateBuff += this->numStates[n]-(*this->strippedStates)[n]->size();
			}
			
			(*this->transitionDataStates)[i] = (stateBuff+ (*this->SSMP)[this->classMap[(*this->transitionDataClasses)[i]]]->getState(this->gopData->gop[i]));
		}
		
		/*counting number of states in the transitionSMP*/
		int tStates=0;
		for(unsigned int i=0;i < this->classes->size();i++){
			tStates += this->numStates[i] - (*this->strippedStates)[i]->size();
		}
		
		this->tSMP = new SimpleSMP::SimpleSMP(this->transitionDataStates,tStates,1);
		this->tSMP->compute();
		
		//~ /*converting rawData (Frames->vector<int>) to rvector datatype*/
		rvector data(0,this->gopData->gop_anz-1);
		for(int i=0; i < this->gopData->gop_anz; i++){
			data[i] = this->gopData->gop[i];
		}
			
		this->discrete = new rmatrix(Hilfsklasse::constructSMP(data,*this->transitionDataStates,this->getDiscretSteps()));
	}
	
	vector<int>* SceneOrientedSMPModel::getSceneLimits(){
		return this->sceneLimits;
	}
	
	void SceneOrientedSMPModel::exportToXML(const char* filename){
		BasicIO::exportToFile(filename,this->tSMP->getTransitionMatrix(),(*this->discrete));
	}
	
	void SceneOrientedSMPModel::compute(){
		this->captureSceneLimits();
		this->calculateClasses();
		this->computeTransitionSMP(this->getDiscretSteps());
	}
}
