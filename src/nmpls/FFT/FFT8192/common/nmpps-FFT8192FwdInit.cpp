#include "fft2.h"
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
nm32sc toFixW8192(int arg, int max){
	nm32sc res;
	double argIm= -2.0*PI/8192.0*arg;
	double expRe= cos(argIm)*max+0.5;
	double expIm= sin(argIm)*max+0.5;
	res.re= expRe;
	res.im= expIm;
	return res;
}
*/	

//int nmppsFFT8192FwdInitAlloc4x8x8x8(  NmppsFFTSpec* spec, src int settings)



void nmppsFFT8192Fwd28888InitSinCos(NmppsFFTSpec* spec)
{
	nm32sc z;
	int ii=0,k,kk,j,i,n,h;	
	
	//---------------------------------- 1 -----------------------------------------
	nm8s* cosTbl=(nm8s*)spec->fftTable[0];
	nm8s* sinTbl=(nm8s*)spec->fftTable[1];

	//for(ii=0,kk=0; kk<4; kk++){
	//	for( k=0; k<8; k++){	
	//		for( h=0; h<8; h++,ii++){
	//			expFFT127<8192>(64*h*(4*k+kk),spec->amp[1],&z);
	//			nmppsPut_8s(cosTbl,ii,z.re);
	//			nmppsPut_8s(sinTbl,ii,z.im);
	//		}
	//	}
	//}
	for(int k2=0; k2<2; k2++){
		for(int k1=0; k1<8; k1++){	
			int k=k1*2+k2;
			for(int g=0; g<8; g++,ii++){
				expFFT127<8192>(512*g*k,spec->amp[1],&z);
				nmppsPut_8s(cosTbl,ii,z.re);
				nmppsPut_8s(sinTbl,ii,z.im);
			}
		}
	}


	//---------------------------------- 2 -----------------------------------------

	for (int k2=0; k2<16;k2++){
		for (int k1=0; k1<8;k1++){
			int k=16*k1+k2;
			for(int h=0; h<8; h++,ii++){
				expFFT127<8192>(64*h*k,spec->amp[2],&z);
				nmppsPut_8s(cosTbl,ii,z.re);
				nmppsPut_8s(sinTbl,ii,z.im);
			}
		}
	}
	//---------------------------------- 3 -----------------------------------------
	for (int k2=0; k2<128; k2++){
		for (int k1=0; k1<8; k1++){
			int k=128*k1+k2; //for(int k=0; k<1024; k++){
			for(int j=0; j<8; j++,ii++){
				expFFT127<8192>(8*j*k,spec->amp[3],&z);
				nmppsPut_8s(cosTbl,ii,z.re);
				nmppsPut_8s(sinTbl,ii,z.im);
			}
		}
	}
	//---------------------------------- 4 -----------------------------------------
	for (int k2=0; k2<1024; k2++){
		for (int k1=0; k1<8; k1++){
			int k=1024*k1+k2;
			for(int i=0; i<8; i++,ii++){
				expFFT127<8192>(i*k,spec->amp[4],&z);
				nmppsPut_8s(cosTbl,ii,z.re);
				nmppsPut_8s(sinTbl,ii,z.im);
			}
		}
	}

	/*
		for (int k2=0; k2<1024; k2++){
			for (int k1=0; k1<8; k1++){
				int k=1024*k1+k2; 
				for(int i=0; i<8; i++,ii++){
					expFFT127<8192>(i*k,spec->amp[4]);
					nmppsPut_8s(cosTbl,ii,z.re);
					nmppsPut_8s(sinTbl,ii,z.im);
			}
		}
	}
*/
}

//#define NMPP_OPTIMIZE_ALLOC 1
//#define NMPP_CUSTOM_ALLOC 2
//#define SKIP_SINCOS 4
int  nmppsFFT8192Fwd28888InitAlloc( NmppsFFTSpec** specFFT, const void* src, const void* dst,  int settings)
{
	if (settings&NMPP_OPTIMIZE_ALLOC){
		nmppsMallocResetRoute();
		do {
			NmppsFFTSpec* spec;
			if (nmppsFFT8192Fwd28888InitAlloc(&spec, src,dst, NMPP_CUSTOM_ALLOC|SKIP_SINCOS)==NMPP_OK){
				nmppsMallocTimerStart();
				nmppsFFT8192Fwd28888((nm32sc*)src, (nm32sc*)dst, spec);
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
	

	spec->buffer[0]  =nmppsMalloc_32sc(8192);
	spec->buffer[1]  =nmppsMalloc_32sc(8192);
	spec->fftTable[0]=nmppsMalloc_8s(2*8*8+16*8*8+128*8*8+8*1024*8);	// Bytes
	spec->fftTable[1]=nmppsMalloc_8s(2*8*8+16*8*8+128*8*8+8*1024*8);	// Bytes
	spec->fftTable[2]=0;
	spec->fftTable[3]=0;
	
	spec->shift[0]=0;
	spec->shift[1]=7;
	spec->shift[2]=7;
	spec->shift[3]=7;
	spec->shift[4]=7;
	
	spec->amp[0]=1<<spec->shift[0];
	spec->amp[1]=1<<spec->shift[1];
	spec->amp[2]=1<<spec->shift[2];
	spec->amp[3]=1<<spec->shift[3];
	spec->amp[4]=1<<spec->shift[4];

	spec->round[0]=1<<(spec->shift[0]-1);
	spec->round[1]=1<<(spec->shift[1]-1);
	spec->round[2]=1<<(spec->shift[2]-1);
	spec->round[3]=1<<(spec->shift[3]-1);
	spec->round[4]=1<<(spec->shift[3]-1);


	spec->free=free;
	if (spec->fftTable[0]==0) 	return -1;
	if (spec->fftTable[1]==0) 	return -1;
	if (spec->buffer[0]==0) 	return -1;
	if (spec->buffer[1]==0) 	return -1;
	
	//if (settings==-1)
	//	return 0;
	if (!(settings&SKIP_SINCOS)){
		nmppsFFT8192Fwd28888InitSinCos(spec);
	}	

	
	return NMPP_OK;
}

