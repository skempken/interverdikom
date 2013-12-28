#include "CompUtil.h"

real CompUtil::getExpectationValue(const ivector &data)
{
	return getExpectationValue(getMeanVector(data));
}

real CompUtil::getExpectationValue(const rvector &data)
{
	real exp = 0.0;
	for(int i = Lb(data); i<=Ub(data); ++i)
	{
		exp += i*data[i];
	}
	return exp;
}

real CompUtil::getDistributionVariance(const ivector &data)
{
	return getDistributionVariance(getMeanVector(data));
}

real CompUtil::getDistributionVariance(const rvector &data)
{
	const real mean = getExpectationValue(data);
		
	real v = 0.0;
	for(int value = Lb(data); value<=Ub(data); ++value)
	{
		const real tmp = value - mean;
		v += data[value] * tmp * tmp;
	}
	return v;
}

real CompUtil::getDistributionStandardDeviation(const ivector &data)
{
	return getDistributionStandardDeviation(getMeanVector(data));
}

real CompUtil::getDistributionStandardDeviation(const rvector &data)
{
	return sqrt(getDistributionVariance(data));
}

real CompUtil::getSum(const rvector & data) {
	real sum = 0.0;

	for (int i = Lb(data); i <= Ub(data); i++) {
		sum += data[i];
	}

	return sum;
}

real CompUtil::getSum(const ivector & data) {
	return getSum(getMeanVector(data));
}

real CompUtil::getMean(const rvector & data) {
	return getSum(data) / (Ub(data) - Lb(data) + 1);
}

real CompUtil::getMean(const ivector & data) {
	return getMean(getMeanVector(data));
}

real CompUtil::getVariance(const rvector & data) {
	if (Ub(data) == Lb(data)) {
		return 0.0;
	}
	
	real mean = getMean(data);
	real sigma = 0.0;

	for (int i = Lb(data); i <= Ub(data); i++) {
		sigma += (mean - data[i]) * (mean - data[i]);
	}

	return sigma / (Ub(data) - Lb(data));
}

real CompUtil::getVariance(const ivector & data) {
	return getVariance(getMeanVector(data));
}

real CompUtil::getStandardDeviation(const rvector & data) {
	return sqrt(getVariance(data));
}

real CompUtil::getStandardDeviation(const ivector & data) {
	return getStandardDeviation(getMeanVector(data));
}

rvector CompUtil::getMeanVector(const ivector & data) {
	rvector inf = Inf(data);
	rvector sup = Sup(data);
	rvector result;

	int firstIndex = Lb(data);
	int lastIndex = Ub(data);

	Resize(result, lastIndex - firstIndex + 1);
	SetLb(result, firstIndex);
	SetUb(result, lastIndex);
	
	for (int i = firstIndex; i <= lastIndex; i++) {
		result[i] = (inf[i - Lb(data) + Lb(inf)] + sup[i - Lb(data) + Lb(sup)]) / 2;
	}
	
	return result;
}
