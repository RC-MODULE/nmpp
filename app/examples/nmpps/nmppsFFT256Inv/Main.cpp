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
	
	NmppsFFTSpec* spec;
	//fseq64 route=0xF10;
	//nmppsFFT256FwdOptimize(src,dst,&route);
	//nmppsMallocSetRouteMode(route);
	if (nmppsFFT256InvInitAlloc(&spec, src,dst, 0))
		return -1;
		
	t0=clock();
	nmppsFFT256Inv(src,dst,spec);
	t1=clock();
	
	
	//return route;
	//return t1-t0;
	return  nmppsCrc_32s((nm32s*)dst,256*2)>>2;
	
	nmppsFree(src);
	nmppsFree(dst);
	nmppsFFTFree(spec);
	
	
	return t1-t0;
}
