#ifndef GIPROCESS_H_
#define GIPROCESS_H_

#include <rvector.hpp>
#include "data/SSMProcess.h"

using namespace cxsc;

namespace ivk
{

class GIProcess : public SSMProcess
{
public:
	GIProcess(const rvector &_distribution);
	GIProcess(const ivector &_distribution);
	virtual ~GIProcess();
	
	void setDistribution(const rvector &_distribution);
	void setDistribution(const ivector &_distribution);
	ivector getDistribution() const;
	
	friend GIProcess operator-(const GIProcess &a, const GIProcess &b);
	friend GIProcess operator+(const GIProcess &a, const GIProcess &b);
};

}

#endif /*GIPROCESS_H_*/
