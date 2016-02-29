#include "fft.h"
#include "time.h"
#include "malloc32.h"

#include "fft2.h"


extern "C" {
#include "rpc-host.h"	

	void nmppsFFT2048Fwd(nm32sc* src, nm32sc* dst, NmppsFFTSpec* spec)
	{
	#ifdef RPC
		int ret;	
		int size=2048;
		int k=8;
		struct aura_buffer *iobuf_src = aura_buffer_request(n, size*k);	
		struct aura_buffer *iobuf_dst = aura_buffer_request(n, size*k);	
		memcpy(iobuf_src->data,src,size*k);	
		struct aura_buffer *retbuf; 
		ret = aura_call(n, "nmppsFFT2048Fwd", &retbuf,  iobuf_src, iobuf_dst, spec); 
		if (ret != 0) {
			slog(0, SLOG_ERROR, "call failed, reason: %d\n", ret);
			BUG(n, "Call nmppsFFT2048Fwd failed!"); 
		}
		memcpy(dst,iobuf_dst->data,size*k);
		aura_buffer_release(n, iobuf_dst); 
		aura_buffer_release(n, iobuf_src); 
		aura_buffer_release(n, retbuf); 
		slog(0, SLOG_INFO, "ARM: Call nmppsFFT2048Fwd -ok"); 
	#else 
		FFT_Fwd2048(src,dst,spec->buffer[0],spec->shift[0]);
	#endif

	
	}

	int nmppsFFT2048FwdInitAllocCustom(  NmppsFFTSpec** specFFT, Malloc32Func* allocate, Free32Func* free, int settings)
	{
		NmppsFFTSpec* spec=(NmppsFFTSpec*)allocate(sizeof32(NmppsFFTSpec));
		*specFFT = spec;
		if (spec==0) return -1;
		spec->buffer[0]=allocate(2048*2*4);
		spec->buffer[1]=0;
		spec->buffer[2]=0;
		spec->buffer[3]=0;
		spec->shift [0]=-1;
		spec->free=free;
		if (spec->buffer[0]==0) return -1;
#ifndef RPC		
		FFT_Fwd2048Set7bit();
#endif
		return 0;
	}


	int nmppsFFT2048FwdInitAlloc( NmppsFFTSpec** spec, void* src, void* dst,  int settings)
	{
#ifdef RPC
		struct aura_buffer *iobuf_src = aura_buffer_request(n, 2048*8);	
		struct aura_buffer *iobuf_dst = aura_buffer_request(n, 2048*8);	
		struct aura_buffer *retbuf; 
		int ret =  aura_call(n, "nmppsFFT2048FwdInitAlloc", &retbuf,  iobuf_src, iobuf_dst, settings); 
		if (ret != 0) {
			slog(0, SLOG_ERROR, "call failed, reason: %d\n", ret);
			BUG(n, "Call nmppsFFT2048FwdInitAlloc failed!"); 
		}
		*spec = (NmppsFFTSpec*) aura_buffer_get_u32(retbuf);
		ret   = aura_buffer_get_u32(retbuf);
		aura_buffer_release(n, iobuf_src); 
		aura_buffer_release(n, iobuf_dst); 
		aura_buffer_release(n, retbuf); 
		slog(0, SLOG_INFO, "ARM: Call nmppsFFT2048FwdInitAlloc -ok"); 
		return ret;
#else
		int ret;
		if (settings&NMPP_OPTIMIZE_DISABLE){}
		else {
			//!fseq64 allocRoute;
			//!ret=nmppsFFT2048FwdOptimize(src, dst, &allocRoute);
			//!!!nmppsMallocSetRouteMode(allocRoute); 
		}
		ret = nmppsFFT2048FwdInitAllocCustom(spec, nmppsMalloc32, nmppsFree, settings);
		return ret;
#endif
	}

	int nmppsFFT2048FwdOptimize(void* src, void* dst, fseq64* allocOrder) 
	{
		unsigned heapIndx0;
		unsigned heapIndx1;
		fseq64   route;
		*allocOrder=0xFFFFFF00;
		clock_t t0,t1,bestTime=0x1000000;

		for(heapIndx0=0; heapIndx0<4; heapIndx0++){
			for(heapIndx1=0; heapIndx1<4; heapIndx1++){


				route =0xF00|(heapIndx1<<4)|(heapIndx0); 
				//!!!nmppsMallocSetRouteMode(route);
				NmppsFFTSpec* spec;
				if (nmppsFFT2048FwdInitAllocCustom(&spec, nmppsMalloc32, nmppsFree, NMPP_OPTIMIZE_DISABLE )==NMPP_OK){
					t0=clock();
					nmppsFFT2048Fwd((nm32sc*)src, (nm32sc*)dst, spec);
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



};

