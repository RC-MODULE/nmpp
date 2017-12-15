//#include "fft.h"


#include "time.h"
#include "malloc32.h"
#include "fft.h"
#include "stdio.h"

void  FFT_Fwd256(
			const nm32sc*	GSrcBuffer,		// Source buffer :long[256]
			nm32sc*	LDstBuffer,		// Result FFT    :long[256]
			void*		LBuffer,	// Temp buffer   :long[256*3]
			void*		GBuffer,	// Temp buffer   :long[256*2]
			int			ShiftR	// Shift normalization	by default it means ShiftR=14 at 7 bit precision and   ShiftR=12 at 6 bit precision
			);
void FFT_Fwd256Set7bit();			
//extern "C"{


void nmppsFFT256Fwd(const nm32sc* src, nm32sc* dst,const NmppsFFTSpec* spec)
{
	FFT_Fwd256(src,dst,spec->buffer[0],spec->buffer[1],spec->shift[0]);
}


int nmppsFFT256FwdInitAllocCustom(  NmppsFFTSpec** specFFT, Malloc32Func* allocate, Free32Func* free, int settings)
{
	NmppsFFTSpec* spec=(NmppsFFTSpec*)malloc(sizeof(NmppsFFTSpec));
	if (spec==0) { *specFFT = 0; return -1;	}
	if (spec==0) return -1;
	nmppsFFTResetSpec(spec);
	spec->buffer[0]=(nm32sc*)allocate(256*2*3);
	spec->buffer[1]=(nm32sc*)allocate(256*2*2);
	spec->shift [0]=-1;
	spec->free=free;
	if (spec->buffer[0]==0) {free(spec); *specFFT=0 ;return -1; }
	if (spec->buffer[1]==0) {free(spec->buffer[0]);free(spec); *specFFT=0 ;return -1; }
	*specFFT = spec;	
	FFT_Fwd256Set7bit();
	return 0;
}


int nmppsFFT256FwdInitAlloc( NmppsFFTSpec** spec,const void* src, const void* dst,  int settings)
{
	int ret;
	if (settings&NMPP_OPTIMIZE_DISABLE){}
	else {
		//!fseq64 allocRoute;
		//!ret=nmppsFFT256FwdOptimize(src, dst, &allocRoute);
		//!nmppsMallocSetRouteMode(allocRoute); 
	}
	ret = nmppsFFT256FwdInitAllocCustom(spec, nmppsMalloc32, nmppsFree, settings);
	return ret;
}

int nmppsFFT256FwdOptimize(void* src, void* dst, fseq64* allocOrder) 
{
	unsigned heapIndx0;
	unsigned heapIndx1;
	fseq64   route,bestRoute;
	NmppsFFTSpec* spec;
	clock_t t0,t1;
	clock_t bestTime=0x1000000;
	*allocOrder=0xFFFFFF00;

	//for(heapIndx0=0; heapIndx0<4; heapIndx0++){
		//for(heapIndx1=0; heapIndx1<4; heapIndx1++){
	nmppsMallocSetRouteMode();
	nmppsMallocResetRoute();
	//nmppsMallocSpec.route[0]=0x0;
	nmppsMallocGetRoute16(allocOrder);
	printf("%x--\n",*allocOrder);
	do{
		//nmppsMallocSpec.route[0]=0x0;
		nmppsMallocResetPos();
		//route =0xF00|(heapIndx1<<4)|(heapIndx0); 
		//!nmppsMallocSetRouteMode(route);
		//nmppsMallocSetRoute16(route);
		
		if (nmppsFFT256FwdInitAllocCustom(&spec, nmppsMalloc32, nmppsFree, NMPP_OPTIMIZE_DISABLE )==NMPP_OK){
			t0=clock();
			nmppsFFT256Fwd((nm32sc*)src, (nm32sc*)dst, spec);
			t1=clock();

			if (bestTime>t1-t0){
				bestTime=t1-t0;
				nmppsMallocGetRoute16(allocOrder);
				printf("%x\n",*allocOrder);
				//!nmppsMallocGetHistory(allocOrder,2);
			}
		}
		nmppsMallocSpec.status=0;
		nmppsFFTFree(spec);
	}
	while (!nmppsMallocIncrementRoute());

	

	if (bestTime<0x1000000)	return NMPP_OK;
	else					return NMPP_ERROR;
}


//};