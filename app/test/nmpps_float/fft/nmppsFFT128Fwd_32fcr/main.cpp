#include "fft_32fcr.h"
#include "nmpp.h"
#include "time.h"
#include <nmtype.h>
#include <malloc.h>
#include <stdio.h>

#define		SIZE 		128

int main()
{
	int i, tm;
	clock_t t1, t2;
	nm32fcr *src, *dst;
	// best config (tm = 1200)
	src = (nm32fcr *)malloc(SIZE * sizeof(nm32fcr));
	dst = (nm32fcr *)malloc(SIZE * sizeof(nm32fcr));
	for(i = 0; i < SIZE; i++) {
		src[i].im = 1;
		src[i].re = i;
		dst[i].im = 0;
		dst[i].re = 0;
	}
	NmppsFFTSpec_32fcr *rat, *irat;
	tm = nmppsFFT128FwdInitAlloc_32fcr(&rat);
	if(tm) {
		return 123;
	}
	tm = nmppsFFT128InvInitAlloc_32fcr(&irat);
	if(tm) {
		return 124;
	}
	t1 = clock();
	nmppsFFT128Fwd_32fcr(src, dst, rat);
	t2 = clock();
	nmppsFFT128Inv_32fcr(dst, dst, irat);
	tm = nmppsFFTFree_32fcr(rat);
	if(tm) {
		return 125;
	}
	tm = nmppsFFTFree_32fcr(irat);
	if(tm) {
		return 126;
	}
	float norm;
	nmppsNormDiff_L2_32fcr(src, dst, SIZE, &norm);
	printf("%.7f\n", norm);

	// for(i = 0; i < SIZE; i++){
	// 	printf("%.5f %.5f\n", dst[i].re, dst[i].im);
	// }
	return t2 - t1;
}