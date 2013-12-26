#include "GISteadyOutput.h"
#include "SMPWienerHopf.h"
#include "ISMPWHWorkload.h"

namespace ivk
{

GISteadyOutput::GISteadyOutput(const pair<GIProcess,GIProcess>* queue, const ComputationParameters &parameters)
: AbstractComputation< pair<GIProcess,GIProcess>, GIProcess>(queue, parameters)
{
	this->m_output = 0;
	this->m_workload = 0;
	this->m_arrival = &(queue->first);
	this->m_service = &(queue->second);
	rvector tmp = rvector(0,0);
	tmp[0] = 0.0;
	this->m_output = new GIProcess(tmp);
	tmp[0] = 1.0;
	this->m_workload = new GIProcess(tmp);
}

GISteadyOutput::~GISteadyOutput()
{
	if(this->m_output) delete m_output;
	if(this->m_workload) delete m_workload;
}

GIProcess* GISteadyOutput::compute()
{
	// Construct queue object
	GIProcess queue = (*m_arrival) - (*m_service);
		
	// Wiener-Hopf factorization of the queue object
	const int workloadUpTo = 500;
	
	ComputationParameters param_wh;
	param_wh.setReal(SMPWienerHopf::PARAM_EPSILON, 1e-15);
	param_wh.setInt(SMPWienerHopf::PARAM_NUMITERATIONS, 500);
	SMPWienerHopf _wh(&queue, param_wh);
	ISMPWHFactors* whfactors = _wh.compute();
	
	ComputationParameters param_workload;
	param_workload.setInt(ISMPWHWorkload::PARAM_UPTO, workloadUpTo);
	ISMPWHWorkload _wl(whfactors, param_workload);
	ivector iWorkloads = _wl.compute()->getWorkloadVector();
	
	// copy workload
	if(m_workload) delete m_workload;
	m_workload = new GIProcess(iWorkloads);
	
	// Convolutions
	// O = min(W+A,S)
	ivector	tmp = SSMProcess::addDists(iWorkloads, m_arrival->getDistribution());
	ivector service = m_service->getDistribution();
	ivector depart(0, Ub(service));
	
	// Abgangsverteilung
	for(int k = Lb(depart); k<=Ub(depart); ++k)
	{
		idotprecision _depart;
		_depart = interval(0.0);
		
		for(int i=k; i<=Ub(service); ++i)
		{
			accumulate(_depart, tmp[k], service[i]);
		}
		
		for(int j=k+1; j<=Ub(tmp); ++j)
		{
			accumulate(_depart, service[k], tmp[j]);
		}
		
		depart[k] = rnd(_depart);
	}
	
	return new GIProcess(depart);
}

}
