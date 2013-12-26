#include "SMPOutputModeler.h"
#include <SMProcess.h>
#include <stdexcept>
#include <SMPWienerHopf.h>
#include <IMatrixUtils.h>
#include <limits.h>

namespace ivk
{

SMPOutputModeler::SMPOutputModeler(const SSMPQueue* data, const ComputationParameters &params)
: AbstractComputation<SSMPQueue, SSMProcess>(data, params)
{
	// check type of queue
	if(data->getQueueType() != SSMPQueue::Interarrival)
		throw new std::invalid_argument("Output modeler only applicable to queues given by interarrival / service times.");
}

SMPOutputModeler::~SMPOutputModeler()
{
}

void SMPOutputModeler::setParameters(const ComputationParameters &params)
{
	// nothing to do here...
}

SSMProcess* SMPOutputModeler::compute()
{
	// get queue parameters
	const int g = - Lb(m_ptrData->getDistribution(1,1));
	const int h = Ub(m_ptrData->getDistribution(1,1));
	cout << "g=" << g << ", h=" << h << endl;

	const int M = m_ptrData->getNumStates();

	// perform Wiener-Hopf factorization
	ComputationParameters whParams;
	whParams.setInt(SMPWienerHopf::PARAM_NUMITERATIONS, 200);
	whParams.setReal(SMPWienerHopf::PARAM_EPSILON, real(1e-14));
	whParams.setInt(SMPWienerHopf::PARAM_RELAXATIONSTEPS, 0);
	SMPWienerHopf wh(m_ptrData, whParams);
	const ISMPWHFactors* whFactors = wh.compute();

	IMatrixPolynomial l = whFactors->getIdleDistributions();
	IMatrixPolynomial v = whFactors->getPhaseDistributions();

	// SMP(2M)-Modell erzeugen
	// Übergangswahrscheinlichkeiten
	imatrix trans = IMatrixUtils::zeros(1,2*M,1,2*M);
	const imatrix p = m_ptrData->getTransitionMatrix();


	// (i,0) -> (j,0)
	for(int i = 1; i<=M; ++i)
	{
		for(int j=1; j<=M; ++j)
		{
			ivector u_ij = m_ptrData->getDistribution(i,j);
			for(int k=1; k<=g; ++k)
			{
				trans[i][j] += u_ij[-k];
			}
			trans[i][j] *= p[i][j];
		}
	}
	cout << trans << endl;
	for(int i = 1; i<=M; ++i)
	{
		for(int j=1; j<=M; ++j)
		{
			// (i,0) -> (i,1)
			if(i==j)
			{
				interval sum(0.0);
				for(int k = 1; k<=M; ++k)
					sum += trans[i][k];
				trans[i][M+i] = 1.0 - sum;
			}
			else
			{
				// (i,0) -> (j,1)
				trans[i][M+j] = 0.0;
				// (i,1) -> (j,1)
				trans[i+M][j+M] = 0.0;
			}


		}
	}
	cout << trans << endl;

	// Determine E(N_i)
	imatrix v1 = v.sum();
	const imatrix I = IMatrixUtils::eye(M);
	const ivector e_n = IMatrixUtils::sumRows(IMatrixUtils::invert(I-v1));

	// (i,1) -> (j,1)
	for(int i = 1; i<=M; ++i)
		trans[i+M][i+M] = 1.0 - (trans[i][i+M] / (e_n[i]-1.0));

	for(int i = 1; i<=M; ++i)
	{
		for(int j=1; j<=M; ++j)
		{

			// (i,1) -> (j,0)
			// Determine l_ij
			ivector l_ijk = l.getVectorAt(i,j);
			interval l_ij(0.0);
			for(int k=1; k<=g; ++k)
				l_ij += l_ijk[k];

			trans[i+M][j] = (l_ij - trans[i][j])*(1-trans[i+M][i+M])/trans[i][i+M];
		}
	}

	// DONE: Check for stochastic matrix!
	// cout << "Transition probs:" << endl << trans << endl << IMatrixUtils::sumRows(trans) << endl;

	// state-dependent distributions
	// I^(N=1) (z)
	// allocate space
	IMatrixPolynomial i_n_eq_1 = IMatrixPolynomial::zeros(1,g,1,M,1,M);
	for(int i = 1; i<=M; ++i)
	{
		for(int j = 1; j<=M; ++j)
		{
			// compute denominator
			interval denom(0.0);
			ivector u_ij = m_ptrData->getDistribution(i,j);
			for(int n=1; n<=g; ++n)
				denom += p[i][j] * u_ij[-n];
			for(int z=1; z<=g; ++z)
			{
				i_n_eq_1[z] =(p[i][j] * u_ij[-z]) / denom;
			}
		}
	}

	// I^(N>1) (z)
	// allocate space
	IMatrixPolynomial i_n_gr_1 = IMatrixPolynomial::zeros(0,g,1,M,1,M);
	for(int i = 1; i<=M; ++i)
	{
		for(int j = 1; j<=M; ++j)
		{
			// compute denominator
			interval denom(0.0);
			ivector u_ij = m_ptrData->getDistribution(i,j);
			ivector l_ij = l.getVectorAt(i,j);
			for(int n=1; n<=g; ++n)
				denom += u_ij[-n];
			denom = 1.0 - p[i][j]*denom;
			cout << "l_ij(0): " << l_ij[0] << endl;
			// compute nominator
			i_n_gr_1[0] = l_ij[0]/denom;
			for(int z=1; z<=g; ++z)
			{
				i_n_gr_1[z] = (l_ij[z]/p[i][j] - p[i][j]*u_ij[z])/denom;
			}
		}
	}
	// TODO: Assert valid distribution!
	imatrix sum_eq = IMatrixUtils::zeros(1,M,1,M);
	imatrix sum_gr = IMatrixUtils::zeros(1,M,1,M);
	imatrix sum_l = IMatrixUtils::zeros(1,M,1,M);
	imatrix sum_v = IMatrixUtils::zeros(1,M,1,M);
	imatrix sum_u = IMatrixUtils::zeros(1,M,1,M);

	for(int k = 1;k<=g; ++k)
	{
		imatrix test_eq = i_n_eq_1[k];
		imatrix test_gr = i_n_gr_1[k];
		for(int i = 1; i<=M; ++i)
			for(int j = 1; j<=M; ++j)
			{
				ivector u_ij = m_ptrData->getDistribution(i,j);
				ivector v_ij = v.getVectorAt(i,j);
				sum_u[i][j] += u_ij[k];
				sum_eq[i][j] += test_eq[i][j];
				sum_gr[i][j] += test_gr[i][j];
				//cout << "=: i=" << i << ", j=" << j << ", k=" << k << ": " << test_eq[i][j] << endl;
				cout << ">: i=" << i << ", j=" << j << ", k=" << k << ": " << test_gr[i][j] << endl;
				assert(Inf(test_eq[i][j])>=0.0);
				assert(1.0 >= Sup(test_eq[i][j]));
				/*
				assert(Inf(test_gr[i][j])>=0.0);
				assert(1.0 >= Sup(test_gr[i][j]));*/
			}
	}
	cout << "Sum =: " << endl << sum_eq << endl;
	cout << "Sum >: " << endl << sum_gr << endl;
	cout << "Sum l: " << endl << l.sum() << endl;
	cout << "Sum u(n), n>0: " << endl << sum_u << endl;
	cout << "p: " << endl << p << endl;
	cout << "l[0]:" << endl << i_n_gr_1[0] << endl;

	// state-specific distributions
	assert(m_ptrData->getServiceProcess()->getNumStates()==1);
	ivector s = m_ptrData->getServiceProcess()->getDistribution(1,1);

	// find bounds
	int lowerBound = INT_MAX;
	int upperBound = INT_MIN;
	for(int i = 1; i<=M; ++i)
	{
		for(int j = 1; j<=M; ++j)
		{
			const ivector i_n_eq_1_ij = i_n_eq_1.getVectorAt(i,j);
			const ivector i_n_gr_1_ij = i_n_gr_1.getVectorAt(i,j);
			// determine bounds
			lowerBound = std::min<int>(lowerBound, Lb(s));
			upperBound = std::max<int>(upperBound, Ub(s) + std::max<int>(Ub(i_n_eq_1_ij), Ub(i_n_gr_1_ij)));
		}
	}

	IMatrixPolynomial dists(lowerBound, upperBound, 1, 2*M, 1, 2*M);
	// state-independent parts
	const ivector a01 = s;
	const ivector a10 = s;

	for(int i = 1; i<=M; ++i)
	{
		for(int j = 1; j<=M; ++j)
		{
			const ivector i_n_eq_1_ij = i_n_eq_1.getVectorAt(i,j);
			const ivector i_n_gr_1_ij = i_n_gr_1.getVectorAt(i,j);
			const ivector a00 = IMatrixUtils::conv(i_n_eq_1_ij, s);
			const ivector a11 = IMatrixUtils::conv(i_n_gr_1_ij, s);

			// determine bounds
			const int lowerBound = Lb(s);
			const int upperBound = Ub(s) + std::max<int>(Ub(i_n_eq_1_ij), Ub(i_n_gr_1_ij));
			dists.setVectorAt(i, j, a00);
			dists.setVectorAt(i, j+M, a01);
			dists.setVectorAt(i+M, j, a10);
			dists.setVectorAt(i+M, j+M, a11);
		}
	}

	// create SMP model
	SMProcess outputModel(trans, dists);

	// convert to SSMP model
	SSMProcess* ssmpOutputModel = new SSMProcess(outputModel);

	// return
	return ssmpOutputModel;
}

}
