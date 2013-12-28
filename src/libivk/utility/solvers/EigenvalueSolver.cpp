#include "solvers/EigenvalueSolver.h"

#include <vector>
#include <climits>

#include <intvector.hpp>
#include <cimatrix.hpp>
#include <complex.hpp>

#include "cpplapack/cpplapack.h"
#include "utility/types/Matrix.hpp"

#include "utility/MatrixUtils.hpp"
#include "utility/CIMatrixUtils.h"
#include "utility/CMatrixUtils.h"
#include "utility/IMatrixUtils.h"

#include "utility/CppLapackUtils.h"

#include "utility/solvers/CComplexILinSys.hpp"

using namespace CPPL;

using std::vector;

using cxsc::real;
using cxsc::complex;

namespace ivk {

EigenvalueSolver::EigenvalueSolver() {

}

cvector EigenvalueSolver::getEigenvalues(const rmatrix & matrix) {
	cvector resultVector;
	cmatrix discardedMatrix;
	getEigenvalues(matrix, resultVector, discardedMatrix);
	return resultVector;
}

void EigenvalueSolver::getEigenvalues(const rmatrix & matrix,
		cvector & eigenValues, cmatrix & eigenVectors) {
	getEigenvalues(matrix,
			MatrixUtils<rmatrix, rvector, cxsc::real>::eye(RowLen(matrix)),
			eigenValues, eigenVectors);
}

void EigenvalueSolver::getEigenvalues(const rmatrix & A, const rmatrix & B,
		cvector & eigenValues, cmatrix & eigenVectors) {
	int lb1 = Lb(A, 1);
	int lb2 = Lb(A, 2);
	int height = Ub(A, 1) - Lb(A, 1) + 1;
	int width = Ub(A, 2) - Lb(A, 2) + 1;

	if (width != height) {
		return;
	}

	int matrixSize = width;
	cout << "Matrix A = [" << endl;
	dgematrix lapackA(matrixSize, matrixSize);
	for (int row = 0; row < matrixSize; row++) {
		for (int col = 0; col < matrixSize; col++) {
			lapackA(row, col) = _double(A[row + lb1][col + lb2]);
			cout << _double(A[row + lb1][col + lb2]) << " ";
		}
		cout << ";" << endl;
	}

	cout << "] Matrix B = [" << endl;
	dgematrix lapackB(matrixSize, matrixSize);
	for (int row = 0; row < matrixSize; row++) {
		for (int col = 0; col < matrixSize; col++) {
			lapackB(row, col) = _double(B[row + Lb(B,1)][col + Lb(B,2)]);
			cout << _double(B[row + Lb(B,1)][col + Lb(B,2)]) << " ";
		}
		cout << ";" << endl;
	}

	cout << "]" << endl;

	vector<double> realValues, imgValues;
	vector<dcovector> realVectors, imgVectors;
	lapackA.dggev(lapackB, realValues, imgValues, realVectors, imgVectors);
	int eigenwertCount = realValues.size();

	Resize(eigenValues, 1, eigenwertCount);
	for (int i = 0; i < eigenwertCount; i++) {
		eigenValues[i+1] = cxsc::complex(realValues[i], imgValues[i]);
	}

	if (realVectors.size()) {
		unsigned int vectorSize = realVectors[0].l;
		Resize(eigenVectors, 1, vectorSize, 1, realVectors.size());

		for (int i = 0; i < realVectors.size(); i++) {
			cvector tempVector(1, vectorSize);
			for (int j = 0; j < vectorSize; j++) {
				tempVector[j+1] = cxsc::complex(realVectors[i](j),
						imgVectors[i](j));
			}

			eigenVectors[Col(i+1)] = tempVector;
		}
	} else {
		eigenVectors = cmatrix();
	}
}

bool EigenvalueSolver::getVerifiedEigenvalues(const imatrix A,
		cxsc::complex lambda, cmatrix xs, imatrix B, cinterval &L, cimatrix &X) {
	typedef CIMatrixUtils CIMUtil;
	typedef MatrixUtils<cmatrix, cvector, cxsc::complex> CMU;

	// [n k] = size(xs);
	int n = ColLen(xs);
	int k = RowLen(xs);

	// [N,I] = sort(sum(abs(xs),2));
	rmatrix abs_xs = abs(xs);
	rvector sum_xs(1, n);
	for (int i = 1; i <= n; i++) {
		sum_xs = 0;
	}
	for (int i = Lb(abs_xs, 1); i <= Ub(abs_xs, 1); i++) {
		for (int j = Lb(abs_xs, 2); j <= Ub(abs_xs, 2); j++) {
			sum_xs[i] += abs_xs[i][j];
		}
	}
	intvector I(1, n);
	for (int i = 1; i <= n; i++) {
		I[i] = i;
	}
	for (int roundNo = 1; roundNo < n; roundNo++) {
		for (int i = 1; i <= (n - roundNo); i++) {
			if (sum_xs[i+1] < sum_xs[i]) {
				cxsc::real tempReal = sum_xs[i];
				sum_xs[i] = sum_xs[i+1];
				sum_xs[i+1] = tempReal;

				int tempInt = I[i];
				I[i] = I[i+1];
				I[i+1] = tempInt;
			}
		}
	}

	// u = I(1:n-k);
	// v = I(n-k+1:n);
	vector<int> u;
	vector<int> v;
	for (int i = 1; i <= n; i++) {
		if (i <= n - k) {
			u.push_back(I[i]);
		} else {
			v.push_back(I[i]);
		}
	}

	// midA = mid(A);
	// midB = mid(B);
	rmatrix midA = mid(A);
	rmatrix midB = mid(B);

	// R = midA - lambda*midB;
	cmatrix R = midA - lambda * midB;

	// R(:,v) = -midB*xs;
	cmatrix minusMidBTimesXs = -midB * xs;
	int indexCounter = 1;
	for (unsigned int i = 0; i < v.size(); i++) {
		int index = v[i];
		R[Col(index)] = minusMidBTimesXs[Col(indexCounter++)];
	}

	// y = R\(midA*xs-lambda*midB*xs);
	cmatrix ldivRhs = midA * xs - lambda * midB * xs;
	cmatrix y = CppLapackUtils::solveLss(R, ldivRhs);

	// xs(u,:) = xs(u,:) - y(u,:);
	cmatrix _xs(xs);
	for (unsigned int i = 0; i < u.size(); i++) {
		int index = u[i];
		_xs[Row(index)] = _xs[Row(index)] - y[Row(index)];
	}

	// lambda = lambda - sum(diag(y(v,:)))/k;
	cmatrix v_of_y(v.size(), RowLen(y));
	indexCounter = 1;
	for (unsigned int i = 0; i < v.size(); i++) {
		int index = v[i];
		v_of_y[Row(indexCounter)] = y[Row(index)];
		indexCounter++;
	}
	cxsc::complex _lambda = lambda - CMU::sum(CMU::diag(v_of_y))/k;

	// R = midA - lambda*midB;
	cmatrix _R = midA - _lambda * midB;

	// R(:,v) = -midB*xs;
	cmatrix rhsMatrix = -midB * _xs;
	indexCounter = 1;
	for (unsigned int i = 0; i < v.size(); i++) {
		int index = v[i];
		_R[Col(index)] = rhsMatrix[Col(indexCounter++)];
	}

	// R = inv( R );
	_R = CppLapackUtils::solveLss(R, CMatrixUtils::eye(RowLen(R)));

	// C = A - intval(lambda)*B;
	// Z = - R * ( C * xs );
	cimatrix C = A - cinterval(lambda) * B;
	cimatrix Z = -_R * (C * _xs);

	//exit(0);
	// C(:,v) = -B*xs;
	cimatrix irhsMatrix = -B * _xs;
	indexCounter = 1;
	for (unsigned int i = 0; i < v.size(); i++) {
		int index = v[i];
		C[Col(index)] = irhsMatrix[Col(indexCounter++)];
	}

	// C = speye(n) - R * C;
	C = CIMatrixUtils::eye(n) - _R * C;

	// Y = Z;
	cimatrix Y = Z;

	// Eps = 0.1*mag(Y)*hull(-1,1) + midrad(0,realmin);
	double realmin = DBL_MIN;
	cimatrix Eps(0.1 * abs(Y) * interval(-1, 1));
	for (int i = 1; i <= Ub(Eps, 1); i++) {
		for (int j = 1; j <= Ub(Eps, 2); j++) {
			Eps[i][j] += cinterval(cxsc::complex(-realmin, -realmin),
					cxsc::complex(realmin, realmin));
		}
	}

	// m = 0;
	cxsc::real m = 0;

	// mmax = 15 * ( sum(sum(mag(Z(v,:))>.1)) + 1 );
	imatrix magZ = abs(Z);
	int mmax = 1;
	for (int i = 1; i <= Ub(magZ, 1); i++) {
		for (int j = 1; j <= Ub(magZ, 2); j++) {
			if (magZ[i][j] > 0.1) {
				mmax++;
			}
		}
	}
	mmax *= 15;

	// ready = 0;
	bool ready = false;

	// while ( ~ready ) & ( m<mmax ) & ( ~any(isnan(Y(:))) )
	while (!ready && (m < mmax) && !CIMatrixUtils::containsNAN(Y)) {
		// m = m+1;
		// X = Y + Eps;
		// XX = X;
		m = m + 1;
		X = Y + Eps;
		cimatrix XX = X;

		// XX(v,:) = 0;
		for (unsigned int i = 0; i < v.size(); i++) {
			int index = v[i];
			XX[index] = 0;
		}

		// Y = Z + C*X + R*(XX*X(v,:));
		cimatrix v_of_X(v.size(), Ub(X, 2)-Lb(X, 2)+1);
		indexCounter = 1;
		for (unsigned int i = 0; i < v.size(); i++) {
			int index = v[i];
			v_of_X[Row(indexCounter)] = X[Row(index)];
			indexCounter++;
		}
		Y = Z + C*X + R*(B*XX*v_of_X);

		// ready = all(all(in0(Y,X)));
		ready = isIncludedIn(Y, X);
	}

	// if ready
	if (ready) {
		// M = mag(Y(v,:));
		rmatrix M = Sup(abs(getIndexedRows(Y, v)));
		// if length(v)==1                          % one eigenvalue
		if (v.size() == 1) {
			// L = midrad(lambda,M);
			L = cinterval(_lambda - M[1][1], _lambda + M[1][1]);
		} else {
			// [Evec,Eval] = eig(M); (Evec. column vectors = eigenvectors)
			cvector Eval;
			cmatrix Evec;
			getEigenvalues(M, Eval, Evec);

			// [rho,index] = max(abs(diag(Eval)));
			int index = 0;
			cxsc::real maxEvalValue = -1;
			for (int i = Lb(Eval); i <= Ub(Eval); i++) {
				if (abs(Eval[i]) > maxEvalValue) {
					maxEvalValue = abs(Eval[i]);
					index = i;
				}
			}

			// Perronx = abs(Evec(:,index));
			rvector Perronx = abs(Evec[Col(index)]);

			// setround(1);
			// rad = max( ( M*Perronx ) ./ Perronx );   % upper bound for Perron root
			// setround(0)
			rvector mXp = M * Perronx;
			for (int i = 1; i <= Ub(Perronx); i++) {
				mXp[i] = divup(mXp[i], Perronx[i]);
			}
			cxsc::real maxMxp = mXp[1];
			for (int i = 1; i <= Ub(mXp); i++) {
				if (mXp[i] > maxMxp) {
					maxMxp = mXp[i];
				}
			}
			cxsc::real rad = maxMxp;

			// L = cintval(midrad(lambda,rad));
			L = cinterval(lambda - rad, lambda + rad);
		}

		// Y(v,:) = 0;
		for (unsigned int i = 0; i < v.size(); i++) {
			int index = v[i];
			Y[index] = 0;
		}

		// X = xs + Y;
		X = _xs + Y;

		return true;
	} else {
		// % disp('no inclusion achieved')
		// X = intval(NaN*ones(size(xs)));
		// L = intval(NaN);
		X = SignalingNaN;
		L = SignalingNaN;
		return false;
	}
}

void EigenvalueSolver::getVerifiedEigenvalues(const imatrix A,
		civector & eigenValues, cimatrix & eigenVectors) {
	getVerifiedEigenvalues(A, IMatrixUtils::eye(Ub(A, 1) - Lb(A, 1) + 1),
			eigenValues, eigenVectors);
}

void EigenvalueSolver::getVerifiedEigenvalues(const imatrix A, const imatrix B,
		civector & eigenValues, cimatrix & eigenVectors) {
	setProgressText("Getting eigenproblem point approximation...");
	setProgressMax(1);
	setProgressValue(0);

	cvector pointEigenvalues;
	cmatrix pointEigenvectors;
	getEigenvalues(mid(A), mid(B), pointEigenvalues, pointEigenvectors);

	setProgressValue(1);

	cout << "point eigenvalue A range:" << Lb(A, 1) << ".." << Ub(A, 1) << ", "
			<< Lb(A, 2) << ".." << Ub(A, 2) << endl;
	cout << "point eigenvalue B range:" << Lb(B, 1) << ".." << Ub(B, 1) << ", "
			<< Lb(B, 2) << ".." << Ub(B, 2) << endl;
	cout << "point eigenvalues:" << endl << SetPrecision(20, 16)
			<< pointEigenvalues << endl;
	cout << "point eigenvectors:" << endl << SetPrecision(20, 16)
			<< pointEigenvectors << endl;

	vector<bool> validValues(Ub(pointEigenvalues), true);

	int colSizeA = Ub(A, 1) - Lb(A, 1) + 1;
	cimatrix evec(1, colSizeA, 1, Ub(pointEigenvectors, 2));
	civector eval(1, Ub(pointEigenvalues));

	setProgressText("Calculating interval enclosures...");
	setProgressMax(Ub(pointEigenvalues));
	setProgressValue(0);

	cinterval L;
	cimatrix X;
	for (int i = Lb(pointEigenvalues); i <= Ub(pointEigenvalues); i++) {
		cxsc::complex lambda = pointEigenvalues[i];
		bool validValue;

		if ((lambda == 0) || IsInfinity(Re(lambda))) {
			validValue = false;
		} else {
			cmatrix xs(1, colSizeA, 1, 1);
			xs[Col(1)] = pointEigenvectors[Col(i)];
			validValue = getVerifiedEigenvalues(A, lambda, xs, B, L, X);
		}

		if (validValue) {
			cout << "verified eigenvalue: " << L << endl;
			eval[i] = L;
			evec[Col(i)] = X[Col(1)];
		} else {
			cout << "invalid eigenvalue" << endl;
			validValues[i-1] = false;
		}

		setProgressValue(i);
	}

	setProgressText("Filtering values...");
	setProgressMax(1);
	setProgressValue(0);

	int validValueCount = 0;
	for (int i = 0; i < validValues.size(); i++) {
		if (validValues[i]) {
			validValueCount++;
		}
	}

	cout << "valid eigenvalues: " << validValueCount << endl;
	Resize(eigenValues, 1, validValueCount);
	Resize(eigenVectors, 1, colSizeA, 1, validValueCount);

	int evIndex = 1;
	for (int i = 0; i < validValues.size(); i++) {
		if (validValues[i]) {
			eigenValues[evIndex] = eval[i+1];
			eigenVectors[Col(evIndex)] = evec[Col(i+1)];
			evIndex++;
		}
	}

	setProgressValue(1);
	setProgressText("Done.");
}

void EigenvalueSolver::getVerifiedEigenvalues(
		const IMatrixPolynomial & polynomial, civector & eigenValues,
		cimatrix & eigenVectors) {
	setProgressText("Building matrices...");
	setProgressMax(1);
	setProgressValue(0);

	cout << "polyeig port called!" << endl;
	// Get dimensions of problem
	int upperBound = polynomial.upperBound();
	int lowerBound = polynomial.lowerBound();
	while (IMatrixUtils::isZero(polynomial.at(lowerBound))) {
		lowerBound++;
	}
	while (IMatrixUtils::isZero(polynomial.at(upperBound))) {
		upperBound--;
	}
	int componentSize = polynomial.matrixWidth();
	int linMatrixSize = (upperBound - lowerBound) * componentSize;
	cout << "POLYEIG lowerBound = " << lowerBound << ", upperBound = "
			<< upperBound << ", componentSize = " << componentSize
			<< ", size of linearized matrices = " << linMatrixSize << endl;

	// Build left-hand matrix of 2D eigenvalue problem
	imatrix A(1, linMatrixSize, 1, linMatrixSize);
	A = 0;
	int componentRow = (linMatrixSize - componentSize + 1);
	int componentCol = 1;
	imatrix idMatrix = IMatrixUtils::eye(componentSize);

	cout << polynomial.at(lowerBound);
	for (int i = lowerBound; i < upperBound; i++) {
		imatrix componentMatrix = polynomial.at(i);

		// Put component matrix at "bottom" of matrix
		A(componentRow, componentRow + componentSize - 1, componentCol,
				componentCol + componentSize - 1) = -componentMatrix;

		// Insert identity submatrix "above"
		if (i > lowerBound) {
			int idRow = componentCol - componentSize;
			int idCol = componentCol;
			A(idRow, idRow + componentSize - 1, idCol, idCol + componentSize
					- 1) = idMatrix;
		}

		// Increase index counter
		componentCol += componentSize;
	}

	// Build right-hand matrix of 2D eigenvalue problem
	imatrix B = IMatrixUtils::eye(linMatrixSize);
	B(linMatrixSize - componentSize + 1, linMatrixSize, linMatrixSize
			- componentSize + 1, linMatrixSize) = polynomial.at(upperBound);

	setProgressValue(1);

	cout << "POLYEIG A = " << endl << A;
	cout << "POLYEIG B = " << endl << B;
	cout << "--------------------------------------------------------" << endl;

	// Call generalized 2D eigenvalue calculation
	getVerifiedEigenvalues(A, B, eigenValues, eigenVectors);

	if (upperBound == 1) {
		return;
	}

	setProgressText("Choosing most accurate eigenvectors...");
	setProgressMax(Ub(eigenValues));
	setProgressValue(0);

	cimatrix chosenEigenvectors(1, componentSize, 1, Ub(eigenValues));

	// Iterate over all eigenvalues
	cimatrix vectorCandidates(1, componentSize, 1, upperBound);
	for (int eigenvalueNo = 1; eigenvalueNo <= Ub(eigenValues); eigenvalueNo++) {
		// Fill eigenvector candidate matrix
		vectorCandidates = 0;
		for (int candidateNo = 1; candidateNo <= upperBound; candidateNo++) {
			int candidateOffset = (candidateNo-1) * componentSize + 1;
			vectorCandidates[Col(candidateNo)] = eigenVectors(candidateOffset,
					candidateOffset + componentSize - 1, eigenvalueNo,
					eigenvalueNo);
		}

		cout << "eigenvector candidates " << eigenvalueNo << " = " << endl
				<< vectorCandidates;

		// Evaluate polynomial with eigenvalue
		cimatrix R = polynomial.evaluateCI(eigenValues[eigenvalueNo]);
		cout << "R1 = " << endl << R;
		cout << "vectorCandidates = " << endl << vectorCandidates;
		R *= vectorCandidates;
		cout << "R2 = " << endl << R;

		// Calculate normalized residuals
		int candidateCount = Ub(vectorCandidates, 2);
		civector normalizedResiduals(1, candidateCount);
		civector resultSums(1, candidateCount);
		resultSums = IMatrixUtils::sumCols(abs(R));
		civector candidateSums(1, candidateCount);
		candidateSums = IMatrixUtils::sumCols(abs(vectorCandidates));
		for (int candidateNo = 1; candidateNo <= candidateCount; candidateNo++) {
			// TODO: Is this a useful workaround?
			if (candidateSums[candidateNo] == 0) {
				normalizedResiduals[candidateNo] = candidateNo;
			} else {
				normalizedResiduals[candidateNo] = resultSums[candidateNo]
						/ candidateSums[candidateNo];
			}
		}

		// Choose and normalize vector with smallest normalized residual
		civector chosenVector(1, componentSize);
		cout << "ind = " << CIMatrixUtils::minIndex(normalizedResiduals)
				<< endl;
		chosenVector = vectorCandidates[Col(CIMatrixUtils::minIndex(normalizedResiduals))];
		/* Normalisierung: Schwierig, wenn sehr kleine Werte beteiligt (2.37E-322)
		 cout << "chosen vector = " << endl << chosenVector << endl;
		 chosenVector /= IMatrixUtils::norm2(abs(chosenVector));
		 */
		chosenEigenvectors[Col(eigenvalueNo)] = chosenVector;

		setProgressValue(eigenvalueNo);
	}

	cout << "eigenValues: " << eigenValues << endl << "eigenvectors:" << endl
			<< eigenVectors << endl << "chosenEigenvectors:" << endl
			<< chosenEigenvectors;

	eigenVectors = chosenEigenvectors;

	setProgressText("Done.");
}

cimatrix EigenvalueSolver::getIndexedRows(const cimatrix & matrix,
		const std::vector<int> & indices) {
	cimatrix result(indices.size(), indices.size());
	int indexCounter = 1;
	for (unsigned int i = 0; i < indices.size(); i++) {
		int index = indices[i];
		result[Row(indexCounter)] = matrix[Row(index)];
		indexCounter++;
	}

	return result;
}

bool EigenvalueSolver::isIncludedIn(const cimatrix & a, const cimatrix & b) {
	for (int i = Lb(a, 1); i <= Ub(a, 1); i++) {
		for (int j = Lb(a, 2); j <= Ub(a, 2); j++) {
			if (!(a[i][j] <= b[i][j])) {
				return false;
			}
		}
	}

	return true;
}

}
