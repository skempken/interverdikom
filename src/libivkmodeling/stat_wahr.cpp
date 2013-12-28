#include "stat_wahr.hpp"

namespace IvkModeling{
	rvector Stationaere_wahrscheinlichkeiten::berechnen(rmatrix umatrix){
		rvector sp = QueueTools::computeStationaryProbabilities(umatrix);
		return sp;
	}
}
