#include "IntFastConvolution.h"
#include <iostream>
#include <stdexcept>

#define PI 3.141592653589793

using namespace std;
namespace ivk
{

IntFastConvolution::IntFastConvolution(const ivector &firstIvector, const ivector &secondIvector)
{
	if(VecLen(this->firstIvector)!=VecLen(this->secondIvector))
		throw std::invalid_argument("Vectors must have the same length.");
	this->firstIvector = firstIvector;
	this->secondIvector = secondIvector;
	this->length = 2*VecLen(this->firstIvector);	
}

IntFastConvolution::~IntFastConvolution()
{
}

civector IntFastConvolution::compute()
{
	civector one = check(this->firstIvector);
	civector two = check(this->secondIvector);
	one = fft(this->length, one);
	two = fft(this->length, two);
	civector product = multiply(one, two);
	civector result = ifft(this->length, product);
	Resize(result, Lb(result), Lb(result) + VecLen(this->firstIvector) + VecLen(this->secondIvector)-2);
	return result;
}

civector IntFastConvolution::check(const ivector &checkIvector)
{
	int count = 2;
	while(count<this->length)
		count *= 2;
	
	this->length=count;
	
	civector ret(0, count-1);
	for(int i=Lb(checkIvector); i<=Ub(checkIvector); ++i)
	{
		ret[i] = cinterval(checkIvector[i]);
	}
	for(int i=Ub(checkIvector)+1; i<=Ub(ret); ++i)
	{
		ret[i] = cinterval(interval(0.0,0.0));
	}
	return ret;
}

civector IntFastConvolution::fft(const int &length, const civector transformCIvector)
{
	int localLength = length;
	
	if(localLength==1)
		return transformCIvector;
	else
	{
		civector even(0,localLength/2-1);
		civector odd(0,localLength/2-1);
		for(int i=Lb(even); i<=Ub(even); i++)
		{
			even[i] = cinterval(interval(0.0,0.0));
			odd[i] = cinterval(interval(0.0,0.0));
		}
		for(int i=0; i<localLength/2; i++)
		{
			even[i] = transformCIvector[2*i];
			odd[i] = transformCIvector[2*i+1];
		}
		even = fft(localLength/2, even);
		odd = fft(localLength/2, odd);
		civector transformedCIvector(0,localLength-1);
		/*for(int k=0; k<=localLength-1; k++)
			transformedCIvector[k] = cinterval(interval(0.0,0.0));*/
				
		for(int k=0; k<localLength/2; k++)
		{
			complex _factor = complex(0.0,-2 * PI * k / localLength);
			cinterval factor = cxsc::exp(cinterval(_factor, _factor));
			transformedCIvector[k] = even[k] + odd[k] * factor;
			transformedCIvector[k+localLength/2] = even[k] - odd[k] * factor;
		}
		return transformedCIvector;
	}
}

civector IntFastConvolution::multiply(const civector &firstCIvector, const civector &secondCIvector)
{
	civector civectorProduct(0,this->length-1);
	for(int i=0; i<this->length; i++ )
		civectorProduct[i] = firstCIvector[i] * secondCIvector[i];
	return civectorProduct;
}

civector IntFastConvolution::ifft(const int &length, const civector backTransformCIvector)
{
	int localLength = length;
		
	if(localLength==1)
		return backTransformCIvector;
	else
	{
		civector even(0,localLength/2-1);
		civector odd(0,localLength/2-1);
		for(int i=Lb(even); i<=Ub(even); i++)
		{
			even[i] = complex(0.0,0.0);
			odd[i] = complex(0.0,0.0);
		}
		for(int i=0; i<localLength/2; i++)
		{
			even[i] = backTransformCIvector[2*i];
			odd[i] = backTransformCIvector[2*i+1];
		}
		
		
		even = ifft(localLength/2, even);
		odd = ifft(localLength/2, odd);
		civector backTransformedCIvector(0,localLength-1);
		for(int i=Lb(backTransformedCIvector); i<=Ub(backTransformedCIvector); ++i)
			backTransformedCIvector[i] = cinterval(interval(0.0,0.0));
		for(int k=0; k<localLength/2; k++)
		{
			complex _factor = complex(0.0,2 * PI * k / localLength);
			cinterval factor = cxsc::exp(cinterval(_factor, _factor));
			backTransformedCIvector[k] = even[k] + odd[k] * factor;
			backTransformedCIvector[k+localLength/2] = even[k] - odd[k] * factor;
		}
		
		if(localLength == this->length)
		{
			for(int i=0; i<localLength; i++)
				backTransformedCIvector[i] /= localLength;
		}
		return backTransformedCIvector;
	}
}

}
