#ifndef DISKRETGEN_H
#define DISKRETGEN_H
#include<math.h>
#include "rmatrix.hpp"
#include "simplesmp.hpp"

using cxsc::rmatrix;
using cxsc::rvector;
using IvkModeling::SimpleSMP;

namespace IvkModeling{
	namespace Gen{
		/**\class Diskretisierung
		\brief Diskretisierung ist eine Klasse um die Diskretisierung einer Zustandsfolge zu errechnen*/
		class Diskretisierung{
			private:
				double min;
				double max;
				int m;
				int gop_anz;
				Diskretisierung();
				~Diskretisierung();
			
			public:
				/** Fuehrt die Diskretisierung durch.
				\param pool Ist der Genetische Pool aus dem die Folge zur Berechnung herausgeholt wird.
				\param folge Ist der Index der Folge, die aus dem Pool benutzt wird.
				\param gop[] Ist die Datenreihe fuer die Berechnungsgrundlage.
				\param schritte Ist die Schrittweite der Berechnung.*/
				static rmatrix diskretisieren(rmatrix pool,int folge, int schritte,double gop[],int m,double min, double max);
				static rmatrix diskretisieren(SimpleSMP* model);
		};
	}
}
#endif
