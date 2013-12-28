#ifndef EIGENVALUESOLVER_H_
#define EIGENVALUESOLVER_H_

#include <vector>

#include <rmatrix.hpp>
#include <imatrix.hpp>
#include <cmatrix.hpp>
#include <cvector.hpp>
#include <civector.hpp>

#include "utility/MatrixPolynomial.hpp"
#include "utility/ProgressNotifier.h"

using namespace cxsc;

namespace ivk {

class EigenvalueSolver : public ProgressNotifier
{
public:
	EigenvalueSolver();

	cvector getEigenvalues(const rmatrix & matrix);

	void getEigenvalues(const rmatrix & matrix, cvector & eigenValues, cmatrix & eigenVectors);

	void getEigenvalues(const rmatrix & A, const rmatrix & B, cvector & eigenValues,
			cmatrix & eigenVectors);

	bool getVerifiedEigenvalues(const imatrix A, cxsc::complex lambda, cmatrix xs, imatrix B, cinterval &L, cimatrix &X);

	void getVerifiedEigenvalues(const imatrix A, civector & eigenValues, cimatrix & eigenVectors);

	void getVerifiedEigenvalues(const IMatrixPolynomial & polynomial, civector & eigenValues, cimatrix & eigenVectors);

	void getVerifiedEigenvalues(const imatrix A, const imatrix B, civector & eigenValues, cimatrix & eigenVectors);

	bool isIncludedIn(const cimatrix & a, const cimatrix & b);

	cimatrix getIndexedRows(const cimatrix & matrix, const std::vector<int> & indices);
};

}

#endif /*EIGENVALUESOLVER_H_*/

