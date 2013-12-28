/*.BA*/
/*.KA{C 3}{L"osung algebraischer Gleichungen}
          {Verfahren zur L"osung algebraischer Gleichungen}*/
/*.FE{C 3.3.2}{Das Verfahren von Muller}{Das Verfahren von Muller}*/

/*.BE*/
/* ------------------------ MODUL fmueller.c ------------------------ */

#include "basis.hpp"
#include "u_proto.hpp"
#include <iostream>

using namespace std;


#define SABS(A,B) (ABS(A) + ABS(B))     /* Summe der Absolutbetraege  */

#define ITERMAX 5000                     /* Iterationsmaximum,         */
                                        /* bei hohem Polynomgrad      */
                                        /* eventl. erhoehen           */
#define START (REAL)0.125               /* Startwert bei skaleit = 0  */
#define MAXDIFF (REAL)5e-5

void printhex2(REAL &d)
{
	int* ip1, *ip2;
	ip1 = (int*)&d;
	ip2=ip1+1;
	cout.width(8);
	cout << hex << *ip2; 
	cout.width(8);
	cout << hex << *ip1;
	return;
}; 


/*.BA*/

/*.BE*/
int mueller             /* Mueller Verfahren fuer reelle Polynome ....*/
/*.BA*/
/*.IX{mueller}*/
/*.BE*/
            (
             int   n,             /* Polynomgrad .....................*/
             REAL  a[],           /* Koeffizientenvektor .............*/
             int   scaleit,       /* Skalieren .......................*/
             REAL  zreal[],       /* Realteile Loesung ...............*/
             REAL  zimag[]        /* Imaginaerteile Loesung ..........*/
            )
/*.BA*/

/*====================================================================*
 *                                                                    *
 *  muller bestimmt saemtliche reellen und komplexen Nullstellen      *
 *  eines Polynoms P vom Grade n                                      *
.BE*)
 *  mit                                                               *
 *                     n             n-1                              *
 *      P(x) = a[n] * x  + a[n-1] * x    + ... + a[1] * x + a[0],     *
 *                                                                    *
 *  wobei a[i], i=0..n, reell sind.                                   *
 *                                                                    *
 *  Die Startwerte fuer das Mueller-Verfahren werden durch die        *
 *  Konstante START = 0.125 vorgegeben. Diese Wahl hat sich           *
 *  als guenstig erwiesen, kann aber gegebenenfalls abgeaendert       *
 *  werden.                                                           *
 *                                                                    *
 *====================================================================*
 *                                                                    *
 *   Anwendung:                                                       *
 *   =========                                                        *
 *      Beliebige Polynome mit reellen Koeffizienten.                 *
 *      Mehrfache Nullstellen liegen in einem kleinen Kreis           *
 *      um den wahren Wert, der etwa mit dem Mittelwert der berech-   *
 *      neten Naeherungen uebereinstimmt.                             *
 *                                                                    *
 *====================================================================*
 *                                                                    *
 *   Literatur:                                                       *
 *   =========                                                        *
 *      Mueller, D.E., A method for solving algebraic equations       *
 *      using an automatic computer, Math. Tables Aids Comp. 10,      *
 *      p. 208-251, (1956).                                           *
 *                                                                    *
 *====================================================================*
 *                                                                    *
 *   Eingabeparameter:                                                *
 *   ================                                                 *
 *      n        Grad des Polynoms ( >= 1 )    int    n;              *
 *      a        Vektor der Koeffizienten      REAL   a[];            *
 *               ( a[0],..,a[n] )                                     *
 *      scaleit  = 0, keine Skalierung         int    scaleit;        *
 *               != 0 automatische Skalierung                         *
 *                                                                    *
 *   Ausgabeparameter:                                                *
 *   ================                                                 *
 *      zreal    Vektor der Laenge n,          REAL   zreal[];        *
 *               zreal[0],..,zreal[n-1] sind                          *
 *               die Realteile der n Nullstellen                      *
 *      zimag    zimag[0],..,zimag[n-1] ent-   REAL   zreal[];        *
 *               halten die Imaginaerteile der                        *
 *               berechneten Nullstellen                              *
 *                                                                    *
 *   Rueckgabewert:                                                   *
 *   =============                                                    *
 *      = 0      alles ok                                             *
 *      = 1      Unzulaessige Eingabeparameter                        *
 *      = 2      Iterationsmaximum ITERMAX ueberschritten             *
 *                                                                    *
 *====================================================================*
 *                                                                    *
 *   Benutzte Funktionen:                                             *
 *   ===================                                              *
 *                                                                    *
 *     fmval():     Bestimmt den Funktionswert des aktuellen Polynoms *
 *     quadsolv():  Loesst eine quadratische Geichung mit komplexen   *
 *                  Koeffizienten                                     *
 *                                                                    *
 *   Aus der C-Bibliothek: pow()                                      *
 *                                                                    *
 *====================================================================*
 *                                                                    *
 *   Benutzte Konstanten: MACH_EPS, EPSROOT, EPSQUAD, ITERMAX, START  *
 *   ===================                                              *
 *                                                                    *
.BA*)
 *====================================================================*/
/*.BE*/
{
	int i;
	int iu, iter, iter2, wiederholung, iukopie;

	REAL  p, q, temp, scale, start, zrealn,
	      x0real, x0imag, x1real, x1imag, x2real,x2imag,
	      f0r,    f0i,    f1r,    f1i,    f2r,   f2i,
        h1real, h1imag, h2real, h2imag, hnr,   hni,
        fdr,    fdi,    fd1r,   fd1i,   fd2r,  fd2i,
        fd3r,   fd3i,
        b1r,    b1i,
        pot,
        *polynomkopie;

	if (zreal == NULL || zimag == NULL || a == NULL) return (1);

	for (i = 0; i < n; i++)
	{
		zreal[i] = a[i];                        /*  a auf zreal kopieren  */
		zimag[i] = ENGELN_ZERO;                        /*  zimag mit 0 besetzen  */
	}

	if ((n <= 0) || (ABS(a[n]) <= ENGELN_ZERO))
		return (1);                             /* unzulaessige Parameter */

	scale = ENGELN_ZERO;            /* Skaliere Polynom, wenn ( scaleit != 0 ) */

	if (scaleit != 0)          /* scale                                 */
	{                          /*               a[i]  1/(n-i)           */
		p = ABS(a[n]);           /*  =  max{ ABS( ---- )       ,i=0..n-1} */
		for (i = 0; i < n; i++)  /*               a[n]                    */
			if (zreal[i] != ENGELN_ZERO)
			{
				zreal[i] /= p;
        pot = POW (ABS(zreal[i]), ONE / (REAL) (n - i));
        scale = ENGELN_max (scale, pot);
      }

    zrealn = a[n] / p;                        /* zrealn = +/-1        */

                             /*                      n-i              */
    if ( scale != ONE &&     /* a[i] = a[i] / ( scale    ), i=0..n-1  */
         scale != ENGELN_ZERO )
      for (p = ONE, i = n - 1; i >= 0; i--)
      {
        p *= scale;
        zreal[i] /= p;
      }
  }    /* end if (scaleit.. */
  else
  {
    scale = ONE;
    zrealn = a[n];
  }

  iu = 0;

  do
  {   /*  Muellerverfahren bis iu == n-1  */

    while (ABS(zreal[iu]) < EPSQUAD)            /* Nulloesungen des   */
    {                                           /* Rest-Polynoms      */
      zreal[iu] = zimag[iu] = ENGELN_ZERO;
      iu++;
      if (iu == n - 1) break;
    }

    if (iu >= n - 1)                       /* Wenn iu == n-1 --> Ende */
    {
      zreal[n-1] *= -scale / zrealn;
      zimag[n-1] = ENGELN_ZERO;
      return (0);
    }

    if (scaleit)                           /* Wenn Skalierung, Start- */
    {                                      /* wert neu berechnen      */
      for (start = ENGELN_ZERO, i = n - 1; i >= iu; i--)
        start = ENGELN_max (start, ABS(zreal[i]));

      start /= (REAL)128.0;            /* Alle Nullstellen liegen im  */
    }                                  /* Kreis um (0,0) mit Radius   */
    else                               /* r = 1 + max{ABS(a[i]),i=..} */
      start = START;

    iter = 0;                     /* Iterationszaehler initialisieren */
    iter2 = 0;
    wiederholung = 0;
    REAL differenz;
    polynomkopie = new REAL[n+1];

		do
		{
	    if (iter2 > 0)
  	  {
  	  	start += 0.125;
  	  	iu = iukopie;
  	  	for (i = 0; i <= n; i++)
  	  	  zreal[i] = polynomkopie[i];
  	  }
  	  else
  	  {
  	  	start = START;
  	  	iukopie = iu;
  	  	for (i = 0; i <= n; i++)
  	  	  polynomkopie[i] = zreal[i];
  	  }
  	  	

    	x0real = -start;              /* Startwerte fuer Mueller-Verf.    */
	    x0imag = ENGELN_ZERO;
	
  	  x1real = start;
    	x1imag = ENGELN_ZERO;

	    x2real = ENGELN_ZERO;
  	  x2imag = ENGELN_ZERO;

	    h1real = x1real - x0real; h1imag = ENGELN_ZERO;    /*  h1 = x1 - x0      */
  	  h2real = x2real - x1real; h2imag = ENGELN_ZERO;    /*  h2 = x2 - x1      */

	    f0r = zrealn;   f0i = ENGELN_ZERO;         /* zugehoerige Funktionswerte */
  	  f1r = f0r;      f1i = ENGELN_ZERO;

	    for (i = n; i > iu; )
  	  {
    	  f0r = f0r * x0real + zreal[--i];
      	f1r = f1r * x1real + zreal[i];
      	//if (iu == 2) 
      	//	cout << "zreal = " << zreal[i] << endl;
	    }

	    f2r = zreal[iu];
  	  f2i = ENGELN_ZERO;
    	differenz = ABS(f0r-f1r) + ABS(f0r-f2r) + ABS(f1r-f2r);
//	    cout << "Differenz = " << differenz;
//  	  cout << dec << ", iu = " << iu
//    			 << ", f0r = " << f0r 
//    			 << ", f1r = " << f1r 
//    			 << ", f2r = " << f2r << endl;
	  	

	    fd1r = (f1r - f0r) / h1real;      /* 1. dividierte Differenz Nr.1 */
  	  fd1i = ENGELN_ZERO;                      /* fd1 = (f1 - f0) / h1         */

    	do /* Mueller-Iteration */
    	{
      	if ( SABS(f0r,f0i) < EPSQUAD             /* Startwert ist gute  */
        	   || SABS(f1r,f1i) < EPSQUAD )        /* Naeherung           */
      	{
        	x1real = x0real;
        	x1imag = x0imag;

        	f2r = f0r;
        	f2i = f0i;
        	break;
      	}
	                                      /* 1. dividierte Differenz Nr.2 */
  	                                    /* fd2 = (f2 - f1) / h2         */
    	  temp = h2real * h2real + h2imag * h2imag;
      	fdr = f2r - f1r;
      	fdi = f2i - f1i;

      	fd2r = ( fdr * h2real + fdi * h2imag ) / temp;
      	fd2i = ( fdi * h2real - fdr * h2imag ) / temp;

      	fdr = fd2r - fd1r;             /* 2. dividierte Differenz       */
      	fdi = fd2i - fd1i;             /* fd3 = (fd2 - fd1) / (h1 + h2) */

      	hnr = h1real + h2real; hni = h1imag + h2imag;
      	temp = hnr * hnr + hni * hni;
	      fd3r = ( fdr * hnr + fdi * hni ) / temp;
  	    fd3i = ( fdi * hnr - fdr * hni ) / temp;

    	  b1r = h2real * fd3r - h2imag * fd3i + fd2r;       /*  h2 * f3   */
      	b1i = h2real * fd3i + h2imag * fd3r + fd2i;

      	h1real = h2real;                 /* letzte Korrek. merken,      */
      	h1imag = h2imag;
                                       /* neue berechnen              */
                                       
      	if ( (fd3r != ENGELN_ZERO) || (fd3i != ENGELN_ZERO) ||
        	   (b1r != ENGELN_ZERO)  || (b1i != ENGELN_ZERO)     )
      	{ 
      		quadsolv (fd3r, fd3i, b1r, b1i, f2r, f2i, &h2real, &h2imag);
      	}
      
      	else
      	{
        	h2real = HALF;
        	h2imag = ENGELN_ZERO;
      	}

      	x1real =  x2real;                /* alte Loesung merken,        */
      	x1imag =  x2imag;
      	x2real += h2real;                /* neue berechnen:             */
      	x2imag += h2imag;                /* x2 = x2 + h2                */

      	f1r  = f2r;                      /* genauso fuer Funktionswerte */
      	f1i  = f2i;
      	fd1r = fd2r;
      	fd1i = fd2i;

      	fmval (n, iu, zreal, zrealn, x2real, x2imag, &f2r, &f2i);

      	                     /* Uneffektive Richtungen und damit over-  */
      	                     /* flow vermeiden                          */
      	i = 0;
      	while (SABS(f2r,f2i) > n * SABS(f1r,f1i))
      	{
      	                                  /* gegen underflow sichern    */
        	if (i > 10) break;
        	else
        	  i++;

        	h2real *= HALF;                 /* h halbieren; x2,f2 korrig. */
        	h2imag *= HALF;

        	x2real -= h2real;
        	x2imag -= h2imag;

        	fmval (n, iu, zreal, zrealn, x2real, x2imag, &f2r, &f2i);
      	}

      	iter++;
      	if (iter > ITERMAX) return (2);     /* ITERMAX ueberschritten   */
    	}                                     /* Ende Mulleriteration     */

    	while ( (SABS(f2r,f2i) > EPSQUAD) &&
    	         (SABS(h2real,h2imag) > MACH_EPS * SABS(x2real,x2imag)) );

    	if (SABS(f1r,f1i) < SABS(f2r,f2i))    /* bessere Naeherung        */
    	{                                     /* aussuchen                */
    	  x2real = x1real;
    	  x2imag = x1imag;
    	}
    
    	if (ABS(x2imag) > EPSROOT * ABS(x2real))
    	{                                     /* Abdividieren einer kom-  */
    	                                      /* plexen Nullstelle u. der */
      	                                    /* komplex konjugierten     */
      	p  = x2real + x2real;
      	q  = -x2real * x2real - x2imag * x2imag;
//      	if (iu == 0)
//      		cout << "p = " << p << ", q = " << q << endl;

      	zreal[n-1] += p * zrealn;
      	zreal[n-2] += p * zreal[n-1] + q * zrealn;

      	for (i = n - 3; i > iu + 1; i--)
      	  zreal[i] += p * zreal[i+1] + q * zreal[i+2];

      	x2real *= scale;
      	x2imag *= scale;

      	zreal [iu+1] =  x2real;
      	zimag [iu+1] =  x2imag;
      	zreal [iu]   =  x2real;
      	zimag [iu]   = -x2imag;
      	iu += 2;                              /* Grad um 2 erniedrigen  */
    	}
    	else
    	{
      	zreal[n-1] += zrealn * x2real;        /* reelle Nullstelle ab-  */
      	                                      /* dividieren             */
      	for (i = n - 2; i > iu; i--)
      	  zreal[i] += zreal[i+1] * x2real;

      	zreal[iu] = x2real * scale;
      	zimag[iu] = ENGELN_ZERO;
      	iu++;                                 /* Grad um 1 erniedrigen  */
    	}

   		if ((n > 1)&&(iu < n))
   		{
   			//if (iu == 2) 
//	   		cout << "\nzreal[n] = " << zreal[iu] << endl; 
   			//printhex2(zreal[iu]);
    		int *ip1, *ip2;
				ip1 = (int*)&zreal[iu];
				ip2=ip1+1;
		    if ((*ip2 >= 0xfff00000) || (*ip2 >= 0x7ff00000) || (zreal[iu] > 1e100) || (ABS(zreal[iu]) < EPSQUAD))
		    //if ((zreal[iu] < -1e100) || (zreal[iu] > 1e100) || (ABS(zreal[iu]) < EPSQUAD))
    			wiederholung = 1; //cout << "\nWiederholung!" << endl;
    		else 
    			wiederholung = 0;
   		}
   		iter2++;
		} while ((wiederholung) && (iter2 <= 7));
	
		if (iter2 > 7)
		{
			cout << "Zu oft geschleift!" << endl;
			return(3);
		}
  }
  while (iu < n);                           /* Ende Mullerverfahren   */

  return (0);
}


void fmval              /* (Komplexer) Polynomwert ...................*/
/*.IX{fmval}*/
           (
            int     n,            /* Hoechster Koeffizient ...........*/
            int     iu,           /* Niedrigster Koeffizient .........*/
            REAL    zre[],        /* Koeffizienten ...................*/
            REAL    zren,         /* Fuehrender Koeffizient ..........*/
            REAL    xre,          /* Realteil x ......................*/
            REAL    xim,          /* Imaginaerteil x .................*/
            REAL *  fre,          /* Realteil Funktionswert ..........*/
            REAL *  fim           /* Imaginaerteil Funktionswert .....*/
           )
/*====================================================================*
 *                                                                    *
 *  fmval bestimmt den Funktionswert eines Polynoms vom Grade n-iu    *
 *  mit den reellen Koeffizienten zre[iu],..,zre[n-1],zren an         *
 *  der (komplexen) Stelle (xre, xim).                                *
 *                                                                    *
 *====================================================================*
 *                                                                    *
 *  Eingabeparameter:                                                 *
 *  ================                                                  *
 *      zre    Vektor der Koeffizienten         REAL   zre[];         *
 *      zren   fuehrender Koeffizient           REAL   zren;          *
 *      xre    Realteil der Auswertungsstelle   REAL   xre;           *
 *      xim    Imaginaerteil Auswertungsstelle  REAL   xim;           *
 *                                                                    *
 *  Ausgabeparameter:                                                 *
 *  ================                                                  *
 *      fre    Realteil des Polynomwerts        REAL   *fre:          *
 *      fim    Imaginaerteil des Polynomwerts   REAL   *fim;          *
 *                                                                    *
 *====================================================================*/
{
  int i;
  REAL     tmp;

  *fre = zren;
  *fim = ENGELN_ZERO;

  if (xim == ENGELN_ZERO)                         /* Funktionwert reell      */
    for (i = n; i > iu; )
      *fre = *fre * xre + zre[--i];
  else
    for (i = n; i > iu; )                  /* Funktionswert komplex   */
    {
      tmp  = *fre;
      *fre = *fre * xre - *fim * xim + zre[--i];
      *fim = tmp * xim + xre * *fim;
    }
}

/* ------------------------- ENDE fmueller.c ------------------------ */
