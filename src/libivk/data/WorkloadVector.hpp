#ifndef WORKLOADVECTOR_H_
#define WORKLOADVECTOR_H_

#include <rvector.hpp>
#include <ivector.hpp>

using cxsc::rvector;
using cxsc::ivector;

namespace ivk
{

template <class V>
class WorkloadVector
{
public:
	WorkloadVector(const V &vector)
	{
		setWorkloadVector(vector);
	}

	virtual ~WorkloadVector()
	{
		// Nothing to do
	}

	void setWorkloadVector(const V &vector)
	{
		this->m_vector = vector;
	}

	V getWorkloadVector() const
	{
		return V(this->m_vector);
	}

private:
	V m_vector;
};

typedef WorkloadVector<ivector> IWorkloadVector;
typedef WorkloadVector<rvector> RWorkloadVector;
}

#endif /*WORKLOADVECTOR_H_*/
