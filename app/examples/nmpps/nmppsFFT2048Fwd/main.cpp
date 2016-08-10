#include "fft2.h"
#include "nmpp.h"
#include <time.h>
#include <stdio.h>

//void nmppsFFT2048FwdRef2x4x8  ( nm32sc* src, nm32sc* dst);
void nmppsFFT2048FwdRef_f( nm32sc* src, nm32sc* dst);
void nmppsFFT2048FwdRef2x32x32_f(const nm32sc* src, nm32sc* dst);
//void nmppsFFT2048FwdRef2x32_f( nm32sc* src, nm32sc* dst);
//void nmppsFFT2048FwdRef2x4õ8_f( nm32sc* src, nm32sc* dst);
//void nmppsFFT2048FwdRef8x8_f( nm32sc* src, nm32sc* dst);
//void nmppsFFT2048FwdRef8x8( nm32sc* src, nm32sc* dst);

#define FFT_SIZE 2048


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
		nmppsFFT2048FwdInitAlloc4x8x8x8(&spec,src,dst,SKIP_SINCOS);
		
		if (!nmppsMallocFail())	 {
			
			t0=clock();
			dt=nmppsFFT2048Fwd4x8x8x8Raw         (src,dst,spec); // 36573   121231 best route
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

void nmppsFFT2048FwdRef4x8x8x8_ff(const nm32sc* src, nm32sc* dst);
void nmppsFFT2048FwdRef4x8x8x8_fff(const nm32sc* src, nm32sc* dst);
void nmppsFFT2048FwdRef4x8x8x8_1(const nm32sc* src, nm32sc* dst);
void nmppsFFT2048FwdRef4x8x8x8_2(const nm32sc* src, nm32sc* dst);
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
	//nmppsFFT2048FwdInitAlloc(&spec,src,dst,0);
	
	//MALLOC_OPTIMIZE_BEGIN();
	nmppsFFT2048FwdInitAlloc4x8x8x8(&spec,src,dst,NMPP_CUSTOM_ALLOC);
	//MALLOC_OPTIMIZE_END();
	
	//nmppsFFT2048FwdInitAlloc4x8x8x8(&spec,src,dst,AUTO_ALLOC);
	//nmppsMallocSetRoute(route,12);
	//nmppsMallocModifySetRoute(route,12);

	//nmppsFFT2048FwdInitAlloc4x8x8x8(&spec,src,dst,ROUTE_ALLOC);
		
	if (nmppsMallocFail())	return -2;
		
	nmppsRandUniform_64s((nm64s*)src,FFT_SIZE);
	nmppsRShiftC_32s((nm32s*)src,24,(nm32s*)src,2*FFT_SIZE);
	//nmppsSet_64s((nm64s*)src,0,FFT_SIZE);
		//src[0].re=100;
		//src[1].re=100;
	nmppsRandUniform_64s((nm64s*)dst,FFT_SIZE);
		
		//nmppsFFT64FwdRef2x4x8  (src,dst);
	float msd;
//	nmppsFFT2048Fwd_RefFloat(src,dstf);
//	nmppsFFT2048Fwd4x8x8x8_RefFloat( src,  dstf2);msd=nmppsMSD_32sc(dstf,dstf2,2048);	printf("msd 1=%f\n",msd);
//	nmppsFFT2048Fwd4x8x8x8_RefInt  ( src,  dstf2);	msd=nmppsMSD_32sc(dstf,dstf2,2048);	printf("msd 1=%f\n",msd);
	t0=clock();
	nmppsFFT2048Fwd4x8x8x8Raw         (src,dst,spec); //		msd=nmppsMSD_32sc(dstf,dstf2,2048);	printf("msd 1=%f\n",msd);
	t1=clock();
	nmppsRShiftC_32s((nm32s*)dst,7,(nm32s*)dst,2048*2);
	
	
	crc=nmppsCrc_32s((nm32s*)dst,2048*2);
	
	nmppsMallocWipe();
	
	//return t1-t0;
	return crc;//t1-t0;
	
}
#include "nmtl/tcmplx_spec.h"
cmplx<double> W2048(int power);

extern "C" {
	void nmppsFFT2048FwdRaw4x8x8x8     ( void* a,void* b,void* c,void* d,void* e); 
};

#define pi 3.1415926535897932384626433832795
int main()
{
     
    // return 1000*sin(pi/2);
	
	
	/*
	float minerr=10000;
	for (int k=1; k<256; k++){
		float err=0;
		for(int i=1; i<2048; i++){
			cmplx<double> z=W2048(i);
			double diff1=z.re*(z.re*k-int(z.re*k));
			double diff2=z.im*(z.im*k-int(z.im*k));
			err+=diff1*diff1+diff2*diff2;
//			printf("%f %f\n",z.re,z.im);
		}
		if (minerr>err) minerr=err;
		printf("%d %f %f\n",k, err,minerr);
		
	}
	*/
	//printf("Start...");
	//return selfTest();
	return speedTest();
/*
	void* a=malloc1(100); //ar0 -data
	void* b=malloc2(100); //ar1 -data
	void* c=malloc3(100); //ar4 -wfifo
	void* d=malloc2(100); //ar5 -afifo
	void* e=malloc1(100); //ar6 -afifo
	
	
	clock_t t0=clock();
	nmppsFFT2048FwdRaw4x8x8x8     ( a,b,c,d,e); 
	clock_t t1=clock();
	return t1-t0;
	*/
	
	//return speedTest();
	
}
// magic number (64) = 51 
// magic number (32) = 87
// magic number (16) = 91
// 51 0.470908 0.470908
// 52 1.399659 0.470908
// 53 3.833596 0.470908
// 54 4.436022 0.470908
// 55 4.605351 0.470908
// 56 3.492216 0.470908
// 57 3.098235 0.470908
// 58 2.212720 0.470908
// 59 2.899916 0.470908
// 60 3.350208 0.470908
// 61 2.854783 0.470908
// 62 2.796789 0.470908
// 63 1.782727 0.470908
// 64 1.577785 0.470908
// 127 2.271446 0.470908
// 128 1.550667 0.470908

// magic number (4) = 106 
// 104 0.489548 0.091493
// 105 0.070389 0.070389
// 106 2.482518 0.070389
// 107 1.947161 0.070389
// 108 1.202854 0.070389
// 109 0.997611 0.070389
// 110 1.284355 0.070389
// 111 0.823439 0.070389
// 112 0.639666 0.070389
// 113 1.103795 0.070389
// 114 0.664349 0.070389
// 115 0.204118 0.070389
// 116 0.094787 0.070389
// 117 0.725584 0.070389
// 118 0.200097 0.070389
// 119 1.620172 0.070389
// 120 2.255188 0.070389
// 121 1.404554 0.070389
// 122 1.078270 0.070389
// 123 1.643463 0.070389
// 124 1.061507 0.070389
// 125 0.756694 0.070389
// 126 0.308362 0.070389
// 127 0.938785 0.070389