#include <nmtype.h>
#include <malloc.h>
#include <stdio.h>
#include "fft_32fcr.h"
#include "math.h"
#include "nmpp.h"

int main()
{
	int i, tm;
	nm32fcr *src, *dst;
	src = (nm32fcr *) malloc(32 * sizeof(nm32fcr));
	dst = (nm32fcr *) malloc(32 * sizeof(nm32fcr));
	for(i = 0; i < 32; i++) {
		src[i].im = 1;
		src[i].re = i;
		dst[i].im = 0;
		dst[i].re = 0;
	}
	//return (int)dst;
	NmppsFFTSpec_32fcr *rat, *irat;
	tm = nmppsFFT32FwdInitAlloc_32fcr(&rat);
	tm = nmppsFFT32InvInitAlloc_32fcr(&irat);
	if(tm) {
		return 123;
	}
	nmppsFFT32Fwd_32fcr(src, dst, rat);
	nmppsFFT32Inv_32fcr(dst, dst, irat);
	tm = nmppsFFTFree_32fcr(rat);
	if(tm) {
		return 124;
	}
	tm = nmppsFFTFree_32fcr(irat);
	if(tm) {
		return 125;
	}
	unsigned int crc1 = 0;
	nmppsCrcAcc_32f((nm32f *)dst, 11, 32*2, &crc1);
	for(i = 0; i < 32; i++)
		printf("%.5f %.5f\n", dst[i].re, dst[i].im);
	return crc1 >> 2;
}

