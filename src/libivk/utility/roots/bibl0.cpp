/***********************************************************************/
/* bibl0.cpp                                                           */
/*                                                                     */
/* Standardfunktionen, die im Hauptprogramm verwendet werden  				 */
/*                                                                     */
/* Letzte Aenderung: 26.07.2002                                        */
/***********************************************************************/

// #include <stdio.h> 


// #include "complex.h"
#include "bibl0.hpp"
 
using namespace std;


//double abs(double rn) { if (rn > 0) return rn; else return -rn; }
// bestimmt den Absolutbetrag einer reellen Zahl


double betrag_quad_komplex(double realteil, double imagteil)
// bestimmt den Absolutbetrag zum Quadrat einer komplexen Zahl 
{
	double erg;
	erg = (realteil * realteil) + (imagteil * imagteil);
	return erg;
}


double exppos(double rn)
{
	int    i = 1;
	double delta, erg;

	if (rn < 0) 
		return 1;
	else
		if (rn > 0.1) 
			return exppos(rn/2)*exppos(rn/2);
		else 
		{ 
			erg = 1 + rn; 
			delta = rn; 
			while (delta > 1e-15)
			{ 
				++i; 
				delta = delta*rn/i; 
				erg = erg + delta; 
			}

			return erg;
		}

}

/*double exp(double rn) 
{ if (rn > 0) return exppos(rn);
  else        return 1/exppos(-rn);
} 
*/
/*
COMPLEX power(COMPLEX basis, int exp)
{
	COMPLEX hilfe(1.0,0.0);
	
	while (exp > 0)
	{
		hilfe = hilfe * basis;
		exp--;
	}
	return hilfe;
}
*/


void outint(int i, int length, int plumin)
   /* Formatierte Integerausgabe */

{ 
	long int j;
    int k,l,stellen;
  
//  cout << "outint";
	j = 10; stellen = 1;
	while (cxsc::abs(i) >= j)
	{
		++stellen; 
		j = 10*j;
	}
	
	for (k=1; k <= length-stellen; k++) 
		cout << " ";

	if (i < 0)
	{
		cout <<"-";
		i = -i;
	} 
	else 
	if (plumin == 0) 
		cout <<" "; 
	else 
		cout <<"+";

	for (k=0; k<stellen; k++)
	{ 
		j = j/10; 
		l = i/j; 
		cout << l; 
		i = i%j;
	}

	cout << " ";
}

// double sqr(double zahl) { return(zahl*zahl); };

void outreal(double i, int nachkom)
/* Formatierte Realausgabe */
{     
	int k,l,expon; 

	if (i < 0)
	{
		cout <<" -"; i = -i;
	} 
	else cout <<" +";
  
	expon = 0; 

	while (i >= 10.0)
	{
		++expon; 
		i = i/10.0;
	}

	if (expon == 0) 
		while ((i < 1.0) && (expon > -100))
		{
			--expon; 
			i = 10.0*i;
		}

	if (expon == -100) 
	{
		expon = 0; 
		i = 0.0;
	}

	// HIER IST DER EXPONENT BESTIMMT UND (1 <= I < 10) oder (I = 0)

	double iplus = 0.5;
	for (k=1; k <= nachkom; k++) iplus = iplus/10.0;

	i += iplus;
	for (k=0; k <= nachkom; k++) 
	{ 
		l =(int) i; 
		cout << l; 
		if (k == 0) 
			cout << ".";
		i = 10.0*(i-l);
	}

	cout << "E"; 
	if (expon < 0) cout << "-"; else cout << "+";
	expon = abs(expon);
	if (expon < 10) cout << 0;
	cout << expon << " ";
}

/*
void fileoutreal(double i, int nachkom)
// Formatierte Realausgabe in eine Datei

{ 
	int k,l,expon; 
	extern ofstream Ziel;

	if (i < 0) {Ziel <<" -"; i = -i;} else Ziel <<" +";
	expon = 0; 
	while (i >= 10.0) {++expon; i = i/10.0;}
	if (expon == 0) while ((i < 1.0) && (expon > -100))
                  {--expon; i = 10.0*i;};
	if (expon == -100) {expon = 0; i = 0.0;};

	// HIER IST DER EXPONENT BESTIMMT UND (1 <= I < 10) oder (I = 0)

	double iplus = 0.5;
	for (k=1; k <= nachkom; k++) iplus = iplus/10.0;
	i += iplus;
	for (k=0; k <= nachkom; k++) 
	{ 
		l =(int) i; Ziel << l; if (k == 0) Ziel << ".";
		i = 10.0*(i-l);
	};  

	Ziel << "E"; 
	if (expon < 0) Ziel << "-"; else Ziel << "+";
	expon = abs(expon);
	if (expon < 10) Ziel << 0;
	Ziel << expon << " ";
}
*/

inline void newl() 
{
	cout << "\n";
}

void outvekt(double* v, int elem)
// Formatierte Ausgabe eines Vektors
{ 
	for (int j = 0; j < elem; j++)
	{ 
		if (!(j % 5)) { outint(j,3); cout << ":"; }; 
		cout << v[j] << "  "; 
		if ((j%5 == 4) || (j == elem)) newl();
	}
}


void outvekti(interval* v, int elem)
// Formatierte Ausgabe eines Vektors
{ 
	for (int j = 0; j < elem; j++)
	{ 
		if (!(j % 5)) { outint(j,3); cout << ":"; }; 
		cout << v[j]; 
		if ((j%5 == 4) || (j == elem)) newl();
	}
}
