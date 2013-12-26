#ifndef MATRIXPOLYNOMIAL_H_
#define MATRIXPOLYNOMIAL_H_

#include "Polynomial.hpp"

#include <sstream>

#include <rvector.hpp>
#include <ivector.hpp>
#include <cvector.hpp>
#include <civector.hpp>

#include <rmatrix.hpp>
#include <imatrix.hpp>
#include <cmatrix.hpp>
#include <cimatrix.hpp>

using cxsc::rvector;
using cxsc::ivector;
using cxsc::cvector;
using cxsc::civector;

using cxsc::rmatrix;
using cxsc::imatrix;
using cxsc::cmatrix;
using cxsc::cimatrix;

namespace ivk {

template <class M, class V, class P> class MatrixPolynomial :
	public Polynomial<M> {
public:
	MatrixPolynomial() :
		Polynomial<M>() {

	}

	MatrixPolynomial(int lower, int upper, int lb1, int ub1, int lb2, int ub2) :
		Polynomial<M>(lower, upper) {
		M emptyElement = M(lb1, ub1, lb2, ub2);

		(*this)[lower] = emptyElement;

	}

	static MatrixPolynomial<M,V,P> zeros(int lower, int upper, int lb1, int ub1, int lb2, int ub2)
	{
		MatrixPolynomial<M,V,P> empty(lower, upper, lb1, ub1, lb2, ub2);
		M emptyMatrix = M(lb1,ub1,lb2,ub2);
		for(int i = lb1; i<=ub1; ++i)
			for(int j=lb2; j<=ub2; ++j)
				emptyMatrix[i][j] = P(0.0);
		for(int z=lower; z<=upper; ++z)
			empty[z] = emptyMatrix;
		return empty;
	}

	MatrixPolynomial(int degree) :
		Polynomial<M>(degree) {
	}

	V getVectorAt(int row, int col) const {
		V result(this->lowerBound(), this->upperBound());
		for (int i = this->lowerBound(); i<= this->upperBound(); ++i)
			result[i] = this->at(i)[row][col];
		return result;
	}

	cimatrix evaluateCI(cinterval x) const {
		M firstElement = this->at(this->lowerBound());
		cimatrix result(firstElement);
		result = 0;

		for (int i = this->upperBound(); i >= 0; i--) {
			result *= x;

			if (i >= this->lowerBound()) {
				result += cimatrix(this->at(i));
			}
		}

		cinterval invX = cinterval(1) / x;
		cimatrix invResult(firstElement);
		invResult = 0;

		if (this->lowerBound() < 0) {
			for (int i = this->lowerBound(); i < 0; i++) {
				invResult *= invX;

				if (i <= this->upperBound()) {
					invResult += cimatrix(this->at(i));
				}
			}

			invResult *= invX;
		}

		result += invResult;

		return result;
	}

	int matrixHeight() const {
		M firstElement = this->at(this->lowerBound());
		return Ub(firstElement, 1) - Lb(firstElement, 1) + 1;
	}

	int matrixWidth() const {
		M firstElement = this->at(this->lowerBound());
		return Ub(firstElement, 2) - Lb(firstElement, 2) + 1;
	}

	void setVectorAt(int row, int col, const V &vector) {
		// check if new vector fits in MatrixPolynomial
		if ((Lb(vector) < this->lowerBound()) || (Ub(vector)
				> this->upperBound())) {
			throw new std::invalid_argument("Index out of bound.");
		}

		// fits now. copy values.
		for (int i = Lb(vector); i<=Ub(vector); ++i) {
			(*this)[i][row][col] = vector[i];
		}
	}

	Polynomial<P> getPolynomialAt(int row, int col) const {
		Polynomial<P> result(this->lowerBound(), this->upperBound());
		for (int i = this->lowerBound(); i<= this->upperBound(); ++i)
			result[i] = this->at(i)[row][col];
		return result;
	}
};

typedef MatrixPolynomial<rmatrix, rvector, real> RMatrixPolynomial;
typedef MatrixPolynomial<imatrix, ivector, interval> IMatrixPolynomial;
typedef MatrixPolynomial<cmatrix, cvector, complex> CMatrixPolynomial;
typedef MatrixPolynomial<cimatrix, civector, cinterval> CIMatrixPolynomial;

}

#endif /*MATRIXPOLYNOMIAL_H_*/
