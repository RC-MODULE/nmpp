#include "time.h"
#include "fft_32fcr.h"
#include "nmpp.h"
#include <nmtype.h>
#include <malloc.h>
#include <stdio.h>

#define		SIZE 		1024

// #pragma data_section ".data_imu1"
// 	nm32fcr src[SIZE];
// #pragma data_section ".data_imu5"
// 	nm32fcr dst[SIZE];

int main()
{
	int i, st;
	clock_t t1, t2;
	nm32fcr *src, *dst;
	// best config (cycles = 10223) src - imu1, dst - imu5
	src = (nm32fcr *)malloc(SIZE * sizeof(nm32fcr));
	dst = (nm32fcr *)malloc1(SIZE * sizeof(nm32fcr));
	for(i = 0; i < SIZE; i++) {
		src[i].im = 1;
		src[i].re = i;
		dst[i].im = 0;
		dst[i].re = 0;
	}
	NmppsFFTSpec_32fcr *rat, *irat;
	st = nmppsFFT1024FwdInitAlloc_32fcr(&rat);
	if(st) {
		return 123;
	}
	st = nmppsFFT1024InvInitAlloc_32fcr(&irat);
	if(st) {
		return 124;
	}
	t1 = clock();
	nmppsFFT1024Fwd_32fcr(src, dst, rat);
	t2 = clock();
	nmppsFFT1024Inv_32fcr(dst, dst, irat);
	st = nmppsFFTFree_32fcr(rat);
	if(st) {
		return 125;
	}
	st = nmppsFFTFree_32fcr(irat);
	if(st) {
		return 126;
	}
	float norm;
	nmppsNormDiff_L2_32fcr(src, dst, SIZE, &norm);
	printf("%.7f\n", norm);
	// for(i = 0; i < SIZE; i++){
	// 	printf("%.2f %.2f\n", dst[i].re, dst[i].im);
	// }
	return t2 - t1;
}