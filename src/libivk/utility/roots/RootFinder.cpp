#include "RootFinder.h"

// Interne Includes
#include "CIPZero.h"
#include <cipoly.hpp>
#include <stdexcept>
#include <cstring>
#include "utility/CPolynomialUtils.h"

using cxscx::CIPZero;

namespace ivk {

RPolynomial RootFinder::splitOffRootAt1(const RPolynomial &poly)
{
	RPolynomial ret(poly.lowerBound(), poly.upperBound()-1);

	const int n = poly.upperBound();
	for(int k = ret.lowerBound(); k<=ret.upperBound(); ++k)
	{
		real a = 0.0;
		for(int j=k+1; j<=n; ++j)
			a += poly.at(j);
		ret[k] = a;
	}
	return ret;
}

/*
 * Wraps implementation of Mueller root finding algorithm.
 */
cvector RootFinder::rootsMueller(const RPolynomial &poly)
{
	const int n = poly.degree();
	void *vmblock;
    vmblock = vminit();
    REAL* polynom = (REAL *)vmalloc( vmblock, VEKTOR, n + 1, 0 ); // fuer Mueller/Bauhuber

    for (int i = 0; i <= poly.degree(); i++)
    {
        polynom[i] = _double(poly.at(i));
    }

    cvector z(1,n);

   //:> Bereitstellung der Daten fuer den Root-Finder
    REAL *zreal, *zimag, *ai, *val; //, fre, fim;  // Variablen fuer den Root-Finder
    int rc, zaehl = 0, scale = 0;

    vmblock = vminit();
    zreal = (REAL *)vmalloc(vmblock, VEKTOR, n + 1, 0); // Realteil der Loesungen
    zimag = (REAL *)vmalloc(vmblock, VEKTOR, n + 1, 0); // Imaginaerteil der Loesungen
    ai    = (REAL *)vmalloc(vmblock, VEKTOR, n + 1, 0); // fuer Bauhuber
    val   = (REAL *)vmalloc(vmblock, VEKTOR, n + 1, 0); // fuer Bauhuber

    SetVec (n + 1, ai, 0.0);                            // fuer Bauhuber

    rc = mueller (n, polynom, scale, zreal, zimag);
    if (rc)
    	throw std::runtime_error("Error has occurred (Mueller).");
    for (int i = 0; i < n; i++)
    {
       //:> Ausgabe in Zieldatei und zaehlen der Nullstellen im Einheitskreis != 0
        complex hilf(zreal[i], zimag[i]);
        zaehl++;
        z[zaehl] = hilf;
    } // end for
    return z;
}

/*
 * Wraps implementation of Bauhuber root finding algorithm.
 */
cvector RootFinder::rootsBauhuber(const RPolynomial &poly)
{
	const int n = poly.degree();
	void *vmblock;
    vmblock = vminit();
    REAL* polynom = (REAL *)vmalloc( vmblock, VEKTOR, n + 1, 0 ); // fuer Mueller/Bauhuber

    for (int i = 0; i <= poly.degree(); i++)
    {
        polynom[i] = _double(poly.at(i));
    }

    cvector z(1,n);

   //:> Bereitstellung der Daten fuer den Root-Finder
    REAL *zreal, *zimag, *ai, *val; //, fre, fim;  // Variablen fuer den Root-Finder
    int rc, zaehl = 0, scale = 0;

    vmblock = vminit();
    zreal = (REAL *)vmalloc(vmblock, VEKTOR, n + 1, 0); // Realteil der Loesungen
    zimag = (REAL *)vmalloc(vmblock, VEKTOR, n + 1, 0); // Imaginaerteil der Loesungen
    ai    = (REAL *)vmalloc(vmblock, VEKTOR, n + 1, 0); // fuer Bauhuber
    val   = (REAL *)vmalloc(vmblock, VEKTOR, n + 1, 0); // fuer Bauhuber

    SetVec (n + 1, ai, 0.0);                            // fuer Bauhuber

    rc = bauhub (0, scale, n, polynom, ai, zreal, zimag, val);
    if (rc)
    	throw std::runtime_error("Error has occurred (Bauhuber).");

    for (int i = 0; i < n; i++)
    {
       //:> Ausgabe in Zieldatei und zaehlen der Nullstellen im Einheitskreis != 0
        complex hilf(zreal[i], zimag[i]);
        zaehl++;
        z[zaehl] = hilf;
    } // end for
    return z;
}

cvector RootFinder::rootsLapack(const RPolynomial &poly)
{
	const int degree = poly.degree();
	cvector polyCoefficients(0, poly.degree());
	for (int i = Lb(polyCoefficients); i<= Ub(polyCoefficients); ++i)
	{
		polyCoefficients[i] = cxsc::complex(poly.at(degree-i), 0.0);
	}
	return CPolynomialUtils::roots(polyCoefficients);
}

/*
 * Deflates polynomial (Removes roots at zero).
 */
RPolynomial RootFinder::deflatePolynomial(const RPolynomial &poly)
{
	int multi = 0;
	while(poly.at(multi) == 0)
	{
		multi++;
	}
	int degree = poly.degree();
	while(poly.at(degree) == 0)
	{
		degree--;
	}
	RPolynomial ret(degree-multi);
	for(int i=degree; i>=multi; i--)
	{
		ret[i-multi] = poly.at(i);
	}
	return ret;
}

/*
 * Wraps implementation of automatic generation of approximations.
 */
cvector RootFinder::rootsSphere(const RPolynomial &p, const int number)
{
	const int n = p.degree();

	// Find radius
    ::CIPolynomial p_red(n-1);
    interval help;
    help = p.at(n);

    for (int i = n-1; i >= 0; i--)
    {
    	p_red[i] = help;
        help += p.at(i);
    }

    real radius;
    complex z;
    ::CIPolynomial qq(n-2);
    cinterval zz;
    int Err = 0;
    Re(z) = 1.0;
    Im(z) = 0;
    CIPZero rootFinder;

    rootFinder.getCIPolyZero( p_red, z, qq, zz, Err );
	if (!Err)
    	radius = mid(Re(zz));
    else
    	cerr << "Uh-Oh. Radius for automatic approximations: " << radius << endl;

	// Generate approximations
	const double Pi = 3.141592;
	cvector approx(number+1);
	Re(approx[number+1]) = 1.0;
	Im(approx[number+1]) = 0.0;
	for(int i=0;i<number;i++)
	{
		double argument = ((double)i/number)*2.0*Pi;
		Re(approx[i+1]) = radius * sin(argument);
		Im(approx[i+1]) = radius * cos(argument);
	}
	return approx;
}

}

