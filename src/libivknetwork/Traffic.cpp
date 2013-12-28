#include "Traffic.h"

namespace ivk
{

Traffic::Traffic(const ivector &distribution)
{
	m_loss = 0.0;
	m_distribution = distribution;
}

Traffic::~Traffic()
{
}

ivector Traffic::getDistribution()
{
	return m_distribution;
}

void Traffic::setDistribution(const ivector &distribution)
{
	m_distribution = distribution;
}

interval Traffic::getLoss()
{
	return m_loss;
}

void Traffic::setLoss(const interval &loss)
{
	m_loss = loss;
}

}
