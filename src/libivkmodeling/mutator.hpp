#ifndef MUTATOR_H
#define MUTATOR_H

#include<math.h>
#include<iostream>
#include<rmatrix.hpp>
#include "mathe.hpp"

using cxsc::rmatrix;
using cxsc::Ub;

namespace IvkModeling{
	/**\class Mutator
	\brief Mutator ist eine Klasse, mit der Zustandsfolgen zufällig mutiert werden können*/
	class Mutator{
		private:
			int n;
			int m;
			double * mut_wahr;
			int* bereich;
		public:
			/**Konstruktor der Klasse
			\param m Anzahl der Zustaende
			\param pool Folgenpool mit dem gearbeitet wird*/
			Mutator(int m,rmatrix& pool);
			/**Destruktor*/
			~Mutator();
			/**Wahrscheinlichkeiten der einzelnen Mutatoren*/
			rmatrix* mut_stat;
			
			rmatrix folge;
			/**Methode um eine Folge mutieren zu lassen
			\param pool Pool aus der die Folge genommen wird
			\param n Index der Folge im Pool*/
			void mutier(rmatrix& pool,int n);
			/**Methode um einen bestimmten Mutator auf eine Folge aus einem Pool an zuw enden
			\param mut Index des Mutators
			\param pool Pool aus dem die Folge genommen wird
			\param n Index der zu veraendernden Folge*/
			void benutze_mutator(int mut,rmatrix& pool,int n);
			/**Methode um eine Folge nach anwendung der Mutatoren auf korrektheit bzgl. der Uebergangsmatrix zu testen
			\param pool Pool aus der die zu testende Folge stammt
			\param folge Index der zu testenden Folge*/
			void testKorrektur(rmatrix& pool,int folge);
			/**Methode um einen zufaelligen bereich in einer Folge fest zu legen
			\param pool Pool um laenge einer Folge heraus zu finden*/
			void berechne_bereich(rmatrix& pool);
			/**Blockmutator (anfang->ende mit gleichen zufaelligen Indexen setzen)
			\param pool Pool aus dem die Folge entnommen wird
			\param n Index der Folge, die mutiert wird*/
			void mut_block(rmatrix& pool,int n);
			/**Inversmutator (anfang->ende in ende->anfang tauschen)
			\param pool Pool aus dem die Folge entnommen wird
			\param n Index der Folge, die mutiert wird*/
			void mut_inverse(rmatrix& pool,int n);
			/**Shufflemutator (anfang->ende alle Indexe aus dem Bereich nehmen und zufaellig neu setzen)
			\param pool Pool aus dem die Folge entnommen wird
			\param n Index der Folge, die mutiert wird*/
			void mut_shuffle(rmatrix& pool,int n);
			/**Swapmutator (anfang,ende miteinander tauschen)
			\param pool Pool aus dem die Folge entnommen wird
			\param n Index der Folge, die mutiert wird*/
			void mut_swap(rmatrix& pool,int n);
			/**Crossovermutator (anfang->ende mit dem gleichen Bereich einer anderen Folge tauschen)
			\param pool Pool aus dem die Folge entnommen wird
			\param n Index der Folge, die mutiert wird*/
			void mut_crossover(rmatrix& pool,int n);
	};
}
#endif
