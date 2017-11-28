#include <math.h>
#include <malloc.h>
#include "time.h"
#include "fft_32fc.h"
#include "nmpp.h"
//#include <stdio.h>

#pragma data_section ".data_imu1"
	nm32fcr src[256];
#pragma data_section ".data_imu5"
	nm32fcr dst[256];

int main()
{
	int i, tm, time;
	clock_t t1, t2;
	for(i = 0; i < 256; i++) {
		src[i].im = 0;
		src[i].re = i;
		dst[i].im = 0;
		dst[i].re = 0;
	}
	NmppsFFTSpec_32fc *rat;
	tm = nmppsFFT256FwdInitAlloc_32fc(&rat);
	if(tm == 123) {
		return 123;
	}
	t1 = clock();
	nmppsFFT256Fwd_32fc(src, dst, rat);
	t2 = clock();
	time = t2 - t1; // best config 1812 ticks
	tm = nmppsFFTFree_32fc(rat);
	unsigned int crc1 = 0;
	unsigned int crc2 = 0;
	nmppsCrcAcc_32f((nm32f *)dst, 17, 256*2, &crc1);
	tm = nmppsFFTFwdInitAlloc_32fc(&rat, 8);
	if(tm == 123) {
		return 123;
	}
	tm = nmppsFFTFwd_32fc(src, dst, rat);
	tm = nmppsFFTFree_32fc(rat);
	nmppsCrcAcc_32f((nm32f *)dst, 16, 256*2, &crc2);
	// printf("%d\n", crc1>>2);
	// printf("%d\n", crc2>>2);
	//printf("%d\n", time);
	return crc1 >> 2;
}