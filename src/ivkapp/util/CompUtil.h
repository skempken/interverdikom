#ifndef COMPUTIL_H_
#define COMPUTIL_H_

#include <real.hpp>
#include <rvector.hpp>
#include <ivector.hpp>

using cxsc::rvector;
using cxsc::ivector;
using cxsc::real;

class CompUtil
{
public:
	
	static real getDistributionVariance(const ivector &data);
	
	static real getDistributionVariance(const rvector &data);
	
	static real getDistributionStandardDeviation(const ivector &data);
	
	static real getDistributionStandardDeviation(const rvector &data);
	
	static real getExpectationValue(const rvector & data);
	
	static real getExpectationValue(const ivector & data);
	
	static real getMean(const rvector & data);
	
	static real getMean(const ivector & data);
	
	static real getSum(const rvector & data);
	
	static real getSum(const ivector & data);
	
	static real getVariance(const rvector & data);
	
	static real getVariance(const ivector & data);
		
	static real getStandardDeviation(const rvector & data);
	
	static real getStandardDeviation(const ivector & data);
	
	static rvector getMeanVector(const ivector & data);
};

#endif /*COMPUTIL_H_*/
