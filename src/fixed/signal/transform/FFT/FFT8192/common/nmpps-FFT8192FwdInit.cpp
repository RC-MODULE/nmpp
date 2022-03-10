#include "fft.h"
#include <math.h>
#include "fftexp.h"
#include "nmpp.h"

#ifndef PI
#define PI 3.14159265359
#endif

extern "C" {



int nmppsFFT8192Fwd28888InitSinCos(NmppsFFTSpec* spec, int settings)
{
	nm32sc z;
	int ii=0,k,kk,j,i,n,h;	
	
	//---------------------------------- 1 -----------------------------------------
	nm8s* cosTbl=(nm8s*)spec->fftTable[0];
	nm8s* sinTbl=(nm8s*)spec->fftTable[2];

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
	cosTbl=(nm8s*)spec->fftTable[1];
	sinTbl=(nm8s*)spec->fftTable[3];
	ii=0;

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
	return 1;
}


int nmppsFFT8192Fwd28888InitSinCosFast(NmppsFFTSpec* spec, int settings, nm64s* tmp0)
{
	nm32sc z;
	int ii=0,k,kk,j,i,n,h;	
	nm32sc* cache = (nm32sc*)tmp0;
	
	nm8s* cosTbl;
	nm8s* sinTbl;
	
	//---------------------------------- 4 -----------------------------------------
	cosTbl=(nm8s*)spec->fftTable[1];
	sinTbl=(nm8s*)spec->fftTable[3];

	ii=0;
	nmppsSet_32s(0xCCCCCCCC, (nm32s*)cache, 8192*2);
	for (int k2=0; k2<1024; k2++){
		for (int k1=0; k1<8; k1++){
			int k=1024*k1+k2;
			for(int i=0; i<8; i++,ii++){
				int idx=(i*k)&0x1FFF;
				if (cache[idx].re==0xCCCCCCCC){
					expFFT127<8192>(i*k,spec->amp[4],cache+idx);	
				}
				nmppsPut_8s(cosTbl,ii,cache[idx].re);
				nmppsPut_8s(sinTbl,ii,cache[idx].im);
			}
		}
	}


	//---------------------------------- 1 -----------------------------------------
	ii=0;
	cosTbl=(nm8s*)spec->fftTable[0];
	sinTbl=(nm8s*)spec->fftTable[2];

	for(int k2=0; k2<2; k2++){
		for(int k1=0; k1<8; k1++){	
			int k=k1*2+k2;
			for(int g=0; g<8; g++,ii++){
				//expFFT127<8192>(512*g*k,spec->amp[1],&z);
				int idx=(512*g*k)&0x1FFF;
				nmppsPut_8s(cosTbl,ii,cache[idx].re);
				nmppsPut_8s(sinTbl,ii,cache[idx].im);
			}
		}
	}


	//---------------------------------- 2 -----------------------------------------

	for (int k2=0; k2<16;k2++){
		for (int k1=0; k1<8;k1++){
			int k=16*k1+k2;
			for(int h=0; h<8; h++,ii++){
				//expFFT127<8192>(64*h*k,spec->amp[2],&z);
				int idx=(64*h*k)&0x1FFF;
				nmppsPut_8s(cosTbl,ii,cache[idx].re);
				nmppsPut_8s(sinTbl,ii,cache[idx].im);
			}
		}
	}
	//---------------------------------- 3 -----------------------------------------
	for (int k2=0; k2<128; k2++){
		for (int k1=0; k1<8; k1++){
			int k=128*k1+k2; //for(int k=0; k<1024; k++){
			for(int j=0; j<8; j++,ii++){
				//expFFT127<8192>(8*j*k,spec->amp[3],&z);
				int idx=(8*j*k)&0x1FFF;
				nmppsPut_8s(cosTbl,ii,cache[idx].re);
				nmppsPut_8s(sinTbl,ii,cache[idx].im);
			}
		}
	}
	
	return 1;
}


//#define NMPP_OPTIMIZE_ALLOC 1
//#define NMPP_CUSTOM_ALLOC 2
//#define SKIP_SINCOS 4

int  nmppsFFT8192Fwd28888Init( NmppsFFTSpec* spec,  int settings, nm64s *buf0, nm64s* buf1, nm64s* tbl0, nm64s* tbl1, nm64s* tbl2, nm64s* tbl3)
{
	spec->buffer[0]  =(nm32sc*)buf0; // [8192]nm32s;
	spec->buffer[1]  =(nm32sc*)buf1; // [8192]nm32s;
	spec->buffer[2]  =0;
	spec->buffer[3]  =0;
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


	if (!(settings&SKIP_SINCOS)){
		//nmppsFFT8192Fwd28888InitSinCos(spec,settings);
		//nm32sc* cache= new nm32sc[8192];
		nmppsFFT8192Fwd28888InitSinCosFast(spec,  settings, buf0);
		//delete cache;
	}	

	

	return NMPP_OK;
}



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

	return nmppsFFT8192Fwd28888Init( spec,  settings, (nm64s*)buffer0, (nm64s*)buffer1, tbl0,tbl1,tbl2,tbl3);
}

};