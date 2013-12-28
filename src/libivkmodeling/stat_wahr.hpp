#ifndef STAT_WAHR_H
#define STAT_WAHR_H
#include<QueueTools.h>

using ivk::QueueTools;
using namespace std;

namespace IvkModeling{
	/**\class Stationaere_wahrscheinlichkeiten
	\brief Stationaere_wahrscheinlichkeiten ist eine Klasse um stationaere Wahrscheinlichkeiten zu berechnen*/
	class Stationaere_wahrscheinlichkeiten{
		public:
			/**Methode um die stationaeren Wahrscheinlichkeiten zu berechnen
			\param umatrix Uebergangsmatrix, die als Berechnungsgrundlage dient*/
			static rvector berechnen(rmatrix umatrix);
		private:
			Stationaere_wahrscheinlichkeiten();
			~Stationaere_wahrscheinlichkeiten();
	};
}
#endif
