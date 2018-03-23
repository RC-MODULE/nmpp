#include "time.h"
#include "fft_32fcr.h"
#include "nmpp.h"
#include <nmtype.h>
#include <malloc.h>
#include <stdio.h>

int main()
{
	int i, st;
	clock_t t1, t2;
	nm32fcr *src, *dst;
	// best config (cycles = 3700)
	src = (nm32fcr *)malloc(512 * sizeof(nm32fcr));
	dst = (nm32fcr *)malloc(512 * sizeof(nm32fcr));
	for(i = 0; i < 512; i++) {
		src[i].im = 1;
		src[i].re = i;
		dst[i].im = 0;
		dst[i].re = 0;
	}
	NmppsFFTSpec_32fcr *rat, *irat;
	st = nmppsFFT512FwdInitAlloc_32fcr(&rat);
	if(st) {
		return 123;
	}
	st = nmppsFFT512InvInitAlloc_32fcr(&irat);
	if(st) {
		return 124;
	}
	t1 = clock();
	nmppsFFT512Fwd_32fcr(src, dst, rat);
	t2 = clock();
	nmppsFFT512Inv_32fcr(dst, dst, irat);
	st = nmppsFFTFree_32fcr(rat);
	if(st) {
		return 125;
	}
	unsigned int crc = 0;
	nmppsCrcAcc_32f((nm32f *)dst, 11, 512*2, &crc);
	st = nmppsFFTFree_32fcr(irat);
	if(st) {
		return 126;
	}
	for(i = 0; i < 512; i++){
		printf("%.2f %.2f\n", dst[i].re, dst[i].im);
	}
	return t2 - t1;
}