/*.BA*/



/*.FE{C 3.3.3}{Das Verfahren von Bauhuber}{Das Verfahren von Bauhuber}*/

/*.BE*/
/* ------------------------ MODUL fbauhube.c ------------------------ */

#include "basis.hpp"
#include "u_proto.hpp"

#define ITERMAX 2000               /* Maximale Anzahl der Funktions-  */
                                   /* auswertungen pro Nullstelle     */
#define EPS (REAL)((REAL)64.0 * MACH_EPS)    /* Genauigkeit im Funktionswert    */
#define BETA (REAL)((REAL)8.0 * EPS)
#define QR (REAL)0.1               /* Real-/Imaginaerteil des         */
#define QI (REAL)0.9               /* Spiralisierungsfaktors          */

//using basis_h::max;





/**
 * @param n			int,  Vektorlaenge
 * @param ar[]		REAL, Realteil des Vektors
 * @param ai[]		REAL, Imaginaerteil des Vektors
 * @param scal		REAL, Skalierungsfaktor
 */
static void scpoly( int n, REAL ar[], REAL ai[], REAL* scal );



/**
 * @param n			int,  Hoechstgrad
 * @param iu		int,  Niedrigster Grad
 * @param ar[]		REAL, Realteile Koeffizienten
 * @param ai[]		REAL, Imaginaerteile Koeffizienten
 * @param x0r		REAL, Realteil Nullstelle
 * @param x0i		REAL, Imaginaerteil Nullstelle
 */
static int bauroot( int n, int iu, REAL ar[], REAL ai[], REAL* x0r, REAL* x0i );


/**
 * @param n			int,  Hoechster Polynomkoeff
 * @param iu		int,  Niedrigster Polynomkoeff
 * @param ar[]		REAL, Realteile Koeffizienten
 * @param ai[]		REAL, Imaginaerteile Koeffizienten
 * @param xr		REAL, Realteil x
 * @param xi		REAL, Imaginaerteil x
 * @param pr		REAL, Realteil Funktionswert
 * @param pi		REAL, Imaginaerteil Funktionswert
 * @param p1r		REAL, Realteil 1. Ableitung
 * @param p1i		REAL, Imaginaerteil 1. Ableitung
 * @param p2r		REAL, Realteil 2. Ableitung
 * @param p2i		REAL, Imaginaerteil 2. Ableitung
 * @param rf1		REAL, Fehlerschaetzung 1. Ableitung
 */
static void chorner( int n, int iu, REAL ar[], REAL ai[], REAL xr, REAL xi, REAL* pr, 
                     REAL* pi, REAL* p1r, REAL* p1i, REAL* p2r, REAL* p2i, REAL* rf1 );


/**
 * @param n			int,  Hoechstgrad
 * @param iu		int,  Niedrigster Grad
 * @param ar[]		REAL, Realteile Koeffizienten
 * @param ai[]		REAL, Imaginaerteile Koeffizienten
 * @param x0r		REAL, Realteil x
 * @param x0i		REAL, Imaginaerteil x
 */
static void polydiv( int n, int iu, REAL ar[], REAL ai[], REAL x0r, REAL x0i );



/**
 * @param real		int,  Koeffizienten sind reell ?
 * @param scale		int,  Skalieren ?
 * @param n			int,  Polynomgrad
 * @param ar[]		REAL, Realteile Koeffizienten
 * @param ai[]		REAL, Imaginaerteile Koeffizienten
 * @param rootr[]	REAL, Realteile Nullstellen
 * @param rooti[]	REAL, Imaginaerteile Nullstellen
 * @param absf[]	REAL, Absolutbetraege der Funktionswerte
 * @brief Bauhuber Verfahren fuer komplexe Polynome
 *
 *  Es werden mit dem Verfahren von Bauhuber saemtliche reellen 
 *  und komplexen Nullstellen eines Polynoms P vom Grade n bestimmt         <br>
 *  mit																		<br><br>
 *                                                          
 *      P(x) = a[0] + a[1] * x + ... + a[n-1] * x^(n-1)    + a[n] * x^n ,	<br><br>
 *                                                                    
 *  wobei a[i], i=0..n, komplex sind.										<br><br>
 *                                                                    
 *   Anwendung:                                                       
 *   =========                                                        
 *      Beliebige Polynome mit komplexen Koeffizienten.						<br>
 *      Ist das Polynom schlecht konditioniert (kleine Aenderungen in den 
 *		Koeffizienten fuehren zu grossen Aenderungen in den Nullstellen),so 
 *		sollte das Polynom nicht skaliert werden;							<br>
 *      ansonsten ist eine Skalierung fuer Stabilitaet und Performance von Vorteil.                                            
 *
 *																			<br>
 *																			<br><br>
 *   Eingabeparameter:														<br>
 *   ================														<br>
 *      real     int real;													<br>
 *        = 0    Polynomkoeffizienten sind komplex							<br>
 *       != 0    Polynomkoeffizienten sind reell							<br>
 *      scale    int scale;													<br>
 *        = 0    keine Skalierung											<br>
 *       != 0    Skalierung des Polynoms, s. polysc()						<br>
 *      n        int n;														<br>
 *               Grad des Polynoms ( >= 1 )									<br>
 *      ar, ai   REAL   ar[], ai[];											<br>
 *               Real-/Imaginaerteile der Polynomkoeffizienten				<br>
 *               ( ar[0],..,ar[n] )											<br>
 *																			<br><br>
 *   Ausgabeparameter:														<br>
 *   ================														<br>
 *      rootr    REAL   rootr[];   (Vektor der Laenge n+1 !!!)				<br>
 *               rootr[0],..,rootr[n-1] sind die Realteile der				<br>
 *               n Nullstellen												<br>
 *      rooti    REAL   rooti[];   (Vektor der Laenge n+1 !!!)				<br>
 *               rooti[0],..,rooti[n-1] enthalten die Imaginaerteile		<br>
 *               der berechneten Nullstellen								<br>
 *      absf     REAL   absf[];												<br>
 *               absf[0],..,absf[n-1] sind die Absolutbetraege				<br>
 *               der Polynomwerte an den gefundenen Nullstellen				<br><br>
 *																			<br>
 *   Rueckgabewert:															<br>
 *   =============															<br>
 *      = 0      alles ok													<br>
 *      = 1      n < 1 oder ungueltige Eingabeparameter						<br>
 *      = 2      ar[n] = 0.0 und ai[n] = 0.0 gewaehlt						<br>
 *      = 3      Iterationsmaximum ITERMAX ueberschritten					<br><br>
 *                                                                    
 *   Benutzte Funktionen:													<br>
 *   ===================													<br>
 *     bauroot():   Bestimmt eine Nullstelle des Polynoms					<br>
 *     scpoly():    Skaliert das Polynom									<br>
 *     chorner():   Berechnung des Polynomwerts								<br>
 *     polydiv():   Abdividieren einer Nullstelle							<br>
 *     comabs():      Komplexer Absolutbetrag								<br>
 */
int bauhub( int real, int scale, int n, REAL ar[], REAL ai[],
            REAL rootr[], REAL rooti[], REAL absf[] )
{
  int    i, res;
  REAL x0r, x0i, tempr, tempi, t1, t2, t3, t4, t5;
  REAL scalefak = ONE;

  if (n < 1) return (1);

  if (ar == NULL || ai == NULL) return (1);
  if (rootr == NULL || rooti == NULL) return (1);

  if (ar[n] == ENGELN_ZERO && ai[n] == ENGELN_ZERO)			/* Fuehrender Koeffizient muss */
    return (2);												/* verschieden von 0 sein      */

  for (i = 0; i <= n; i++)									/* Kopiere die Originalkoeffizien- */
  {															/* ten auf root                    */
    rootr[i] = ar[i];
    rooti[i] = ai[i];
    if (i < n) absf[i] = ENGELN_ZERO;
  }

  scalefak = ONE;
  if (scale)												/* Skaliere Polynom, falls gewuenscht */
    scpoly (n, rootr, rooti, &scalefak);

  x0r = ENGELN_ZERO;                                           /* Startwert */
  x0i = ENGELN_ZERO;

  for (i = 0; i < n; i++)
  {															/* i-te Nullstelle berechnen */
    res = bauroot (n, i, rootr, rooti, &x0r, &x0i);

    rootr[i] = scalefak * x0r;								/* Nullstelle merken */
    rooti[i] = scalefak * x0i;

    if (res) return (3);									/* Iterationsmaximum erreicht */

    /* Polynomwert des Originalpolynoms an (rootr[i], rooti[i])       */

    chorner (n, 0, ar, ai, rootr[i], rooti[i],
             &tempr, &tempi, &t1, &t2, &t3, &t4, &t5);

    absf[i] = comabs (tempr, tempi);						/* Fehler merken      */

    polydiv (n, i, rootr, rooti, x0r, x0i);					/* Abdividieren       */

    if (real)												/* Neuer Startwert in Abhaen- */
      x0i = -x0i;											/* gigkeit von real           */
    else
      x0r = x0i = ENGELN_ZERO;
  }

  return (0);
}



/**
 * @param n			int,  Vektorlaenge
 * @param ar[]		REAL, Realteile des Vektors
 * @param ai[]		REAL, Imaginaerteile des Vektors
 * @param scal		REAL, Skalierungsfaktor
 * @brief Skaliert das Polynom P
 *
 * Skaliert das Polynom P mit												<br><br>
 *
 *      P(x) = a[0] + a[1] * x + ... + a[n-1] * x^(n-1)    + a[n] * x^n ,	<br><br>
 *
 *  wobei a[i], i=0..n, komplex sind.										<br><br>
 *
 *   Eingabeparameter:														<br>
 *   ================                                                 		<br>
 *      n        int n;														<br>
 *               Grad des Polynoms ( >= 1 )                           		<br>
 *      ar, ai   REAL   ar[], ai[];                                   		<br>
 *               Real-/Imaginaerteile der Koeffizienten a[0],..,a[n]  		<br>
 *                                                                    		<br><br>
 *   Ausgabeparameter:                                                		<br>
 *   ================                                                 		<br>
 *      ar, ai   REAL   ar[], ai[];                                   		<br>
 *               Real-/Imaginaerteile der Koeffizienten a[0],..,a[n]  		<br>
 *               des skalierten Polynoms.                             		<br>
 *      scal     REAL   *scal;                                        		<br>
 *               Skalierungsfaktor                                    		<br><br>
 *
 *   Benutzte Funktionen:                                             		<br>
 *   ===================                                              		<br>
 *      comabs():  Komplexer Absolutbetrag                            		<br>
 *                                                                    		<br>
 *   Aus der C - Bibliothek: pow()                                    		<br>
 *                                                                    		<br>
 *   Macros:     max                                                  		<br>
 */
static void scpoly( int n, REAL ar[], REAL ai[], REAL* scal )
{
  REAL p, pot;
  int    i;

  *scal = ENGELN_ZERO;
														/* scal =                                */
  p = comabs (ar[n], ai[n]);							/*               a[i]  1/(n-i)           */
  for (i = 0; i < n; i++)								/*    max{ cabs( ---- )       ,i=0..n-1} */
														/*               a[n]                    */
    if (ar[i] != ENGELN_ZERO || ai[i] != ENGELN_ZERO)
    {
      ai[i] /= p;
      ar[i] /= p;

      pot = POW (comabs (ar[i],ai[i]), 1.0/(n-i));
      *scal = ENGELN_max (*scal, pot);
    }

  ar[n] /= p;											/* Betrag von a[n] = 1                   */
  ai[n] /= p;

  if (*scal == ENGELN_ZERO) *scal = ONE;

  for (p = ONE, i = n-1; i >= 0; i--)
  {
    p *= *scal;											/*                    n-i              */
    ar[i] /= p;											/* a[i] = a[i] / (scal    ), i=0..n-1  */
    ai[i] /= p;											/*                                     */
  }
}



/**
 * @param n			int,  Hoechster Polynomkoeff
 * @param iu		int,  Niedrigster Polynomkoeff 
 * @param ar[]		REAL, Realteile Koeffizienten
 * @param ai[]		REAL, Imaginaerteile Koeffizienten
 * @param xr		REAL, Realteil x
 * @param xi		REAL, Imaginaerteil x
 * @param pr		REAL, Realteil Funktionswert
 * @param pi		REAL, Imaginaerteil Funktionswert
 * @param p1r		REAL, Realteil 1. Ableitung
 * @param p1i		REAL, Imaginaerteil 1. Ableitung
 * @param p2r		REAL, Realteil 2. Ableitung
 * @param p2i		REAL, Imaginaerteil 2. Ableitung
 * @param rf1		REAL, Fehlerschaetzung 1. Ableitung
 * @brief Komplexes Hornerschema
 *
 *  Hornerschema fuer Polynome mit komplexen Koeffizienten; berechnet			<br>
 *  werden:																		<br>
 *    1. Polynomwert des Polynoms P (komplex) vom Grade n - iu,    				<br>
 *    2. die 1. Ableitung,														<br>
 *    3. die 2. Ableitung an der Stelle x,                            			<br>
 *    4. eine Fehlerschaetzung der 1. Ableitung.                      			<br>
 *																				<br>
 *   Eingabeparameter:                                                			<br>
 *   ================                                                 			<br>
 *      n        int n;                                               			<br>
 *               Maximalgrad des Polynoms ( >= 1 )                    			<br>
 *      ar, ai   REAL   ar[], ai[];                                   			<br>
 *               Real-/Imaginaerteile der Koeffizienten des Polynoms  			<br>
 *               mit Koeffizienten a[iu],..,a[n]                      			<br>
 *      x0r,x0i  REAL   x0r, x0i;                                     			<br>
 *               Real-/Imaginaerteil der Auswertungsstelle            			<br>
 *                                                                    			<br>
 *   Ausgabeparameter:                                                			<br>
 *   ================                                                 			<br>
 *      pr, pi   REAL   *pr, *pi;                                     			<br>
 *               Real-/Imaginaerteil des Polynomwerts                 			<br>
 *      p1r, p1i REAL   *p1r, *p1i;                                   			<br>
 *               Real-/Imaginaerteil der 1. Ableitung                 			<br>
 *      p2r, p2i REAL   *p2r, *p2i;                                   			<br>
 *               Real-/Imaginaerteil der 2. Ableitung                 			<br>
 *      rf1      REAL   *rf1;                                         			<br>
 *               Fehlerschaetzung fuer die 1. Ableitung               			<br>
 *                                                                    			<br>
 *   Benutzte Funktionen:                                             			<br>
 *   ===================                                              			<br>
 *     comabs():    Komplexer Absolutbetrag                           			<br>
 *     pow ():      Potenzfunktion                                    			<br>
 *																				<br>
 *   Benutzte Konstanten:  EPS                                        			<br>
 */
static void chorner( int n, int iu, REAL ar[], REAL ai[], REAL xr, REAL xi, REAL*  pr, REAL* pi, 
                     REAL* p1r, REAL* p1i, REAL* p2r, REAL* p2i, REAL* rf1 )
{
  int i, j;
  int      i1;
  REAL   temp, temp1;

  *p2r = ar[n];
  *p2i = ai[n];

  *pr = *p1r = *p2r;
  *pi = *p1i = *p2i;

  *rf1 = comabs (*pr, *pi);
  i1 = n - iu;

  for (j = n - iu, i = n - 1; i >= iu; i--, j--)
  {
    temp = *pr;                        /* Polynomwert (pr,pi)         */
    *pr = *pr * xr - *pi * xi + ar[i];
    *pi = *pi * xr + temp * xi + ai[i];
    if ( i == iu ) break;

    temp = *p1r;                       /* 1. Ableitung (p1r,p1i)      */
    *p1r = *p1r * xr - *p1i * xi;
    *p1i = *p1i * xr + temp * xi;

    temp = comabs (*p1r, *p1i);        /* Fehlerschaetzung fuer die   */
    *p1r += *pr;                       /* Ableitung des Polynoms      */
    *p1i += *pi;

    temp1 = comabs (*pr, *pi);
    temp = ENGELN_max (temp, temp1);
    if ( temp > *rf1 )
    {
      *rf1 = temp;
      i1 = j - 1;
    }

    if (i - iu <= 1) continue;

    temp = *p2r;                       /* 2. Ableitung (p2r,p2i)      */
    *p2r = *p2r * xr - *p2i * xi + *p1r;
    *p2i = *p2i * xr + temp * xi + *p1i;
  }

  temp = comabs (xr, xi);
  if ( temp != ENGELN_ZERO )
    *rf1 *= POW (temp, (REAL) i1) * (i1 + 1);
  else
    *rf1 = comabs (*p1r, *p1i);

  *rf1 *= EPS;

  *p2r += *p2r;
  *p2i += *p2i;
}




/**
 * @param n			int,  Hoechstgrad
 * @param iu		int,  Niedrigster Grad
 * @param ar[]		REAL, Realteile Koeffizienten
 * @param ai[]		REAL, Imaginaerteile Koeffizienten
 * @param x0r		REAL, Realteil Nullstelle
 * @param x0i		REAL, Imaginaerteil Nullstelle
 * @brief Berechnet eine Nullstelle des Polynoms P vom Grad n-iu
 *
 *  Berechnet eine Nullstelle des Polynoms P vom Grad n-iu:						<br>
 *														            			<br>
 *      P(x) = a[iu] + a[iu+1] * x + ... + a[n] * x^(n-iu)						<br>
 *																				<br>
 *	mit																			<br>
 *                                                                    			<br>
 *  komplexen Koeffizienten a[i], i=iu..n.                            			<br>
 *  Dabei wird das Newtonverfahren auf die Funktion P(x) / P'(x) angewandt, 	<br>
 *  die Iteration durch Spiralisierung und Extrapolation stabilisiert. 			<br>
 *																				<br>
 *   Eingabeparameter:                                                			<br>
 *   ================                                                 			<br>
 *      n        int n;                                               			<br>
 *               Maximalgrad des Polynoms ( >= 1 )                    			<br>
 *      iu       int iu;                                              			<br>
 *               Index des konstanten Terms im Polynom, n-iu ist der  			<br>
 *               Grad des Polynoms mit Koeff. a[iu],...,a[n]          			<br>
 *      ar, ai   REAL   ar[], ai[];                                   			<br>
 *               Real-/Imaginaerteile der Koeffizienten               			<br>
 *                                                                    			<br>
 *   Ausgabeparameter:                                                			<br>
 *   ================                                                 			<br>
 *      x0r,x0i  REAL   *x0r, x0i;                                    			<br>
 *               Real-/Imaginaerteil der gefundenen Nullstelle        			<br>
 *                                                                    			<br>
 *   Rueckgabewert:                                                   			<br>
 *   =============                                                    			<br>
 *      = 0      alles ok                                             			<br>
 *      = 1      Division durch 0                                     			<br>
 *      = 2      Iterationsmaximum ITERMAX ueberschritten             			<br>
 *      = 3      Unzulaessige Eingabeparameter                        			<br>
 *                                                                    			<br>
 *   Benutzte Funktionen:                                             			<br>
 *   ===================                                              			<br>
 *     chorner():   Berechnung des Polynomwerts                       			<br>
 *     comabs():    Komplexer Absolutbetrag                           			<br>
 *     comdiv():    Komplexe Division                                 			<br>
 *     quadsolv():  Quadratische Gleichung loesen                     			<br>
 *                                                                    			<br>
 *   Benutzte Konstanten: TRUE, FALSE, ITERMAX,                       			<br>
 *   ===================  QR, QI, MACH_EPS, EPS, EPSROOT, BETA        			<br>
 */
static int bauroot( int n, int iu, REAL ar[], REAL ai[], REAL* x0r, REAL*  x0i )
{
  int  rc, result = 2, 
       iter = 0, i = 0;

  int endit = false;

  REAL xoldr = ENGELN_ZERO, xoldi = ENGELN_ZERO,
       xnewr, xnewi, h, h1, h2, h3, h4, dzmax, dzmin,
       dxr = ENGELN_ZERO, dxi = ENGELN_ZERO, tempr, tempi,
       abs_pold, abs_pnew, abs_p1new, temp, ss, u, v, bdze = ENGELN_ZERO,
       pr, pi, p1r, p1i, p2r, p2i;

  if (n < 1) return (3);

  if (n - iu == 1)													/* Polynom vom Grad 1    */
  {
    quadsolv (ENGELN_ZERO, ENGELN_ZERO, ar[n], ai[n], ar[n-1], ai[n-1], x0r, x0i);
    return (0);
  }

  if (n - iu == 2)													/* Polynom vom Grad 2    */
  {
    quadsolv (ar[n],ai[n], ar[n-1],ai[n-1], ar[n-2],ai[n-2], x0r,x0i);
    return (0);
  }

  xnewr = *x0r;  xnewi = *x0i;
  endit = false;

  chorner (n, iu, ar, ai, xnewr, xnewi,								/* Polynomwert berechnen  */
           &pr, &pi, &p1r, &p1i, &p2r, &p2i, &ss);
  iter++;

  abs_pnew = comabs (pr, pi);
  if (abs_pnew < EPS) return (0);									/* Startwert ist gute Naeherung */

  abs_pold = abs_pnew;
  dzmin = BETA * (EPSROOT + comabs (xnewr, xnewi));

  while ( iter < ITERMAX )											/* Bauhuber-Iteration */
  {
    abs_p1new = comabs (p1r, p1i);

    if (abs_pnew > abs_pold)										/* Spiralisierungsschritt */
    {
      i = 0;														/* dx = dx * q            */
      iter++;
      temp = dxr;

      dxr = QR * dxr - QI * dxi;
      dxi = QR * dxi + QI * temp;
    }
    else
    {
      dzmax = ONE + comabs (xnewr, xnewi);
      h1 = p1r * p1r - p1i * p1i - pr * p2r + pi * p2i;
      h2 = TWO * p1r * p1i - pr * p2i - pi * p2r;
      if (    abs_p1new > (REAL)10.0 * ss
           && comabs (h1, h2) > (REAL)100.0 * ss * ss)
      {
        i++;
        if ( i > 2 ) i = 2;
        tempr = pr * p1r - pi * p1i;
        tempi = pr * p1i + pi * p1r;

        rc = comdiv (-tempr, -tempi, h1, h2, &dxr, &dxi);
        if (rc != 0) return (1);

        if ( comabs (dxr, dxi) > dzmax )
        {
          temp = dzmax / comabs (dxr, dxi);							/* Newton-Schritt   */
          dxr *= temp;
          dxi *= temp;
          i = 0;
        }

        if (   i == 2
            && comabs (dxr, dxi) < dzmin / EPSROOT
            && comabs (dxr, dxi) > ENGELN_ZERO)
        {
          i = 0;													/* Extrapolationsschritt  */
          rc = comdiv (xnewr - xoldr, xnewi - xoldi,
                                   dxr, dxi, &h3, &h4);
          if (rc != 0) return (1);

          h3 += ONE;
          h1 = h3 * h3 - h4 * h4;
          h2 = TWO * h3 * h4;
          rc = comdiv (dxr, dxi, h1, h2, &h3, &h4);
          if (rc != 0) return (1);

          if ( comabs (h3, h4) < (REAL)50.0 * dzmin )
          {
            dxr += h3;
            dxi += h4;
          }
        }

        xoldr = xnewr;
        xoldi = xnewi;
        abs_pold = abs_pnew;
      }
      else
      {
        i = 0;														/* Sattelpunktnaehe       */
        h = dzmax / abs_pnew;
        dxr = h * pr;
        dxi = h * pi;

        xoldr = xnewr;
        xoldi = xnewi;
        abs_pold = abs_pnew;

        do
        {
          chorner (n, iu, ar, ai, xnewr+dxr, xnewi+dxi,
                         &u, &v, &h, &h1, &h2, &h3, &h4);
          iter++;

          dxr += dxr;
          dxi += dxi;												/* dx = dx * 2.0         */
        }
        while ( ABS (comabs (u,v) / abs_pnew - ONE) < EPSROOT );
      }
    }

    if (endit)
    {
      if ( comabs (dxr, dxi) < (REAL)0.1 * bdze )
      {
        xnewr += dxr;  xnewi += dxi;
      }

      result = 0;
      break;														/* Iteration beenden */
    }
    else
    {
      xnewr = xoldr + dxr;
      xnewi = xoldi + dxi;
      dzmin = BETA * (EPSROOT + comabs (xnewr, xnewi));
      chorner (n, iu, ar, ai, xnewr, xnewi,
               &pr, &pi, &p1r, &p1i, &p2r, &p2i, &ss);
      iter++;
      abs_pnew = comabs ( pr, pi);

      if (abs_pnew == ENGELN_ZERO)
      {
        result = 0;
        break;
      }

      if (comabs (dxr, dxi) < dzmin || abs_pnew < EPS)
      {
        endit = true;
        bdze = comabs (dxr, dxi);
      }
    }
  } /* Ende Bauhuber-Iteration */

  *x0r = xnewr;
  *x0i = xnewi;

  return (result);
}

/**
 * @param n			int,  Hoechstgrad
 * @param iu		int,  Niedrigster Grad
 * @param ar[]		REAL, Realteile Koeffizienten
 * @param ai[]		REAL, Imaginaerteile Koeffizienten
 * @param x0r		REAL, Realteil Nullstelle
 * @param x0i		REAL, Imaginaerteil Nullstelle
 * @brief Berechnet die Koeffizienten des Polynoms Q, das durch
 *                                                                    			<br>
 *  polydiv berechnet die Koeffizienten des Polynoms Q, das durch     			<br>
 *  Division des Polynoms P durch x - x0 entsteht, falls x0 eine      			<br>
 *  Nullstelle von P ist: P(x) = Q(x) * ( x - x0 ). Alle Groessen     			<br>
 *  sind komplex.                                                     			<br>
 *                                                                    			<br>
 *   Eingabeparameter:                                                			<br>
 *   ================                                                 			<br>
 *      n        int n;                                               			<br>
 *               Maximalgrad des Polynoms ( >= 1 )                    			<br>
 *      ar, ai   REAL   ar[], ai[];                                   			<br>
 *               Real-/Imaginaerteile der Koeffizienten des Polynoms  			<br>
 *               P vom Grade n-iu mit a[iu],..,a[n]                   			<br>
 *      x0r,x0i  REAL   x0r, x0i;                                     			<br>
 *               Real-/Imaginaerteil der abzudividierenden Nullstelle 			<br>
 *                                                                    			<br>
 *   Ausgabeparameter:                                                			<br>
 *   ================                                                 			<br>
 *      ar, ai   REAL   ar[], ai[];                                   			<br>
 *               Real-/Imaginaerteile der Koeffizienten               			<br>
 *               ar[iu+1],..,ar[n] des Quotientenpolynoms Q           			<br>
 */
static void polydiv( int n, int iu, REAL ar[], REAL ai[], REAL x0r, REAL x0i )
{
  int i;
  REAL     temp;

  for (i = n - 1; i > iu; i--)
  {
    temp = ar[i+1];
    ar[i] += temp * x0r - ai[i+1] * x0i;
    ai[i] += ai[i+1] * x0r + temp * x0i;
  }
}




/* ------------------------- ENDE fbauhube.c ------------------------ */
