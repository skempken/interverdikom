#include "TrafficNode.h"

#include "SharedOutputLink.h"
#include "OrderedOutputLink.h"

namespace ivk
{

TrafficNode::TrafficNode()
{
	m_tickCount = 0;
}

TrafficNode::~TrafficNode()
{
	// Delete outgoing traffic flows
	map<Traffic*, Traffic*>::iterator iter;
	for(iter = m_traffics.begin(); iter!=m_traffics.end(); ++iter)
	{
		delete iter->second;
	}
	
	// Delete OutputLinks
	map<TrafficNode*, BaseOutputLink*>::iterator iter2;
	for(iter2 = m_outputLinks.begin(); iter2!=m_outputLinks.end(); ++iter2)
	{
		delete iter2->second;
	}
}

void TrafficNode::addOutputLink(TrafficNode *targetNode, const int bufferSize, const ivector &linkCapacity, const Prioritization &priority)
{
	BaseOutputLink* _output = NULL;
	
	switch(priority)
	{
		case Ordered:
			_output = new OrderedOutputLink(bufferSize, linkCapacity);
			break;
		case Shared:
			_output = new SharedOutputLink(bufferSize, linkCapacity);
			break;
	}
	
	m_outputLinks.insert(make_pair(targetNode, _output)); 
}

Traffic* TrafficNode::addTrafficFlow(Traffic* source, TrafficNode* target)
{
	// Traffic arrives and is being routed to target
	
	// Create new departing Traffic object
	ivector zeroDist(0,0);
	zeroDist[0] = 1.0;
	Traffic* depart = new Traffic(zeroDist);
	m_traffics.insert(make_pair(source, depart));
	
 	// Add to corresponding output link
 	map<TrafficNode*, BaseOutputLink*>::iterator iter = m_outputLinks.find(target);
 	BaseOutputLink* outputLink = iter->second;
 	outputLink->addOutFlow(source, depart);
	
	return depart;
}

Traffic* TrafficNode::getOutFlow(Traffic* source)
{
	map<Traffic*, Traffic*>::iterator iter = m_traffics.find(source);
	Traffic* outflow = iter->second;
	return outflow;
}

void TrafficNode::tick()
{
	++m_tickCount;
	
	// Model new traffic flows according to priority
	
	// for each output link
	map<TrafficNode*, BaseOutputLink*>::iterator outputLinkIter;
	for(outputLinkIter = m_outputLinks.begin(); outputLinkIter != m_outputLinks.end(); outputLinkIter++)
	{
		outputLinkIter->second->tick();
	}
}

}
