#include "fft2.h"
#include "nmpp.h"
#include <time.h>
#include <stdio.h>


#define FFT_SIZE 32

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
		NmppsFFTSpec spec;
		nmppsFFT32FwdInitAlloc(&spec,0);
		
		if (nmppsMallocFail()) return -2;
		
		nmppsSet_64s((nm64s*)src,0,FFT_SIZE);
		nmppsRandUniform_64s((nm64s*)dst,FFT_SIZE);
		src[0].re=100;
		src[1].re=100;
		
		t0=clock();
		nmppsFFT32FwdRaw(src,dst,&spec);
		//nmppsFFT32FwdRawRef2x16(src,dst);
		t1=clock();
		if (t1-t0<bestTime)
			bestTime=t1-t0;
		nmppsFFT32Free(&spec);
		nmppsFree(src);
		nmppsFree(dst);
		printf("%8x %d\n",(int)nmppsMallocSpec.route[0], t1-t0);
		if (nmppsMallocIncrementRoute())
			return (bestTime);
	}
	
	return t1-t0;
}
int selfTest(){
	clock_t t0,t1,bestTime=0xFFFFF;
	float msd;
	unsigned int crc = 0;
	//nmppsMallocSpec.route[0] = 0x23013;
	nmppsMallocSpec.route[0] = 0x0;
	// 2   3   0   1   3
	//ar4 ar2 ar1 ar6 ar0
	nmppsMallocSetRouteMode();
	
	nmppsMallocResetPos();
	nm32sc* src   =(nm32sc*)nmppsMalloc_64s(FFT_SIZE);
	nm32sc* dstRef=(nm32sc*)nmppsMalloc_64s(FFT_SIZE);
	nm32sc* dst   =(nm32sc*)nmppsMalloc_64s(FFT_SIZE);
	
	NmppsFFTSpec spec;
	nmppsFFT32FwdInitAlloc(&spec,0);
	if (nmppsMallocFail())	return -2;

	nmppsSet_64s((nm64s*)src,0,FFT_SIZE);
	nmppsRandUniform_64s((nm64s*)dst,FFT_SIZE);
	src[0].re=100;
	src[1].re=100;
		
	//nmppsFFT32FwdRaw(src,dst,&spec);
	nmppsFFT32FwdRef2x16_f(src,dstRef); 
	nmppsFFT32FwdRef2x16  (src,dst);	msd=nmppsMSD_32sc(dst,dstRef,64);
	nmppsFFT32Fwd(src,dst,&spec);		msd=nmppsMSD_32sc(dst,dstRef,64);
	//nmppsFFT32FwdRawRef2x16(src,dst);
	
	nmppsFFT32Free(&spec);
	nmppsFree(src);
	nmppsFree(dst);
	nmppsFree(dstRef);
	printf("%8x %d\n",(int)nmppsMallocSpec.route[0], t1-t0);
	
}

int main()
{
	
	if (!selfTest())
		return -1;
	return speedTest();
	
}