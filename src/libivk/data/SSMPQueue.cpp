#include "SSMPQueue.h"

namespace ivk
{

SSMPQueue::SSMPQueue(const rmatrix &_transition, const rmatrix &_distributions, const int trimEmptyStates)
: SSMProcess(_transition, _distributions, trimEmptyStates)
{
	// Nothing else to do.
}

SSMPQueue::SSMPQueue(const imatrix &_transition, const imatrix &_distributions, const int trimEmptyStates)
: SSMProcess(_transition, _distributions, trimEmptyStates)
{
	// Nothing else to do.
}

SSMPQueue::~SSMPQueue()
{
	
}

SSMPQueue* SSMPQueue::constructTimeSlottedQueue(const SSMProcess* arrival, const SSMProcess* service)
{
	SSMProcess difference = (*arrival) - (*service);
	SSMPQueue* queue = new SSMPQueue(difference.getTransitionMatrix(), difference.getDistributions());
	queue->setArrivalProcess(arrival);
	queue->setServiceProcess(service);
	queue->setQueueType(TimeSlotted);
	return queue;
}

SSMPQueue* SSMPQueue::constructInterarrivalQueue(const SSMProcess* arrival, const SSMProcess* service)
{
	SSMProcess difference = (*service) - (*arrival);
	SSMPQueue* queue = new SSMPQueue(difference.getTransitionMatrix(), difference.getDistributions());
	queue->setArrivalProcess(arrival);
	queue->setServiceProcess(service);
	queue->setQueueType(Interarrival);
	return queue;
}

const SSMProcess* SSMPQueue::getArrivalProcess() const
{
	return this->m_arrival;
}

void SSMPQueue::setArrivalProcess(const SSMProcess* arrival)
{
	this->m_arrival = arrival;
}

const SSMProcess* SSMPQueue::getServiceProcess() const
{
	return this->m_service;
}

void SSMPQueue::setServiceProcess(const SSMProcess* service)
{
	this->m_service = service;
}

SSMPQueue::QueueType SSMPQueue::getQueueType() const
{
	return this->m_queueType;
}

void SSMPQueue::setQueueType(QueueType queueType)
{
	this->m_queueType = queueType;
}

}
