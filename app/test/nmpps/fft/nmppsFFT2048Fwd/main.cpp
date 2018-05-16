#include "fft.h"
#include "nmpp.h"
#include "minrep.h"
#include <time.h>
#include <stdio.h>

#define FFT_SIZE 2048

int selfTest(){
	//clock_t t0,t1;
	//--------------- nmppsFFT2048FwdInitAlloc test ------------
	unsigned int crc = 0;
	nmppsMallocSetRoute16(0x3112003);  
	nm32sc* src  =(nm32sc*)nmppsMalloc_64s(FFT_SIZE);	// alloc in heap(3)
	nm32sc* dst	 =(nm32sc*)nmppsMalloc_64s(FFT_SIZE);	// alloc in heap(0)
		
	NmppsFFTSpec* spec;
	nmppsFFT2048FwdInitAlloc(&spec,src,dst,NMPP_CUSTOM_ALLOC);	// alloc in heaps: 0,2,1,1,3
		
	if (nmppsMallocFail())	return -2;
		
	nmppsRandUniform_64s((nm64s*)src,FFT_SIZE);
	nmppsRShiftC_32s((nm32s*)src,24,(nm32s*)src,2*FFT_SIZE);
	nmppsRandUniform_64s((nm64s*)dst,FFT_SIZE);
		
	nmppsFFT2048Fwd     ( src, dst, spec); 	nmppsCrcAcc_32s((nm32s*)dst,2048*2,&crc);
	nmppsFFT2048FwdRaw  ( src, dst, spec); 	nmppsCrcAcc_32s((nm32s*)dst,2048*2,&crc);
	nmppsFFTFree(spec);
	
	//--------------- nmppsFFT2048FwdInit test ------------
	nm64s* buffer0= nmppsMalloc_64s(FFT2048_TBL0_SIZE64);
	nm64s* buffer1= nmppsMalloc_64s(FFT2048_TBL1_SIZE64);
	nm64s* buffer2= nmppsMalloc_64s(FFT2048_TBL2_SIZE64);
	nm64s* buffer3= nmppsMalloc_64s(FFT2048_TBL3_SIZE64);
	
	if (nmppsMallocFail())	return -3;
	NmppsFFTSpec staticSpec;
	nmppsFFT2048FwdInit(&staticSpec, buffer0, buffer1, buffer2, buffer3,0);	
		
	nmppsFFT2048Fwd     ( src, dst, &staticSpec); 	nmppsCrcAcc_32s((nm32s*)dst,2048*2,&crc);
	nmppsFFT2048FwdRaw  ( src, dst, &staticSpec); 	nmppsCrcAcc_32s((nm32s*)dst,2048*2,&crc);
	
	nmppsFree(buffer0);
	nmppsFree(buffer1);
	nmppsFree(buffer2);
	nmppsFree(buffer3);
	
	nmppsFree(src);
	nmppsFree(dst);
	
	return crc>>2;
	
}

int main()
{
 	return selfTest();
}

//nmppsMallocSpec.route[0] = 0x23013;
	//nmppsMallocSetRouteMode();
	
	//nmppsMallocResetPos();

	//nmppsMallocSetRoute16(0xf1032010);
	//nmppsMallocSetRoute16(0x0013122);
	//                      SC10-oi
	
//float msd;
	//nmppsFFT2048Fwd_RefFloat    ( src, dst); crc=nmppsCrc_32s((nm32s*)dst,2048*2);
	//nmppsFFT2048Fwd4888_RefFloat( src, dst); nmppsCrcAcc_32s((nm32s*)dst,2048*2,&crc);
	//nmppsFFT2048Fwd4888_RefInt  ( src, dst); nmppsCrcAcc_32s((nm32s*)dst,2048*2,&crc); 
	//nmppsFFT2048FwdRaw	( src, dst, spec); 	nmppsCrcAcc_32s((nm32s*)dst,2048*2,&crc);
	//nmppsMallocWipe();
	