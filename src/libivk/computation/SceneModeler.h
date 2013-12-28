#ifndef SCENEORIENTED_H_
#define SCENEORIENTED_H_

#include "AbstractDiscreteSSMPModeler.h"
#include <vector>
#include "utility/RMatrixUtils.h"

namespace ivk{
	
	class SceneModeler: public AbstractDiscreteSSMPModeler{
		
		public:
			static const char* PARAM_EPSILON;
			SceneModeler(const Trace* ptrData,const ComputationParameters &parameters);
			~SceneModeler();
			void setThreshold(real value);
			real getThreshold() const;
		
			void setParameters(ComputationParameters parameters);
			SSMProcess* compute();
		
		private:
			real threshold;
			/// Vektor der Szenenstart-GoP-Indizes
			vector<int>* sceneLimits;
			/// Vektor der Szenenmittelwerte
			vector<double>* means;
			/// Anzahl der Klassen
			int numClasses;
			/// Anzahl der Zustaende je Klasse
			int* numStates;
			/// Vektor der Szenennummer je Klasse
			vector< vector<int> >* classes;
			/// GoP-Abfolge je Klasse
			vector< vector<double>* >* classData;
			/// 2 dim vector der die oberen Randpunkte der Zustaende je Klasse enthaelt
			vector< Trace* >* classTraces;
			vector< int >* transitionDataClasses;
			intvector* transitionDataStates;
			/// Liste der nicht verwendeten Klassennummern
			int* classMap;
			/// Liste der nicht verwendeten Zustandsnummern je Klasse
			vector< vector< int >* >* strippedStates;
			/// Szenenwechselprozess-Objekt
			int getStateFromTrace(Trace &_data,real value);
			
			void captureSceneLimits();
			void calculateClasses();
			void computeIndexSequence();
	};
}

#endif
