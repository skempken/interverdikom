#ifndef DETERMINANT_H_
#define DETERMINANT_H_

#include "Polynomial.hpp"

namespace ivk {

class Determinant
{
public:
	static IPolynomial laplace(IPolynomial** polyMatrix, int m);
	static IPolynomial faddeev(IPolynomial** polyMatrix, const int &m);
};

}
#endif /*DETERMINANTEVALUATION_H_*/
