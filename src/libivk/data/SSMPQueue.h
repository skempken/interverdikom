#ifndef SMPQUEUE_H_
#define SMPQUEUE_H_

#include "data/SSMProcess.h"

namespace ivk
{

class SSMPQueue : public ivk::SSMProcess
{
public:
	enum QueueType { Interarrival, TimeSlotted };
	virtual ~SSMPQueue();
	
	static SSMPQueue* constructTimeSlottedQueue(const SSMProcess* arrival, const SSMProcess* service);
	static SSMPQueue* constructInterarrivalQueue(const SSMProcess* arrival, const SSMProcess* service);
	
	virtual const SSMProcess* getArrivalProcess() const;
	virtual const SSMProcess* getServiceProcess() const;
	QueueType getQueueType() const;
	
private:
	SSMPQueue(const rmatrix &_transition, const rmatrix &_distributions, const int trimEmptyStates = true);
	SSMPQueue(const imatrix &_transition, const imatrix &_distributions, const int trimEmptyStates = true);
	
	void setArrivalProcess(const SSMProcess* arrival);
	void setServiceProcess(const SSMProcess* service);
	void setQueueType(QueueType queueType);
	
	const SSMProcess* m_arrival;
	const SSMProcess* m_service;
	QueueType m_queueType;
	
};

}

#endif /*SMPQUEUE_H_*/
