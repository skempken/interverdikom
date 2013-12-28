#include "CIMatrixUtils.h"

#include "utility/solvers/CComplexILinSys.hpp"

namespace ivk {

cimatrix CIMatrixUtils::invert(const cimatrix & matrix) {
	CComplexILinSys solver;
	civector identityVector(1, Ub(matrix, COL));
	cimatrix result(Lb(matrix, ROW), Ub(matrix, ROW), Lb(matrix, COL), Ub(matrix, COL));
	for (int i = 1; i <= (Ub(matrix, COL) - Lb(matrix, COL) + 1); i++) {
		for (int j = 1; j <= Ub(identityVector); j++) {
			identityVector[j] = 0;
		}

		identityVector[i] = 1;
		civector resultVector;
		int returnCode;

		solver.CILinSolve(matrix, identityVector, resultVector,
				returnCode);
		result[Col(i)] = resultVector;
	}
	
	return result;
}

}
