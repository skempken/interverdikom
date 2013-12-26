#include "data/ISMPPFResult.h"

#include <iostream>
#include <map>
#include <assert.h>
#include <imatrix.hpp>

#include "utility/solvers/CComplexILinSys.hpp"
#include "utility/MatlabExport.h"

using std::cout;
using std::cerr;
using std::endl;
using std::multimap;

namespace ivk {

cinterval ipower(const cinterval &value, int exp) {
	cinterval ret = 1/value;
	for (int i = -1; i>exp; --i)
		ret = ret * value;
	return 1/ret;
}

ISMPPFResult::ISMPPFResult() :
	success(false) {
}

ISMPPFResult::~ISMPPFResult() {
}

bool ISMPPFResult::getVerifiedCoefficients(cimatrix & alpha, civector & beta) const {
	cout << "Choosing suitable eigenvalues..." << endl;
	int Mh = M*h;
	alpha = cimatrix(1, Ub(eigenVectors, 1), 1, Mh); // gewählte Eigenvektoren
	beta = civector(1, Mh); // gewählte Eigenwerte

	
	multimap<double,int> sortedIndices;
	typedef std::pair<double,int> IndexPair;
	for (int i = Lb(eigenValues); i <= Ub(eigenValues); i++) {
		double absValue = _double(Sup(abs(eigenValues[i])));
		sortedIndices.insert(IndexPair(absValue, i));
	}

	int selectedValues = 0;
	map<double,int>::iterator it;
	for (it = sortedIndices.begin(); it != sortedIndices.end(); it++) {
		double absValue = (*it).first;
		int valueIndex = (*it).second;

		if ((absValue < 1.0) && (selectedValues < Mh)) {
			cout << "Selected value: " << eigenValues[valueIndex] << " with abs: " << abs(Sup(eigenValues[valueIndex])) << endl;
			selectedValues++;
			
			beta[selectedValues] = eigenValues[valueIndex];
			alpha[Col(selectedValues)] = eigenVectors[Col(valueIndex)];
		} else {
			if (absValue < 1.0) {
				cout << "Additional values are available!" << endl;
			}
			
			break;
		}
	}

	cout << "Selected " << selectedValues << " out of total " << Ub(eigenValues)
			<< " values. Required: " << Mh << ". M: " << M << ", h: " << h
			<< "." << endl << endl;
	
	if (selectedValues < Mh) {
		return false;
	}
	
	/*
	int j = 1;
	for (int i = Lb(eigenValues); i <= Ub(eigenValues); i++) {
		if (j > (Mh)) {
			cout << "Additional eigenvalue!" << endl;
			break;
		}

		if (abs(Sup(eigenValues[i])) < 0.9999999) {
			cout << "Added " << eigenValues[i] << " with abs: " << abs(Sup(eigenValues[i])) << endl;
			beta[j] = eigenValues[i];
			alpha[Col(j)] = eigenVectors[Col(i)];
			j++;
		}
	}

	cout << "Filtered eigenvalues: Selected " << (j-1) << " out of a total of " << Ub(eigenValues) << " values. Required: " << Mh << " values. M: " << M << ", h: " << h << endl;
	if (j <= Mh) {
		return false;
	}
*/
	
	return true;
}

bool ISMPPFResult::calculateGamma(const SSMProcess & process) {
	//return true;
	imatrix tm = process.getTransitionMatrix();
	M = RowLen(tm);
	h = Ub(process.getDistributions(), 2);
	int Mh = M * h;

	cimatrix alpha; // gewählte Eigenvektoren
	civector beta; // gewählte Eigenwerte

	bool enoughEigenvalues = getVerifiedCoefficients(alpha, beta);
	if (!enoughEigenvalues) {
		cerr << "Nicht genug Eigenwerte im Einheitskreis!" << endl;
		return false;
	}

	// Aufstellen des Gleichungssystems für Koeffizienten gamma
	cimatrix G(1, Mh, 1, Mh);

	// first blockrow, betaexp = -1
	for (int row = 1; row <= M; row++) {
		for (int col=1; col <= Mh; col++) {
			G[row][col] = alpha[row][col]/beta[col];
		}
	}

	// subsequent blockrows, betaexp = -2..-h+1
	for (int block = 2; block<h; block++) {
		for (int row = 1; row <= M; row++) {
			for (int col=1; col <= Mh; col++) {
				assert((block-1)*M + row <= Mh);
				G[(block-1)*M + row][col] = G[(block-2)*M + row][col]/beta[col];
			}
		}
	}

	// last blockrow
	for (int row = 1; row <= M; row++) {
		for (int col=1; col <= Mh; col++) {
			assert((Mh-M) + row <= Mh);
			G[(Mh-M) + row][col] = alpha[row][col]/(1.0 - beta[col]);
		}
	}

	civector p = civector(process.getStationaryProbabilities());
	civector b(1, Mh);
	b = 0;
	for (int i = 1; i <= M; i++) {
		b[(Mh-M) + i] = p[i];
	}

	// Lösen des Gleichungssystems
	CComplexILinSys solver;
	int errorCode;
	civector gamma(1, Mh);

	cout << "G: " << endl << G << endl;
	cout << "b: " << endl << b << endl;
	solver.CILinSolve(G, b, gamma, errorCode);

	cout << "Gamma: " << endl << gamma << endl;

	this->gamma = gamma;

	return true;
}

IWorkloadVector ISMPPFResult::getWorkload(int k) const {
	cout << "Calculating workload up to " << k << "..." << endl << endl;
	ivector workload(0, k);

	for (int i = 0; i <= k; i++) {
		workload[i] = getWorkloadComponent(i);
		cout << "Workload[" << i << "] = " << workload[i] << endl << endl;
	}
	
	cout << "Done." << endl << endl;

	return IWorkloadVector(workload);
}

template<class T>
T customPow(T base, int exponent) {
	T result;
	result = 1;
	for (int i = 0; i < exponent; i++) {
		result *= base;
	}
	return result;
}

interval ISMPPFResult::getWorkloadComponent(int k) const {
	cimatrix alpha;
	civector beta;
	getVerifiedCoefficients(alpha, beta);

	int Mh = M*h;
	cxsc::cinterval workload;
	workload = 0;
	for (int i = 1; i <= Mh; i++) {
		cinterval _alpha;
		_alpha = 0;
		for (int j = 1; j <= M; j++) {
			_alpha += gamma[i] * alpha[j][i];
		}
		
		workload += _alpha * customPow(beta[i], k);
	}
	
	cout << "workload = " << workload << endl << "abs(workload) = " << abs(workload) << endl;
	return abs(workload);
}

}
