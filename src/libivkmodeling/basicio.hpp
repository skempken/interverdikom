#ifndef BASICIO_H_
#define BASICIO_H_

#include<vector>
#include<iostream>
#include<fstream>
#include<rmatrix.hpp>


using cxsc::rmatrix;
using std::fstream;
using std::ifstream;

namespace IvkModeling{
	
	class BasicIO{
		
		public:
			/**Method to read data from file
			\param filename specific filename that contains data*/
			static std::vector< double >* importFromFile(const char* filename);
			/**Method to export transitionMatrix in XML-style to file
			\param filename specific filename of destinationfile
			\param umatrix transitionMatrix that is used to be stored*/
			static void exportToFile(const char* filename,rmatrix umatrix);	
			/**Method to export transitionMatrix and discretizationData in XML-style to file
			\param filename specific filename of destinationfile
			\param umatrix transitionMatrix that is used to be stored
			\param discrete discretizationData that is used to be stored*/
			static void exportToFile(const char* filename,rmatrix umatrix, rmatrix discrete);
			
		private:
			BasicIO();
			~BasicIO();
	};
}

#endif
