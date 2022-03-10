//#include "fft.h"
#include "time.h"
#include "malloc32.h"
#include "fft.h"

void FFT_Inv256Set7bit();	

void  FFT_Inv256(
		const 	nm32sc*	GSrcBuffer,	// Source buffer :long[256]
			nm32sc*	GDstBuffer,	// Result FFT    :long[256]
			void*		LBuffer,	// Temp buffer   :long[256*3]
			void*		GBuffer,	// Temp buffer   :long[256*3]
			int			ShiftR1,	// Intermediate shift normalization
			int			ShiftR2		// Final shift normalization
									// by default it means ShiftR2=14 at 7 bit precision
									//				 and   ShiftR2=12 at 6 bit precision
			);
			

	void nmppsFFT256Inv(const nm32sc* src, nm32sc* dst, const NmppsFFTSpec* spec)
	{
		FFT_Inv256(src, dst, spec->buffer[0], spec->buffer[1], spec->shift[0], spec->shift[1] );
	}

	int nmppsFFT256InvInitAllocCustom(  NmppsFFTSpec** specFFT, Malloc32Func* allocate, Free32Func* free, int settings)
	{
		NmppsFFTSpec* spec=(NmppsFFTSpec*)malloc(sizeof(NmppsFFTSpec));
		
		if (spec==0) { *specFFT = 0; return -1;	}
		nmppsFFTResetSpec(spec);
		spec->buffer[0]=(nm32sc*)allocate(256*2*3);
		spec->buffer[1]=(nm32sc*)allocate(256*2*3);
		//spec->buffer[2]=0;
		//spec->buffer[3]=0;
		spec->shift [0]=8;
		spec->shift [1]=-1;
		spec->free=free;
		if (spec->buffer[0]==0) {free(spec); *specFFT=0 ;return -1; }
		if (spec->buffer[1]==0) {free(spec->buffer[0]);free(spec); *specFFT=0 ;return -1; }
		*specFFT = spec;
		
		FFT_Inv256Set7bit();
		return 0;
	}




	int nmppsFFT256InvInitAlloc( NmppsFFTSpec** spec,const void* src, const void* dst, int settings)
	{
		int ret;
		if (settings&NMPP_OPTIMIZE_DISABLE){}
		else {
			//!fseq64 allocRoute;
			//!ret=nmppsFFT256InvOptimize(src, dst, &allocRoute);
			//!nmppsMallocSetRouteMode(allocRoute); 
		}
		ret = nmppsFFT256InvInitAllocCustom(spec, nmppsMalloc32, nmppsFree, settings);
		return ret;
	}
	int nmppsFFT256InvOptimize(const void* src, const void* dst, fseq64* allocOrder) 
	{
		unsigned heapIndx0;
		unsigned heapIndx1;
		fseq64   route;
		NmppsFFTSpec* spec;
		clock_t t0,t1;
		clock_t bestTime=0x1000000;
		*allocOrder=0xFFFFFF00;

		for(heapIndx0=0; heapIndx0<4; heapIndx0++){
			for(heapIndx1=0; heapIndx1<4; heapIndx1++){


				route =0xF00|(heapIndx1<<4)|(heapIndx0); 
				//!nmppsMallocSetRouteMode(route);
				
				if (nmppsFFT256InvInitAllocCustom(&spec, nmppsMalloc32, nmppsFree, NMPP_OPTIMIZE_DISABLE )==NMPP_OK){
					t0=clock();
					nmppsFFT256Inv((nm32sc*)src, (nm32sc*)dst, spec);
					t1=clock();

					if (bestTime>t1-t0){
						bestTime=t1-t0;
						//!nmppsMallocGetHistory(allocOrder,2);
					}
				}
				nmppsMallocSpec.status=0;
				nmppsFFTFree(spec);
			}
		}
		if (bestTime<0x1000000)	return NMPP_OK;
		else					return NMPP_ERROR;
	}



