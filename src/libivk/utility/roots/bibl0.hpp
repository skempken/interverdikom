/***********************************************************************/
/* bibl0.h                                                             */
/*                                                                     */
/* Headerdatei von bibl0.cpp:                                          */
/* Standardfunktionen, die im Hauptprogramm verwendet werden           */
/*                                                                     */
/* Letzte Aenderung: 26.07.2002                                        */
/***********************************************************************/
#ifndef BIBL0_H
#define BIBL0_H

#include "interval.hpp"

using namespace cxsc;
//#include "complex.h"

//extern double abs(double rn);

extern double betrag_quad_komplex(double realteil, double imagteil);

extern double exppos(double rn);

//extern double exp(double rn);

// extern double sqr(double zahl);

//extern COMPLEX power(COMPLEX basis, int exp);

extern void outint(int i, int length = 3, int plumin = 0);
// Formatierte Integerausgabe 

extern void newl();

extern void outreal(double i, int nachkom = 4);
// Formatierte Realausgabe 

extern void fileoutreal(double i, int nachkom = 4);
// Formatierte Realausgabe in eine Datei

void outvekt(double* v, int elem);
// Formatierte Ausgabe eines Vektors mit "elem" Elementen 

void outvekti(interval* v, int elem);
// Formatierte Ausgabe eines Vektors mit "elem" Elementen 

#endif


