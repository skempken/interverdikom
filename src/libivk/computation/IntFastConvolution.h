#ifndef INTFASTCONVOLUTION_H_
#define INTFASTCONVOLUTION_H_

#include <ivector.hpp>
#include <civector.hpp>

using namespace cxsc;

namespace ivk
{

class IntFastConvolution
{
public:
	IntFastConvolution(const ivector &firstRvector, const ivector &secondRvector);
	virtual ~IntFastConvolution();
	
	virtual civector compute();
	civector check(const ivector &checkRvector);
	civector fft(const int &length, const civector transformCvector);
	civector multiply(const civector &firstCvector, const civector &secondCvector);
	civector ifft(const int &length, const civector backTransformCvector);
	
protected:
	ivector firstIvector;
	ivector secondIvector;
	int length;
};

}

#endif /*INTFASTCONVOLUTION_H_*/
