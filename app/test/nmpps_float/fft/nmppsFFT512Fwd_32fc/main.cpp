#include <math.h>
#include <malloc.h>
#include "time.h"
#include "fft_32fc.h"
#include "nmpp.h"
#include <stdio.h>

#pragma data_section ".data_imu2"
	nm32fcr src[32*16];
#pragma data_section ".data_imu1"
	nm32fcr dst[32*16];

int main()
{
	int i, tm, t;
	clock_t t1, t2;
	// best config (tm = 5389, src - malloc, dst - malloc1)
	for(i = 0; i < 512; i++) {
		src[i].im = 0;
		src[i].re = i;
		dst[i].im = 0;
		dst[i].re = 0;
	}
	NmppsFFTSpec_32fc *rat;
	tm = nmppsFFT512FwdInitAlloc_32fc(&rat);
	if(tm == 123) {
		return 123;
	}
	t1 = clock();
	nmppsFFT512Fwd_32fc(src, dst, rat);
	t2 = clock();
	t = t2 - t1;
	printf("%d\n", t);
	tm = nmppsFFTFree_32fc(rat);
	unsigned int crc1 = 0;
	unsigned int crc2 = 0;
	nmppsCrcAcc_32f((nm32f *)dst, 17, 512*2, &crc1);
	//tm = nmppsFFTFwdInitAlloc_32fc(&rat, 9);
	if(tm == 123) {
		return 123;
	}
	//tm = nmppsFFTFwd_32fc(src, dst, rat);
	//tm = nmppsFFTFree_32fc(rat);
	//nmppsCrcAcc_32f((nm32f *)dst, 16, 512*2, &crc2);
	//for(i = 0; i < 512; i++)
	//	printf("%d  %.1f %.1f\n", i, dst[i].re, dst[i].im);
	// printf("%d\n", crc1>>2);
	// printf("%d\n", crc2>>2);
	return crc1>>2;
}