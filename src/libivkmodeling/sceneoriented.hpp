#ifndef SCENEORIENTED_H_
#define SCENEORIENTED_H_

#include<vector>
#include"frames.hpp"
#include<iostream>
#include<fstream>
#include "simplesmp.hpp"
#include "basicio.hpp"
#include "mathe.hpp"


using IvkModeling::SimpleSMP;
using cxsc::rmatrix;
using IvkModeling::BasicIO;

namespace IvkModeling{
	
	class SceneOrientedSMPModel{
		
		public:
			SceneOrientedSMPModel(vector<int>* gops,double threshold,int discretSteps);
			SceneOrientedSMPModel(const char* filename,int gopSize,double threshold,int discretSteps);
			void setGops(vector<int>* gops);
			void setThreshold(double threshold);
			void setFilename(const char* filename);
			void setGopSize(int gopSize);
			void setDiscretSteps(int discretSteps);
		
			int getDiscretSteps();
			vector<int>* getGops();
			double getThreshold();
			const char* getFilename();
			int getGopSize();
			rmatrix getDiscrete();
		
			void compute();
			void exportToXML(const char* filename);
		
		private:
			double threshold;
			const char* filename;
			int gopSize;
			vector<int>* gops;
			int discretSteps;
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
			Frames* gopData;
			/// GoP-Abfolge je Klasse
			vector< vector<double>* >* classData;
			/// Einfache Modellierungs-Objekte je Klasse
			vector< SimpleSMP::SimpleSMP* >* SSMP;
			vector< int >* transitionDataClasses;
			intvector* transitionDataStates;
			/// Liste der nicht verwendeten Klassennummern
			int* classMap;
			/// Liste der nicht verwendeten Zustandsnummern je Klasse
			vector< vector< int >* >* strippedStates;
			/// Szenenwechselprozess-Objekt
			SimpleSMP::SimpleSMP* tSMP;

			void captureSceneLimits();
			void calculateClasses();
			vector<int>* getSceneLimits();
			void computeTransitionSMP(int discretSteps);
			rmatrix* discrete;
	};
}

#endif
