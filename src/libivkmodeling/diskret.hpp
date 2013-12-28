#ifndef DISKRET_H
#define DISKRET_H
#include<math.h>
namespace IvkModeling{
	class Diskretisierung{
		private:
			double min;
			double max;
			int m;
			int gop_anz;
			double* zustaende;
		
		public:
			/** Erzeugt eine Instanz zum Errechnen der Diskretisierung
			\param m Ist die Anzahl der Zustaende.
			\param gop_anz Ist die Anzahl der Elemente in der Datenreihe.
			\param min Ist der kleinste Wert der Datenreihe.
			\param max Ist der groesste Wert der Datenreihe.
			\param zustaende Ist das Array indem die Zustaende enthalten sind.*/
			Diskretisierung(int m,int gop_anz,double min, double max,double* zustaende);
			~Diskretisierung();
			/** Testet in welchem Zustand frame liegt.
			\param frame Ist das Frame, das getestet wird.*/
			int zustand_testen(double frame);
			/** Methode, die zum rekursiven Aufbau benoetigt wird.*/
			int zustand_testen(double frame,int pos,int max);
			/** Fuehrt die Diskretisierung durch.
			\param gop Ist die Datenreihe fuer die Berechnungsgrundlage.
			\param schritte Ist die Schrittweite der Berechnung.
			\param disk Ist die Variabel in der die Ergebnisse gespeichert werden.*/
			double** diskretisieren(double* gop, int schritte);
	};
}
#endif
