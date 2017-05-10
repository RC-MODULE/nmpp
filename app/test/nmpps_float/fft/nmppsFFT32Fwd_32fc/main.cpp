//#include <math.h>
#include "time.h"
#include <nmtype.h>
#include <malloc32.h>
#include "fft_32fc.h"
#include "math.h"
#include "nmpp.h"

#define		NU32	64

union abc {
	float FL;
	int IN;
};

void invfft32(nm32fc *X32, nm32fc *x32);

int main()
{
	int i, tm;
	clock_t t1, t0;
	union abc ab;
	nm32fc *src, *dst, *outInv1;
	// best conf (tm = 351)
	src = (nm32fc *) malloc(64);
	dst = (nm32fc *) malloc(64);
	outInv1 = (nm32fc *) malloc(64);
	for(i = 0; i < 32; i++) {
		src[i].im = 0;
		src[i].re = i;
		dst[i].im = 0;
		dst[i].re = 0;
		outInv1[i].im = 0;
		outInv1[i].re = 0;
	}
	//return (int)dst;
	float SKO_dft32;
	NmppsFFTSpec_32fc *rat;
	tm = nmppsFFT32FwdInitAlloc_32fc(&rat);
	if(tm == 123) {
		return 123;
	}
	SKO_dft32 = 0;
	t0 = clock();
	nmppsFFT32Fwd_32fc(src, dst, rat);
	unsigned int crc=0;
	nmppsCrcAcc_32s((int*)dst,32*2,&crc);
	//round(dst,dst,5);
	t1 = clock();
	tm = t1 - t0;
	//invfft32(dst, outInv1);
	for(i = 0; i < NU32/2; i++) {
	  	outInv1[i].re = outInv1[i].re / 32.0;
	  	outInv1[i].im = outInv1[i].im / 32.0;
	}
	for(i = 0; i < NU32/2; i++) {
       SKO_dft32 += (src[i].re - outInv1[i].re) * (src[i].re - outInv1[i].re);
       SKO_dft32 += (src[i].im - outInv1[i].im) * (src[i].im - outInv1[i].im);
    }
    SKO_dft32 = SKO_dft32 / NU32;
    SKO_dft32 = sqrtf(SKO_dft32);
    ab.FL = SKO_dft32;
	return crc>>2;
}