#include "DiscretizedTrace.h"

namespace ivk
{

DiscretizedTrace::DiscretizedTrace(const intvector &_trace)
: Trace(rvector(Lb(_trace), Ub(_trace)))
{
	rvector trace(Lb(_trace), Ub(_trace));
	for(int i = Lb(trace); i<=Ub(trace); ++i)
		trace[i] = _trace[i];
	setTrace(trace);
}

DiscretizedTrace::~DiscretizedTrace()
{
}

Trace DiscretizedTrace::scale(const rvector &s) const
{
	rvector ret(Lb(m_trace), Ub(m_trace));
	for(int i = Lb(m_trace); i<=Ub(m_trace); ++i)
	{
		int index = (int)_double(m_trace[i]);
		if(index < Lb(s) || index > Ub(s))
		{
			throw std::out_of_range("Invalid state index.");
		}
		ret[i] = s[index];
	}
	return Trace(ret);
}

}
