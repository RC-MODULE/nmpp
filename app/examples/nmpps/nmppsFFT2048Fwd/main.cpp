#include "fft.h"
#include "nmpp.h"
#include <time.h>
#include <stdio.h>

#define FFT_SIZE 2048

//void nmppsFFT2048Fwd_RefFloat(const nm32sc* src, nm32sc* dst);

int speedTest(){

	clock_t t0,t1,dt,bestTime=0xFFFFF;
	unsigned int crc = 0;
	unsigned int bestRoute;
	//nmppsMallocSpec.route[0] = 0x23013;
	// 2   3   0   1   3
	//ar4 ar2 ar1 ar6 ar0
	nmppsMallocSetRouteMode();
	
	do
	{
		nmppsMallocResetPos();
		nm32sc* src   =(nm32sc*)nmppsMalloc_64s(FFT_SIZE);
		nm32sc* dst	  =src;//(nm32sc*)nmppsMalloc_64s(FFT_SIZE);
		
		NmppsFFTSpec* spec;
		nmppsFFT2048FwdInitAlloc(&spec,src,dst,SKIP_SINCOS);
		
		if (!nmppsMallocFail())	 {
			
			t0=clock();
			nmppsFFT2048Fwd         (src,dst,spec); // 36573   121231 best route
			t1=clock();
			dt =t1-t0;
			if (dt<bestTime){
				bestTime=dt;
				bestRoute=(int)nmppsMallocSpec.route[0];
			}
			nmppsMallocWipe();
			printf("%07x\t%d\t%d\n",(int)nmppsMallocSpec.route[0], dt, bestTime);
		}
		else 
			printf("%8x memory allocation error \n",(int)nmppsMallocSpec.route[0]);

	} while (nmppsMallocIncrementRoute()==0); 
	printf("Best time=%d; %d/2048/2=%f ; Best route = %07x \n",bestTime,bestTime,float(bestTime)/2048/2,bestRoute);
	return bestTime;
}

int selfTest(){
	clock_t t0,t1;
	unsigned int crc = 0;
	//nmppsMallocSpec.route[0] = 0x23013;
	nmppsMallocSetRouteMode();
	
	nmppsMallocResetPos();

	//nmppsMallocSetRoute16(0xf1032010);
	//nmppsMallocSetRoute16(0x0013122);
	//                      SC10-oi
	nmppsMallocSetRoute16(0x3112003);  
	nm32sc* src  =(nm32sc*)nmppsMalloc_64s(FFT_SIZE);
	nm32sc* dst	 =(nm32sc*)nmppsMalloc_64s(FFT_SIZE);
	//nm32sc* dstf =(nm32sc*)nmppsMalloc_64s(FFT_SIZE);
	//nm32sc* dstf2=(nm32sc*)nmppsMalloc_64s(FFT_SIZE);
		
		
	NmppsFFTSpec* spec;
	nmppsFFT2048FwdInitAlloc(&spec,src,dst,NMPP_CUSTOM_ALLOC);
		
	if (nmppsMallocFail())	return -2;
		
	nmppsRandUniform_64s((nm64s*)src,FFT_SIZE);
	nmppsRShiftC_32s((nm32s*)src,24,(nm32s*)src,2*FFT_SIZE);
	nmppsRandUniform_64s((nm64s*)dst,FFT_SIZE);
		
	float msd;
//	nmppsFFT2048Fwd_RefFloat(src,dstf);
//	nmppsFFT2048Fwd4888_RefFloat( src,  dstf2);msd=nmppsMSD_32sc(dstf,dstf2,2048);	printf("msd 1=%f\n",msd);
//	nmppsFFT2048Fwd4888_RefInt  ( src,  dstf2);	msd=nmppsMSD_32sc(dstf,dstf2,2048);	printf("msd 1=%f\n",msd);
	t0=clock();
	nmppsFFT2048Fwd         (src,dst,spec); 	;//	msd=nmppsMSD_32sc(dst,dstf2,2048);	printf("msd 1=%f\n",msd);
	t1=clock();
	//nmppsRShiftC_32s((nm32s*)dst,7,(nm32s*)dst,2048*2);
	
	
	crc=nmppsCrc_32s((nm32s*)dst,2048*2);
	
	nmppsMallocWipe();
	
	return t1-t0;
	return crc;//t1-t0;
	
}

#define pi 3.1415926535897932384626433832795
int main()
{	//return selfTest();
	return speedTest();
	
}
