#include "fft.h"
#include <math.h>
#include "fftexp.h"
#include "nmpp.h"

#ifndef PI
#define PI 3.14159265359
#endif

extern "C" {
	/*
	cmplx<int > Y;
	X.re*=Ampl;
	X.im*=Ampl;
	Y.re=floor(X.re+0.5);
	Y.im=floor(X.im+0.5);
	if (Ampl>127){
		Y.re= Y.re > 127 ? 127:Y.re;
		Y.im= Y.im > 127 ? 127:Y.im;
	}
	return Y;
	*/
	/*
	nm32sc toFixW2048(int arg, int max){
		nm32sc res;
		double argIm= -2.0*PI/2048.0*arg;
		double expRe= cos(argIm)*max+0.5;
		double expIm= sin(argIm)*max+0.5;
		res.re= expRe;
		res.im= expIm;
		return res;
	}
	*/

	//int nmppsFFT2048FwdInitAlloc4888(  NmppsFFTSpec* spec, src int settings)


	int nmppsFFT16FwdInitSinCos242(NmppsFFTSpec* spec)
	{
		int amplitude = spec->amp[0];
		nm16s* wRe = (nm16s*)spec->fftTable[0];
		nm16s* wIm = (nm16s*)spec->fftTable[1];


		int k = 0;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++, k++) {
				cmplx<int> w = expFFT<8>(2 * i*j, amplitude);
				nmppsPut_16s(wRe, k, w.re);
				nmppsPut_16s(wIm, k, w.im);
			}

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++, k++) {
				cmplx<int> w = expFFT<8>(2 * i*j + i, amplitude);
				nmppsPut_16s(wRe, k, w.re);
				nmppsPut_16s(wIm, k, w.im);
			}

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++, k++) {
				cmplx<int> w = expFFT<8>(2 * i*j + j, amplitude);
				nmppsPut_16s(wRe, k, w.re);
				nmppsPut_16s(wIm, k, w.im);
			}

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++, k++) {
				cmplx<int> w = expFFT<16>(2 * (2 * i*j + j + i) + 1, amplitude);
				nmppsPut_16s(wRe, k, w.re);
				nmppsPut_16s(wIm, k, w.im);
			}

		return NMPP_OK;
	}
	int  nmppsFFT16HiFwdInit(NmppsFFTSpec* spec, void* buffer0, void* buffer1, void* fftTable0, void* fftTable1)
	{
		spec->buffer[0] = (nm32sc*)buffer0;
		spec->buffer[1] = (nm32sc*)buffer1;
		spec->fftTable[0] = (nm16s*)fftTable0;
		spec->fftTable[1] = (nm16s*)fftTable1;
		spec->norm[0].shift= 8;
		spec->amp[0] = 1 << spec->norm[0].shift;
		spec->norm[0].round = spec->amp[0] / 2;
		
		
			
		//nmppsSet_64s((nm64s*)spec->buffer[0], 0,16);
		//nmppsSet_64s((nm64s*)spec->buffer[1], 0,16);
		

		nmppsFFT16FwdInitSinCos242(spec);
		return 0;
	}



	int  nmppsFFT16HiFwdInitAlloc(NmppsFFTSpec* spec, const void* src, const void* dst, int settings)
	{
		spec->norm[0].shift = 8;
		spec->amp[0] = 1 << spec->norm[0].shift;
		spec->norm[0].round = spec->amp[0] / 2;
		

		spec->buffer[0]   = nmppsMalloc_32sc(16);
		spec->buffer[1]   = nmppsMalloc_32sc(16);
		spec->fftTable[0] = (void*)nmppsMalloc_16s(4*4*4);
		spec->fftTable[1] = (void*)nmppsMalloc_16s(4*4*4);

		//nmppsSet_64s((nm64s*)spec->buffer[0], 0,16);
		//nmppsSet_64s((nm64s*)spec->buffer[1], 0,16);
		//nmppsSet_64s((nm64s*)dst, 0, 16);

		//clock_t t0, t1, dt, mindt=0x100000;
		//if (setting& OPTIMIZE) {
		//	while () {
		//		spec->buffer[0] = nmppsMalloc_32sc(16);
		//		spec->buffer[1] = nmppsMalloc_32sc(16);
		//		spec->fftTable[0] = (void*)nmppsMalloc_16s(4 * 4 * 4);
		//		spec->fftTable[1] = (void*)nmppsMalloc_16s(4 * 4 * 4);
		//
		//		t0 = clock();
		//		nmppsFFT16FwdRaw(src, dst, &FFTSpec);
		//		t1 = clock();
		//		dt = t1 - t0;
		//		if (dt < mindt) {
		//			mindt = dt;
		//
		//		}
		//
		//
		//	}
		//
		//}
		

		if (
			(spec->buffer[0]   ==0)|
			(spec->buffer[1]   ==0)|
			(spec->fftTable[0] ==0)|
			(spec->fftTable[1] ==0)
		) return -1;
		
		nmppsFFT16FwdInitSinCos242(spec);
		return 0;
	}

};