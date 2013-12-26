#include "IVKExport.h"

#include <iostream>
#include <fstream>

#include "SSMProcess.h"
#include "imatrix.hpp"

namespace ivk
{

IVKExport::IVKExport()
{
}

IVKExport::~IVKExport()
{
}

void IVKExport::writeToIVKFile(const char* filename, const SSMProcess &arrival, const GIProcess &service)
{
	//TODO: Consider interval probabilities!
	rmatrix umatrix = mid(arrival.getTransitionMatrix());
	rmatrix discrete = mid(arrival.getDistributions());
	rvector s = mid(service.getDistribution());
	
	int zustaende = cxsc::Ub(umatrix,ROW)+1;
	
	fstream toWrite(filename,fstream::out);
	toWrite << "<?xml version=\"1.0\" standalone=\"no\"?>\n<!DOCTYPE SMPQueue PUBLIC \"-//InterVerdiKom Team//SMPQueue//EN\" \"SMPQueue.dtd\">\n";
	toWrite << "<SMPQueue type=\"TimeSlotted\">\n\t<ArrivalProcess>\n\t\t<SSMProcess numStates=\"" << zustaende <<"\">\n";
	
	toWrite << "\t\t\t<SMTransitionMatrix>\n";
	for(int from = 0;from < zustaende;from++){
		for(int to = 0; to < zustaende;to++){
			toWrite << "\t\t\t\t" << "<SMTMatrixValue fromState=\"" << from << "\" toState=\"" << to << "\">" << cxsc::_double(umatrix[from][to]) << "</SMTMatrixValue>\n";
		}
	}
	toWrite << "\t\t\t</SMTransitionMatrix>\n";
	
	for(int m=0;m < zustaende;m++){
		toWrite << "\t\t\t<SMDistribution stateIndex=\""<< m <<"\" steps=\""<< Ub(discrete,COL)+1 <<"\">\n";
		for(int n=0;n <=Ub(discrete,COL);n++){
			toWrite << "\t\t\t\t<SMDistValue step=\""<<n<<"\">"<< cxsc::_double((discrete)[m][n])<<"</SMDistValue>\n";
		}
		toWrite << "\t\t\t</SMDistribution>\n";
	}
	toWrite << "\t\t</SSMProcess>\n\t</ArrivalProcess>\n";
	
	// Service process
	toWrite << "\t<ServiceProcess>\n\t\t<GIProcess>\n";
	toWrite << "\t\t\t<GIDistribution steps=\"" << Ub(s)+1 <<"\" >\n";
	for(int i = 0; i<=Ub(s);++i)
		toWrite << "\t\t\t\t<GIDistValue step=\"" << i << "\" >" << cxsc::_double(s[i]) <<" </GIDistValue>\n";
	toWrite << "\t\t\t</GIDistribution>\n";
	toWrite << "\t\t</GIProcess>\n";
	toWrite << "\t</ServiceProcess>\n";
	toWrite << "</SMPQueue>\n";
	toWrite.close();
}

void IVKExport::intervalPolynomialMatrixExport(const char* filename, const SSMProcess &model){
	imatrix transition(model.getTransitionMatrix());
	imatrix distributions(model.getDistributions());
	
	int dim[3];
	dim[0] =Ub(transition,1)-Lb(transition,1);
	dim[1] =Ub(transition,1)-Lb(transition,1);
	dim[2] =Ub(distributions,2)-Lb(distributions,2);
	
	double outPutMatrix[ dim[0] ][ dim[1] ][ dim[2] ][2];
	
	for(int i = Lb(transition,1) ; i <= Ub(transition,1); i++){
		for(int j = Lb(transition,2) ; j <= Ub(transition,2); j++){
			for(int k = Lb(distributions,2) ; k <= Ub(distributions,2) ; k++){
				outPutMatrix[i][j][k][0] = _double(Inf(transition[i][j] * distributions[i][k]) );
				outPutMatrix[i][j][k][1] = _double(Sup(transition[i][j] * distributions[i][k]) );
			}
		}
	}
	
	fstream toWrite(filename,fstream::out);
	toWrite << dim[0] << endl;
	toWrite << dim[1] << endl;
	toWrite << dim[2] << endl << endl;
	
	for(int i = Lb(transition,1) ; i <= Ub(transition,1); i++){
		for(int j = Lb(transition,2) ; j <= Ub(transition,2); j++){
			for(int k = Lb(distributions,2) ; k <= Ub(distributions,2) ; k++){
				toWrite << outPutMatrix[i][j][k][0] << "\t";
			}
			
			toWrite << endl;
		}
		
		toWrite << endl;
		
		for(int j = Lb(transition,2) ; j <= Ub(transition,2); j++){
			for(int k = Lb(distributions,2) ; k <= Ub(distributions,2) ; k++){
				toWrite << outPutMatrix[i][j][k][1] << "\t";
			}
			
			toWrite << endl;
		}
		
		toWrite << endl << endl;
	}	
	
	toWrite.close();
}

}
