#include "nmpp.h"
//#include "fft.h"
#include "fft.h"
#include "stdio.h"
#include <time.h>

#define FFT_SIZE 512 

int speedTest(){
	clock_t t0,t1,bestTime=0xFFFFF;
	unsigned int crc = 0;
	//nmppsMallocSpec.route[0] = 0x23013;
	nmppsMallocSpec.route[0] = 0x0;
	// 2   3   0   1   3
	//ar4 ar2 ar1 ar6 ar0
	nmppsMallocSetRouteMode();
	
	while (1)
	{
		nmppsMallocResetPos();
		nm32sc* src   =(nm32sc*)nmppsMalloc_64s(FFT_SIZE);
		nm32sc* dst	  =(nm32sc*)nmppsMalloc_64s(FFT_SIZE);
		NmppsFFTSpec* spec;
		nmppsFFT512FwdInitAlloc(&spec,src,dst,-1);
		
		if (nmppsMallocFail()) return -2;
		
		nmppsSet_64s((nm64s*)src,0,FFT_SIZE);
		nmppsRandUniform_64s((nm64s*)dst,FFT_SIZE);
		src[0].re=100;
		src[1].re=100;
		
		t0=clock();
		nmppsFFT512Fwd(src,dst,spec);
		//nmppsFFT32FwdRawRef2x16(src,dst);
		t1=clock();
		if (t1-t0<bestTime)
			bestTime=t1-t0;
		nmppsFFTFree(spec);
		nmppsFree(src);
		nmppsFree(dst);
		printf("%8x %d\n",(int)nmppsMallocSpec.route[0], t1-t0);
		if (nmppsMallocIncrementRoute())
			return (bestTime);
	}
	
	return t1-t0;
}


int main()
{
	return speedTest();
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
