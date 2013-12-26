#include "cicircle.h"
#include <stdexcept>

using namespace cxsc;
using namespace std;

namespace ivk {

//--Konstruktoren--------------------------------------------------------------
cicircle::cicircle() {}

cicircle::cicircle(complex m, real r)
{
	midpoint = m;
	radius = r;
}

cicircle::cicircle(complex m)
{
	midpoint = m;
	radius = 0.0;
}

cicircle::cicircle(real m)
{
	midpoint = m;
	radius = 0.0;
}

cicircle::cicircle(real m, real r)
{
	midpoint = m;
	radius = r;
}

//--Typumwandlungskonstruktoren fuer Intervalle--------------------------------

cicircle::cicircle(cinterval i)
{
	cinterval hilfe;
	interval abstand;

	// Fr den Radius: Feststellen der grten Entfernung
	// zu einer der vier Intervall-Ecken
	midpoint = mid(i);
	if (Re(midpoint) - Inf(Re(i)) > Sup(Re(i)) - Re(midpoint))
		Re(hilfe) = Re(midpoint) - Inf(Re(i));
	else
		Re(hilfe) = Sup(Re(i)) - Re(midpoint);

	if (Im(midpoint) - Inf(Im(i)) > Sup(Im(i)) - Im(midpoint))
		Im(hilfe) = Im(midpoint) - Inf(Im(i));
	else
		Im(hilfe) = Sup(Im(i)) - Im(midpoint);

	abstand = abs(hilfe);
	// Bestimmung des neuen Radius als grter Abstand zu Intervall-Ecken
	radius = Sup(abstand);
}

cicircle::cicircle(interval i)
{
	cinterval ii;
	Re(ii) = i;
	Im(ii) = 0;
	cicircle neu(ii);
	midpoint = neu.midpoint;
	radius = neu.radius;
}

//--Assignments--------------------------------------------------------------
cicircle cicircle::operator=(cicircle a)
{
	midpoint = a.midpoint;
	radius = a.radius;
	return *this;
}

cicircle cicircle::operator=(complex c)
{
	midpoint = c;
	radius = 0.0;
	return *this;
}

cicircle cicircle::operator=(real m)
{
	cicircle tmp(m);
	midpoint = tmp.midpoint;
	radius = tmp.radius;
	return *this;
}

cicircle cicircle::operator=(cinterval ci)
{
	cicircle tmp(ci);
	midpoint = tmp.midpoint;
	radius = tmp.radius;
	return *this;

}

cicircle cicircle::operator=(interval i)
{
	cicircle tmp(i);
	midpoint = tmp.midpoint;
	radius = tmp.radius;
	return *this;
}

/*cinterval operator=(cicircle ii, cinterval i)
{
	//cinterval tmp;
	i = ii.umwandeln();
	return i;
}*/
// funktioniert so nicht...


//--Ein-/Ausgabe---------------------------------------------------------------

std::ostream & operator << (std::ostream &s, const cicircle& a)
{
	s << '<'
   	  << a.midpoint << ','
	  << a.radius
	  << '>';
	return s;
}

std::string & operator << (std::string &s, const cicircle &a)
{
	s+='<';
	s << a.midpoint;
	s+=',';
	s << a.radius;
	s+='>';
	return s;
}


std::istream & operator >> (std::istream &s, cicircle &a)
{
	char c;

	skipeolnflag = inpdotflag = true;
	c = skipwhitespacessinglechar (s, '<');
	if (inpdotflag)
		s.putback(c);

	s >> a.midpoint;

	skipeolnflag = inpdotflag = true;
	c = skipwhitespacessinglechar (s, ',');
	if (inpdotflag) s.putback(c);

	s >> a.radius >> RestoreOpt;

	if (!waseolnflag)
	{
		skipeolnflag = false, inpdotflag = true;
		c = skipwhitespaces (s);
		if (inpdotflag && c != '>')
			s.putback(c);
	}
	return s;
}

std::string & operator >> (std::string &s, cicircle &a)
{
	s = skipwhitespacessinglechar (s, '<');
	s >> SaveOpt >> RndDown >> a.midpoint;
	s = skipwhitespacessinglechar (s, ',');
	s >> RndUp >> a.radius >> RestoreOpt;
	s = skipwhitespaces (s);

	if (s[0] == '>')
		s.erase(0,1);
	return s;
}

void operator >>(const std::string &s,cicircle &a)
{
	std::string r(s);
	r>>a;
}

void operator >>(const char *s,cicircle &a)
{
	std::string r(s);
	r>>a;
}

//--Operatoren---------------------------------------------------------------

cicircle operator -(cicircle a)
{
	return cicircle(-a.midpoint, a.radius);
}

cicircle operator +(cicircle a)
{
	return a;
}

cicircle operator+(cicircle a, cicircle b)
{
	cicircle tmp;
	cinterval mittea, mitteb, hilfe;
	interval abstand, radiusa, radiusb, hilferadius;

	// Bestimmung des neuen Mittelpunkts
	mittea = a.midpoint;
	mitteb = b.midpoint;
	mittea += mitteb;
	tmp.midpoint = mid(mittea);

	// Fr den Radius: Feststellen der grten Entfernung
	// zu einer der vier Intervall-Ecken
	if (Re(tmp.midpoint) - Inf(Re(mittea)) > Sup(Re(mittea)) - Re(tmp.midpoint))
		Re(hilfe) = Re(tmp.midpoint) - Inf(Re(mittea));
	else
		Re(hilfe) = Sup(Re(mittea)) - Re(tmp.midpoint);

	if (Im(tmp.midpoint) - Inf(Im(mittea)) > Sup(Im(mittea)) - Im(tmp.midpoint))
		Im(hilfe) = Im(tmp.midpoint) - Inf(Im(mittea));
	else
		Im(hilfe) = Sup(Im(mittea)) - Im(tmp.midpoint);

	abstand = abs(hilfe);
	// Bestimmung des neuen Radius als Summe der alten Radien + Fehler
	radiusa = a.radius;
	radiusb = b.radius;
	hilferadius = radiusa + radiusb + abstand;
	tmp.radius = Sup(hilferadius);
	return tmp;
}

cicircle operator-(cicircle a, cicircle b)
{
	cicircle tmp;
	cinterval mittea, mitteb, hilfe;
	interval abstand, radiusa, radiusb, hilferadius;

	// Bestimmung des neuen Mittelpunkts
	mittea = a.midpoint;
	mitteb = b.midpoint;
	mittea -= mitteb;
	tmp.midpoint = mid(mittea);

	// Fr den Radius: Feststellen der grten Entfernung
	// zu einer der vier Intervall-Ecken
	if (Re(tmp.midpoint) - Inf(Re(mittea)) > Sup(Re(mittea)) - Re(tmp.midpoint))
		Re(hilfe) = Re(tmp.midpoint) - Inf(Re(mittea));
	else
		Re(hilfe) = Sup(Re(mittea)) - Re(tmp.midpoint);

	if (Im(tmp.midpoint) - Inf(Im(mittea)) > Sup(Im(mittea)) - Im(tmp.midpoint))
		Im(hilfe) = Im(tmp.midpoint) - Inf(Im(mittea));
	else
		Im(hilfe) = Sup(Im(mittea)) - Im(tmp.midpoint);

	abstand = abs(hilfe);
	// Bestimmung des neuen Radius als Summe der alten Radien + Fehler
	radiusa = a.radius;
	radiusb = b.radius;
	hilferadius = radiusa + radiusb + abstand;
	tmp.radius = Sup(hilferadius);
	return tmp;
}

cicircle operator*(cicircle a, cicircle b)
{
	cicircle tmp;
	cinterval mittea, mitteb, hilfe;
	interval abstand, radiusa, radiusb, hilferadius;

	// Bestimmung des neuen Mittelpunkts
	mittea = a.midpoint;
	mitteb = b.midpoint;
	mittea *= mitteb;
	tmp.midpoint = mid(mittea);

	// Fr den Radius: Feststellen der grten Entfernung
	// zu einer der vier Intervall-Ecken
	if (Re(tmp.midpoint) - Inf(Re(mittea)) > Sup(Re(mittea)) - Re(tmp.midpoint))
		Re(hilfe) = Re(tmp.midpoint) - Inf(Re(mittea));
	else
		Re(hilfe) = Sup(Re(mittea)) - Re(tmp.midpoint);

	if (Im(tmp.midpoint) - Inf(Im(mittea)) > Sup(Im(mittea)) - Im(tmp.midpoint))
		Im(hilfe) = Im(tmp.midpoint) - Inf(Im(mittea));
	else
		Im(hilfe) = Sup(Im(mittea)) - Im(tmp.midpoint);

	abstand = abs(hilfe);
	// Bestimmung des neuen Radius als |mittea| * r2 + |mitteb| * r1 + r1*r2 + Fehler
	radiusa = a.radius;
	radiusb = b.radius;
	mittea = a.midpoint;
	hilferadius = abs(mittea)*radiusb + abs(mitteb)*radiusa + radiusa*radiusb + abstand;
/*	if (hilferadius == Infinity)
	{ cout << "Absolutbetrag zu gro!" << endl;
		interval hilferadius2 = (abs(Re(mittea))+abs(Im(mittea)))*radiusb + (abs(Re(mitteb))+abs(Im(mitteb)))*radiusa + radiusa*radiusb + abstand;
		cout << "abstand = " << abstand << endl;}*/
	tmp.radius = Sup(hilferadius);
	return tmp;
}

cicircle operator/(cicircle a, cicircle b)
{
	cicircle tmp;
	tmp = a * kehrwert(b);
	return tmp;
}


cicircle operator+(cicircle a, complex b)
{
	cicircle bb(b), tmp;
	tmp = a + bb;
	return tmp;
}

cicircle operator+(complex a, cicircle b)
{
	cicircle aa(a), tmp;
	tmp = aa + b;
	return tmp;
}

cicircle operator-(cicircle a, complex b)
{
	cicircle bb(b), tmp;
	tmp = a - bb;
	return tmp;
}

cicircle operator-(complex a, cicircle b)
{
	cicircle aa(a), tmp;
	tmp = aa - b;
	return tmp;
}

cicircle operator*(cicircle a, complex b)
{
	cicircle bb(b), tmp;
	tmp = a * bb;
	return tmp;
}

cicircle operator*(complex a, cicircle b)
{
	cicircle aa(a), tmp;
	tmp = aa * b;
	return tmp;
}

cicircle operator/(cicircle a, complex b)
{
	cicircle bb(b), tmp;
	tmp = a / bb;
	return tmp;
}

cicircle operator/(complex a, cicircle b)
{
	cicircle aa(a), tmp;
	tmp = aa / b;
	return tmp;
}


cicircle cicircle::operator+=(cicircle a){ *this = *this + a; return *this; }
cicircle cicircle::operator-=(cicircle a){ *this = *this - a; return *this; }
cicircle cicircle::operator*=(cicircle a){ *this = *this * a; return *this; }
cicircle cicircle::operator/=(cicircle a){ *this = *this / a; return *this; }

cicircle cicircle::operator+=(complex b){ return *this = *this + b; }
cicircle cicircle::operator-=(complex b){ return *this = *this - b; }
cicircle cicircle::operator*=(complex b){ return *this = *this * b; }
cicircle cicircle::operator/=(complex b){ return *this = *this / b; }

//--Vergleichs-Operatoren------------------------------------------------------

bool operator!(const cicircle & a){
	return !a.midpoint && !a.radius; }
bool operator== (const cicircle & a, const cicircle & b){
	return a.midpoint == b.midpoint && a.radius == b.radius; }
bool operator!= (const cicircle & a, const cicircle & b){
	return a.midpoint!=b.midpoint || a.radius!=b.radius; }
bool operator== (const cicircle & a, const complex & b){
	return !a.radius && a.midpoint == b; }
bool operator== (const complex & a, const cicircle & b){
	return !b.radius && a==b.midpoint; }
bool operator!= (const cicircle & a, const complex & b){
	return !!a.radius || a.midpoint!=b; }
bool operator!= (const complex & a, const cicircle & b){
	return !!b.radius || a!=b.midpoint; }

//---Methoden------------------------------------------------------------------

void cicircle::setmidpoint(complex m){ midpoint = m; }

void cicircle::setradius(real r){ radius = r; }

complex cicircle::getmidpoint() const { return midpoint; }

real cicircle::getradius() const { return radius;}

cinterval cicircle::umwandeln() const
{
	cinterval tmp, mitte;
	mitte = midpoint;
	Sup(Re(tmp)) = Sup(Re(mitte) + radius);
	Inf(Re(tmp)) = Inf(Re(mitte) - radius);
	Sup(Im(tmp)) = Sup(Im(mitte) + radius);
	Inf(Im(tmp)) = Inf(Im(mitte) - radius);
	return tmp;
}

cicircle conj(cicircle a)
{
	cicircle tmp;
	tmp.midpoint = conj(a.midpoint);
	tmp.radius = a.radius;
	return tmp;
}


cicircle kehrwert(cicircle a)
{
	cicircle tmp;
	cinterval mittea, hilfe;
	interval abstand, radiusa, hilferadius;

	// Test, ob 0 nicht im Kreis liegt
	if (a.radius < abs(a.midpoint)){
		mittea = a.midpoint;
		radiusa = a.radius;
		mittea = conj(mittea) / (mittea * conj(mittea) - radiusa * radiusa);
		tmp.midpoint = mid(mittea);

		// Fr den Radius: Feststellen der grten Entfernung
		// zu einer der vier Intervall-Ecken
		if (Re(tmp.midpoint) - Inf(Re(mittea)) > Sup(Re(mittea)) - Re(tmp.midpoint))
			Re(hilfe) = Re(tmp.midpoint) - Inf(Re(mittea));
		else
			Re(hilfe) = Sup(Re(mittea)) - Re(tmp.midpoint);
		if (Im(tmp.midpoint) - Inf(Im(mittea)) > Sup(Im(mittea)) - Im(tmp.midpoint))
			Im(hilfe) = Im(tmp.midpoint) - Inf(Im(mittea));
		else
			Im(hilfe) = Sup(Im(mittea)) - Im(tmp.midpoint);

		abstand = abs(hilfe);

		// Bestimmung des neuen Radius als r / (mittea * conj(mittea) - r*r) + Fehler
		mittea = a.midpoint;
		hilfe = mittea * conj(mittea);
		hilferadius = radiusa / (Re(hilfe) - radiusa*radiusa) + abstand;
		tmp.radius = Sup(hilferadius);
		return tmp;
	}
	else
	{
		throw std::runtime_error("Division by zero.");
		return a;
	}
}

}
