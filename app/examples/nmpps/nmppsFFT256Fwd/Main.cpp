#include "nmpp.h"
//#include "fft.h"
#include "fft2.h"
#include <time.h>


int main()
{
	clock_t t0,t1,bestTime=0x1000000;
	
	t0=clock();


	//FFT_Fwd256Set7bit();

	
	nm32sc* src =(nm32sc*)nmppsMalloc_64s(256);
	nm32sc* dst =(nm32sc*)nmppsMalloc_64s(256);
	
	nmppsRandUniform_32s((nm32s*)src,256*2);
	nmppsRShiftC_32u((nm32u*)src,24, (nm32u*)src, 256*2);
	
	NmppsFFTSpec* specFFT256Fwd;
	//fseq64 route=0xF10;
	//nmppsFFT256FwdOptimize(src,dst,&route);
	//nmppsMallocSetRouteMode(route);
	nmppsFFT256FwdInitAlloc(&specFFT256Fwd,src,dst,0);
	t0=clock();
	nmppsFFT256Fwd(src,dst,specFFT256Fwd);
	t1=clock();
	
	NmppsFFTSpec* specFFT256Inv;
	//fseq64 route=0xF10;
	//nmppsFFT256FwdOptimize(src,dst,&route);
	//nmppsMallocSetRouteMode(route);
	//nmppsFFT256InvInitAlloc(&specFFT256Inv,src,dst,0);
	//t0=clock();
	//nmppsFFT256Inv(dst,src,specFFT256Inv);
	//t1=clock();

	
	//return route;
	//return t1-t0;
	unsigned crc = nmppsCrc_32s((nm32s*)dst,256*2)>>2;
	nmppsFree(src);
	nmppsFree(dst);
	nmppsFFTFree(specFFT256Fwd);
	//return crc;
	return t1-t0;
}
