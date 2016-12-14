#include "malloc32.h"
//#include "fft.h"
void FFT_Fwd512Set7bit();// Sets 7-bit accuracy of sin-cosine coefficients
void  FFT_Fwd512(
		const	nm32sc*	GSrcBuffer,	// Source buffer :long[512]
			nm32sc*	GDstBuffer,	// Result FFT    :long[512]
			void*		LBuffer,	// Temp buffer   :long[512*3]
			void*		GBuffer,	// Temp buffer	 :long[512*3]
			int			ShiftR	// Right shift normalization
			);
			
#include "fft2.h"


	void nmppsFFT512Fwd_(const nm32sc* src, nm32sc* dst, const NmppsFFTSpec* spec)
	{
		FFT_Fwd512(src,dst,spec->buffer[0],spec->buffer[1],spec->shift[0]);
	}

	int nmppsFFT512FwdInitAllocCustom(  NmppsFFTSpec** specFFT, Malloc32Func* allocate, Free32Func* free, int settings)
	{
		NmppsFFTSpec* spec=(NmppsFFTSpec*)allocate(sizeof32(NmppsFFTSpec));
		if (spec==0) { *specFFT = 0; return -1;	}
		nmppsFFTResetSpec(spec);
		spec->buffer[0]=(nm32sc*)allocate(512*2*3);
		spec->buffer[1]=(nm32sc*)allocate(512*2*3);
		//spec->buffer[2]=0;
		//spec->buffer[3]=0;
		spec->shift [0]=-1;
		spec->free=free;
		if (spec->buffer[0]==0) {free(spec); *specFFT=0 ;return -1; }
		if (spec->buffer[1]==0) {free(spec->buffer[0]);free(spec); *specFFT=0 ;return -1; }
		*specFFT = spec;
		FFT_Fwd512Set7bit();
		return 0;
	}


	int nmppsFFT512FwdInitAlloc_( NmppsFFTSpec** spec, const void* src, const void* dst,  int settings)
	{
		int ret;
		if (settings&NMPP_OPTIMIZE_DISABLE){}
		else {
			//!fseq64 allocRoute;
			//!ret=nmppsFFT512FwdOptimize(src, dst, &allocRoute);
			//!nmppsMallocSetRouteMode(allocRoute); 
		}
		ret = nmppsFFT512FwdInitAllocCustom(spec, nmppsMalloc32, nmppsFree, settings);
		return ret;
	}

	int nmppsFFT512FwdOptimize(const void* src, const void* dst, fseq64* allocOrder) 
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
				
				if (nmppsFFT512FwdInitAllocCustom(&spec, nmppsMalloc32, nmppsFree, NMPP_OPTIMIZE_DISABLE )==NMPP_OK){
					t0=clock();
					nmppsFFT512Fwd((nm32sc*)src, (nm32sc*)dst, spec);
					t1=clock();

					if (bestTime>t1-t0){
						bestTime=t1-t0;
						//!!nmppsMallocGetHistory(allocOrder,2);
					}
				}
				nmppsMallocSpec.status=0;
				nmppsFFTFree(spec);
			}
		}
		if (bestTime<0x1000000)	return NMPP_OK;
		else					return NMPP_ERROR;
	}





