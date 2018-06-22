#include "time.h"
#include "fft_32fcr.h"
#include "nmpp.h"
#include <nmtype.h>
#include <malloc.h>
#include <stdio.h>

#define		SIZE 		512

#pragma data_section ".data_imu1"
	nm32fcr src[512];
#pragma data_section ".data_imu5"
	nm32fcr dst[512];

int main()
{
	int i, st;
	clock_t t1, t2;
//	nm32fcr *src, *dst;
// best config (ticks = 3783)
//	src = (nm32fcr *)malloc(SIZE * sizeof(nm32fcr));
//	dst = (nm32fcr *)malloc(SIZE * sizeof(nm32fcr));
	for(i = 0; i < SIZE; i++) {
		src[i].im = 1;
		src[i].re = i;
		dst[i].im = 0;
		dst[i].re = 0;
	}
	NmppsFFTSpec_32fcr *rat, *irat;
	st = nmppsFFT512FwdInitAlloc_32fcr(&rat);
	if(st) {
		return st;
	}
	st = nmppsFFT512InvInitAlloc_32fcr(&irat);
	if(st) {
		return st;
	}
	t1 = clock();
	nmppsFFT512Fwd_32fcr(src, dst, rat);
	t2 = clock();
	nmppsFFT512Inv_32fcr(dst, dst, irat);
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
	// for(i = 0; i < SIZE; i++){
	// 	printf("%.2f %.2f\n", dst[i].re, dst[i].im);
	// }
	return t2 - t1;
}