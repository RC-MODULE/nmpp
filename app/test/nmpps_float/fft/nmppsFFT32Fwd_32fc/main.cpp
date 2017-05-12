//#include <math.h>
#include <stdio.h>
#include "time.h"
#include <nmtype.h>
#include <malloc.h>
#include "fft_32fc.h"
#include "math.h"
#include "nmpp.h"

int main()
{
	int i, tm;
	nm32fcr *src, *dst, *outInv1;
	// best conf (tm = 351)
	//nmppsMallocSetRoute16(0xFF3210);
	// src = nmppsMalloc_32fc(32);
	// dst = nmppsMalloc_32fc(32);
	 src = (nm32fcr *) malloc(64 * sizeof(nm32fcr));
	 dst = (nm32fcr *) malloc(64 * sizeof(nm32fcr));
	for(i = 0; i < 32; i++) {
		src[i].im = 0;
		src[i].re = i;
		dst[i].im = 0;
		dst[i].re = 0;
	}
	//return (int)dst;
	NmppsFFTSpec_32fc *rat;
	tm = nmppsFFT32FwdInitAlloc_32fc(&rat);
	if(tm == 123) {
		return 123;
	}
	//return 5;
	nmppsFFT32Fwd_32fc(src, dst, rat);
	for(int i = 0; i < 32; i++)
		printf("%.5f %.5f\n", dst[i].re, dst[i].im);
	unsigned int crc = 0;
	nmppsCrcAcc_32f((nm32f *)dst, 9, 32*2, &crc);
	return crc>>2;
}

