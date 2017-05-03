#include <math.h>
#include <malloc.h>
#include "time.h"
#include "fft_32fc.h"

union abc {
	float FL;
	int IN;
};

void invfft512(nm32fc *invX64, nm32fc *invx64);

int main()
{
	int i, tm;
	clock_t t1, t0;
	union abc ab;
	nm32fc *src, *dst, *outInv1;
	// best config (tm = 5389, src - malloc, dst - malloc1)
	src = (nm32fc *)malloc(1024);
	dst = (nm32fc *)malloc(1024);
	outInv1 = (nm32fc *)malloc1(1024);
	for(i = 0; i < 512; i++) {
		src[i].im = 0;
		src[i].re = i;
		dst[i].im = 0;
		dst[i].re = 0;
		outInv1[i].im = 0;
		outInv1[i].re = 0;
	}
	float SKO_dft32;
	NmppsFFTSpec_32fc *rat;
	tm = nmppsFFT512FwdInitAlloc_32fc(&rat);
	if(tm == 123) {
		return 123;
	}
	SKO_dft32 = 0;
	t0 = clock();
	nmppsFFT512Fwd_32fc(src, dst, rat);
	t1 = clock();
	tm = t1 - t0;
	//invfft512(dst, outInv1);
	for(i = 0; i < 512; i++) {
	  	//outInv[i] = outInv[i] / 64.0;
	  	outInv1[i].re = outInv1[i].re / 512.0;
	  	outInv1[i].im = outInv1[i].im / 512.0;
	}
	for(i = 0; i < 512; i++) {
       //SKO_dft32 += (a[i]- outInv[i]) * (a[i] - outInv[i]);
       SKO_dft32 += (src[i].re - outInv1[i].re) * (src[i].re - outInv1[i].re);
       SKO_dft32 += (src[i].im - outInv1[i].im) * (src[i].im - outInv1[i].im);
    }
    SKO_dft32 = SKO_dft32 / 1024;
    SKO_dft32 = sqrtf(SKO_dft32);
    ab.FL = SKO_dft32;
	return tm;
}