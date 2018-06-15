#include "time.h"
#include "fft_32fcr.h"
#include "nmpp.h"
#include <nmtype.h>
#include <malloc.h>
#include <stdio.h>

#pragma data_section ".data_imu3"
	nm32fcr src[4096];
#pragma data_section ".data_imu5"
	nm32fcr dst[4096 + 12];

#define		SIZE 		4096

int main()
{
	int i, st;
	clock_t t1, t2;
	//nm32fcr *src, *dst;
	// best config (ticks = 24219)
	//src = (nm32fcr *)malloc(SIZE * sizeof(nm32fcr));
	//dst = (nm32fcr *)malloc(SIZE * sizeof(nm32fcr));
	for(i = 0; i < SIZE; i++) {
		src[i].im = 0;
		src[i].re = i;
		dst[i].im = 0;
		dst[i].re = 0;
	}

	for(i = 0; i < SIZE + 12; i++) {
		src[i].im = 0;
		src[i].re = i;
		dst[i].im = 0;
		dst[i].re = 0;
	}

	NmppsFFTSpec_32fcr *rat, *irat;
	st = nmppsFFT4096FwdInitAlloc_32fcr(&rat);
	if(st) {
		return st;
	}
	st = nmppsFFT4096InvInitAlloc_32fcr(&irat);
	if(st) {
		return st;
	}
	t1 = clock();
	nmppsFFT4096Fwd_32fcr(src, dst, rat);
	t2 = clock();
	nmppsFFT4096Inv_32fcr(dst, dst, irat);
	st = nmppsFFTFree_32fcr(rat);
	if(st) {
		return st;
	}
	st = nmppsFFTFree_32fcr(irat);
	if(st) {
		return st;
	}
	float norm;
	nmppsNormDiff_L2_32fcr(src, dst, SIZE, &norm);
	printf("%.7f\n", norm);
	// for(i = 0; i < SIZE + 12; i += 2) {
	// 	printf("[%d]  %.2f  %.2f          %.2f  %.2f\n", i, dst[i].re, dst[i].im, dst[i + 1].re, dst[i + 1].im);
	// }
	return t2 - t1;
}