#ifndef FFT_H_
#define FFT_H_

#include <cvector.hpp>

using cxsc::cvector;

/**
 * Utility class for fast discrete Fourier transforms. In principle, it provides
 * an interface to the routines of FFTW (http://www.fftw.org).
 */

namespace ivk
{

class FFT
{
public:
	/// Discrete Fourier transform
	static cvector fft(const cvector &vector);
	
	/// Discrete Fourier transform with given vector size
	static cvector fft(cvector vector, const int size);
	
	/// Inverse discrete Fourier transform
	static cvector ifft(const cvector &vector);
	
	/// Discrete Fourier transform with given vector size
	static cvector ifft(cvector vector, const int size);
	
	static cvector fconv(const cvector &a, const cvector &b);
};

}

#endif /*FFT_H_*/
