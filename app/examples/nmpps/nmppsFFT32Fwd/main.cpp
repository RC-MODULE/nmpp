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
		nmppsFFT32FwdInitAlloc(&spec,-1);
		
		if (nmppsMallocFail()) return -2;
		
		nmppsSet_64s((nm64s*)src,0,FFT_SIZE);
		nmppsRandUniform_64s((nm64s*)dst,FFT_SIZE);
		src[0].re=100;
		src[1].re=100;
		
		t0=clock();
		nmppsFFT32Fwd(src,dst,&spec);
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
	nm32sc* dstRef_f=(nm32sc*)nmppsMalloc_64s(FFT_SIZE);
	nm32sc* dst   =(nm32sc*)nmppsMalloc_64s(FFT_SIZE);
	
	NmppsFFTSpec spec;
	nmppsFFT32FwdInitAlloc(&spec,0);
	if (nmppsMallocFail())	return -2;

	nmppsSet_64s((nm64s*)src,0,FFT_SIZE);
	nmppsRandUniform_64s((nm64s*)dst,FFT_SIZE);
	//nmppsRandUniform_64s((nm64s*)src,FFT_SIZE);
	//nmppsRShiftC_32s((nm32s*)src,16,(nm32s*)src,FFT_SIZE*2); 
	src[0].re=100;
	src[1].re=200;
	src[2].re=300;
	src[3].re=400;
	
	nmppsFFT32FwdRef2x16_f(src,dstRef_f); 
	nmppsFFT32FwdRef2x16  (src,dstRef);	msd=nmppsMSD_32sc(dstRef_f,dstRef,32); 	printf("msd[ref_f:ref] =%f\n",msd);
	nmppsFFT32Fwd(src,dst,&spec);		msd=nmppsMSD_32sc(dstRef_f,dst,32); 	printf("msd[ref_f:fwd] =%f\n",msd);
		                                                                      
	nmppsFFT32FwdRaw(src,dst,&spec);									
	nmppsAddC_32s((nm32s*)dst,spec.round[0],(nm32s*)dst,FFT_SIZE*2); 	
	nmppsRShiftC_32s((nm32s*)dst,spec.shift[0],(nm32s*)dst,FFT_SIZE*2); 
	msd=nmppsMSD_32sc(dst,dstRef,32);											printf("msd[raw:fwd]   =%f\n",msd);
	
	
	nmppsFFT32Free(&spec);
	nmppsFree(src);
	nmppsFree(dst);
	nmppsFree(dstRef);
	nmppsFree(dstRef_f);
}

int main()
{
	
	if (!selfTest())
		return -1;
	return speedTest();
	
}