#include "fft_32fcr.h"
#include "nmpp.h"
#include "time.h"
#include <nmtype.h>
#include <malloc.h>
#include <stdio.h>

class Duration {
public:
  Duration(char* new_message) {
    message = new_message;
	t1 = clock();
  }
  ~Duration() {
    t2 = clock();
	printf("%s%d\n", message, t2 - t1 - 60);
  }
private:
  char* message;
  clock_t t1;
  clock_t t2;
};

#define DURATION(message)         \
  Duration duration(message);

#define		SIZE 		256

#pragma data_section ".mem_bank1"
	nm32fcr src[256];
#pragma data_section ".mem_bank5"
	nm32fcr dst[256];

int main()
{
	int i, st;
	clock_t t1, t2;
//	nm32fcr *src, *dst;
//  best config (ticks = 1763)
//	src = (nm32fcr *)malloc(SIZE * sizeof(nm32fcr));
//	dst = (nm32fcr *)malloc(SIZE * sizeof(nm32fcr));
	for(i = 0; i < SIZE; i++) {
		src[i].im = 1;
		src[i].re = i;
		dst[i].im = 0;
		dst[i].re = 0;
	}
	NmppsFFTSpec_32fcr *rat, *irat;
	st = nmppsFFT256FwdInitAlloc_32fcr(&rat);
	if(st) {
		return st;
	}
	st = nmppsFFT256InvInitAlloc_32fcr(&irat);
	if(st) {
		return st;
	}
	{
	DURATION("FFT256Fwd: ")
	//t1 = clock();
	nmppsFFT256Fwd_32fcr(src, dst, rat);
	//t2 = clock();
	}
	nmppsFFT256Inv_32fcr(dst, dst, irat);
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
	// 	printf("%.5f %.5f\n", dst[i].re, dst[i].im);
	// }
	return t2 - t1;
}
