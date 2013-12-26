#include "geneticmodeling.hpp"
namespace IvkModeling{
	GeneticModeling::GeneticModeling(char* filename,int gopSz,int states,int autok,int iteration,int poolSz){
		this->model = new Genetik::Genetik(filename,gopSz,states,autok,iteration,poolSz);	
	}
	
	GeneticModeling::GeneticModeling(vector<int>* data,int gopSz,int states,int autok,int iteration,int poolSz){
		this->model = new Genetik::Genetik(filename,gopSz,states,autok,iteration,poolSz);	
	}
	
	GeneticModeling::~GeneticModeling(){
		delete this->model;
	}
		
	char* GeneticModeling::getFilename(){	 	return this->filename; }
	int GeneticModeling::getGopSz(){ 			return this->gopSz; }	
	int GeneticModeling::getStates(){	 		return this->states; }
	int GeneticModeling::getAutok(){				return this->autok; }
	int GeneticModeling::getIter(){				return this->iteration; }
	int GeneticModeling::getPoolSz(){			return this->poolSz; }

	void GeneticModeling::setFilename(char* filename){ 	this->filename = filename; }
	void GeneticModeling::setGopSz(int gopSz){ 				this->gopSz = gopSz; }
	void GeneticModeling::setStates(int states){			 	this->states = states; }
	void GeneticModeling::setAutok(int autok){				this->autok = autok; }
	void GeneticModeling::setIter(int iteration){			this->iteration = iteration; }
	void GeneticModeling::setPoolSz(int poolSz){				this->poolSz = poolSz; }

	void GeneticModeling::compute(){
		this->model->addProgressListener(this);
		cout << "### Evolution("<< this->model->getIter() <<") wird gestartet" << endl;
		this->model->evolutionStarten();
		cout <<endl<< "### Evolution beendet" << endl;
		
	}
	void GeneticModeling::exportToXML(char* filename){
		rmatrix bestMatrix(this->model->getBesteUmatrix());
		BasicIO::exportToFile(filename, bestMatrix);
	}
	
	int GeneticModeling::setTaskText(const string &text){
		return setProgressText(text);
	}
	int GeneticModeling::setTaskMax(const int &max){
		return setProgressMax(max);
	}
	int GeneticModeling::setTaskValue(const int &value){
		return setProgressValue(value);
	}	
	int GeneticModeling::setTaskETA(const int &value){
		return setProgressETA(value);
	}	
}
