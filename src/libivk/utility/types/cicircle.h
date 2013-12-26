#ifndef cicircle_hpp
#define cicircle_hpp

#include <complex.hpp>
#include <real.hpp>
#include <cinterval.hpp>
#include <interval.hpp>

using namespace std;
using namespace cxsc;

namespace ivk {

class cicircle
{
private:
	complex midpoint;
	real radius;

public:

//--Konstruktoren------------------------------------------------------------

	cicircle();
	cicircle(complex m, real r);
	cicircle(complex m);
	cicircle(real m);
	cicircle(real m, real r);

//--Typumwandlungskonstruktoren fuer Intervalle------------------------------

    cicircle(cinterval i);
    cicircle(interval i);

//--Assignments--------------------------------------------------------------

    cicircle operator =(cicircle);
    cicircle operator =(complex);
    cicircle operator =(real);
    cicircle operator =(cinterval);
    cicircle operator =(interval);

//	cinterval operator =(cicircle, cinterval);

//--Ein-/Ausgabe-------------------------------------------------------------

    friend std::ostream & operator <<(std::ostream &,const cicircle &);
    friend std::istream & operator >>(std::istream &,cicircle &);
    friend std::string &  operator <<(std::string &,const cicircle &);
    friend std::string &  operator >>(std::string &,cicircle &);
    friend void           operator >>(const char *,cicircle &);
    friend void           operator >>(const std::string &,cicircle &);

//--Operatoren---------------------------------------------------------------
    friend cicircle operator -(cicircle);
    friend cicircle operator +(cicircle);

    friend cicircle operator +(cicircle, cicircle);
    friend cicircle operator -(cicircle, cicircle);
    friend cicircle operator *(cicircle, cicircle);
    friend cicircle operator /(cicircle, cicircle);

    friend cicircle operator +(cicircle, complex);
    friend cicircle operator +(complex, cicircle);
    friend cicircle operator -(cicircle, complex);
    friend cicircle operator -(complex, cicircle);
    friend cicircle operator *(cicircle, complex);
    friend cicircle operator *(complex, cicircle);
    friend cicircle operator /(cicircle, complex);
    friend cicircle operator /(complex, cicircle);


    cicircle operator +=(cicircle);
    cicircle operator -=(cicircle);
    cicircle operator *=(cicircle);
    cicircle operator /=(cicircle);

    cicircle operator +=(complex);
    cicircle operator -=(complex);
    cicircle operator *=(complex);
    cicircle operator /=(complex);

//--Vergleichs-Operatoren----------------------------------------------------

    friend bool operator!  (const cicircle & a);
    friend bool operator== (const cicircle & a, const cicircle & b);
    friend bool operator!= (const cicircle & a, const cicircle & b);
    friend bool operator== (const cicircle & a, const complex & b);
    friend bool operator== (const complex & a, const cicircle & b);
    friend bool operator!= (const cicircle & a, const complex & b);
    friend bool operator!= (const complex & a, const cicircle & b);


//--Methoden-----------------------------------------------------------------
    void setmidpoint(complex m);
    void setradius(real r);
    complex getmidpoint() const;
    real getradius() const;
    void ausgeben();
    cinterval umwandeln() const;
    friend cicircle conj(cicircle);
    friend cicircle kehrwert(cicircle);

};

}
#endif  // cicircle_hpp
