#include "OrderedOutputLink.h"

#include <iostream>

using std::cout;
using std::endl;

using std::make_pair;

namespace ivk
{
	
OrderedOutputLink::OrderedOutputLink(const int bufferSize, const ivector &capacity)
: BaseOutputLink(bufferSize, capacity)
{
	
}

OrderedOutputLink::~OrderedOutputLink()
{
}

void OrderedOutputLink::tick()
{
	m_tickCount++;
	
	// Starting with full capacity.
	ivector capacity(m_capacity);
	
	// for each output traffic
	list<Traffic*>::iterator trafficIter;
	
	int trafficCount = 0;
	for(trafficIter = m_inTraffics.begin(); trafficIter != m_inTraffics.end(); ++trafficIter)
	{	
		trafficCount++;
		// fetch output object
		Traffic* ptrTraffic = *trafficIter;
		map<Traffic*, Traffic*>::iterator outputIter = m_outTraffics.find(ptrTraffic);
		Traffic* ptrOutput = outputIter->second;
		
		// fetch buffer for traffic flow
		map<Traffic*, ivector>::iterator bufferIter = m_buffers.find(ptrOutput);
		ivector &buffer = bufferIter->second;
		
		// compute departure traffic according to remaining capacity
		
		ivector arrival = ptrTraffic->getDistribution();
		interval loss = interval(0.0);
		
		ivector depart = computeStep(buffer, loss, arrival, capacity);
		
		// set departure traffic
		ptrOutput->setDistribution(depart);
		ptrOutput->setLoss(loss);
		
		capacity = computeRemaining(depart, capacity);		
	}
}



}
