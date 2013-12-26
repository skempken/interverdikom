#ifndef GENETICMODELING_H_
#define GENETICMODELING_H_
#include "genetik.hpp"
#include<fstream>
#include<iostream>

#include <Computation.h>
#include <ProgressListener.h>
#include "basicio.hpp"

using IvkModeling::BasicIO;

namespace IvkModeling{
	/**\class GeneticModeling
	\brief GeneticModeling is used to calculate a genetic SemiMarkovProcess*/
	class GeneticModeling : public ivk::Computation, public ivk::ProgressListener {
		public:
			/**Constructor for the genetic process with a file as basedata
			\param filename The filename where the framesizes are saved
			\param gopSz The size of the groups of pictures
			\param states The number of the states
			\param autok The number of steps the autocorrelation must do
			\param iteration The number of iterations the genetic process must do to determine the fittest
			\param poolSz The number cycles in the pool*/			
			GeneticModeling(char* filename,int gopSz,int states,int autok,int iteration,int poolSz);
			/**Constructor for the genetic process with a vector<int> as basedata
			\param data The vector where the framesizes are saved
			\param gopSz The size of the groups of pictures
			\param states The number of the states
			\param autok The number of steps the autocorrelation must do
			\param iteration The number of iterations the genetic process must do to determine the fittest
			\param poolSz The number cycles in the pool*/			
			GeneticModeling(vector<int>* data,int gopSz,int states,int autok,int iteration,int poolSz);		
			/** Destructor*/
			virtual ~GeneticModeling();
			/**Method to get the filename */
			char* getFilename();
			/**Method to get the size of GoP(group of pictures) */
			int getGopSz();
			/**Method to get the number of states*/
			int getStates();
			/**Method to get the number of autocorrelation steps*/
			int getAutok();
			/**Method to get the number of iterations*/
			int getIter();
			/**Method to get the number of cycles it the pool*/
			int getPoolSz();
			/**Method to set the filename */
			void setFilename(char* filename);
			/**Method to set the size of GoP(group of pictures) */
			void setGopSz(int gopSz);
			/**Method to set the number of states*/
			void setStates(int states);
			/**Method to set the number of autocorrelation steps*/
			void setAutok(int autok);
			/**Method to set the number of iterations*/
			void setIter(int iteration);
			/**Method to set the number of cycles it the pool*/
			void setPoolSz(int poolSz);
			/**Method to compute the genetic process*/
			virtual void compute();
			/**Method to export the result in XML-type*/
			void exportToXML(char* filename);
			/**Method to set the Text for the progessnotifier
			\param text Text to be set*/
			virtual int setTaskText(const string &text);
			/**Method to set the maximum value for the progessnotifier
			\param max Max-value to be set*/
			virtual int setTaskMax(const int &max);
			/**Method to set the value for the progessnotifier
			\param value Value to be set*/			
			virtual int setTaskValue(const int &value);
			/**Method to set the estimated time of arrival
			\param eta ETA in seconds*/
			virtual int setTaskETA(const int &eta);
			/** */
		private:
			/** */
			Genetik::Genetik* model;
			/** */
			char* filename;
			/** */
			int gopSz;
			/** */
			int states;
			/** */
			int autok;
			/** */
			int iteration;
			/** */
			int poolSz;
	};
}
#endif
