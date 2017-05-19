#include <math.h>
#include <malloc.h>
#include "time.h"
#include "fft_32fc.h"
#include "nmpp.h"
#include <stdio.h>

int main()
{
	int i, tm;
	nm32fcr *src, *dst;
	// best config (tm = 2155, src - malloc, dst - malloc2, or
	// src - malloc3, dst - malloc1)
	src = (nm32fcr *)malloc(256  * sizeof(nm32fcr));
	dst = (nm32fcr *)malloc(256  * sizeof(nm32fcr));
	for(i = 0; i < 256; i++) {
		src[i].im = 0;
		src[i].re = i;
		dst[i].im = 0;
		dst[i].re = 0;
	}
	NmppsFFTSpec_32fc *rat;
	tm = nmppsFFT256FwdInitAlloc_32fc(&rat);
	if(tm < 0) {
		return 123;
	}
	nmppsFFT256Fwd_32fc(src, dst, rat);
	for(int i=0;i<256;i++)
		printf("%.7f %.7f\n", dst[i].re, dst[i].im);
	tm = nmppsFFTFree_32fc(rat);
	unsigned int crc = 0;
	nmppsCrcAcc_32f((nm32f *)dst, 16, 256*2, &crc);
	return crc>>2;
}