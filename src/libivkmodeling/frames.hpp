#ifndef FRAMES_H
#define FRAMES_H
#include<vector>
#include<math.h>
#include<iostream>

using std::cout;
using std::vector;

namespace IvkModeling{
	/**\struct Frames
	\brief Frames dient zum Speichern und Verarbeiten einer Datenreihe.*/
	struct Frames{
		/// Groesster Wert der Datenreihe.
		double max;
		/// Kleinster Wert der Datenreihe.
		double min;
		/// Anzahl der Elemente der Datenreihe.
		int gop_anz;
		/// Die Rohdaten an sich.
		vector<double>* inhalt;
		/// Die Datenreihe verarbeitet zu GoPs mit der methode frames_zu_gop
		double* gop;

		Frames();
		/** Methode um einzeldaten zu GoPs (Group of Pictures) zusammen zu fassen.
		\param gop_groesse Anzahl wieviele Bilder zusammen gefasst werden sollen*/
		void frames_zu_gop(int gop_groesse);
		/** Methode um eine Kopie der GoPs zurück zu geben*/
		double* getGop();
		/**Methode um den Minimalwert der Gops zu erhalten*/
		double getMin();
		/**Methode um den Maximalwert der Gops zu erhalten*/
		double getMax();
		/**Destruktor*/
		~Frames();
	};
}
#endif
