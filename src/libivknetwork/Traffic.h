#ifndef TRAFFIC_H_
#define TRAFFIC_H_

#include <interval.hpp>
#include <ivector.hpp>

using cxsc::interval;
using cxsc::ivector;

namespace ivk
{

class Traffic
{
public:
	Traffic(const ivector &distribution);
	virtual ~Traffic();

	ivector getDistribution();
	void setDistribution(const ivector &distribution);
	interval getLoss();
	void setLoss(const interval &loss);

private:
	/// Probability of data loss at source node.
	interval m_loss;
	ivector m_distribution;
};

}

#endif /*TRAFFIC_H_*/
