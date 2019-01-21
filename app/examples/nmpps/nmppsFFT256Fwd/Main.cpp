#include "nmpp.h"
//#include "fft.h"
#include "fft.h"
#include "stdio.h"
#include <time.h>

#define FFT_SIZE 256 

int speedTest(){
	clock_t t0,t1,bestTime=0xFFFFF;
	unsigned int crc = 0;
	//nmppsMallocSpec.route[0] = 0x23013;
	nmppsMallocSpec.route[0] = 0x0;
	// 2   3   0   1   3
	//ar4 ar2 ar1 ar6 ar0
	nmppsMallocSetRouteMode();
	
	int routing=true;
	while (routing)
	{
		nmppsMallocResetPos();
		nm32sc* src   =(nm32sc*)nmppsMalloc_64s(FFT_SIZE);
		nm32sc* dst	  =(nm32sc*)nmppsMalloc_64s(FFT_SIZE);
		NmppsFFTSpec* spec;
		nmppsFFT256FwdInitAlloc(&spec,src,dst,-1);
		
		printf("%8x %d\n",(int)nmppsMallocSpec.route[0], t1-t0);
		if (nmppsMallocIncrementRoute())
			routing=false;
		
		if (nmppsMallocFail()) {
			if (src) nmppsFree(src);
			if (dst) nmppsFree(dst);
			nmppsFFTFree(spec);
			continue;
		};

		
		nmppsSet_64s((nm64s*)src,0,FFT_SIZE);
		nmppsRandUniform_64s((nm64s*)dst,FFT_SIZE);
		src[0].re=100;
		src[1].re=100;
		
		t0=clock();
		nmppsFFT256Fwd(src,dst,spec);

		t1=clock();
		if (t1-t0<bestTime)
			bestTime=t1-t0;
		nmppsFFTFree(spec);
		nmppsFree(src);
		nmppsFree(dst);
	}
	
	return bestTime;
}

extern "C"{
void FFT_Fwd256_2x8x16(void* src,void* dst,void * a, void*b , void*  ,void *d );

};

int main()
{
//	return speedTest();
	clock_t t0,t1,bestTime=0x1000000;
	
	t0=clock();


	//FFT_Fwd256Set7bit();

	
	//nm32sc* src =(nm32sc*)nmppsMalloc_64s(256);
	//nm32sc* dst =(nm32sc*)nmppsMalloc_64s(256);
	
	//nmppsRandUniform_32s((nm32s*)src,256*2);
	//nmppsRShiftC_32u((nm32u*)src,24, (nm32u*)src, 256*2);
	
	NmppsFFTSpec* specFFT256Fwd;
	//fseq64 route=0xF3210;
	fseq64 route=0xF3210;
	
	nmppsMallocSpec.route[0] = 0x0;
	// 2   3   0   1   3
	//ar4 ar2 ar1 ar6 ar0
	nmppsMallocSetRouteMode();
	//nmppsFFT256FwdOptimize(src,dst,&route);
	//return route;
	//nmppsMallocSetShortRoute(route);
	//nmppsMallocSetRoute16(route);
	//nmppsFFT256FwdInitAlloc(&specFFT256Fwd,src,dst,0);
	t0=clock();
	//int bestTime=0xFFFFF;
	//nmppsFFT256Fwd(src,dst,specFFT256Fwd);
	int routing=true;
	while (routing){
		nmppsMallocResetPos();
	void* src = (nm32sc*)nmppsMalloc_64s(256);
	void* dst = (nm32sc*)nmppsMalloc_64s(256);
	void * a = (nm32sc*)nmppsMalloc_64s(256);
	void*b  = (nm32sc*)nmppsMalloc_64s(256);
	void* c = (nm32sc*)nmppsMalloc_64s(256+128);
	void* d = (nm32sc*)nmppsMalloc_64s(256);
	
	if (nmppsMallocIncrementRoute())
			routing=false;
	if (nmppsMallocFail()){
		printf(".");
		nmppsMallocWipe();
		continue;
	}
	//FFT_Fwd256_2x8x16(src,dst,specFFT256Fwd->buffer[0],specFFT256Fwd->buffer[0],specFFT256Fwd->buffer[1],specFFT256Fwd->buffer[0]);
	t0=clock();
	FFT_Fwd256_2x8x16(src,dst,a,b,c,d);
/*	
	ar0=[--ar5];						// GSrcBuffer[256*2]
	ar1=[--ar5];						// GDstBuffer[256*2]
	ar2=[--ar5];						// W0 GSrcBuffer[256*2]
	ar3=[--ar5];						// W1 GDstBuffer[256*2]
	ar4=[--ar5];						// Tmp0 LBuffer[256*3]
	ar5=[--ar5];						// Tmp1 GBuffer[256*2]
*/
	t1=clock();
	//printf("%d \n",t1-t0);
	printf("new = %8x %d\n",(int)nmppsMallocSpec.route[0], t1-t0);
	
		if (t1-t0<bestTime)
			bestTime=t1-t0;
	}
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
	//unsigned crc = nmppsCrc_32s((nm32s*)dst,256*2)>>2;
	//nmppsFree(src);
	//nmppsFree(dst);
	//nmppsFFTFree(specFFT256Fwd);
	//return crc;
	return bestTime;
}
// 3856
