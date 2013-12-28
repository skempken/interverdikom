#include "sceneoriented.hpp"
#include "geneticmodeling.hpp"
#include<iostream>

#define DATA "horizon.data" // Dateiname
#define GOP_GROESSE 12 // L�nge der GoPs
#define ZUSTAENDE 10 // Anzahl Zustände
#define AUTOKORRELATION 100 // Autokorrelation bis N
#define ITERATIONEN 10
#define POOL 10 // Gr��e des Pools
#define DISKRETISIERUNGSSCHRITTE 10

#include <ProgressListener.h>

#include "basicio.hpp"
#include "mmc.hpp"

using ivk::ProgressListener;

using IvkModeling::GeneticModeling;
using IvkModeling::SceneOrientedSMPModel;
using IvkModeling::BasicIO;
using IvkModeling::MMC;

int main(int argc,char* argv[]){
	const char* data = (argc >= 2) ? argv[1] : DATA;

	MMC::MMC model(data,12);
	model.setW(3);
	model.setMA(3);
	model.setMS(3);
	
	model.compute();
	
	rvector rv(0,9);
	for(int i=0;i < 10;i++){ rv[i] = i+10; }
	return 0;
}
