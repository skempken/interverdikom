#include "GIOutputModeler.h"

#include <SMProcess.h>
#include <stdexcept>
#include <SMPWienerHopf.h>
#include <IMatrixUtils.h>

namespace ivk
{

GIOutputModeler::GIOutputModeler(const SSMPQueue* data, const ComputationParameters &params)
: AbstractComputation<SSMPQueue, SSMProcess>(data, params)
{
	// check number of states
	if(data->getNumStates() > 1)
		throw new std::invalid_argument("Output modeler only applicable to GI/G/1 queues.");
	// check type of queue
	if(data->getQueueType() != SSMPQueue::Interarrival)
		throw new std::invalid_argument("Output modeler only applicable to queues given by interarrival / service times.");
}

GIOutputModeler::~GIOutputModeler()
{
}

void GIOutputModeler::setParameters(const ComputationParameters &params)
{
	// nothing to do here...
}

SSMProcess* GIOutputModeler::compute()
{
	const int g = - Lb(m_ptrData->getDistribution(1,1));
	const int h = Ub(m_ptrData->getDistribution(1,1));
	const ivector u = m_ptrData->getDistribution(1,1);

	// perform Wiener-Hopf factorization
	ComputationParameters whParams;
	whParams.setInt(SMPWienerHopf::PARAM_NUMITERATIONS, 200);
	whParams.setReal(SMPWienerHopf::PARAM_EPSILON, real(1e-14));
	SMPWienerHopf wh(m_ptrData, whParams);
	const ISMPWHFactors* whFactors = wh.compute();

	ivector l = whFactors->getIdleDistributions().getVectorAt(1,1);
	ivector v = whFactors->getPhaseDistributions().getVectorAt(1,1);

	// create SMP model as described by Haßlinger
	// transition probabilities
	imatrix trans = IMatrixUtils::zeros(1,2,1,2);

	// a_00
	for(int i = 1; i<=g; ++i)
		trans[1][1] += u[-i];

	// E(N) = (I-V(1))^-1
	interval v1(0.0);
	for(int i = Lb(v); i<=Ub(v); ++i)
		v1 += v[i];
	interval e_n = 1.0 / (1.0 - v1);

	// a_11
	trans[2][2] = 1.0 - ((1.0 - trans[1][1])/(e_n - 1.0));

	// a_01, a_10
	trans[1][2] = 1.0 - trans[1][1];
	trans[2][1] = 1.0 - trans[2][2];

	// END of transition probabilities.

	// I^(N=1) (z)
	ivector i_n_eq_1(1,g);
	for(int i = 1; i<=g; ++i)
	{
		i_n_eq_1[i] = u[-i] / trans[1][1];
	}

	// I^(N>1) (z)
	ivector i_n_gr_1(1,g);
	for(int i = 1; i<=g; ++i)
	{
		i_n_gr_1[i] = (l[i] - trans[1][1]*i_n_eq_1[i])/(1.0 - trans[1][1]);
	}

	// state-specific distributions
	ivector s = m_ptrData->getServiceProcess()->getDistribution(1,1);
	ivector a00 = IMatrixUtils::conv(i_n_eq_1, s);
	ivector a01 = s;
	ivector a10 = s;
	ivector a11 = IMatrixUtils::conv(i_n_gr_1, s);

	// determine bounds
	int lowerBound = Lb(s);
	int upperBound = Ub(s) + std::max<int>(Ub(i_n_eq_1), Ub(i_n_gr_1));

	IMatrixPolynomial distributions(lowerBound, upperBound,1,2,1,2);
	imatrix emptyMatrix(1,2,1,2);
	emptyMatrix[1][1] = interval(0.0); emptyMatrix[1][2] = interval(0.0);
	emptyMatrix[2][1] = interval(0.0); emptyMatrix[2][2] = interval(0.0);
	for(int i = lowerBound; i<=upperBound; ++i)
		distributions[i] = emptyMatrix;
	distributions.setVectorAt(1,1,a00);
	distributions.setVectorAt(1,2,a01);
	distributions.setVectorAt(2,1,a10);
	distributions.setVectorAt(2,2,a11);


	// create SMP model
	SMProcess outputModel(trans, distributions);

	// convert to SSMP model
	SSMProcess* ssmpOutputModel = new SSMProcess(outputModel);

	// return
	return ssmpOutputModel;
}

}
