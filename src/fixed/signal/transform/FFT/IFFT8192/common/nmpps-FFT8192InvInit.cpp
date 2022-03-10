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

//int nmppsFFT8192InvInitAlloc4x8x8x8(  NmppsFFTSpec* spec, src int settings)

extern "C" {



int nmppsFFT8192Inv28888InitSinCos(NmppsFFTSpec* spec, int settings)
{
	nm32sc z;
	int ii=0,k,kk,j,i,n,h;	
	
	//---------------------------------- 1 -----------------------------------------
	nm8s* cosTbl=(nm8s*)spec->fftTable[0];
	nm8s* sinTbl=(nm8s*)spec->fftTable[2];

	//for(ii=0,kk=0; kk<4; kk++){
	//	for( k=0; k<8; k++){	
	//		for( h=0; h<8; h++,ii++){
	//			expIFFT127<8192>(64*h*(4*k+kk),spec->amp[1],&z);
	//			nmppsPut_8s(cosTbl,ii,z.re);
	//			nmppsPut_8s(sinTbl,ii,z.im);
	//		}
	//	}
	//}
	for(int k2=0; k2<2; k2++){
		for(int k1=0; k1<8; k1++){	
			int k=k1*2+k2;
			for(int g=0; g<8; g++,ii++){
				expIFFT127<8192>(512*g*k,spec->amp[1],&z);
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
				expIFFT127<8192>(64*h*k,spec->amp[2],&z);
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
				expIFFT127<8192>(8*j*k,spec->amp[3],&z);
				nmppsPut_8s(cosTbl,ii,z.re);
				nmppsPut_8s(sinTbl,ii,z.im);
			}
		}
	}
	//---------------------------------- 4 -----------------------------------------
	cosTbl=(nm8s*)spec->fftTable[1];
	sinTbl=(nm8s*)spec->fftTable[3];
	ii=0;

	for (int k2=0; k2<1024; k2++){
		for (int k1=0; k1<8; k1++){
			int k=1024*k1+k2;
			for(int i=0; i<8; i++,ii++){
				expIFFT127<8192>(i*k,spec->amp[4],&z);
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
					expIFFT127<8192>(i*k,spec->amp[4]);
					nmppsPut_8s(cosTbl,ii,z.re);
					nmppsPut_8s(sinTbl,ii,z.im);
			}
		}
	}
*/
	return 1;
}

//#define NMPP_OPTIMIZE_ALLOC 1
//#define NMPP_CUSTOM_ALLOC 2
//#define SKIP_SINCOS 4

int  nmppsFFT8192Inv28888Init( NmppsFFTSpec* spec,  int settings, nm64s *buf0, nm64s* buf1, nm64s* tbl0, nm64s* tbl1, nm64s* tbl2, nm64s* tbl3)
{
	spec->buffer[0]  =(nm32sc*)buf0; // [8192]nm32s;
	spec->buffer[1]  =(nm32sc*)buf1; // [8192]nm32s;

	spec->fftTable[0]=tbl0;	// [ 9344]Bytes 
	spec->fftTable[1]=tbl1;	// [65536]Bytes (64kB)
	spec->fftTable[2]=tbl2;	// [ 9344]Bytes 
	spec->fftTable[3]=tbl3;	// [65536]Bytes (64kB)
	
	if (spec->fftTable[0]==0) 	return -1;
	if (spec->fftTable[1]==0) 	return -1;
	if (spec->fftTable[2]==0) 	return -1;
	if (spec->fftTable[3]==0) 	return -1;
	if (spec->buffer[0]==0) 	return -1;
	if (spec->buffer[1]==0) 	return -1;

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

	spec->shift[4]+=13;


	if (!(settings&SKIP_SINCOS)){
		nmppsFFT8192Inv28888InitSinCos(spec,settings);
	}	

	

	return NMPP_OK;
}



int  nmppsFFT8192Inv28888InitAlloc( NmppsFFTSpec** specFFT, const void* src, const void* dst,  int settings)
{
	if (settings&NMPP_OPTIMIZE_ALLOC){
		nmppsMallocResetRoute();
		do {
			NmppsFFTSpec* spec;
			if (nmppsFFT8192Inv28888InitAlloc(&spec, src,dst, NMPP_CUSTOM_ALLOC|SKIP_SINCOS)==NMPP_OK){
				nmppsMallocTimerStart();
				nmppsFFT8192Inv28888((nm32sc*)src, (nm32sc*)dst, spec);
				nmppsMallocTimerStop();
				nmppsMallocBetterRoute();
				nmppsFFTFree(spec);
			} 
		}			
		while (nmppsMallocIncrementRoute0()==0);
		nmppsMallocSetBestRoute(1);
	}

	
	NmppsFFTSpec* spec=(NmppsFFTSpec*)nmppsMalloc_32s(sizeof32(NmppsFFTSpec));
	*specFFT=spec;
	if (spec==0) {
		return -1;
	}
	
	nm32sc* buffer0 =nmppsMalloc_32sc(8192);
	nm32sc* buffer1 =nmppsMalloc_32sc(8192);
	//nm8s*   tbl0    =nmppsMalloc_8s(2*8*8+16*8*8+128*8*8);	// 9344  Bytes 
	//nm8s*   tbl1    =nmppsMalloc_8s(1024*8*8);				// 65536 Bytes 
	//nm8s*   tbl2    =nmppsMalloc_8s(2*8*8+16*8*8+128*8*8);	// 9344  Bytes 
	//nm8s*   tbl3    =nmppsMalloc_8s(1024*8*8);				// 65536 Bytes 
	

	nm64s*   tbl0    =nmppsMalloc_64s(FFT8192_TBL0_SIZE64);	// 9344  Bytes 
	nm64s*   tbl1    =nmppsMalloc_64s(FFT8192_TBL1_SIZE64);	// 65536 Bytes 
	nm64s*   tbl2    =nmppsMalloc_64s(FFT8192_TBL2_SIZE64);	// 9344  Bytes 
	nm64s*   tbl3    =nmppsMalloc_64s(FFT8192_TBL3_SIZE64);	// 65536 Bytes 

	return nmppsFFT8192Inv28888Init( spec,  settings, (nm64s*)buffer0, (nm64s*)buffer1, tbl0,tbl1,tbl2,tbl3);
}

};