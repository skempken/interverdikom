#include "computation/SMPVerifyEig.h"

#include "utility/MatrixPolynomial.hpp"
#include "utility/solvers/EigenvalueSolver.h"
#include "utility/IMatrixUtils.h"
#include "utility/solvers/CComplexILinSys.hpp"
#include "utility/Determinant.h"

#include "utility/roots/RootFinder.h"

#include <imatrix.hpp>

namespace ivk {

SMPVerifyEig::SMPVerifyEig(const SSMProcess * ptrData,
		const ComputationParameters &parameters) :
	AbstractComputation<SSMProcess, ISMPPFResult>(ptrData, parameters) {
}

SMPVerifyEig::~SMPVerifyEig() {
}

ISMPPFResult * SMPVerifyEig::compute() {
	ISMPPFResult *result = new ISMPPFResult;
	result->success = false;
	const SSMProcess & process = *m_ptrData;

	imatrix transitionMatrix = process.getTransitionMatrix();
	imatrix unfilteredDistributionMatrix = process.getDistributions();
	imatrix distributionMatrix = unfilteredDistributionMatrix;
	cout << "Lb(distMatrix,2) = " << Lb(distributionMatrix, 2) << ", Ub(distMatrix,2) = " << Ub(distributionMatrix, 2) << endl;

	// U^T(z^-1)-I
	IMatrixPolynomial polynomial = process.getCharacteristicPolynomialMatrix();
	// here: polynomial = P(beta^-1)
	polynomial.fliplr();
	// now: polynomial = P(beta)
	// Reason: Avoid infinity for eigenvalues = complex roots at zero
	cout << "Finished polynomial:" << endl << polynomial;

	civector eigenValues;
	cimatrix eigenVectors;
	EigenvalueSolver es;
	es.addProgressListener(this);
	es.getVerifiedEigenvalues(polynomial, eigenValues,
			eigenVectors);
	// XXX: Kehrwert der Eigenwerte
	for(int i = Lb(eigenValues); i<=Ub(eigenValues); ++i)
		eigenValues[i] = 1.0 / eigenValues[i];

	// XXX: Eigenvektoren entsprechend anpassen!
	// Vielleicht Lösung des Gleichungssystems analog PolyFac
	polynomial.fliplr();
	result->eigenValues = eigenValues;

	int matrixSize = polynomial.matrixWidth();
	eigenVectors = cimatrix(1, matrixSize, Lb(eigenValues), Ub(eigenValues));
	civector linRhs(1, matrixSize);
	linRhs = 0;
	linRhs[matrixSize] = cinterval(complex(1.0, 0.0), complex(1.0, 0.0));
	CComplexILinSys solver;
	for (int i = Lb(eigenValues); i <= Ub(eigenValues); i++) {
		civector eigenVector(1, matrixSize);

		cimatrix linLhs = polynomial.evaluateCI(cinterval(eigenValues[i]));

		linLhs[Row(matrixSize)] = cinterval(complex(1.0, 0.0), complex(1.0, 0.0));

		int solutions;
		solver.CILinSolve(linLhs, linRhs, eigenVector, solutions);
		cout << "eigenValue: " << eigenValues[i] << endl/* << "linLhs:"
				<< endl << linLhs << "linRhs: " << linRhs << endl */
				<< "Solution: " << endl << eigenVector << endl << endl;
		eigenVectors[Col(i)] = eigenVector;
	}

	cout << "Calculated eigenvectors:" << endl << eigenVectors << endl;
	result->eigenVectors = eigenVectors;

	result->success = result->calculateGamma(process);

	return result;
}

void SMPVerifyEig::updateProgressText(const std::string &text)
{
	setProgressText(text);
}

void SMPVerifyEig::updateProgressMax(const int &max)
{
	setProgressMax(max);
}

void SMPVerifyEig::updateProgressValue(const int &value)
{
	setProgressValue(value);
}

void SMPVerifyEig::updateProgressETA(const int &eta)
{

}

}
