#ifndef HILFSMATHE_H
#define HILFSMATHE_H
#include<vector>
#include<rmatrix.hpp>
#include<intvector.hpp>
#include "data/Trace.h"

using cxsc::real;
using cxsc::rmatrix;
using cxsc::rvector;
using cxsc::Lb;
using cxsc::Ub;
using cxsc::Row;
using cxsc::Col;

using namespace std;
using ivk::Trace;

namespace IvkModeling{
	/**\struct Hilfsklasse 
	  *\brief Hilfsklasse ist eine Klasse, in der mathematische Hilfsmehtoden zur verfuegung gestellt werden.*/
	struct Hilfsklasse{
		/// Erzeugt eine Instanz von Hilfsklasse
		Hilfsklasse();
		/// Loescht eine Instanz von Hilfsklasse
		~Hilfsklasse();
		
		/** Fuehrt eine Berechnung des Mittelwerts fuer eine Datenreihe durch
		\param gop Datenreihe die zur Berechnungsgrundlage dient.
		\param gop_anz Groesse der Datenreihe.*/
		static double mittelwert(int* gop,int gop_anz);
		/** Fuehrt eine Berechnung des Mittelwerts fuer eine Datenreihe durch.
		\param gop Datenreihe die zur Berechnungsgrundlage dient.*/
		static double mittelwert(vector<int> gop);
		/** Fuehrt eine Berechnung des Mittelwerts fuer eine Datenreihe durch.
		\param gop Datenreihe die zur Berechnungsgrundlage dient.
		\param gop_anz Groesse der Datenreihe.*/
		static double mittelwert(double* gop,int gop_anz);
		/** Fuehrt eine Berechnung des Mittelwerts fuer eine Datenreihe durch.
		\param gop Datenreihe die zur Berechnungsgrundlage dient.
		\param ende Wert bis zu dem der Mittelwert berechnet werden soll.*/
		static double mittelwert(double* gops,int anfang,int ende);		
		static double mittelwert(vector<double> gops,int anfang,int ende);
		/** Fuehrt eine Berechnung der empirischen Varianz fuer eine Datenreihe durch.
		\param gop Datenreihe die zur Berechnungsgrundlage dient.
		\param gop_anz Groesse der Datenreihe.*/
		static double varianz(int* gop,int gop_anz);
		/** Fuehrt eine Berechnung der empirischen Varianz fuer eine Datenreihe durch.
		\param gop Datenreihe die zur Berechnungsgrundlage dient.
		\param gop_anz Groesse der Datenreihe.*/
		static double varianz(double* gop,int gop_anz);
		/** Fuehrt eine Berechnung der empirischen Varianz fuer eine Datenreihe durch.
		\param gop Datenreihe die zur Berechnungsgrundlage dient.
		\param ende Wert bis zu dem die Varianz berechnet werden soll.*/
		static double varianz(double* gops,int anfang,int ende);		
		static double varianz(vector<double> gops,int anfang,int ende);
		/** Fuehrt eine Berechnung der Standardabweichung durch.
		\param gop Datenreihe die zur Berechnungsgrundlage dient.
		\param gop_anz Groesse der Datenreihe.
		\param max Groesster Wert der Datenreihe.*/
		static double standardAbweichung(int* gop,int gop_anz);
		/** Fuehrt eine Berechnung der Standardabweichung durch.
		\param gop Datenreihe die zur Berechnungsgrundlage dient.
		\param gop_anz Groesse der Datenreihe.
		\param max Groesster Wert der Datenreihe.*/
		static double standardAbweichung(double* gop,int gop_anz);
		/** Fuehrt eine Berechnung der Standardabweichung durch.
		\param gops Datenreihe die zur Berechnungsgrundlage dient.
		\param ende Wert bis zu dem die Standardabweichung berechnet werden soll.*/
		static double standardAbweichung(int anfang,int ende,double* gops);		
		static double standardAbweichung(int anfang,int ende,vector<double>* gops);		
		/**Methode um einen rvector zu nullen
		\param vec Vector der genullt werden soll*/
		static void zero(rvector &vec);
		/**Methode um eine rmatrix zu nullen
		\param mat Matrix die genullt werden soll*/		
		static void zero(rmatrix &mat);
		/**Methode um die fitness von 2 rvectoren zu vergleichen
		\param basis Basis des Vergleichs
		\param vergl Wert der mit Basis verglichen wird*/
		static real fitness(rvector &basis, rvector &vergl);
		/**Methode um eine zufaellige Folge zu generieren
		\param n laenge der Folge
		\param umatrix Uebergansmatrix die als Berechnungsgrundlage dient*/
		static rvector* zustandsfolge(int n,rmatrix umatrix);
		/**Methode um einen rvector mit Werten zu fuellen
		\param vec Vector der gefüllt werden soll
		\param n Wert der eingetragen werden soll*/
		static void fuellen(rvector &vec,int n);
		/**Methode um eine rmatrix mit Werten zu fuellen
		\param mat Matrix der gefüllt werden soll
		\param n Wert der eingetragen werden soll*/	
		static void fuellen(rmatrix &mat,int n);
		/**Methode um nullZeilen und entsprechende Spalten aus einer Matrix zu entfernen
		\param umatrix Matrix aus der die Zeilen entfernt werden sollen*/
		static void testeMatrix(rmatrix &umatrix);
		static rmatrix constructSMP(rvector data, intvector index, int stepCount);
	};
}
#endif
