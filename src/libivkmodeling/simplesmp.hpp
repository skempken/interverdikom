#ifndef SIMPLESMP_H_
#define SIMPLESMP_H_

#include <Computation.h>
#include "ssmp.hpp"
#include "intvector.hpp"

namespace IvkModeling{
	class SimpleSMP : public ivk::Computation{
		public:
			/**Constructor for a simple semi markov process
			\param filename specific filename which contains the data that is used for computation process
			\param states the number of states in the process
			\param gopSize the number of single values that will be summed up*/
			SimpleSMP(const char* filename  ,int states, int gopSize);
			/**Constructor for a simple semi markov process
			\param data the data which is used for computation process
			\param states the number of states in the process
			\param gopSize the number of single values that will be summed up*/		
			SimpleSMP(vector<double>* data  ,int states, int gopSize);
			/**Constructor for a simple semi markov process
			\param data the data which is used for computation process
			\param states the number of states in the process
			\param gopSize the number of single values that will be summed up*/		
			SimpleSMP(vector<int>* data     ,int states, int gopSize);
			/**Constructor for a simple semi markov process
			\param data the data which is used for computation process
			\param states the number of states in the process
			\param gopSize the number of single values that will be summed up*/		
			SimpleSMP(cxsc::intvector* data ,int states, int gopSize);
			
			/**Method to set the number of states
			\param m number of states*/
			void setStates(int m);
			/**Method to set the number of single values that will be summed up
			\param size number of values*/
			void setGopSize(int size);
			/**Method to return the lowest value in the dataseries*/
			double getMin();
			/**Method to return the biggest value in the dataseries*/
			double getMax();
			/**Method to get the stateindex of a specific gop
			\param gop the gop that should be controlled*/
			int getState(double gop);
			/**Method to get the number of states*/
			int getStates();
			/**Method to get the group size of the values(GOPs)*/
			int getGopSize();
			/**Method to get the number of gops that the smp model contains*/
			int getGopAnz();
			/**Method to get the gops*/
			double* getGops();
			/**Method to get a calculated transitionMatrix*/
			rmatrix getTransitionMatrix();
			
			/**Method to start the computaion progress*/
			virtual void compute();
		
			/**Method to export the value to a file
			\param filename specific filename the values will be stored at*/
			void exportToXML(const char* filename);
		private:
			SSMP* ssmp;
			int states;
			int gopSize;	
	};
}
#endif
