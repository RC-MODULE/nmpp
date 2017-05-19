#include <math.h>
#include <malloc.h>
#include "nmpp.h"
#include "fft_32fc.h"

int main()
{
	int i, tm;
	nm32fcr *src, *dst;
	// tm = 13980
	src = (nm32fcr *)malloc(1024  * sizeof(nm32fcr));
	dst = (nm32fcr *)malloc(1024  * sizeof(nm32fcr));
	for(i = 0; i < 1024; i++) {
		src[i].im = 0;
		src[i].re = i;
		dst[i].im = 0;
		dst[i].re = 0;
	}
	NmppsFFTSpec_32fc *rat;
	tm = nmppsFFT1024FwdInitAlloc_32fc(&rat);
	if(tm < 0) {
		return 123;
	}
	nmppsFFT1024Fwd_32fc(src, dst, rat);
	tm = nmppsFFTFree_32fc(rat);
	unsigned int crc = 0;
	nmppsCrcAcc_32f((nm32f *)dst, 16, 1024*2, &crc);
	return crc>>2;
}