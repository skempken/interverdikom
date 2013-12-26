#ifndef TRACE_H_
#define TRACE_H_

#include <real.hpp>
#include <rvector.hpp>
#include <rmatrix.hpp>
#include <intvector.hpp>

using cxsc::real;
using cxsc::rvector;
using cxsc::rmatrix;
using cxsc::intvector;

namespace ivk
{

class Trace
{
public:
	Trace(const rvector &_trace);
	virtual ~Trace();
	
	void setTrace(const rvector &_trace);
	rvector getTrace() const;

	real getMean() const;
	static real getMean(const rvector &_data);
	real getVariance() const;
	static real getVariance(const rvector &_data);
	
	rvector getAutocorrelation(const int upTo) const;
	static rvector getAutocorrelation(const rvector &_data, const int upTo);
	
	real getMaximum() const;
	static real getMaximum(const rvector &_data);
	real getMinimum() const;
	static real getMinimum(const rvector &_data);
	
	rmatrix discretize(const rvector &s, const intvector &_index) const;
	static rmatrix discretize(const rvector &_data, const rvector &s, const intvector &_index);
	
	rvector discretize(const rvector &s) const;
	static rvector discretize(const rvector &_data, const rvector &_s);
	
	rvector getDiscretizationPoints(const int g) const;
	static rvector getDiscretizationPoints(const rvector &_data, const int g);
	
	

private:
	rvector m_trace;
};

}

#endif /*TRACESTATS_H_*/
