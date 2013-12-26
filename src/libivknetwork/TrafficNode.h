#ifndef TRAFFICNODE_H_
#define TRAFFICNODE_H_

#include <map>
#include <vector>
#include <ivector.hpp>

#include "Traffic.h"
#include "BaseOutputLink.h"

using cxsc::ivector;
using std::map;
using std::make_pair;
using std::vector;

namespace ivk
{
	
	// TODO: Add class OutputLink

class TrafficNode
{
public:
	enum Prioritization
	{
		Ordered,
		Shared
	};
	
	TrafficNode();
	virtual ~TrafficNode();

	/// Adds a link to another Network Element
	void addOutputLink(TrafficNode *node, const int bufferSize, const ivector &linkCapacity, const Prioritization &priority);
	
	/// Adds another traffic flow
	/**
	 * @return index of the fraffic flow at this node.
	 */
	Traffic* addTrafficFlow(Traffic* source, TrafficNode* target);
	
	/// Returns the outgoing traffic flow for the given input traffic.
	Traffic* getOutFlow(Traffic* source);
	
	/// Computes the next step.
	void tick();
	
protected:
	/// List of outgoing link capacities, indexed by target nodes.
	map<TrafficNode*, BaseOutputLink*> m_outputLinks;
	
	/// List of outgoing traffics, indexed by corresponding incoming traffic.
	map<Traffic*, Traffic*> m_traffics;
	
	
private:
	int m_tickCount;
};

}

#endif /*TRAFFICNODE_H_*/
