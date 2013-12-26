#ifndef BASEOUTPUTLINK_H_
#define BASEOUTPUTLINK_H_

#include <list>
#include <map>
#include <ivector.hpp>
#include <idot.hpp>
#include "Traffic.h"

using std::list;
using std::map;

using cxsc::ivector;
using cxsc::idotprecision;

namespace ivk
{

/// Abstract base class for outgoing connections between TrafficNodes.
/**
 * In inheriting classes, the method \c tick has to be implemented.
 */
class BaseOutputLink
{
public:
	/// Constructor.
	/**
	 * \param bufferSize Size of the buffers for each traffic flow.
	 * \param capacity Distribution of the capacity for the link.
	 */
	BaseOutputLink(const int bufferSize, const ivector &capacity);
	
	/// Destructor.
	virtual ~BaseOutputLink();
	
	/// Adds a traffic Flow to this link.
	/**
	 * \param input Source traffic distribution.
	 * \param output Pointer to the traffic object the computed distributions will be written to.
	 */
	virtual void addOutFlow(Traffic* input, Traffic* output);
	
	/// Computes the next step.
	/**
	 * Has to be implemented in inheriting classes.
	 */
	virtual void tick() = 0;

protected:
	/// List of buffers, indexed by the source traffic flows.
	map<Traffic*, ivector> m_buffers;
	
	/// Capacity distribution of this link.
	ivector m_capacity;
	
	/// List of incoming traffics.
	list<Traffic*> m_inTraffics;
	
	/// List of outgoing traffics, indexed by corresponding incoming traffic objects.
	map<Traffic*, Traffic*> m_outTraffics;
	
	/// Counter for the current step.	
	int m_tickCount;
	
	/// Size of the buffers for each traffic flow.
	int m_bufferSize;
	
	/// Computes the next-step distributions for buffer, capacity and loss probability.
	virtual ivector computeStep(ivector &buffer, interval &loss, const ivector &arrival, const ivector &capacity);
	
	virtual ivector computeRemaining(ivector depart, ivector remainingCapacity);
	
};

}

#endif /*BASEOUTPUTLINK_H_*/
