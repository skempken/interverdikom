#include "computation/SMPPolyFac.h"

#include "utility/MatrixPolynomial.hpp"
#include "utility/solvers/EigenvalueSolver.h"
#include "utility/IMatrixUtils.h"
#include "utility/solvers/CComplexILinSys.hpp"
#include "utility/Determinant.h"
#include "utility/MatlabExport.h"

#include "utility/roots/RootFinder.h"

#include <imatrix.hpp>

namespace ivk {

const char* SMPPolyFac::PARAM_ROOTS = "roots";
const char* SMPPolyFac::PARAM_DETERMINANT = "det";

SMPPolyFac::SMPPolyFac(const SSMProcess * ptrData,
		const ComputationParameters &parameters) :
	AbstractComputation<SSMProcess, ISMPPFResult>(ptrData, parameters), p(parameters) {
}

SMPPolyFac::~SMPPolyFac() {
}

ISMPPFResult * SMPPolyFac::compute() {
	ISMPPFResult *result = new ISMPPFResult;
	result->success = false;
	const SSMProcess & process = *m_ptrData;

	imatrix transitionMatrix = process.getTransitionMatrix();
	imatrix unfilteredDistributionMatrix = process.getDistributions();
	imatrix distributionMatrix = unfilteredDistributionMatrix;
	cout << "Lb(distMatrix,2) = " << Lb(distributionMatrix, 2)
			<< ", Ub(distMatrix,2) = " << Ub(distributionMatrix, 2) << endl;

	// U^T(z^-1)-I
	IMatrixPolynomial p = process.getCharacteristicPolynomialMatrix();

	cout << MatlabExport::toString(p);

	int matrixSize = p.matrixWidth();
	IPolynomial **polyMatrix = new IPolynomial*[matrixSize];

	int lowerBound = p.lowerBound();
	int lb1 = Lb(p.at(lowerBound), 1);
	int lb2 = Lb(p.at(lowerBound), 2);
	for (int i = 0; i < matrixSize; i++) {
		polyMatrix[i] = new IPolynomial[matrixSize];

		for (int j = 0; j < matrixSize; j++) {
			polyMatrix[i][j] = p.getPolynomialAt(i + lb1, j + lb2);
		}
	}

	// Compute Determinant
	IPolynomial det;
	switch ((*this).p.getInt(PARAM_DETERMINANT)) {
	case 0:
		det = Determinant::laplace(polyMatrix, matrixSize);
		break;
	case 1:
		det = Determinant::faddeev(polyMatrix, matrixSize);
		break;
	}

	int lowerNZ = det.lowerBound();
	while (det[lowerNZ] == 0.0) {
		lowerNZ++;
		if (lowerNZ > det.upperBound()) {
			throw new std::invalid_argument("Polynomial with all-zero determinant.");
		}
	}
	int upperNZ = det.upperBound();
	while (det[upperNZ] == 0.0) {
		upperNZ--;
	}

	int indexOffset = -lowerNZ;
	RPolynomial realDet(lowerNZ + indexOffset, upperNZ + indexOffset);
	// Polynom verschieben: *z^Mh
	for (int i = lowerNZ; i <= upperNZ; i++) {
		realDet[i + indexOffset] = mid(det[i]);
	}

	cout << "upperNZ: " << upperNZ << ", lowerNZ: " << lowerNZ << endl;
	cout << "Characteristic Polynomial:" << endl << realDet << endl;

	// XXX: Test remove root at (1,0)
	// realDet = RootFinder::splitOffRootAt1(realDet);

	cvector roots;
	try {
		switch ((*this).p.getInt(PARAM_ROOTS)) {
		case 0:
			roots = RootFinder::rootsMueller(realDet);
			break;
		case 1:
			roots = RootFinder::rootsBauhuber(realDet);
			break;
		case 2:
			roots = RootFinder::rootsLapack(realDet);
			break;
		case 3:
			// TODO Zweiter Parameter bei rootsSphere-Aufruf?
			// roots = RootFinder::rootsSphere(realDet);
			break;
		}

	}
	catch (std::runtime_error ex)
	{
		cout << "Error using rootfinder: " << ex.what() << endl;
		throw std::runtime_error("Could not use selected root finder.");
	}
	cout << "Roots found with alternative method: " << endl << roots << endl;
	result->eigenValues = civector(roots);

	cimatrix eigenVectors(1, matrixSize, Lb(roots), Ub(roots));
	civector linRhs(1, matrixSize);
	linRhs = 0;
	linRhs[matrixSize] = cinterval(complex(1.0, 0.0), complex(1.0, 0.0));
	CComplexILinSys solver;
	for (int i = Lb(roots); i <= Ub(roots); i++) {
		civector eigenVector(1, matrixSize);

		cimatrix linLhs = p.evaluateCI(cinterval(roots[i]));

		linLhs[Row(matrixSize)] = cinterval(complex(1.0, 0.0), complex(1.0, 0.0));

		int solutions;
		solver.CILinSolve(linLhs, linRhs, eigenVector, solutions);
		cout << "eigenValue: " << roots[i] << endl/* << "linLhs:"
				<< endl << linLhs << "linRhs: " << linRhs << endl */
				<< "Solution: " << endl << eigenVector << endl << endl;
		eigenVectors[Col(i)] = eigenVector;
	}

	cout << "Calculated eigenvectors:" << endl << eigenVectors << endl;

	result->eigenVectors = eigenVectors;
	result->success = result->calculateGamma(process);

	return result;
}

}
