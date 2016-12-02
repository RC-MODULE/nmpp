//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software                      */
//*                                                                         */
//*   Software design:  S.Mushkaev                                          */
//*                                                                         */
//*                                                                         */
//***************************************************************************/

#include "fft2.h"
#include "fftexp.h"
#include "nmpp.h"

static unsigned crc;
#define CRC32(addres,size) crc=nmppsCrc_32s((nm32s*)addres,size); 

extern "C"{

void nmppsFFT2048Fwd4888Raw(const nm32sc* src, nm32sc* dst, const NmppsFFTSpec* spec)
{
	int round[4];
	round[0]=1<<(spec->shift[0]-1);
	round[1]=1<<(spec->shift[1]-1);
	round[2]=1<<(spec->shift[2]-1);
	round[3]=1<<(spec->shift[3]-1);

	nm8s*   cosTbl;
	nm8s*   sinTbl;
	nm16s*  cosTbl16;
	nm16s*  sinTbl16;
	nm8s*   cosTblHold=(nm8s*)spec->fftTable[0];
	nm8s*   sinTblHold=(nm8s*)spec->fftTable[1];

	nm32sc* pX   =(nm32sc*)src;
	nm32sc* pHRe =(nm32sc*)spec->buffer[0];
	nm32sc* pHIm =(nm32sc*)spec->buffer[1];
	nm32sc* pH   =dst;

	nm32sc* pJRe =(nm32sc*)spec->buffer[0];
	nm32sc* pJIm =(nm32sc*)spec->buffer[1];
	nm32sc* pJRaw=dst;
	nm32sc* pJ   =(nm32sc*)spec->buffer[1];

	nm32sc* pIRe =spec->buffer[0];
	nm32sc* pIIm =dst;
	nm32sc* pIRaw=spec->buffer[1];
	nm32sc* pI   =spec->buffer[0];

	nm32sc* pYRe =dst;
	nm32sc* pYIm =spec->buffer[1];
	nm32sc* pYRaw=dst;
	//nm32sc* pY;

	int k,kk,j,i,n,h;	

	//---------------------------------- 0 -----------------------------------------
	for( i=511; i>=0; i--){
		load_wfifo(pX+i,512,4);
		cosTbl16=(nm16s*)cosTblHold;
		sinTbl16=(nm16s*)sinTblHold;
		for( kk=0; kk<4; kk++){
			vsum_data(cosTbl16,pHRe+512*kk+i,0);	cosTbl16+=4;
			vsum_data(sinTbl16,pHIm+512*kk+i,0);	sinTbl16+=4;
		}
	}
	cosTblHold=(nm8s*)cosTbl16;
	sinTblHold=(nm8s*)sinTbl16;
	
	
	//CRC32(pHRe,2048*2);
	//CRC32(pHIm,2048*2);

	//---------------------------------- 0.1 -----------------------------------------	
	for( i=0; i<2048; i++){
		pH[i].re=pHRe[i].re-pHIm[i].im;
		pH[i].im=pHRe[i].im+pHIm[i].re;
	}

	//CRC32(pH,2048*2);
	//---------------------------------- 1 -----------------------------------------
	for(int i=0; i<64; i++){
		cosTbl=cosTblHold;
		sinTbl=sinTblHold;
		for(int kk=0; kk<4; kk++){
			load_wfifo(pH+512*kk+i,64,8);	
			for(int k=0; k<8; k++){	
				vsum_data(cosTbl,pJRe+256*k+64*kk+i,round[1]);	cosTbl+=8;
				vsum_data(sinTbl,pJIm+256*k+64*kk+i,0);			sinTbl+=8;
			}
		}
	}
	cosTblHold=cosTbl;
	sinTblHold=sinTbl;
	//---------------------------------- 1.1 -----------------------------------------	
	for(int i=0;i<2048; i++){
		pJRaw[i].re=pJRe[i].re-pJIm[i].im;
		pJRaw[i].im=pJRe[i].im+pJIm[i].re;
	}
	//CRC32(pJRaw,2048*2);
	//---------------------------------- 1.2 -----------------------------------------
	for(int i=0; i<2048; i++){
		pJ[i].re=pJRaw[i].re>>spec->shift[1];
		pJ[i].im=pJRaw[i].im>>spec->shift[1];
	}
	//CRC32(pJ,2048*2);
	//---------------------------------- 2 -----------------------------------------
	for(int i=0; i<8; i++){
		cosTbl=cosTblHold;
		sinTbl=sinTblHold;
		for(int kk=0; kk<32; kk++){
			load_wfifo(pJ+64*kk+i,8,8);			
			for(int k=0; k<8; k++){		
				vsum_data(cosTbl,pIRe+256*k+8*kk+i,round[2]);	cosTbl+=8;
				vsum_data(sinTbl,pIIm+256*k+8*kk+i,0);			sinTbl+=8;
			}
		}
	}
	//CRC32(pIRe,2048*2);
	//CRC32(pIIm,2048*2);
	//---------------------------------- 2.1 -----------------------------------------
	for(int i=0; i<2048; i++){
		pIRaw[i].re=pIRe[i].re-pIIm[i].im;
		pIRaw[i].im=pIRe[i].im+pIIm[i].re;
	}
	//CRC32(pIRaw,2048*2);
	//---------------------------------- 2.2 -----------------------------------------
	for(int i=0; i<2048; i++){
		pI[i].re=pIRaw[i].re>>spec->shift[2];
		pI[i].im=pIRaw[i].im>>spec->shift[2];
	}
	//CRC32(pI,2048*2);
	//---------------------------------- 3 -----------------------------------------
	for(int kk=0; kk<256; kk++){
		load_wfifo(pI+8*kk,1,8);								
		for(int k=0; k<8; k++){
			vsum_data(cosTbl,pYRe+256*k+kk,round[3]);	cosTbl+=8;						
			vsum_data(sinTbl,pYIm+256*k+kk,0);			sinTbl+=8;						
		}
	}
	//---------------------------------- 3.1 -----------------------------------------
	for(int i=0; i<2048; i++){
		pYRaw[i].re=pYRe[i].re-pYIm[i].im;	
		pYRaw[i].im=pYRe[i].im+pYIm[i].re;
	}

	//CRC32((nm32s*)pYRe,2048*2);
	//CRC32((nm32s*)pYIm,2048*2);

	//---------------------------------- 3.2 -----------------------------------------
	//for(int i=0; i<2048; i++){
	//	pY[i].re=pYRaw[i].re>>spec->shift[3];
	//	pY[i].im=pYRaw[i].im>>spec->shift[3];
	//}
	//return 0;
}

void nmppsFFT2048Fwd4888(const nm32sc* src, nm32sc* dst, const NmppsFFTSpec* spec)
{
	nmppsFFT2048Fwd4888Raw(src, dst, spec);

	//---------------------------------- 3.2 -----------------------------------------
	for(int i=0; i<2048; i++){
		dst[i].re=dst[i].re>>spec->shift[3];
		dst[i].im=dst[i].im>>spec->shift[3];
	}
	//return 0;
}



void nmppsFFT2048FwdRaw(const nm32sc* src, nm32sc* dst, const NmppsFFTSpec* spec)
{
	nmppsFFT2048Fwd4888Raw(src, dst, spec);
}

void nmppsFFT2048Fwd(const nm32sc* src, nm32sc* dst, const NmppsFFTSpec* spec)
{
	nmppsFFT2048Fwd4888(src, dst, spec);
}


};