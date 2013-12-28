#ifndef POLYNOMIAL_H_
#define POLYNOMIAL_H_

#include <stdexcept>
#include <vector>
#include <iostream>

#include <real.hpp>
#include <interval.hpp>
#include <complex.hpp>
#include <cinterval.hpp>

using std::vector;
using std::ostream;
using std::endl;

using cxsc::real;
using cxsc::interval;
using cxsc::complex;
using cxsc::cinterval;

namespace ivk
{

template <class E>
class Polynomial
{
protected:
	int m_lower;
	int m_upper;
	E* m_coefficients;

public:
	Polynomial()
	{
		this->m_lower = 0;
		this->m_upper = -1;
		m_coefficients = 0;
	}

	Polynomial(Polynomial<E> const &original)
	: m_lower(original.m_lower), m_upper(original.m_upper), m_coefficients(new E[original.m_upper - original.m_lower +1])
	{
		// copy data
		for(int i = m_lower; i<=m_upper; ++i)
			m_coefficients[i-m_lower] = original.m_coefficients[i-m_lower];
	}

	Polynomial<E>& operator=(Polynomial<E> const &original)
	{
		this->m_lower = original.m_lower;
		this->m_upper = original.m_upper;
		m_coefficients = new E[original.m_upper - original.m_lower +1];
		// copy data
		for(int i = m_lower; i<=m_upper; ++i)
			m_coefficients[i-m_lower] = original.m_coefficients[i-m_lower];
	}

	Polynomial(int lower, int upper)
	{
		if(lower > upper)
			throw std::invalid_argument("Lower bound must be smaller than upper bound.");
		this->m_lower = lower;
		this->m_upper = upper;
		m_coefficients = new E[upper - lower + 1];
		for(int i = lower; i<=upper; ++i)
			m_coefficients[i-lower] = (E) 0;
	}

	Polynomial(int upper)
	{
		if(upper < 0)
			throw std::invalid_argument("Degree must be greater than zero.");
		this->m_lower = 0;
		this->m_upper = upper;
		m_coefficients = new E[upper+1];
		for(int i = 0; i<=upper; ++i)
			m_coefficients[i] = (E) 0;
	}

	virtual ~Polynomial()
	{
		if(m_coefficients) delete[] m_coefficients;
	}


	int degree() const
	{
		return m_upper;
	}

	int lowerBound() const
	{
		return m_lower;
	}

	int upperBound() const
	{
		return m_upper;
	}

	void setLowerBound(const int lb)
	{
		m_upper = m_upper + (lb - m_lower);
		m_lower = lb;
	}

	friend ostream& operator<<(ostream& out, Polynomial<E>& p)
	{
		  int n = p.upperBound();
		  int PolyIsZero = true;

		  for (int i = n; i >= p.lowerBound(); i--) {
		    if (!PolyIsZero)
		      out << " + " << endl;

		    out << p[i] << " * z^" << i;
		    PolyIsZero = 0;
		  }
		  out << endl;
		  return out;
	};

	E& operator[](int index)
	{
		if((index > upperBound()) || (index < lowerBound()))
			throw new std::invalid_argument("Index out of bound.");

		return this->m_coefficients[index-m_lower];
	}

	const E& at(int index) const
	{
		if((index > upperBound()) || (index < lowerBound()))
			throw new std::invalid_argument("Index out of bound.");

		return this->m_coefficients[index-m_lower];
	}

	E sum()
	{
		E summe;
		summe = (*m_coefficients);
		for(int i = m_lower+1; i<=m_upper; ++i)
			summe += m_coefficients[i];
		return summe;
	}

	friend Polynomial<E> operator-(const Polynomial<E>& p)
	{
		Polynomial<E> ergebnis(p.lowerBound(), p.upperBound());

		for (int i=p.lowerBound(); i <= p.upperBound(); ++i)
			ergebnis[i] = -p.at(i);
		return ergebnis;
	}

	friend Polynomial<E> operator+(const Polynomial<E> &p, const Polynomial<E> &q)
	{
		const int lowerBound = std::min<int>(p.lowerBound(), q.lowerBound());
		const int upperBound = std::max<int>(p.upperBound(), q.upperBound());

		Polynomial<E> ergebnis(lowerBound, upperBound);

		for(int i = lowerBound; i<=upperBound; ++i)
		{
			E sum = (E) 0;
			if((i >= p.lowerBound()) && (i<=p.upperBound()))
				sum += p.at(i);
			if((i >= q.lowerBound()) && (i<=q.upperBound()))
				sum += q.at(i);
			ergebnis[i] = sum;
		}

		return ergebnis;
	}

	friend Polynomial<E> operator-(const Polynomial<E> &p, const Polynomial<E> &q)
	{
		Polynomial<E> hilfe = - q;
		Polynomial<E> ergebnis = p + hilfe;
		return ergebnis;
	}

	friend Polynomial<E> operator*(const Polynomial<E> &p, const Polynomial<E> &q)
	{
		const int lowerBound = p.lowerBound()+q.lowerBound();
		const int upperBound = p.upperBound()+q.upperBound();

		Polynomial<E> ergebnis(lowerBound, upperBound);
		for(int i = lowerBound; i<=upperBound; ++i)
		{
			ergebnis[i] = (E) 0;
		}
		for(int i = p.lowerBound(); i<=p.upperBound(); ++i)
		{
			for(int j = q.lowerBound(); j<=q.upperBound(); ++j)
			{
				ergebnis[i+j] += p.at(i) * q.at(j);
			}
		}
		return ergebnis;
	}

	Polynomial<E> operator+=(const Polynomial<E> &a){ *this = *this + a; return *this; }
	Polynomial<E> operator-=(const Polynomial<E> &a){ *this = *this - a; return *this; }
	Polynomial<E> operator*=(const Polynomial<E> &a){ *this = *this * a; return *this; }

	virtual void fliplr()
	{
		const int lb = this->lowerBound();
		const int ub = this->upperBound();
		const int limit = (ub-lb +1) / 2;
		for(int i = 0; i<limit; ++i)
		{
			E swap = (*this)[lb+i];
			(*this)[lb+i] = (*this)[ub-i];
			(*this)[ub-i] = swap;
		}
	}
};

typedef Polynomial<interval> 	IPolynomial;
typedef Polynomial<real>		RPolynomial;
typedef Polynomial<complex>		CPolynomial;
typedef Polynomial<cinterval>	CIPolynomial;

}

#endif /*Polynomial_H_*/
