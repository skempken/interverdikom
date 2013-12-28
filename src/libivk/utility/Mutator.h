#ifndef MUTATOR_H
#define MUTATOR_H

#include<math.h>
#include<vector>
#include<rmatrix.hpp>
#include<intvector.hpp>
#include "utility/RMatrixUtils.h"

using namespace cxsc;
using namespace std;

namespace ivk{
	/**\class Mutator
	\brief Mutator ist eine Klasse, mit der Zustandsfolgen zufällig mutiert werden können*/
	class Mutator{
		private:
			int n;
			int m;
			double * mut_wahr;
			int* bereich;
			vector<intvector> pool;
		public:
			/**Konstruktor der Klasse
			\param m Anzahl der Zustaende
			\param pool Folgenpool mit dem gearbeitet wird*/
			Mutator(int m);
			/**Destruktor*/
			~Mutator();
			/**Wahrscheinlichkeiten der einzelnen Mutatoren*/
			rmatrix* mut_stat;
			
			rmatrix folge;
			/**Methode um eine Folge mutieren zu lassen
			\param n Index der Folge im Pool*/
			void mutier(int n,vector<intvector>& pool);
			/**Methode um einen bestimmten Mutator auf eine Folge aus einem Pool an zuw enden
			\param mut Index des Mutators
			\param n Index der zu veraendernden Folge*/
			void benutze_mutator(int mut,int n,vector<intvector>& pool);
			/**Methode um einen zufaelligen bereich in einer Folge fest zu legen*/
			void berechne_bereich(vector<intvector>& pool);
			/**Blockmutator (anfang->ende mit gleichen zufaelligen Indexen setzen)
			\param n Index der Folge, die mutiert wird*/
			void mut_block(int n,vector<intvector>& pool);
			/**Inversmutator (anfang->ende in ende->anfang tauschen)
			\param n Index der Folge, die mutiert wird*/
			void mut_inverse(int n,vector<intvector>& pool);
			/**Shufflemutator (anfang->ende alle Indexe aus dem Bereich nehmen und zufaellig neu setzen)
			\param n Index der Folge, die mutiert wird*/
			void mut_shuffle(int n,vector<intvector>& pool);
			/**Swapmutator (anfang,ende miteinander tauschen)
			\param n Index der Folge, die mutiert wird*/
			void mut_swap(int n,vector<intvector>& pool);
			/**Crossovermutator (anfang->ende mit dem gleichen Bereich einer anderen Folge tauschen)
			\param n Index der Folge, die mutiert wird*/
			void mut_crossover(int n,vector<intvector>& pool);
	};
}
#endif
