#include "SceneModeler.h"
#include "utility/Logging.hpp"

namespace ivk{

	const char* SceneModeler::PARAM_EPSILON = "epsilon";
	
	SceneModeler::SceneModeler(const Trace* ptrData,const ComputationParameters &parameters)
	: AbstractDiscreteSSMPModeler(ptrData, parameters){
		this->sceneLimits = 0;
		this->means = 0;
		this->numStates = 0;
		this->classes = 0;
		this->classData = 0;
		this->classTraces = 0;
		this->transitionDataClasses = 0;
		this->transitionDataStates = 0;
		this->classMap = 0;
		this->strippedStates = 0;
		this->setParameters(parameters);
	}
	
	SceneModeler::~SceneModeler(){
		if(this->sceneLimits) 				{ delete this->sceneLimits ; }
		if(this->means) 						{ delete this->means ; }
		if(this->numStates) 					{ delete this->numStates ; }
		if(this->classes) 					{ delete this->classes ; }
		if(this->classData) 					{ delete this->classData ; }
		if(this->classTraces) 				{ delete this->classTraces ; }
		if(this->transitionDataClasses) 	{ delete this->transitionDataClasses ; }
		if(this->transitionDataStates) 	{ delete this->transitionDataStates ; }
		if(this->classMap) 					{ delete this->classMap ; }
		if(this->strippedStates) 			{ delete this->strippedStates; }
	}
	
	void SceneModeler::setThreshold(real value){ this->threshold = value; }
	real SceneModeler::getThreshold() const { return this->threshold;	}
	
	int SceneModeler::getStateFromTrace(Trace &_data,real value){
		if(_data.getMinimum() == value) { return 0; }
		
		real range = _data.getMaximum() - _data.getMinimum();
		int num = (int) floor(_double(range) / _double(_data.getStandardDeviation()));
		real stepSize = range / num;
		
		return (int) _double(( value - _data.getMinimum() ) / stepSize);
	}
	
	void SceneModeler::setParameters(ComputationParameters parameters){
		AbstractDiscreteSSMPModeler::setParameters(parameters);
		this->setThreshold(parameters.getReal(PARAM_EPSILON));
	}
	
	void SceneModeler::captureSceneLimits(){
		this->sceneLimits = new vector<int>;
		this->sceneLimits->push_back(0);
		vector<real> vk;
		
		rvector trace = m_ptrData->getTrace();
		SetLb(trace,0);
		
		setProgressText("caputre scenelimits");
		for(int i = 0;i <= Ub(trace);i++){
			
			vk.push_back(this->m_ptrData->getVariationCoefficientSlice(this->sceneLimits->back(),i));
			int last = this->sceneLimits->back();
			if( (i-last) >= 1 ){
				if(((i-last+1) * abs(vk[i] - vk[i-1])) > this->threshold){
					this->sceneLimits->push_back(i);
					vk[i] = this->m_ptrData->getVariationCoefficientSlice(this->sceneLimits->back(),i);
				}
			}
			setProgressValue( 1+ (int)( (double) (25.0 / Ub(trace) )) * i );
		}
	}
	
	void SceneModeler::calculateClasses(){
		setProgressText("calculate classes");
		
		this->means = new vector<double>;
		double min = 0;
		double max = 0;
		
		for(unsigned int i = 0; i < this->sceneLimits->size();i++){
			int next = (i != this->sceneLimits->size()-1) ? (*this->sceneLimits)[i+1]-1 : Ub(this->m_ptrData->getTrace());
			
			this->means->push_back(_double(this->m_ptrData->getMeanSlice((*this->sceneLimits)[i],next)));
			min = ((*this->means)[i] < min || min == 0) ? (*this->means)[i] : min;
			max = ((*this->means)[i] > max) ? (*this->means)[i] : max;
			setProgressValue(26 + (int)( (double)( 10.0 / this->sceneLimits->size()) * i));
		}
		this->numClasses = (int) floor((max - min) / _double(this->m_ptrData->getStandardDeviation()));
		double step = ((double)max - (double)min) / this->numClasses;
		
		this->classes = new vector< vector<int> >(this->numClasses);
		
		for(unsigned int i = 0; i < this->means->size();i++){
			if((*this->means)[i] != max){
				(*this->classes)[(int) floor(((*this->means)[i] - (double)min) / step)].push_back(i);
			}
			else{
				(*this->classes)[(int) floor(((*this->means)[i] - (double)min) / step)-1].push_back(i);
			}
			setProgressValue(36 + (int)( (double) ( 15.0 / this->means->size()) * i));
		}
	}
	
	void SceneModeler::computeIndexSequence(){
		setProgressText("compute index sequence");
		rvector rawData(m_ptrData->getTrace());
		int menge = 0;
		for(unsigned int i = 0;i < this->classes->size(); i++){
			if((*this->classes)[i].size() != 0){ menge += 1; }
		}
		
		this->classTraces = new vector< Trace* >;
		this->classData = new vector< vector <double>* >(menge);
		
		this->transitionDataClasses = new vector< int >(Ub(this->m_ptrData->getTrace())+1);
		this->numStates = new int[this->numClasses];
		this->classMap = new int[this->numClasses];
		unsigned int count = 0;
		
		/*creating vectors containing:
			-a map that compensates the empty classes(this->classMap)
			-the specific class for each datapoint(this->transitionDataClasses)*/
		
		for(unsigned int i = 0;i < this->classes->size(); i++){
			
			if((*this->classes)[i].size() != 0){
				this->classMap[i] = i-count;
				(*this->classData)[this->classMap[i]] = new vector<double>;
				
				for(unsigned int n = 0; n < (*this->classes)[i].size(); n++){
					int ende = ((unsigned int) (*this->classes)[i][n] != this->sceneLimits->size()-1) ? ((int) (*this->sceneLimits)[((int) (*this->classes)[i][n])+1]) -1 : Ub(this->m_ptrData->getTrace());;
					for(int x = (*this->sceneLimits)[(*this->classes)[i][n]]; x <= ende; x++){
						(*this->classData)[this->classMap[i]]->push_back(_double(rawData[x]));
						(*this->transitionDataClasses)[x] = i;
					}
				}
				
				double max = 0;
				double min = 0;
				
				for(unsigned int n = 0; n < (*this->classData)[this->classMap[i]]->size();n++){
					min = (n == 0 || min > (*(*this->classData)[this->classMap[i]])[n]) ? (*(*this->classData)[this->classMap[i]])[n] : min;
					max = (max < (*(*this->classData)[this->classMap[i]])[n]) ? (*(*this->classData)[this->classMap[i]])[n] : max;
				}
				
				rvector dump(0,(*this->classData)[this->classMap[i]]->size()-1);
				for(unsigned int n=0;n< (*this->classData)[this->classMap[i]]->size();n++){
					dump[n] = (*(*this->classData)[this->classMap[i]])[n];
				}
				this->classTraces->push_back(new Trace(dump));
				
				if( _double(this->classTraces->back()->getStandardDeviation()) == 0 ){
					this->numStates[i] = 1;
				}
				else{
					this->numStates[i] = (int) floor((max - min) /	_double(this->classTraces->back()->getStandardDeviation()));
				}
					
				
			}
			else{
				this->numStates[i] = 0;
				this->classMap[i] = -1;
				count++;
			}
			setProgressValue(41+ (int)( (double) (20.0 / this->classes->size()) * i));
		}
		
		/*creating vector containing empty states*/
		this->strippedStates = new vector< vector <int>* >(this->classes->size());
		
		for(unsigned int i=0; i < this->classes->size();i++){
			(*this->strippedStates)[i] = new vector<int>;
			
			if(this->classMap[i] != -1){
				intvector intvec(0,Ub((*this->classTraces)[this->classMap[i]]->getTrace()));
				
				for(int c=0;c <= Ub(intvec);c++){
					intvec[c] = this->getStateFromTrace((*(*this->classTraces)[this->classMap[i]]),(*this->classTraces)[this->classMap[i]]->getTrace()[c]);
				}
				
				rmatrix* tmp = new rmatrix(AbstractDiscreteSSMPModeler::computeTransition(intvec));
				
				for(int n=0;n < this->numStates[i];n++){
					real sum=0;
					for(int x=0;x < this->numStates[i];x++){
						sum += (*tmp)[cxsc::Row(n)][x];
					}
					if(((int) cxsc::_double(sum)) != 1){ (*this->strippedStates)[this->classMap[i]]->push_back(n); }
				}
				
				delete tmp;
			}
			setProgressValue(61 + (int)( (double) (20.0 / this->classes->size()) * i));
		}
		
		/*creating intvector containing states for each datapoint*/
		this->transitionDataStates = new intvector(0,Ub(m_ptrData->getTrace()));
		
		for(int i=0; i <= Ub(m_ptrData->getTrace());i++){
			int stateBuff=0;
			for(int n=0;n < (*this->transitionDataClasses)[i];n++){
				stateBuff += this->numStates[n]-(*this->strippedStates)[n]->size();
			}
			
			(*this->transitionDataStates)[i] = (stateBuff+ this->getStateFromTrace( ((*(*this->classTraces)[this->classMap[(*this->transitionDataClasses)[i]]])) , m_ptrData->getTrace()[i] ) );
			setProgressValue(81 + (int)( (double) ( 15.0 / Ub( m_ptrData->getTrace() )) * i));
		}
	}
	
	SSMProcess* SceneModeler::compute(){
		setProgressText("starting computation");
		setProgressMax(100);
		setProgressValue(1);
		this->captureSceneLimits();
		this->calculateClasses();
		this->computeIndexSequence();
		for(int i = Lb(*this->transitionDataStates); i <= Ub(*this->transitionDataStates); i++){
			(*this->transitionDataStates)[i] += 1;
		}
		
		intvector rv(Lb(*this->transitionDataStates) , Ub(*this->transitionDataStates) );
		for(int i = Lb(rv) ; i <= Ub(rv) ; i++){
			rv[i] = (*this->transitionDataStates)[i];
		}
		setProgressText("creating model");
		return modelFromIndexSequence(rv);
	}
}
