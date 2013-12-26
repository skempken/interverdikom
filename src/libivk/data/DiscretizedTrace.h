#ifndef DISCRETIZEDTRACE_H_
#define DISCRETIZEDTRACE_H_

#include "data/Trace.h"
#include "intvector.hpp"
#include <stdexcept>

namespace ivk
{

class DiscretizedTrace : public Trace
{
public:
	DiscretizedTrace(const intvector &_trace);
	virtual ~DiscretizedTrace();
	
	Trace scale(const rvector &s) const;
};

}

#endif /*DISCRETIZEDTRACE_H_*/
