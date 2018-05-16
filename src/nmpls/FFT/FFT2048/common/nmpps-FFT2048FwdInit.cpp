#include "fft.h"
#include <math.h>
#include "fftexp.h"
#include "nmpp.h"

#ifndef PI
#define PI 3.14159265359
#endif
/*
cmplx<int > Y;
X.re*=Ampl;
X.im*=Ampl;
Y.re=floor(X.re+0.5);	
Y.im=floor(X.im+0.5);
if (Ampl>127){
	Y.re= Y.re > 127 ? 127:Y.re;
	Y.im= Y.im > 127 ? 127:Y.im;	
}
return Y;
*/
/*
nm32sc toFixW2048(int arg, int max){
	nm32sc res;
	double argIm= -2.0*PI/2048.0*arg;
	double expRe= cos(argIm)*max+0.5;
	double expIm= sin(argIm)*max+0.5;
	res.re= expRe;
	res.im= expIm;
	return res;
}
*/	

//int nmppsFFT2048FwdInitAlloc4888(  NmppsFFTSpec* spec, src int settings)



void nmppsFFT2048FwdInitSinCos4888(NmppsFFTSpec* spec)
{
	nm16s* cosTbl16=(nm16s*)spec->fftTable[0];
	nm16s* sinTbl16=(nm16s*)spec->fftTable[1];
	nm32sc z;
	int ii,k,kk,j,i,n,h;	
	
	//---------------------------------- 0 -----------------------------------------
	for( kk=0,ii=0; kk<4; kk++){
		for( n=0; n<4; n++,ii++){
			expFFT<2048>(512*n*kk,1,&z);
			nmppsPut_16s(cosTbl16,ii,z.re);
			nmppsPut_16s(sinTbl16,ii,z.im);
		}
	}

	//---------------------------------- 1 -----------------------------------------
	nm8s* cosTbl=(nm8s*)nmppsAddr_16s(cosTbl16,ii);
	nm8s* sinTbl=(nm8s*)nmppsAddr_16s(sinTbl16,ii);

	for(ii=0,kk=0; kk<4; kk++){
		for( k=0; k<8; k++){	
			for( h=0; h<8; h++,ii++){
				expFFT127<2048>(64*h*(4*k+kk),spec->amp[1],&z);
				nmppsPut_8s(cosTbl,ii,z.re);
				nmppsPut_8s(sinTbl,ii,z.im);
			}
		}
	}

	//---------------------------------- 2 -----------------------------------------

	for( kk=0; kk<32; kk++){
		for( k=0; k<8; k++){		
			for( j=0; j<8; j++,ii++){
				expFFT127<2048>(8*j*(32*k+kk),spec->amp[2],&z);
				nmppsPut_8s(cosTbl,ii,z.re);
				nmppsPut_8s(sinTbl,ii,z.im);
			}
		}
	}

	//---------------------------------- 3 -----------------------------------------

	for( kk=0; kk<256; kk++){
		for( k=0; k<8; k++){
			for( i=0; i<8; i++,ii++){
				expFFT127<2048>((256*k+kk)*i,spec->amp[3],&z);
				nmppsPut_8s(cosTbl,ii,z.re);
				nmppsPut_8s(sinTbl,ii,z.im);
			}
		}
	}
}

void nmppsFFT2048FwdInit (NmppsFFTSpec* spec, void* datbuf0, void* datbuf1, void* tblbuf0, void* tblbuf1, int settings )
{
	nmppsFFTResetSpec(spec);
	spec->buffer[0]  =(nm32sc*)datbuf0; //nmppsMalloc_32sc(2048);
	spec->buffer[1]  =(nm32sc*)datbuf1; //nmppsMalloc_32sc(2048);
	spec->fftTable[0]=(nm8s*)tblbuf0; //nmppsMalloc_8s(4*4*2+4*8*8+32*8*8+256*8*8);	// Bytes
	spec->fftTable[1]=(nm8s*)tblbuf1; //nmppsMalloc_8s(4*4*2+4*8*8+32*8*8+256*8*8);	// Bytes
	
	spec->shift[0]=0;
	spec->shift[1]=7;
	spec->shift[2]=7;
	spec->shift[3]=7;
	
	spec->amp[0]=1;
	spec->amp[1]=128;
	spec->amp[2]=128;
	spec->amp[3]=128;

	if (!(settings&SKIP_SINCOS)){
		nmppsFFT2048FwdInitSinCos4888(spec);
	}	

	
}



//#define NMPP_OPTIMIZE_ALLOC 1
//#define NMPP_CUSTOM_ALLOC 2
//#define SKIP_SINCOS 4


int  nmppsFFT2048FwdInitAlloc4888( NmppsFFTSpec** specFFT, const void* src, const void* dst,  int settings)
{
	if (settings&NMPP_OPTIMIZE_ALLOC){
		nmppsMallocResetRoute();
		do {
			NmppsFFTSpec* spec;
			if (nmppsFFT2048FwdInitAlloc4888(&spec, src,dst, NMPP_CUSTOM_ALLOC|SKIP_SINCOS)==NMPP_OK){
				nmppsMallocTimerStart();
				nmppsFFT2048Fwd4888((nm32sc*)src, (nm32sc*)dst, spec);
				nmppsMallocTimerStop();
				nmppsMallocBetterRoute();
				nmppsFFTFree(spec);
			} 
		}			
		while (nmppsMallocIncrementRoute()==0);
		nmppsMallocSetBestRoute(1);
	}

	//if (settings==NMPP_CUSTOM_ALLOC){

	
	NmppsFFTSpec* spec=(NmppsFFTSpec*)nmppsMalloc_32s(sizeof32(NmppsFFTSpec));
	*specFFT=spec;
	if (spec==0) {
		return -1;
	}
	
	nmppsFFTResetSpec(spec);
	spec->buffer[0]  =nmppsMalloc_32sc(2048);
	spec->buffer[1]  =nmppsMalloc_32sc(2048);
	spec->fftTable[0]=nmppsMalloc_8s(4*4*2+4*8*8+32*8*8+256*8*8);	// Bytes
	spec->fftTable[1]=nmppsMalloc_8s(4*4*2+4*8*8+32*8*8+256*8*8);	// Bytes
	//spec->fftTable[2]=0;
	//spec->fftTable[3]=0;
	
	spec->shift[0]=0;
	spec->shift[1]=7;
	spec->shift[2]=7;
	spec->shift[3]=7;
	
	spec->amp[0]=1;
	spec->amp[1]=128;
	spec->amp[2]=128;
	spec->amp[3]=128;


	spec->free=free;
	if ((spec->fftTable[0]==0)||(spec->fftTable[1]==0)||(spec->buffer[0]==0)||(spec->buffer[1]==0)){
		nmppsFFTFree(spec);
		spec=0;
		return -1;
	}
	
	//if (settings==-1)
	//	return 0;
	if (!(settings&SKIP_SINCOS)){
		nmppsFFT2048FwdInitSinCos4888(spec);
	}	

	
	return NMPP_OK;
}

int  nmppsFFT2048FwdInitAlloc( NmppsFFTSpec** specFFT, const void* src, const void* dst,  int settings)
{
	return  nmppsFFT2048FwdInitAlloc4888( specFFT, src, dst, settings);
}

