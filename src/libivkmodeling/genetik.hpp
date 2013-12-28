#ifndef GENETIK_H
#define GENETIK_H

#include<stdlib.h>
#include<stdio.h>
#include<sys/time.h>
#include <ProgressNotifier.h>
#include "ssmp.hpp"
#include "mathe.hpp"
//#include "diskret.hpp"
#include "mutator.hpp"

using cxsc::rvector;
using cxsc::Lb;
using cxsc::Ub;

namespace IvkModeling{
	/**\class Genetik
	\brief Genetik ist eine Klasse um einen SemiMarkov prozess zu berechnen, bei dem die Zustandsfolgen zufaellig generiert und mutiert werden*/
	class Genetik : public ivk::ProgressNotifier {
		public:
			/**Konstruktor des genetischen Algorithmus
			\param dateiname Datei aus dem die Daten zur berechnung gezogen werden
			\param gopGr Anzahl der Bilder, die zu einer Gruppe zusammen gefasst werden
			\param zustaende Anzahl der Zustaende, die das Modell haben soll
			\param autok Anzahl der Schritte, die die Autokorrelation machen soll
			\param iterationen Anzahl der Iterationen die der genetische Algorithmus durchlaufen soll
			\param poolGr Anzahl der Folgen, die in einem Pool vorhanden sein sollen*/
			Genetik(char* dateiname,int gopGr,int zustaende,int autok,int iterationen,int poolGr);
			/**Konstruktor des genetischen Algorithmus
			\param daten Vector aus dem die Daten zur berechnung gezogen werden
			\param gopGr Anzahl der Bilder, die zu einer Gruppe zusammen gefasst werden
			\param zustaende Anzahl der Zustaende, die das Modell haben soll
			\param autok Anzahl der Schritte, die die Autokorrelation machen soll
			\param iterationen Anzahl der Iterationen die der genetische Algorithmus durchlaufen soll
			\param poolGr Anzahl der Folgen, die in einem Pool vorhanden sein sollen*/
			Genetik(vector<double>* daten,int gopGr,int zustaende,int autok,int iterationen,int poolGr);		
			/**Destruktor*/
			~Genetik();
			/**gibt den Dateinamen zurueck, aus der die Werte geholt wurden*/
			char* getDateiname();
			/**gibt die gop (group of pictures) groesse zurueck*/
			int getGopGr();
			/**gibt die Anzahl der Zustaende zurueck*/
			int getZustaende();
			/**gibt die groesse der Diskretisierungsschritte zurueck*/		
			int getDiskret();
			/**gibt die Anzahl der Autokorrelationsschritte zurueck*/		
			int getAutok();
			/**gibt die Anzahl der Iterationen zurueck*/			
			int getIter();
			/**gibt die Anzahl der Folgen zurueck*/			
			int getPoolGr();
			/**gibt den Index der besten Folge des Pools zurueck*/			
			int getBester();
			/**gibt den Minimumwert der ausgelesenen Folge zurueck*/			
			double getMin();
			/**gibt den Maximumwert der ausgelesenen Folge zurueck*/			
			double getMax();
			/**gibt die ausgelesene Folge zurueck*/			
			double* getGop();
			/**gibt den kompletten Pool zurueck*/
			rmatrix getPool();
			/**gibt die Uebergangsmatrix der besten Folge zurueck*/
			rmatrix getBesteUmatrix();
			/**setzt den Dateinamen aus der die Werte gelesen werden sollen
			\param dateiname Name der Datei*/
			void setDateiname(char* dateiname);
			/**setzt die gop groesse
			\param gopGr Wert auf den die gop Groesse gesetzt werden soll*/
			void setGopGr(int gopGr);
			/**setzt die Anzahl der Zustaende
			\param zustaende Anzahl der Zustaende*/
			void setZustaende(int zustaende);
			/**setzt die groesse der Diskretisierungsschritte
			\param diskret groesse der Diskretisierungsschritte*/
			void setDiskret(int diskret);
			/**setzt die Anzahl der Autokorrelationsschritte
			\param autok Anzahl der Autokorrelationsschritte*/
			void setAutok(int autok);
			/**setzt die Anzahl der Iterationen
			\param iterationen Anzahl der Iterationen*/
			void setIter(int iterationen);
			/**setzt die Anzahl der Folgen im Pool
			\param poolGr Anzahl der Folgen*/
			void setPoolGr(int poolGr);
			/**Methode um die empirischen Daten zu erzeugen worauf sie das genetische Modell stuetzt
			\param gopGr groesse der group of pictures
			\param zustaende Anzahl der Zustaende
			\param autok Anzahl der Autokorrelationsschritte*/
			void empirische_Daten_erzeugen(int gopGr,int zustaende,int autok);
			/**Methode um den Pool der Zustandsfolgen zu initialisieren
			\param n Laenge der Zustandsfolgen
			\param umatrix Uebergangsmatrix auf der die Zustandsfolgen basieren
			\param poolgroesse Anzahl der Folgen im Pool*/
			void pool_initialisieren(int n,rmatrix umatrix,int poolgroesse);
			/**Methode um die Zustandsabhaengigen Mittelwerte fuer jede Folge zu berechnen*/
			void mittelwerte_vorbereiten();
			/**Methode um die Folgen mit den empirischen Daten zu vergleichen*/
			int fitness();
			/**Methode um alle Folgen abgesehen von der fittesten zu mutieren
			\param fittest Folge die nicht mutiert werden soll*/
			int mutier(int fittest);
			/**Methode um den genetischen Algorithmus zu starten */
			int evolutionStarten();
		
		private:
			char* dateiname;
			int gopGr;
			int zustaende;
			int autok;
			int iterationen;
			int poolGr;
			rvector* eak;
			rmatrix* zmittelwerte;
			rmatrix* pool;
			SSMP* emp;
			rvector* klemmbrett;
			Mutator* mutator;
			int bester;
			bool datenPerVector;
	};
}
#endif
