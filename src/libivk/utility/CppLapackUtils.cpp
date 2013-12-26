#include "CppLapackUtils.h"

namespace ivk {

CPPL::zgematrix CppLapackUtils::toZgematrix(const cmatrix & originalMatrix) {
	zgematrix result(ColLen(originalMatrix), RowLen(originalMatrix));

	for (int i = Lb(originalMatrix, 1); i <= Ub(originalMatrix, 1); i++) {
		for (int j = Lb(originalMatrix, 2); j <= Ub(originalMatrix, 2); j++) {
			cxsc::complex originalValue = originalMatrix[i][j];
			double originalReal = _double(Re(originalValue));
			double originalImg = _double(Im(originalValue));
			unsigned int resultRowIndex = i - Lb(originalMatrix, 1);
			unsigned int resultColIndex = j - Lb(originalMatrix, 2);
			result(resultRowIndex, resultColIndex) = std::complex<double>(originalReal, originalImg);
		}
	}

	return result;
}

cmatrix CppLapackUtils::toCmatrix(const zgematrix & originalMatrix) {
	cmatrix result(1, originalMatrix.m, 1, originalMatrix.n);

	for (int i = 0; i < originalMatrix.m; i++) {
		for (int j = 0; j < originalMatrix.n; j++) {
			std::complex<double> originalValue = originalMatrix(i, j);
			double originalReal = originalValue.real();
			double originalImg = originalValue.imag();
			result[i+1][j+1] = cxsc::complex(originalReal, originalImg);
		}
	}

	return result;
}

cmatrix CppLapackUtils::solveLss(const cmatrix & A, const cmatrix & B) {
	zgematrix _A = toZgematrix(A);
	zgematrix _B = toZgematrix(B);
	dcovector _S;
	long _rank;
	_A.zgelss(_B, _S, _rank);
	return toCmatrix(_B);
}

}
