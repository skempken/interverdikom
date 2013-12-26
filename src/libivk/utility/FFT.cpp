#include "FFT.h"
#include <complex.hpp>
#include <complex>
#include <fftw3.h>

using std::complex;

namespace ivk
{

cvector FFT::fft(const cvector &vector)
{
	const int N = VecLen(vector);
	
	fftw_complex *in, *out;
    fftw_plan p;
    
    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
    for(int i = Lb(vector); i<=Ub(vector); ++i)
    {
    	in[i-Lb(vector)][0] = _double(Re(vector[i]));
    	in[i-Lb(vector)][1] = _double(Im(vector[i]));
    }
    p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    
    fftw_execute(p); /* repeat as needed */
    
    fftw_destroy_plan(p);
    cvector ret(0, N-1);
    for(int i = 0; i<N; ++i)
    {
    	ret[i] = cxsc::complex(out[i][0], out[i][1]);
    }
    fftw_free(in); fftw_free(out);
    return ret;
}

cvector FFT::fft(cvector vector, const int size)
{
	const int end = Ub(vector);
	cxsc::Resize(vector, Lb(vector), Lb(vector)+size-1);
	for(int i = end+1; i<=Ub(vector); ++i)
		vector[i] = cxsc::complex(0.0, 0.0);
	return fft(vector);
}

cvector FFT::ifft(const cvector &vector)
{
	const int N = VecLen(vector);
	
	fftw_complex *in, *out;
    fftw_plan p;
    
    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
    for(int i = Lb(vector); i<=Ub(vector); ++i)
    {
    	in[i-Lb(vector)][0] = _double(Re(vector[i]));
    	in[i-Lb(vector)][1] = _double(Im(vector[i]));
    }
    p = fftw_plan_dft_1d(N, in, out, FFTW_BACKWARD, FFTW_ESTIMATE);
    
    fftw_execute(p); /* repeat as needed */
    
    fftw_destroy_plan(p);
    cvector ret(0, N-1);
    const cxsc::complex n(1.0/N, 0.0);
    for(int i = 0; i<N; ++i)
    {
    	ret[i] = cxsc::complex(out[i][0], out[i][1]) * n;
    }
    fftw_free(in); fftw_free(out);
    return ret;
}

cvector FFT::ifft(cvector vector, const int size)
{
	const int end = Ub(vector);
	cxsc::Resize(vector, Lb(vector), Lb(vector)+size-1);
	for(int i = end+1; i<=Ub(vector); ++i)
		vector[i] = cxsc::complex(0.0, 0.0);
	return ifft(vector);
}

cvector FFT::fconv(const cvector &a, const cvector &b)
{
	const int neededSize= VecLen(a) + VecLen(b) -1;
	int size = 1;
	while( size <= neededSize) size *= 2;
	
	cvector af = FFT::fft(a, size);
	cvector bf = FFT::fft(b, size);
	cvector cf(Lb(af), Ub(af));
	for(int i = Lb(cf); i<=Ub(cf); ++i)
		cf[i] = af[i] * bf[i];
	cvector result = FFT::ifft(cf);
	cxsc::Resize(result, Lb(result)+1, Lb(result) + neededSize-1);
	return result;
}


}
