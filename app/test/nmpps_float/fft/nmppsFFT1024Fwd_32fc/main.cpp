#include <math.h>
#include <malloc.h>
#include "nmpp.h"
#include "time.h"
#include "fft_32fc.h"
#include <stdio.h>

#pragma data_section ".data_imu1"
	nm32fcr src[32*32];
#pragma data_section ".data_imu5"
	nm32fcr dst[32*32];

int main()
{
	int i, tm, time;
	clock_t t1, t2;
	// time = 10472 ticks
	for(i = 0; i < 1024; i++) {
		src[i].im = 0;
		src[i].re = i;
		dst[i].im = 0;
		dst[i].re = 0;
	}
	NmppsFFTSpec_32fc *rat;
	tm = nmppsFFT1024FwdInitAlloc_32fc(&rat);
	if(tm == 123) {
		return 123;
	}
	t1 = clock();
	nmppsFFT1024Fwd_32fc(src, dst, rat);
	t2 = clock();
	time = t2 - t1;
	tm = nmppsFFTFree_32fc(rat);
	unsigned int crc1 = 0;
	unsigned int crc2 = 0;
	nmppsCrcAcc_32f((nm32f *)dst, 16, 1024*2, &crc1);
	tm = nmppsFFTFwdInitAlloc_32fc(&rat, 10);
	if(tm == 123) {
		return 123;
	}
	tm = nmppsFFTFwd_32fc(src, dst, rat);
	tm = nmppsFFTFree_32fc(rat);
	nmppsCrcAcc_32f((nm32f *)dst, 16, 1024*2, &crc2);
	printf("%d\n", time);
	// printf("%d\n", crc2>>2);
	return crc1>>2;
}