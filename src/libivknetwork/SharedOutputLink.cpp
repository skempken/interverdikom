#include "SharedOutputLink.h"

#include "convolution.h"
#include <iostream>

using std::cout;
using std::endl;

namespace ivk
{

interval sum(ivector vector)
{
	idotprecision ret;
	ret = interval(0.0);
	for(int i = Lb(vector); i<=Ub(vector); ++i)
		accumulate(ret,vector[i], interval(1.0));
	return rnd(ret);
}
	

SharedOutputLink::SharedOutputLink(const int bufferSize, const ivector &capacity)
: BaseOutputLink(bufferSize, capacity)
{
	
}

SharedOutputLink::~SharedOutputLink()
{
}

void SharedOutputLink::tick()
{
	m_tickCount++;
	// cout << "Tick " << m_tickCount << endl;
	
	// Starting with full capacity.
	ivector capacity(m_capacity);
	// cout << "Full capacity: " << sum(capacity) << endl;
	
	// Compute reserved shared capacity.
	const int numFlows = m_inTraffics.size();
	ivector sharedCapacity(0, Ub(m_capacity)/numFlows);
	for(int i = Lb(sharedCapacity); i<=Ub(sharedCapacity); ++i)
	{
		sharedCapacity[i] = 0.0;
	}
	for(int i = Lb(m_capacity); i<=Ub(m_capacity); ++i)
	{
		sharedCapacity[i/numFlows] += m_capacity[i];
	}
	
	// cout << "Reserved per stream: " << sum(sharedCapacity) << endl;

	// Compute capacity for remaining flows
	ivector restCapacity(0, Ub(m_capacity));
	restCapacity[0] = 1.0;
	for(int i=1; i<=Ub(restCapacity); ++i)
		restCapacity[i] = 0.0;
	
	for(int i = 1; i<numFlows; ++i)
		restCapacity = convAdd(restCapacity, sharedCapacity);
	// cout << "Complement / Available for other streams:" << sum(restCapacity) << endl;
		
	// cache buffers
	map<Traffic*, ivector> bufferCache;
	map<Traffic*, ivector>::iterator indexIter;
	for(indexIter = m_buffers.begin(); indexIter != m_buffers.end(); ++indexIter)
	{
		Traffic* a = indexIter->first;
		ivector b(indexIter->second);
		bufferCache.insert(std::make_pair(a,b));
	}
	
	// for each output traffic
	list<Traffic*>::iterator trafficIter;
	
	for(trafficIter = m_inTraffics.begin(); trafficIter != m_inTraffics.end(); ++trafficIter)
	{
		// fetch output object
		Traffic* ptrTraffic = *trafficIter;
		map<Traffic*, Traffic*>::iterator outputIter = m_outTraffics.find(ptrTraffic);
		Traffic* ptrOutput = outputIter->second;
		
		// fetch buffer for traffic flow
		map<Traffic*, ivector>::iterator bufferIter = m_buffers.find(ptrOutput);
		ivector &buffer = bufferIter->second;
		
		// compute capacity considering other streams
		// copy rest capacity
		ivector remainingCapacity(restCapacity);
		// cout << "Remaining capacity for other streams: " << sum(remainingCapacity) << endl;
		list<Traffic*>::iterator otherTrafficIter;
		for(otherTrafficIter=m_inTraffics.begin(); otherTrafficIter!=m_inTraffics.end(); ++otherTrafficIter)
		{
			// All traffic flows except current one.
			if(otherTrafficIter == trafficIter) continue;
			
			// fetch output object
			Traffic* ptrTraffic = *otherTrafficIter;
			map<Traffic*, Traffic*>::iterator outputIter = m_outTraffics.find(ptrTraffic);
			Traffic* ptrOutput = outputIter->second;
			
			// fetch buffer for traffic flow
			map<Traffic*, ivector>::iterator bufferIter = bufferCache.find(ptrOutput);
			ivector buffer = bufferIter->second;
			// cout << "other buffer: " << endl << sum(buffer) << endl;
			interval loss = interval(0.0);
			
			ivector otherTraffic = ptrTraffic->getDistribution();
			// cout << "other traffic: " << sum(otherTraffic) << endl;
			// cout << "other capacity: " << sum(remainingCapacity) << endl;
			ivector depart = computeStep(buffer, loss, otherTraffic, remainingCapacity);
			
			// cout << "departure: " << sum(depart) << endl;

			remainingCapacity = computeRemaining(depart, remainingCapacity);
			// cout << "Remaining capacity for other streams: " << sum(remainingCapacity) << endl;
		}
		// remainingCapacity contains additional capacity probabilities due to non-exhaustive use of other flows
		ivector worstCase = ivector(Inf(remainingCapacity));
		interval diff = sum(worstCase);
		worstCase[0] += interval(1.0)-diff;
		ivector availableCapacity = convAdd(worstCase, sharedCapacity);
		// cout << "Capacity available: " << sum(availableCapacity) << endl;
		
		// sum up reserved and remaining
		
		// compute departure traffic according to remaining capacity
		ivector arrival = ptrTraffic->getDistribution();
		interval loss = interval(0.0);
		ivector depart = computeStep(buffer, loss, arrival, availableCapacity);
		// set departure traffic
		ptrOutput->setDistribution(depart);
		ptrOutput->setLoss(loss);
		// reduce capacity according to departure traffic
		capacity = computeRemaining(depart, availableCapacity);		
	}
}

}
