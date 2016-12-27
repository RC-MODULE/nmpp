#include "fft2.h"
#include "nmpp.h"
#include "minrep.h"
#include <time.h>
#include <stdio.h>

#define FFT_SIZE 8192

#pragma data_section ".data_bank0"
	
	nm64s  tblFwdSin0[FFT8192_TBL0_SIZE64];
	nm64s  buffer1 [1];
#pragma data_section ".data_bank1"
	nm64s  buffer0   [FFT_SIZE];
	nm64s  tblFwdCos1[FFT8192_TBL1_SIZE64];
	
#pragma data_section ".data_bank2"
	nm64s  buffer2   [FFT_SIZE];
	nm64s  tblFwdCos0[FFT8192_TBL0_SIZE64];
#pragma data_section ".data_bank3"
	nm64s  buffer3   [FFT_SIZE];
	nm64s  tblFwdSin1[FFT8192_TBL1_SIZE64];
		


#pragma data_section ".data_bank0"	
	
	


int selfTest(){
	unsigned int crc = 0;
	NmppsFFTSpec specFwd;
	nmppsFFT8192FwdInit(&specFwd,0,buffer2,buffer3,tblFwdCos0,tblFwdCos1,tblFwdSin0,tblFwdSin1);
	nm32sc* src = (nm32sc*)buffer0;	
	nm32sc* dst = src;	
		
	nmppsRandUniform_64s((nm64s*)src,FFT_SIZE);
	
	nmppsRShiftC_32s((nm32s*)src,24,(nm32s*)src,2*FFT_SIZE);
		
	nmppsFFT8192Fwd 	(src,dst,&specFwd); 	crc=nmppsCrc_32s((nm32s*)src,8192*2);
	nmppsFFT8192FwdRaw 	(src,dst,&specFwd); 	crc=nmppsCrc_32s((nm32s*)src,8192*2);
	
	
	return crc>>2;
}

int main()
{
	return selfTest();

}
	