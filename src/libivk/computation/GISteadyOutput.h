#ifndef GISTEADYOUTPUT_H_
#define GISTEADYOUTPUT_H_

#include "AbstractComputation.hpp"
#include "data/GIProcess.h"

#include <utility>

using std::pair;

namespace ivk
{

class GISteadyOutput : public AbstractComputation<pair<GIProcess,GIProcess>, GIProcess>
{
public:
	GISteadyOutput(const pair<GIProcess,GIProcess>* queue, const ComputationParameters &parameters);
	virtual ~GISteadyOutput();
	
	GIProcess* compute();
	virtual void setParameters(const ComputationParameters &parameters) {};
	
private:
	const GIProcess* m_arrival;
	const GIProcess* m_service;
	const GIProcess* m_output;
	const GIProcess* m_workload;
};

}

#endif /*GISTEADYOUTPUT_H_*/
