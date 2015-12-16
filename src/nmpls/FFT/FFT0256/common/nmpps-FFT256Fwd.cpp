#include "fft.h"
#include "time.h"
#include "malloc32.h"

#include "fft2.h"



extern "C" {
#include "rpc-host.h"	

	void nmppsFFT256Fwd(nm32sc* src, nm32sc* dst, NmppsFFTSpec* spec)
	{
	#ifdef RPC
		int ret;	
		int size=256;
		int k=8;
		struct aura_buffer *iobuf_src = aura_buffer_request(n, size*k);	
		struct aura_buffer *iobuf_dst = aura_buffer_request(n, size*k);	
		memcpy(iobuf_src->data,src,size*k);	
		struct aura_buffer *retbuf; 
		ret = aura_call(n, "nmppsFFT256Fwd", &retbuf,  iobuf_src, iobuf_dst, spec); 
		if (ret != 0) {
			slog(0, SLOG_ERROR, "call failed, reason: %d\n", ret);
			BUG(n, "Call nmppsFFT256Fwd failed!"); 
		}
		memcpy(dst,iobuf_dst->data,size*k);
		aura_buffer_release(n, iobuf_dst); 
		aura_buffer_release(n, iobuf_src); 
		aura_buffer_release(n, retbuf); 
		slog(0, SLOG_INFO, "ARM: Call nmppsFFT256Fwd -ok"); 
	#else 
		FFT_Fwd256(src,dst,spec->buffer[0],spec->buffer[1],spec->shift[0]);
		//nmppsFFT256Fwd(src,dst,(NmppsFFTSpec*) specHandle);
	#endif

	
	}




	void nmppsFFTFree(NmppsFFTSpec* spec )
	{
	#ifdef RPC
		RPC_HOST_I("nmppsFFTFree",(int)spec);	
	#else
		spec->free(spec->buffer[0]);
		spec->free(spec->buffer[1]);
		spec->free(spec->buffer[2]);
		spec->free(spec->buffer[3]);
		spec->free(spec);
	#endif
		
	}	


	void nmppsFFT256FwdOptimize(void* src, void* dst, fseq64* allocOrder) 
	{
		unsigned heapIndx0;
		unsigned heapIndx1;
		fseq64   route;
		*allocOrder=0xFFFFFF00;
		clock_t t0,t1,bestTime=0x1000000;

		for(heapIndx0=0; heapIndx0<4; heapIndx0++){
			for(heapIndx1=0; heapIndx1<4; heapIndx1++){


				route =0xF00|(heapIndx1<<4)|(heapIndx0); 
				nmppsMallocSetRouteMode(route);

				NmppsFFTSpec* spec;
				nmppsFFT256FwdInitAlloc(&spec,src,dst, 0 );

				if (nmppsMallocSpec.status==0){
					t0=clock();
					nmppsFFT256Fwd((nm32sc*)src, (nm32sc*)dst, spec);
					t1=clock();

					if (bestTime>t1-t0){
						bestTime=t1-t0;
						nmppsMallocGetHistory(allocOrder,2);
					}
				}
				nmppsMallocSpec.status=0;
				nmppsFFTFree(spec);
			}
		}
	//#endif	
	}

	int nmppsFFT256FwdInitAllocCustom(  NmppsFFTSpec** specFFT, Malloc32Func* allocate, Free32Func* free, int settings)
	{
		NmppsFFTSpec* spec=(NmppsFFTSpec*)allocate(sizeof32(NmppsFFTSpec));
		*specFFT = spec;
		if (spec==0) return -1;
		spec->buffer[0]=allocate(256*2*3);
		spec->buffer[1]=allocate(256*2*2);
		spec->buffer[2]=0;
		spec->buffer[3]=0;
		spec->shift [0]=-1;
		spec->free=free;
		if (spec->buffer[0]==0) return -1;
		if (spec->buffer[1]==0) return -1;
#ifndef RPC		
		FFT_Fwd256Set7bit();
#endif
		return 0;
	}


	int nmppsFFT256FwdInitAlloc( NmppsFFTSpec** spec, void* src, void* dst,  int settings)
	{
		int optimizeAllocation=settings&1;
#ifdef RPC
		struct aura_buffer *iobuf_src = aura_buffer_request(n, 256*8);	
		struct aura_buffer *iobuf_dst = aura_buffer_request(n, 256*8);	
		struct aura_buffer *retbuf; 
		int ret =  aura_call(n, "nmppsFFT256FwdInitAlloc", &retbuf,  iobuf_src, iobuf_dst, optimizeAllocation); 
		if (ret != 0) {
			slog(0, SLOG_ERROR, "call failed, reason: %d\n", ret);
			BUG(n, "Call nmppsFFT256FwdInitAlloc failed!"); 
		}
		*spec = (NmppsFFTSpec*) aura_buffer_get_u32(retbuf);
		ret   = aura_buffer_get_u32(retbuf);
		aura_buffer_release(n, iobuf_src); 
		aura_buffer_release(n, iobuf_dst); 
		aura_buffer_release(n, retbuf); 
		slog(0, SLOG_INFO, "ARM: Call nmppsFFT256FwdInitAlloc -ok"); 
		return ret;
#else
		if (optimizeAllocation){
			fseq64 allocRoute;
			nmppsFFT256FwdOptimize(src, dst, &allocRoute);
			nmppsMallocSetRouteMode(allocRoute);
		}
		int ret = nmppsFFT256FwdInitAllocCustom(spec, nmppsMalloc32, nmppsFree, settings);
		return ret;
#endif
	}

};

