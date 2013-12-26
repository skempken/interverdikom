#include "data/Trace.h"

#include <float.h>
#include <math.h>

using namespace std;
using namespace cxsc;

namespace ivk {

Trace::Trace(const rvector &_trace)
{
	setTrace(_trace);
}

Trace::~Trace()
{
}

void Trace::setTrace(const rvector &_trace)
{
	this->m_trace = _trace;
}

rvector Trace::getTrace() const
{
	return this->m_trace;
}

real Trace::getMean() const
{
	return getMean(m_trace);
}

real Trace::getMean(const rvector &_data)
{
	real sum = 0.0;
	for(int i = Lb(_data); i<=Ub(_data); ++i)
		sum += _data[i];
	return sum / (Ub(_data)-Lb(_data)+1);
}

real Trace::getVariance() const
{
	return getVariance(m_trace);
}

real Trace::getVariance(const rvector &_data)
{
	real mean = getMean(_data);
	real sigma = 0.0;
	
	for(int i = Lb(_data); i<=Ub(_data); ++i)
	{
		sigma += pow(mean - _data[i], 2);
	}
	return sigma / (Ub(_data)-Lb(_data));
}

rvector Trace::getAutocorrelation(const int upTo) const
{
	return getAutocorrelation(m_trace, upTo);
}


rvector Trace::getAutocorrelation(const rvector &_data, const int upTo)
{
	real mean = getMean(_data);
	real variance = getVariance(_data);
	
	const int length = Ub(_data)-Lb(_data)+1;
	
	rvector ret(0, upTo);
	for(int i = Lb(ret); i<=Ub(ret); ++i) ret[i]=0.0;
	
	rvector x_erw(Lb(_data), Ub(_data));
	for(int i = Lb(x_erw); i<=Ub(x_erw); ++i)
	{
		x_erw[i] = _data[i] - mean;
	}
	
	ret[0] = 1.0;
	int limit = min<int>(upTo, length-2);
	
	for(int i=1; i<=limit; ++i)
	{
		int hilfz = length - i;
		rvector z(0, hilfz-1);
		for(int k=Lb(z);k<=Ub(z);++k) z[k]=0.0;
		for(int j =0; j<hilfz; ++j)
		{
			z[j] = x_erw[j]*x_erw[j+1];
		}
		
		ret[i] = getMean(z) /  variance;
	}
	
	return ret;
}

real Trace::getMinimum(const rvector &_data) 
{
	real minValue = DBL_MAX;
	for(int i = Lb(_data); i<=Ub(_data); ++i)
	{
		minValue = min<cxsc::real>(minValue, _data[i]);
	}
	return minValue;
}

real Trace::getMaximum(const rvector &_data)
{
	real maxValue = -DBL_MAX;
	for(int i = Lb(_data); i<=Ub(_data); ++i)
	{
		maxValue = max<cxsc::real>(maxValue, _data[i]);
	}
	return maxValue;
}

real Trace::getMaximum() const
{
	return getMaximum(this->m_trace);
}

real Trace::getMinimum() const
{
	return getMinimum(this->m_trace);
}

rvector Trace::discretize(const rvector &_s) const 
{
	return discretize(this->m_trace, _s);
}

rvector Trace::discretize(const rvector &data, const rvector &s)
{
	rvector R(Lb(s), Ub(s));
	const int K = Ub(data)-Lb(data)+1;
	const real Delta = s[1]-s[0];
	const real KDelta = K*Delta;
	for(int l=Lb(R); l<=Ub(R); ++l)
	{
		R[l] = 0.0;
		for(int k = Lb(data); k<=Ub(data); ++k)
		{
			const real diff = abs(data[k] - s[l]);
			if(diff < Delta)
				R[l] += (Delta - diff)/(KDelta);
		}
	}
	return R;
}

rvector Trace::getDiscretizationPoints(const int g) const
{
	return getDiscretizationPoints(this->m_trace, g);
}

rvector Trace::getDiscretizationPoints(const rvector &data, const int g)
{
	const real minValue = getMinimum(data);
	const real maxValue = getMaximum(data);
	
	const real Delta = (maxValue-minValue)/(g-1);
	rvector s(0,g-1);
	for(int l=Lb(s); l<=Ub(s); ++l)
		s[l] = minValue + l*Delta;
	
	return s;
}

rmatrix Trace::discretize(const rvector &_s, const intvector &_index) const
{
	return discretize(this->m_trace, _s, _index);
}

rmatrix Trace::discretize(const rvector &data, const rvector &s, const intvector &index)
{
	// Find index bounds
	int lowerBound = INT_MAX;
	int upperBound = 0;
	for(int i=Lb(index); i<=Ub(index); ++i)
	{
		lowerBound = std::min<int>(lowerBound, index[i]);
		upperBound = std::max<int>(upperBound, index[i]);
	}
	
	// allocate memory for return values
	rmatrix dists(lowerBound, upperBound, Lb(s), Ub(s));
	
	// for each state
	for(int i = lowerBound; i<=upperBound; ++i)
	{
		// construct data parts
		rvector dataPart(Lb(data), Ub(data));
		int counter = Lb(dataPart);
		for(int j = Lb(data); j<=Ub(data); ++j)
		{
			if(index[j]==i)
				dataPart[counter++] = data[j];
		}
		Resize(dataPart, Lb(dataPart), counter-1);
		
		// Discretize using common discretization points
		dists[i] = Trace::discretize(dataPart, s);
	}
	
	return dists;
}


}
