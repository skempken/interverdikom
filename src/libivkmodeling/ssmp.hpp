#ifndef SSMP_H
#define SSMP_H

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <rmatrix.hpp>
#include <intvector.hpp>
#include <ProgressNotifier.h>
#include "frames.hpp"
#include "basicio.hpp"
#include "mathe.hpp"
#include "stat_wahr.hpp"

using cxsc::real;
using cxsc::rmatrix;
using cxsc::rvector;
using cxsc::power;
using cxsc::intvector;

namespace IvkModeling{
	/**\class SSMP
		\brief SSMP dient zur Berechnung der Parameter eines Simple Semi Markov Process*/
	class SSMP : public ivk::ProgressNotifier {
		public:
			/** Datenreihe die zur Berechnungsgrundlage der meisten Berechnungen benoetigt wird.*/
			Frames* datenreihe;
			/** Groesse der Group of Pictures*/
			int gop_groesse;
			/**Konstruktor der SSMP Klasse, der eine Datei oeffnet um Daten zu bekommen
			\param dateiname Char* der den zu oeffnenden Dateinamen enthaelt*/
			SSMP(const char* dateiname);
			/**Konstruktor der SSMP Klasse, der eine Datenreihe uebernimmt
			\param gops Die schon in ein vector<int> verpackten Daten zur weiterverarbeitung*/
			SSMP(vector<int>* gops);
			/**Konstruktor der SSMP Klasse, der eine Datenreihe uebernimmt
			\param gops Die schon in ein vector<double> verpackten Daten zur weiterverarbeitung*/		
			SSMP(vector<double>* gops);
			/**Konstruktor der SSMP Klasse, der eine Datenreihe uebernimmt
			\param gops Die schon in ein cxsc::intvector verpackten Daten zur weiterverarbeitung*/		
			SSMP(intvector* gops);
			/** methode zum errechnen der Zustandswerte und entsprechendes Abspeichern in SSMP->zustaende nach der Formel:
				Zustand[x] = x* (max-min/m)
			\param m Anzahl der Zustaende.*/
			void zustaende_berechnen(int m);
			/** Methode um die Anzahl der Zustaende zu bekommen*/
			int get_Zustaende();
			/** Testet in welchem Zustand frame liegt.
			\param frame Ist das Frame, das getestet wird.*/
			int zustand_testen(double frame);
			/** Methode, die zum rekursiven Aufbau benoetigt wird.*/
			int zustand_testen(double frame,int pos,int max);
			/** Methode um die zustandsabhaengigen Mittelwerte zu berechnen und in SSMP::zustandsmittelwerte zu speichern.*/
			void zmittelwerte();
			/** Methode um die Uebergangsmatrix zu erstellen. */
			void umatrix_erstellen();
			/** Methode um eine Uebergangsmatrix fuer den genetischen Algorithmus zu erstellen
			\param pool genetischer Pool
			\param folge Folge aus dem Pool
			\param m Anzahl der Zustaende*/
			rmatrix umatrix_erstellen(rmatrix &pool,int folge,int m);
			/** Methode um eine Uebergangsmatrix fuer den genetischen Algorithmus zu erstellen
			\param folge Folge aus dem Pool
			\param m Anzahl der Zustaende*/			
			static rmatrix umatrix_erstellen(rvector &folge,int m);
			/** Methode um auf die Uebergangsmatrix zu bekommen*/
			rmatrix get_umatrix();
			/**Methode zur berechnung der stationeren Wahrscheinichkeiten*/
			void stat_wahrsch_rechnen();
			/**Methode um die stationaeren Wahrscheinlichkeiten zu bekommen */
			rvector get_stat_wahr();
			/**Methode um die stationaeren Wahrscheinlichkeiten anhand einer Uebergangsmatrix zu berechnen*/
			rvector stat_wahrsch_rechnen(rmatrix &umatrix);
			/** Methode um die Autokorrelation bis zu einem gewissen Punkt n zu berechnen
			\param n Bis zu welchem Punkt die Autokorrelation durchgefuehrt werden soll.*/
			rvector autokorrelation_em(int n);
			/** Methode um die Autokorrelation bis zu einem gewissen Punkt n zu berechnen.
			\param n Punkt bis zu dem die Autokorrelation berechnet werden soll.
			\param zmittelwerte zustandsabhaengige Mittelwerte
			\param umatrix Uebergangsmatrix
			\param statWahr stationaere Wahrscheinlichkeiten
			\param folge Folge fuer die die Autokorrelation berechnet werden soll*/
			rvector autokorrelation_um(int n,rmatrix &zmittelwerte,rmatrix &umatrix,rvector &statWahr,int folge);
			/** Methode um eine zufaellige Zustandsfolge zu errechnen. Hierfuer wird die Uebergangsmatrix genoetigt.
			\param n Anzahl der Druchgaenge.
			\param start Zeile mit den Startwahrscheinlichkeiten.
			\param wahrscheinlichkeiten Die errechneten Wahrscheinichkeiten.
			\param m Anzahl der Zustaende.*/
			void zustandsfolge(int n,double* start,int* wahrscheinlichkeiten,int m);
			/** Methode um die Standardabweichung zu berechnen */
			double stdAbweichung();
			/// Destruktor
			~SSMP();
			
		private:
			double* zustaende;
			double* stationaer;
			rmatrix* umatrix;
			
			double schrittweite;
			double* zustandsmittelwerte;
			int m;
			rvector* stat_wahr;			
	};
}
#endif
