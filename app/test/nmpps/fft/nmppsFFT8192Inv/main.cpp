#include "fft2.h"
#include "nmpp.h"
#include <time.h>
#include <stdio.h>

#define FFT_SIZE 8192

//#define SPEEDTEST ON


#pragma data_section ".data_bank0"
	nm64s  tblFwdCos1[FFT8192_TBL1_SIZE64];
	nm64s  tblFwdSin0[FFT8192_TBL0_SIZE64];
	nm64s  tblInvSin0[FFT8192_TBL0_SIZE64];
	nm64s  buffer1   [1];
#pragma data_section ".data_bank1"
	nm64s  buffer0   [FFT_SIZE];
	nm64s  tblInvSin1[FFT8192_TBL1_SIZE64];
#pragma data_section ".data_bank2"
	nm64s  buffer2   [FFT_SIZE];
	nm64s  tblFwdCos0[FFT8192_TBL0_SIZE64];
#pragma data_section ".data_bank3"
	nm64s  buffer3   [FFT_SIZE];
	nm64s  tblFwdSin1[FFT8192_TBL1_SIZE64];
		

	

int selfTest(){
	unsigned int crc = 0;
		
	NmppsFFTSpec specInv;
	nmppsFFT8192InvInit(&specInv,0,buffer2,buffer3,tblFwdCos0,tblFwdCos1,tblInvSin0,tblInvSin1);
	
	nm32sc* src = (nm32sc*)buffer0;	
	nm32sc* dst = src;	
		
	nmppsRandUniform_64s((nm64s*)src,FFT_SIZE);
	nmppsRShiftC_32s((nm32s*)src,24,(nm32s*)src,2*FFT_SIZE);
		
	nmppsFFT8192Inv (src,dst,&specInv); 	
	
	crc=nmppsCrc_32s((nm32s*)src,8192*2);// -0x18e578a4;
	
	return crc;
	
}


int main()
{
	return selfTest();
}

