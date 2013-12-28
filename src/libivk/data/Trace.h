#ifndef TRACE_H_
#define TRACE_H_

#include <sstream>

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
	Trace();
	Trace(const Trace & other);
	Trace(const rvector &_trace);
	Trace(const intvector &_trace);
	Trace(const std::ostringstream &_traceData);
	virtual ~Trace();
	
	void setTrace(const rvector &_trace);
	void setTrace(const intvector &_trace);
	rvector getTrace() const;

	real getMean() const;
	real getMeanSlice(const int from, const int to) const;
	static real getMean(const rvector &_data);
	
	real getVariance() const;
	real getVarianceSlice(const int from, const int to) const;
	static real getVariance(const rvector &_data);
	
	real getStandardDeviation() const;
	real getStandardDeviationSlice(const int from, const int to) const;
	static real getStandardDeviation(const rvector &_data);
	
	real getVariationCoefficientSlice(const int from, const int to) const;
	
	rvector getAutocorrelation(const int upTo) const;
	static rvector getAutocorrelation(const rvector &_data, const int upTo);
	static rvector getAutocorrelationFFT(const rvector &_data, const int upTo);
	
	real getMaximum() const;
	static real getMaximum(const rvector &_data);
	real getMinimum() const;
	static real getMinimum(const rvector &_data);
	
	int getLowerBound() const;
	int getUpperBound() const;
	int getLength() const;
	
	rmatrix discretize(const rvector &s, const intvector &_index) const;
	static rmatrix discretize(const rvector &_data, const rvector &s, const intvector &_index);
	
	rvector discretize(const rvector &s) const;
	static rvector discretize(const rvector &_data, const rvector &_s);
	
	rvector getDiscretizationPoints(const int g) const;
	static rvector getDiscretizationPoints(const rvector &_data, const int g);
	
	rvector computeBuffer(const real &capacity) const;

protected:
	rvector m_trace;

private:
	static const int FFT_THRESHOLD;
};

}

#endif /*TRACE_H_*/
