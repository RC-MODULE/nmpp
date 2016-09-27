#include "fft.h"
//#include "fftext.h"
//#include "nmtl/tcmplx_spec.h"
#include "nmtl/tcmplx.h"
#include <math.h>

#ifndef PI
#define PI 3.14159265359
#endif


template<int power> void expFFT(int arg, float* re, float* im)
{
	float rad=-2.0*PI/power*arg;
	*re=cosf(rad);
	*im=sinf(rad);
}

template<int power> void expIFFT(int arg, float* re, float* im)
{
	float rad=2.0*PI/power*arg;
	*re=cosf(rad);
	*im=sinf(rad);
}


template<int power> void expFFT(int arg, int amplitude, nm32sc* z)
{
	float re;
	float im;
	expFFT<power>(arg,&re,&im);
	z->re=floor(amplitude*re+0.5);	
	z->im=floor(amplitude*im+0.5);
}

template<int power> void expFFT127(int arg, int amplitude, nm32sc* z)
{
	float re;
	float im;
	expFFT<power>(arg,&re,&im);
	z->re=floor(amplitude*re+0.5);	
	z->im=floor(amplitude*im+0.5);
	z->re= z->re > 127 ? 127:z->re;
	z->im= z->im > 127 ? 127:z->im;	
}

template<int power> void expIFFT127(int arg, int amplitude, nm32sc* z)
{
	float re;
	float im;
	expIFFT<power>(arg,&re,&im);
	z->re=floor(amplitude*re+0.5);	
	z->im=floor(amplitude*im+0.5);
	z->re= z->re > 127 ? 127:z->re;
	z->im= z->im > 127 ? 127:z->im;	
}

template<int power> void expFFT127(int arg, int amplitude, cmplx<int>* z)
{
	float re;
	float im;
	expFFT<power>(arg,&re,&im);
	z->re=floor(amplitude*re+0.5);	
	z->im=floor(amplitude*im+0.5);
	z->re= z->re > 127 ? 127:z->re;
	z->im= z->im > 127 ? 127:z->im;	
}

template<int power> void expIFFT127(int arg, int amplitude, cmplx<int>* z)
{
	float re;
	float im;
	expIFFT<power>(arg,&re,&im);
	z->re=floor(amplitude*re+0.5);	
	z->im=floor(amplitude*im+0.5);
	z->re= z->re > 127 ? 127:z->re;
	z->im= z->im > 127 ? 127:z->im;	
}

template<int power> cmplx<int> expFFT127(int arg, int amplitude=128)
{
	cmplx<int> z;
	float re;
	float im;
	expFFT<power>(arg,&re,&im);
	z.re=floor(amplitude*re+0.5);	
	z.im=floor(amplitude*im+0.5);
	z.re= z.re > 127 ? 127:z.re;
	z.im= z.im > 127 ? 127:z.im;	
	return z;
}


template<int power> cmplx<int> expFFT(int arg, int amplitude)
{
	float re;
	float im;
	expFFT<power>(arg,&re,&im);
	cmplx<int> z;
	z.re=floor(amplitude*re+0.5);	
	z.im=floor(amplitude*im+0.5);
	return z;
}

template<int power> cmplx<int> expIFFT(int arg, int amplitude)
{
	float re;
	float im;
	expIFFT<power>(arg,&re,&im);
	cmplx<int> z;
	z.re=floor(amplitude*re+0.5);	
	z.im=floor(amplitude*im+0.5);
	return z;
}



template<int power> cmplx<double> expFFT(int arg)
{
	cmplx<double> z;
	double im=-2.0*PI/power*arg;
	z.re=cos(im);
	z.im=sin(im);
	return z;
}
template<int power> cmplx<double> expIFFT(int arg)
{
	cmplx<double> z;
	double im=2.0*PI/power*arg;
	z.re=cos(im);
	z.im=sin(im);
	return z;
}

void load_wfifo(nm64s* wfifoData, int wfifoStep, int size);
void load_wfifo(cmplx<int>* wcoef, int wstep, int size);
void load_wfifo(nm32sc* wcoef, int wstep, int size);

void vsum_data(nm8s* data,   nm32sc* afifo, int vr);
void vsum_data(nm16s* data,  nm32sc* afifo, int vr);
void vsum_data(nm8s* data,  cmplx<int>* afifo, int vr);
