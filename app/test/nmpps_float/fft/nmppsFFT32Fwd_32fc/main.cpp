//#include <math.h>
#include <nmtype.h>
#include <malloc.h>
#include "fft_32fc.h"
#include "math.h"
#include "nmpp.h"

int main()
{
	int i, tm;
	nm32fcr *src, *dst;
	src = (nm32fcr *) malloc(32 * sizeof(nm32fcr));
	dst = (nm32fcr *) malloc(32 * sizeof(nm32fcr));
	for(i = 0; i < 32; i++) {
		src[i].im = 0;
		src[i].re = i;
		dst[i].im = 0;
		dst[i].re = 0;
	}
	//return (int)dst;
	NmppsFFTSpec_32fc *rat;
	tm = nmppsFFT32FwdInitAlloc_32fc(&rat);
	if(tm == 123) {
		return 123;
	}
	nmppsFFT32Fwd_32fc(src, dst, rat);
	unsigned int crc = 0;
	nmppsCrcAcc_32f((nm32f *)dst, 9, 32*2, &crc);
	return crc>>2;
}

