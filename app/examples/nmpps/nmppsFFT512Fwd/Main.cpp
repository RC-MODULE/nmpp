#include "nmpp.h"
//#include "fft.h"
#include "fft2.h"
#include <time.h>


int main()
{
	clock_t t0,t1,bestTime=0x1000000;
	
	t0=clock();


	//FFT_Fwd512Set7bit();

	
	nm32sc* src =(nm32sc*)nmppsMalloc_64s(512);
	nm32sc* dst =(nm32sc*)nmppsMalloc_64s(512);
	
	nmppsRandUniform_32s((nm32s*)src,512*2);
	nmppsRShiftC_32u((nm32u*)src,24, (nm32u*)src, 512*2);
	
	NmppsFFTSpec* specFFT512Fwd;
	//fseq64 route=0xF10;
	//nmppsFFT512FwdOptimize(src,dst,&route);
	//nmppsMallocSetRouteMode(route);
	nmppsFFT512FwdInitAlloc(&specFFT512Fwd,src,dst,0);
	t0=clock();
	nmppsFFT512Fwd(src,dst,specFFT512Fwd);
	t1=clock();
	nmppsFFTFree(specFFT512Fwd);
	//------------------------------
	NmppsFFTSpec* specFFT512Inv;
	fseq64 route=0xF10;
	//nmppsFFT512InvOptimize(src,dst,&route);
	//nmppsMallocSetRouteMode(route);
	nmppsFFT512InvInitAlloc(&specFFT512Inv,dst,src,NMPP_OPTIMIZE_DISABLE);
	t0=clock();
	nmppsFFT512Inv(dst,src,specFFT512Inv);
	t1=clock();
	nmppsFFTFree(specFFT512Inv);
	
	//return route;
	//return t1-t0;
	unsigned crc = nmppsCrc_32s((nm32s*)dst,512*2)>>2;
	nmppsFree(src);
	nmppsFree(dst);
	
	return crc;
	//return t1-t0;
}
