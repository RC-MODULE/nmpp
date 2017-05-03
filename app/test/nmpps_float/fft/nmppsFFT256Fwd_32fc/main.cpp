#include <math.h>
#include <malloc.h>
#include "time.h"
#include "fft_32fc.h"

union abc {
	float FL;
	int IN;
};

void invfft256(nm32fc *invX64, nm32fc *invx64);

int main()
{
	int i, tm;
	clock_t t1, t0;
	union abc ab;
	nm32fc *src, *dst, *outInv1;
	// best config (tm = 2155, src - malloc, dst - malloc2, or
	// src - malloc3, dst - malloc1)
	src = (nm32fc *)malloc(512);
	dst = (nm32fc *)malloc(512);
	outInv1 = (nm32fc *)malloc(512);
	for(i = 0; i < 256; i++) {
		src[i].im = 0;
		src[i].re = i;
		dst[i].im = 0;
		dst[i].re = 0;
		outInv1[i].im = 0;
		outInv1[i].re = 0;
	}
	float SKO_dft32;
	NmppsFFTSpec_32fc *rat;
	tm = nmppsFFT256FwdInitAlloc_32fc(&rat);
	if(tm == 123) {
		return 123;
	}
	SKO_dft32 = 0;
	t0 = clock();
	nmppsFFT256Fwd_32fc(src, dst, rat);
	t1 = clock();
	tm = t1 - t0;
	//invfft256(dst, outInv1);
	for(i = 0; i < 256; i++) {
	  	outInv1[i].re = outInv1[i].re / 256.0;
	  	outInv1[i].im = outInv1[i].im / 256.0;
	}
	for(i = 0; i < 256; i++) {
       SKO_dft32 += (src[i].re - outInv1[i].re) * (src[i].re - outInv1[i].re);
       SKO_dft32 += (src[i].im - outInv1[i].im) * (src[i].im - outInv1[i].im);
    }
    SKO_dft32 = SKO_dft32 / 512;
    SKO_dft32 = sqrtf(SKO_dft32);
    ab.FL = SKO_dft32;
	return tm;
}