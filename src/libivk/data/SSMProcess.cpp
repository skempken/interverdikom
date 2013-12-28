#include "data/SSMProcess.h"

#include <ivector.hpp>
#include <assert.h>
#include "utility/RMatrixUtils.h"
#include "utility/IMatrixUtils.h"

#include "utility/Logging.hpp"

namespace ivk
{
SSMProcess::SSMProcess(): SMProcess()
{
	setDistributions(rmatrix(0,0,0,0));
}

SSMProcess::SSMProcess(const SMProcess &process)
{
	const int numStatesSMP = process.getNumStates();

	// determine number of states.
	const int numStates = numStatesSMP * numStatesSMP;

	// Assumption: Lower and upper bound is the same for each distribution
	ivector tmpDist = process.getDistribution(1, 1);
	imatrix distsSSMP(1, numStates, Lb(tmpDist), Ub(tmpDist));

	int stateCount = 1;
	// set distributions.
	for(int stateFrom = 1; stateFrom <= numStatesSMP; ++stateFrom)
	{
		for(int stateTo = 1; stateTo <= numStatesSMP; ++stateTo)
		{
			ivector dist = process.getDistribution(stateFrom, stateTo);
			distsSSMP[stateCount++] = dist;
		}
	}
	setDistributions(distsSSMP);

	// set transition matrix.
	imatrix trans = IMatrixUtils::zeros(1, numStates, 1, numStates);
	imatrix transSMP = process.getTransitionMatrix();
	int row = 1;
	for(int i = 1; i<=numStatesSMP; ++i)
	{
		int col = 1;
		for(int stateFrom = 1; stateFrom <= numStatesSMP; ++stateFrom)
		{
			for(int stateTo = 1; stateTo <= numStatesSMP; ++stateTo)
			{
				trans[row][col] = transSMP[stateFrom][stateTo];
				col++;
			}
			row++;
		}
	}
	setTransitionMatrix(trans);
}

IMatrixPolynomial SSMProcess::getCharacteristicPolynomialMatrix() const {
	IMatrixPolynomial polynomial(-Ub(m_distributions, 2), -Lb(m_distributions, 2), Lb(m_transition,1), Ub(m_transition,1), Lb(m_transition,2), Ub(m_transition,2));
	for (int k = Lb(m_distributions, 2); k <= Ub(m_distributions, 2); k++) {
		int componentSize = Ub(m_transition, 1) - Lb(m_transition, 1)+ 1;
		imatrix componentMatrix(1, componentSize, 1, componentSize);
		for (int i = Lb(m_transition, 1); i <= Ub(m_transition, 1); i++) {
			for (int j = Lb(m_transition, 2); j <= Ub(m_transition, 2); j++) {
				int compI = i - Lb(m_transition, 1) + 1;
				int compJ = j - Lb(m_transition, 2) + 1;
				componentMatrix[compJ][compI] = m_transition[i][j]
						* m_distributions[i][k];
			}
		}

		if (k == 0) {
			componentMatrix -= IMatrixUtils::eye(componentSize);
		}

		polynomial[-k] = componentMatrix;
	}
	
	return polynomial;
}

SSMProcess::SSMProcess(const rmatrix &_transition, const rmatrix &_distributions, const int trimEmptyStates)
: SMProcess(_transition)
{
	rmatrix trimmedTrans = _transition;
	assert(Lb(_transition,1)==1);
	assert(Lb(_transition,2)==1);
	assert(Lb(_distributions,1)==1);

	rmatrix trimmedDist = _distributions;

	// trim empty states?
	if(trimEmptyStates)
	{
		int emptyState;
		do
		{
			// Assume no empty state
			emptyState = -1;
			// Compute distribution sums
			rvector distSums = RMatrixUtils::sumRows(trimmedDist);
			// Look for empty distribution
			for(int trimState = Lb(distSums); trimState<=Ub(distSums); ++trimState)
			{
				if(distSums[trimState]==0.0){
					emptyState = trimState;
					emptyState *= 1;
				}
			}
			// if emptyState != -1: Remove state.
			if(emptyState>=0)
			{
				trimmedDist = RMatrixUtils::rmRow(trimmedDist, emptyState);
				trimmedTrans = RMatrixUtils::rmRow(trimmedTrans, emptyState);
				trimmedTrans = RMatrixUtils::rmCol(trimmedTrans, emptyState);
				Logging::log(Logging::Debug, "Trimmed state ", emptyState);
			}
		}
		while(emptyState>=0);
	}

	// accept Values.
	setTransitionMatrix(trimmedTrans);
	setDistributions(trimmedDist);

	Logging::log(Logging::Debug, "Variance of SMP ", this->getVariance());
}

SSMProcess::SSMProcess(const imatrix &_transition, const imatrix &_distributions, const int trimEmptyStates)
: SMProcess(_transition)
{
	assert(Lb(_transition,1)==1);
	assert(Lb(_transition,2)==1);
	assert(Lb(_distributions,1)==1);

	imatrix trimmedDist = _distributions;
	imatrix trimmedTrans = _transition;

	// trim empty states?
	if(trimEmptyStates)
	{
		int emptyState;
		do
		{
			// Assume no empty state
			emptyState = -1;
			// Compute distribution sums
			ivector distSums = IMatrixUtils::sumRows(trimmedDist);
			// Look for empty distribution
			for(int trimState = Lb(distSums); trimState<=Ub(distSums); ++trimState)
			{
				if(0.0 <= distSums[trimState])
					emptyState = trimState;
			}
			// if emptyState != -1: Remove state.
			if(emptyState>=0)
			{
				trimmedDist = IMatrixUtils::rmRow(trimmedDist, emptyState);
				trimmedTrans = IMatrixUtils::rmRow(trimmedTrans, emptyState);
				trimmedTrans = IMatrixUtils::rmCol(trimmedTrans, emptyState);
				Logging::log(Logging::Debug, "Trimmed state ", emptyState);
			}
		}
		while(emptyState>=0);
	}

	// accept Values.

	setTransitionMatrix(trimmedTrans);
	setDistributions(trimmedDist);
}

SSMProcess::~SSMProcess()
{
}

void SSMProcess::setDistributions(const rmatrix &_distributions)
{
	this->m_distributions = (imatrix)_distributions;
}

void SSMProcess::setDistributions(const imatrix &_distributions)
{
	this->m_distributions = _distributions;
}

imatrix SSMProcess::getDistributions() const
{
	return this->m_distributions;
}

ivector SSMProcess::getDistribution(const int stateFrom, const int stateTo) const
{
	return this->m_distributions[stateFrom];
}

real SSMProcess::getExpectationValue() const
{
	rvector statProb(this->getStationaryProbabilities());
	real sum = 0.0;
	rvector means = this->getStateMeans();
	for(int state = Lb(statProb); state <=Ub(statProb); ++state)
	{
		sum += means[state]*statProb[state];
	}
	return sum;
}

rvector SSMProcess::getStateMeans() const
{
	imatrix transition = getTransitionMatrix();
	rvector ret(Lb(transition, 1), Ub(transition,1));
	for(int state = Lb(ret); state <=Ub(ret); ++state)
	{
		real sum = 0.0;
		for(int j = Lb(m_distributions,2); j<=Ub(m_distributions,2); ++j)
		{
			sum += mid(m_distributions[state][j])*j;
		}
		ret[state] = sum;
	}
	return ret;
}

rvector SSMProcess::getAutocorrelation(const int n) const
{
	rvector autok(0,n);
	const rmatrix umatrix = mid(this->getTransitionMatrix());
	const rvector statWahr = this->getStationaryProbabilities();
	const rvector zmittelwerte = this->getStateMeans();
	const int m = this->getNumStates();
	rmatrix P_n(umatrix);

	// compute expectation value of the process
	real E_A = 0;
	for(int i = 1;i <= m;i++){
		E_A += (real)( statWahr[i] * zmittelwerte[i]);
	}

	/*
	// compute variance *according to state means*
	real v = 0;
	for(int i = 0;i < m;i++){
		v += statWahr[i] * power(((real) zmittelwerte[i] - E_A),2);
	}
	*/

	// compute actual variance of the process
	const real v = this->getVariance();

	const real E_A2 = E_A * E_A / v;
	const rvector p = statWahr / v;

	// A(0)
	// Expectation values squared
	rvector E2(1,m);
	for(int i = 1;i <= m;i++){
		E2[i] = zmittelwerte[i]*zmittelwerte[i];
	}
	autok[0] = (p*E2) - E_A2;

	// A(i), 0<i<n
	for(int x = 1;x <= n;x++){
		autok[x] = 0;
		for(int i = 1;i <= m;i++){
			for(int j = 1;j <= m;j++){
				autok[x] = autok[x] + (p[i]*zmittelwerte[i]*P_n[i][j]*zmittelwerte[j]);
			}
		}
		autok[x] = autok[x] - E_A2;
		P_n = P_n * umatrix;
	}
	return autok;
}

real SSMProcess::getVariance() const
{
	const real mean = this->getExpectationValue();
	const rmatrix dist = mid(this->getDistributions());
	const rvector stateProb = this->getStationaryProbabilities();

	real v = 0.0;
	for(int state = Lb(dist,1); state<=Ub(dist,1); ++state)
	{
		for(int value = Lb(dist,2); value<=Ub(dist,2); ++value)
		{
			const real tmp = value - mean;
			v += stateProb[state] * dist[state][value] * tmp * tmp;
		}
	}

	return v;
}

real SSMProcess::getStandardDeviation() const
{
	return sqrt(this->getVariance());
}

SSMProcess operator-(const SSMProcess &A, const SSMProcess &B)
{
	// C = A + B
	const int statesA = A.getNumStates();
	const int statesB = B.getNumStates();
	const int statesC = statesA * statesB;

	// Neue Übergangsmatrix
	imatrix transitionC(0,statesC-1,0,statesC-1);
	imatrix transitionA = A.getTransitionMatrix();
	SetLb(transitionA,1,0); SetLb(transitionA,2,0);
	imatrix transitionB = B.getTransitionMatrix();
	SetLb(transitionB,1,0); SetLb(transitionB,2,0);
	for(int i = 0; i<statesA; ++i)
	{
		for(int k=0; k<statesB; ++k)
		{
			for(int j=0; j<statesA; ++j)
			{
				for(int l=0; l<statesB; ++l)
				{
					transitionC[i*statesB + k][j*statesB+l] = transitionA[i][j]* transitionB[k][l];
				}
			}
		}
	}

	// Neue Ankunftsverteilungen
	imatrix dA = A.getDistributions();
	imatrix dB = B.getDistributions();
	const int lbC = Lb(dA,2)-Ub(dB,2);
	const int ubC = Ub(dA,2)-Lb(dB,2);
	imatrix distsC(Lb(transitionC,1), Ub(transitionC,1), lbC, ubC);
	int stateCount = Lb(distsC,1);
	for(int m = Lb(dA,1); m<=Ub(dA,1); ++m)
	{
		for(int n=Lb(dB,1); n<=Ub(dB,1); ++n)
		{
			distsC[stateCount++] = SSMProcess::subDists(dA[m], dB[n]);
		}
	}
	// Set bounds accordingly.
	SetLb(transitionC,1,1);
	SetLb(transitionC,2,1);
	SetLb(distsC,1,1);
	return SSMProcess(transitionC,distsC);
}

SSMProcess operator+(const SSMProcess &A, const SSMProcess &B)
{
	// C = A + B
	const int statesA = A.getNumStates();
	const int statesB = B.getNumStates();
	const int statesC = statesA * statesB;

	// Neue Übergangsmatrix
	imatrix transitionC(0,statesC-1,0,statesC-1);
	imatrix transitionA = A.getTransitionMatrix();
	SetLb(transitionA,1,0); SetLb(transitionA,2,0);
	imatrix transitionB = B.getTransitionMatrix();
	SetLb(transitionB,1,0); SetLb(transitionB,2,0);
	for(int i = 0; i<statesA; ++i)
	{
		for(int k=0; k<statesB; ++k)
		{
			for(int j=0; j<statesA; ++j)
			{
				for(int l=0; l<statesB; ++l)
				{
					transitionC[i*statesB + k][j*statesB+l] = transitionA[i][j]* transitionB[k][l];
				}
			}
		}
	}

	// Neue Ankunftsverteilungen
	imatrix dA = A.getDistributions();
	imatrix dB = B.getDistributions();
	const int lbC = Lb(dA,2)-Ub(dB,2);
	const int ubC = Ub(dA,2)-Lb(dB,2);
	imatrix distsC(Lb(transitionC,1), Ub(transitionC,1), lbC, ubC);
	int stateCount = Lb(distsC,1);
	for(int m = Lb(dA,1); m<=Ub(dA,1); ++m)
	{
		for(int n=Lb(dB,1); n<=Ub(dB,1); ++n)
		{
			distsC[stateCount++] = SSMProcess::addDists(dA[m], dB[n]);
		}
	}

	// Set bounds accordingly.
	SetLb(transitionC,1,1);
	SetLb(transitionC,2,1);
	SetLb(distsC,1,1);
	return SSMProcess(transitionC,distsC);
}

ivector SSMProcess::subDists(const ivector &dA, const ivector &dB)
{
	ivector dC(Lb(dA)-Ub(dB),Ub(dA)-Lb(dB));

	for(int i = Lb(dC); i<= Ub(dC); i++)
		dC[i] = interval(0.0,0.0);

	//Differenzverteilung berechnen

	for(int i = Lb(dA); i<=Ub(dA); i++)
	{
		for(int j = Lb(dB); j<=Ub(dB); j++)
		{
			assert(i-j >= Lb(dC));
			assert(i-j <= Ub(dC));
			dC[i-j] += dA[i]*dB[j];
		}
	}

	return dC;
}

ivector SSMProcess::addDists(const ivector &dA, const ivector &dB)
{
	// simple Faltung
	ivector dC(Lb(dA)+Lb(dB),Ub(dA)+Ub(dB));

	// Initialisieren
	for(int i = Lb(dC); i<= Ub(dC); i++)
		dC[i] = interval(0.0,0.0);

	//Differenzverteilung berechnen

	for(int i = Lb(dA); i<=Ub(dA); i++)
	{
		for(int j = Lb(dB); j<=Ub(dB); j++)
		{
			assert(i+j >= Lb(dC));
			assert(i+j <= Ub(dC));
			dC[i+j] += dA[i]*dB[j];
		}
	}

	return dC;
}

void SSMProcess::trimDistributions()
{
	// trim left.
	int lb = Lb(m_distributions,2);
	for(;lb<=Ub(m_distributions,2); ++lb)
	{
		bool isZero = true;
		for(int state = Lb(m_distributions,1); state<=Ub(m_distributions,1); ++state)
		{
			if(m_distributions[state][lb]!=0.0)
			{
				isZero = false;
				break;
			}
		}
		if(!isZero) break;
	}

	// trim right.
	int ub = Ub(m_distributions,2);
	for(;ub>=Lb(m_distributions,2); --ub)
	{
		bool isZero = true;
		for(int state = Lb(m_distributions,1); state<=Ub(m_distributions,1); ++state)
		{
			if(m_distributions[state][ub]!=0.0)
			{
				isZero = false;
				break;
			}
		}
		if(!isZero) break;
	}

	// trim.
	m_distributions = m_distributions(Lb(m_distributions,1), Ub(m_distributions,1), lb, ub);
}

rvector SSMProcess::subDists(const rvector &dA, const rvector &dB)
{
	rvector dC(Lb(dA)-Ub(dB),Ub(dA)-Lb(dB));

	for(int i = Lb(dC); i<= Ub(dC); i++)
		dC[i] = 0.0;

	//Differenzverteilung berechnen

	for(int i = Lb(dA); i<=Ub(dA); i++)
	{
		for(int j = Lb(dB); j<=Ub(dB); j++)
		{
			assert(i-j >= Lb(dC));
			assert(i-j <= Ub(dC));
			dC[i-j] += dA[i]*dB[j];
		}
	}

	return dC;
}

rvector SSMProcess::addDists(const rvector &dA, const rvector &dB)
{
	// simple Faltung
	rvector dC(Lb(dA)+Lb(dB),Ub(dA)+Ub(dB));

	// Initialisieren
	for(int i = Lb(dC); i<= Ub(dC); i++)
		dC[i] = 0.0;

	//Differenzverteilung berechnen

	for(int i = Lb(dA); i<=Ub(dA); i++)
	{
		for(int j = Lb(dB); j<=Ub(dB); j++)
		{
			assert(i+j >= Lb(dC));
			assert(i+j <= Ub(dC));
			dC[i+j] += dA[i]*dB[j];
		}
	}

	return dC;
}

}
