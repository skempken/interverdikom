#include "basicio.hpp"

namespace IvkModeling{
	BasicIO::BasicIO(){}
		
	std::vector<double>* BasicIO::importFromFile(const char* filename){
		std::vector<double>* inhalt = new std::vector<double>;
		char tmp[20];
		char tmpstr[20]="";

		ifstream* dateiobjekt = new ifstream(filename);
		
		while(dateiobjekt->getline(tmp,20)){
			for(int i = 0;i<=20;i++){
				if( !isdigit(tmp[i]) ) { 
					strncat(tmpstr,tmp,i);
					break;
				}
			}
			inhalt->push_back(atoi(tmpstr));
			
			strcpy(tmpstr,"");
		}
		
		dateiobjekt->close();
		delete dateiobjekt;
		return inhalt;
	}
	
	void BasicIO::exportToFile(const char* filename,rmatrix umatrix){
		int zustaende = cxsc::Ub(umatrix,ROW)+1;
		fstream toWrite(filename,fstream::out);
		toWrite << "<?xml version=\"1.0\" standalone=\"no\"?>\n<!DOCTYPE SMPQueue PUBLIC \"-//InterVerdiKom Team//SMPQueue//EN\" \"SMPQueue.dtd\">\n";
		toWrite << "<SMPQueue type=\"TimeSlotted\">\n\t<ArrivalProcess>\n\t\t<SMProcess numStates=\"" << zustaende <<"\">\n";
		
		toWrite << "\t\t\t<SMTransitionMatrix>\n";
		for(int from = 0;from < zustaende;from++){
			for(int to = 0; to < zustaende;to++){
				toWrite << "\t\t\t\t" << "<SMTMatrixValue fromState=\"" << from << "\" toState=\"" << to << "\">" << cxsc::_double(umatrix[from][to]) << "</SMTMatrixValue>\n";
			}
		}
		toWrite << "\t\t\t</SMTransitionMatrix>\n";
		toWrite << "\t\t</SMProcess>\n\t</ArrivalProcess>\n</SMPQueue>\n";
		toWrite.close();
	}
	
	void BasicIO::exportToFile(const char* filename,rmatrix umatrix,rmatrix discrete){
		int zustaende = cxsc::Ub(umatrix,ROW)+1;
		fstream toWrite(filename,fstream::out);
		toWrite << "<?xml version=\"1.0\" standalone=\"no\"?>\n<!DOCTYPE SMPQueue PUBLIC \"-//InterVerdiKom Team//SMPQueue//EN\" \"SMPQueue.dtd\">\n";
		toWrite << "<SMPQueue type=\"TimeSlotted\">\n\t<ArrivalProcess>\n\t\t<SMProcess numStates=\"" << zustaende <<"\">\n";
		
		toWrite << "\t\t\t<SMTransitionMatrix>\n";
		for(int from = 0;from < zustaende;from++){
			for(int to = 0; to < zustaende;to++){
				toWrite << "\t\t\t\t" << "<SMTMatrixValue fromState=\"" << from << "\" toState=\"" << to << "\">" << cxsc::_double(umatrix[from][to]) << "</SMTMatrixValue>\n";
			}
		}
		toWrite << "\t\t\t</SMTransitionMatrix>\n";
		
		for(int m=0;m <= Ub(discrete,ROW);m++){
			toWrite << "\t\t\t<SMDistribution stateIndex=\""<< m <<"\" steps=\""<< Ub(discrete,COL)+1 <<"\">\n";
			for(int n=0;n <= Ub(discrete,COL);n++){
				toWrite << "\t\t\t\t<SMDistValue step=\""<<n<<"\">"<< discrete[m][n]<<"</SMDistValue>\n";
			}
			toWrite << "\t\t\t</SMDistribution>\n";
		}
		toWrite << "\t\t</SMProcess>\n\t</ArrivalProcess>\n</SMPQueue>\n";
		toWrite.close();
	}		
}
