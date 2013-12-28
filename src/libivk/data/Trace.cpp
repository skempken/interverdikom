#include "data/Trace.h"

#include <float.h>
#include <math.h>
#include <climits>
#include <cvector.hpp>
#include "utility/FFT.h"
#include "utility/RMatrixUtils.h"

using namespace std;
using namespace cxsc;

namespace ivk
{

const int Trace::FFT_THRESHOLD = 40;

Trace::Trace()
{
}

Trace::Trace(const Trace & other)
{
	setTrace(other.getTrace());
}

Trace::Trace(const rvector &_trace)
{
	setTrace(_trace);
}

Trace::Trace(const intvector &_trace)
{
	setTrace(_trace);
}

Trace::Trace(const std::ostringstream &_traceData)
{
	std::istringstream traceStream(_traceData.str());
	std::string traceString = traceStream.str();

	int numElements = 0;
	for (unsigned int i = 0; i < traceString.size(); i++)
	{
		if (traceString.at(i) == '\n')
		{
			numElements++;
		}
	}

	rvector traceVector;
	Resize(traceVector, numElements);

	traceStream >> traceVector;
	setTrace(traceVector);
}

Trace::~Trace()
{
}

void Trace::setTrace(const rvector &_trace)
{
	this->m_trace = _trace;
}

void Trace::setTrace(const intvector &_trace){
	rvector trace( Lb(_trace) , Ub(_trace) );
	for(int i = Lb( _trace ) ; i <= Ub( _trace ) ; i++){
		trace[i] = _trace[i];
	}

	this->m_trace = trace;
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
	for (int i = Lb(_data); i<=Ub(_data); ++i)
		sum += _data[i];
	return sum / (Ub(_data)-Lb(_data)+1);
}

real Trace::getVariance() const
{
	return getVariance(m_trace);
}

real Trace::getVariance(const rvector &_data)
{
	if (Ub(_data) == Lb(_data))
	{
		return 0.0;
	}
	real mean = getMean(_data);
	real sigma = 0.0;

	for (int i = Lb(_data); i<=Ub(_data); ++i)
	{
		sigma += (mean - _data[i])*(mean - _data[i]);
	}

	return sigma / (Ub(_data)-Lb(_data));
}

real Trace::getStandardDeviation() const
{
	return getStandardDeviation(m_trace);
}

real Trace::getStandardDeviation(const rvector &_data)
{
	real var = getVariance(_data);
	return sqrt(var);
}

rvector Trace::getAutocorrelation(const int upTo) const
{
	if(upTo > FFT_THRESHOLD)
		// use fast computation
		return getAutocorrelationFFT(m_trace, upTo);
	else
		return getAutocorrelation(m_trace, upTo);
}

rvector Trace::getAutocorrelation(const rvector &_data, const int upTo)
{
	const real mean = getMean(_data);
	const real variance = getVariance(_data);

	rvector result(0, upTo);
	for (int i = Lb(result); i<=Ub(result); ++i)
		result[i]=0.0;

	rvector x_erw(Lb(_data), Ub(_data));
	for (int i = Lb(x_erw); i<=Ub(x_erw); ++i)
	{
		x_erw[i] = _data[i] - mean;
	}

	result[0] = 1.0;

	for (int i=1; i<=upTo; ++i)
	{
		int hilfz = Ub(_data) - i;
		rvector z(0, hilfz);
		for (int k=Lb(z); k<=Ub(z); ++k)
			z[k]=0.0;

		for (int j = 0; j<=hilfz; ++j)
		{
			z[j] = x_erw[j]*x_erw[j+i];
		}

		result[i] = (RMatrixUtils::sum(z) / Ub(_data)) / variance;
	}

	return result;
}

rvector Trace::getAutocorrelationFFT(const rvector &_data, const int upTo)
{
	real mean = getMean(_data);

	// Determine next power of 2.
	int n = 2;
	while(n<Ub(_data) + upTo) n*=2;

	cvector d(Lb(_data), n);

	// Subtract mean and pad with zeros.
	for(int i = Lb(_data); i<=Ub(_data); ++i)
	{
		d[i] = (complex)(_data[i] - mean);
	}
	for(int i = Ub(_data)+1; i<=Ub(d); ++i)
	{
		d[i] = complex(0.0,0.0);
	}
	cvector df = FFT::fft(d);

	// Complex conjugate
	cvector dfc(Lb(df), Ub(df));
	for(int i = Lb(df); i<=Ub(df); ++i)
	{
		real re = Re(df[i]);
		real im = Im(df[i]);
		dfc[i] = complex(re*re + im*im, 0.0);
	}
	cvector a = FFT::ifft(dfc);
	rvector ret(0, upTo);
	real factor = Re(a[Lb(a)]);
	for(int i = 0; i<=upTo; ++i)
	{
		ret[i] =  Re(a[i+Lb(a)]) / factor;
	}
	return ret;
}

real Trace::getMinimum(const rvector &_data)
{
	real minValue = DBL_MAX;
	for (int i = Lb(_data); i<=Ub(_data); ++i)
	{
		minValue = min<cxsc::real>(minValue, _data[i]);
	}
	return minValue;
}

real Trace::getMaximum(const rvector &_data)
{
	real maxValue = -DBL_MAX;
	for (int i = Lb(_data); i<=Ub(_data); ++i)
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

int Trace::getLowerBound() const
{
	return Lb(m_trace);
}

int Trace::getUpperBound() const
{
	return Ub(m_trace);
}

int Trace::getLength() const
{
	return Ub(m_trace)-Lb(m_trace)+1;
}

rvector Trace::discretize(const rvector &_s) const
{
	return discretize(this->m_trace, _s);
}

rvector Trace::discretize(const rvector &data, const rvector &s)
{
	rvector R(Lb(s), Ub(s));
	const int K = Ub(data)-Lb(data)+1;
	const real Delta = s[Lb(s)+1]-s[Lb(s)];
	const real KDelta = K*Delta;
	for (int l=Lb(R); l<=Ub(R); ++l)
	{
		R[l] = 0.0;
		for (int k = Lb(data); k<=Ub(data); ++k)
		{
			const real diff = abs(data[k] - s[l]);
			if (diff < Delta)
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

	// TODO: Check distribution bounds!
	if (minValue>0)
	{
		// Discretize from min to max.
		const real Delta = (maxValue-minValue)/(g-1);
		rvector s(0, g-1);
		for (int l=Lb(s); l<=Ub(s); ++l)
			s[l] = minValue + l*Delta;

		return s;
	}
	else
	{
		// Discretize fixed at zero and include min and max
		const real Delta = (maxValue-minValue)/(g-2);
		const int l_index = 1 + (int)_double(minValue / Delta);
		const int u_index = 1 + (int)_double(maxValue / Delta);
		rvector s(l_index, u_index);
		for (int i=l_index; i<=u_index; ++i)
			s[i] = i * Delta;
		return s;
	}
}

rmatrix Trace::discretize(const rvector &_s, const intvector &_index) const
{
	return discretize(this->m_trace, _s, _index);
}

rmatrix Trace::discretize(const rvector &data, const rvector &s,
		const intvector &index)
{
	// Find index bounds
	int lowerBound = INT_MAX;
	int upperBound = 0;
	for (int i=Lb(index); i<=Ub(index); ++i)
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

			rvector Trace::computeBuffer(const real & capacity) const
			{
				rvector buffer(Lb(m_trace), Ub(m_trace));

				for(int i = Lb(m_trace); i<=Ub(m_trace); ++i)
				{
					buffer[i] += m_trace[i] - capacity;
					buffer[i] = std::max<real>(buffer[i], 0.0);
				}
				return buffer;
			}

			real Trace::getMeanSlice(const int from, const int to) const
			{
				real sum = 0.0;
				for(int i = from; i<=to; ++i)
				sum += this->m_trace[i];
				return sum / (to-from+1);
			}

			real Trace::getVarianceSlice(const int from, const int to) const
			{
				if(from==to) return 0.0;
				real mean = getMeanSlice(from,to);
				real sigma = 0.0;

				for(int i = from; i<=to; ++i)
				{
					real tmp = mean - this->m_trace[i];
					sigma += tmp*tmp;
				}
				return sigma / (to-from);
			}

			real Trace::getStandardDeviationSlice(const int from, const int to) const
			{
				real var = getVarianceSlice(from,to);
				return sqrt(var);
			}

			real Trace::getVariationCoefficientSlice(const int from, const int to) const
			{
				if(from==to) return 0;

				real sum = 0.0;
				for(int i = from; i<=to; ++i)
				sum += this->m_trace[i];
				const real mean = sum / (to-from+1);

				real sigma = 0.0;

				for(int i = from; i<=to; ++i)
				{
					real tmp = mean - this->m_trace[i];
					sigma += tmp*tmp;
				}
				const real variance = sigma / (to-from);
				const real std = sqrt(variance);

				return std/mean;
			}

		}
