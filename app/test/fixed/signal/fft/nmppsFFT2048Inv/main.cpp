#include "fft.h"
#include "nmpp.h"
#include "minrep.h"
#include <time.h>
#include <stdio.h>

#define FFT_SIZE 2048

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
	nmppsFFT2048InvInitAlloc(&spec,src,dst,NMPP_CUSTOM_ALLOC);
		
	if (nmppsMallocFail())	return -2;
		
	nmppsRandUniform_64s((nm64s*)src,FFT_SIZE);
	nmppsRShiftC_32s((nm32s*)src,24,(nm32s*)src,2*FFT_SIZE);
	nmppsRandUniform_64s((nm64s*)dst,FFT_SIZE);
		
	//float msd;
	//nmppsFFT2048Fwd_RefFloat    ( src, dst); crc=nmppsCrc_32s((nm32s*)dst,2048*2);
	//nmppsFFT2048Fwd4888_RefFloat( src, dst); nmppsCrcAcc_32s((nm32s*)dst,2048*2,&crc);
	//nmppsFFT2048Fwd4888_RefInt  ( src, dst); nmppsCrcAcc_32s((nm32s*)dst,2048*2,&crc); 
	crc=0;
	
	nmppsFFT2048Inv     ( src, dst, spec); 	nmppsCrcAcc_32s((nm32s*)dst,2048*2,&crc);
	nmppsFFT2048InvRaw  ( src, dst, spec); 	nmppsCrcAcc_32s((nm32s*)dst,2048*2,&crc);
	//nmppsFFT2048FwdRaw	( src, dst, spec); 	nmppsCrcAcc_32s((nm32s*)dst,2048*2,&crc);
	//nmppsMallocWipe();
	nmppsFFTFree(spec);
	nmppsFree(src);
	nmppsFree(dst);
	
	return crc>>2;
	
}

int main()
{
 	return selfTest();
}
