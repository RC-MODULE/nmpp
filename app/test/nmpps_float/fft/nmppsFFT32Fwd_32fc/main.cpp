//#include <math.h>
#include "time.h"
#include <nmtype.h>
#include <malloc32.h>
#include "fft_32fc.h"
#include "math.h"
#include "nmpp.h"

#define		NU32	64

union abc {
	float FL;
	int IN;
};



int main()
{

	int i, tm;
	union abc ab;
	nm32fc *src, *dst, *outInv1;
	// best conf (tm = 351)
	//nmppsMallocSetRoute16(0xFF3210);
	src = nmppsMalloc_32fc(32);
	dst = nmppsMalloc_32fc(32);
	outInv1 = nmppsMalloc_32fc(32);
	for(i = 0; i < 32; i++) {
		src[i].im = 3-i;
		src[i].re = 2*i;
		dst[i].im = 0;
		dst[i].re = 0;
		outInv1[i].im = 0;
		outInv1[i].re = 0;
	}
	//return (int)dst;
	NmppsFFTSpec_32fc *rat;
	tm = nmppsFFT32FwdInitAlloc_32fc(&rat);
	if(tm == 123) {
		return 123;
	}
	nmppsFFT32Fwd_32fc(src, dst, rat);
	unsigned int crc=0;
	nmppsCrcAcc_32f((nm32f *)dst, 16, 32*2, &crc);
	return crc>>2;
}

