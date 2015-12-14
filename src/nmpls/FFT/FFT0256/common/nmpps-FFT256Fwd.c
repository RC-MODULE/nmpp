#include "rpc-host.h"
#include "time.h"
#include "malloc32.h"
#include "fft.h"
#include "fft2.h"


//extern "C" {


	void nmppsFFT256Fwd(nm32sc* src, nm32sc* dst, NmppsFFTSpec* spec)
	{
		FFT_Fwd256(src,dst,spec->buffer[0],spec->buffer[1],spec->shift[0]);
	}

	void nmppsFFT256FwdH(nm32sc* src, nm32sc* dst, int specHandle)
	{
		#ifdef RPC
		//RPC_HOST_PPI("nmppsFFT256Fwd",src,dst,specHandle,4);
		#endif
	
	}

	int nmppsFFT256FwdInitCustomAlloc(Malloc32Func* allocate, Free32Func* free,  NmppsFFTSpec* spec)
	{
		spec->buffer[0]=allocate(256*2*3);
		spec->buffer[1]=allocate(256*2*2);
		spec->buffer[2]=0;
		spec->buffer[3]=0;
		spec->shift[0]=-1;
		spec->free=free;
		if (spec->buffer[0]==0) return -1;
		if (spec->buffer[1]==0) return -1;
		return 0;

	}

	void nmppsFFTFree(NmppsFFTSpec* spec )
	{
		spec->free(spec->buffer[0]);
		spec->free(spec->buffer[1]);
		spec->free(spec->buffer[2]);
		spec->free(spec->buffer[3]);
	}	

	void nmppsFFTFreeH(int specHandle )
	{
#ifdef RPC
		
		//RPC_HOST_I("NmppsFFTSpec",specHandle);	
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

				NmppsFFTSpec spec;
				nmppsFFT256FwdInitCustomAlloc(nmppsMalloc32, nmppsFree32, &spec );

				if (nmppsMallocSpec.status==0){
					t0=clock();
					nmppsFFT256Fwd((nm32sc*)src, (nm32sc*)dst, &spec);
					t1=clock();

					if (bestTime>t1-t0){
						bestTime=t1-t0;
						nmppsMallocGetHistory(allocOrder,2);
					}
				}
				nmppsMallocSpec.status=0;
				nmppsFFTFree(&spec);
			}
		}
	//#endif	
	}

	int nmppsFFT256FwdInitAlloc(void* src, void* dst, NmppsFFTSpec* spec )
	{
		fseq64 allocRoute;
		nmppsFFT256FwdOptimize(src, dst, &allocRoute);
		nmppsMallocSetRouteMode(allocRoute);

		spec->buffer[0]=nmppsMalloc_32s(256*2*3);
		spec->buffer[1]=nmppsMalloc_32s(256*2*2);
		spec->buffer[2]=0;
		spec->buffer[3]=0;
		spec->shift[0] =-1;

		spec->free=nmppsFree;
		if (spec->buffer[0]==0) return -1;
		if (spec->buffer[1]==0) return -1;
		return 0;


	}

	int nmppsFFT256FwdInitAllocH(void* src, void* dst, int specHandle){
		int ret;		
		/*
		#ifdef RPC
		struct aura_buffer *iobuf_src = aura_buffer_request(n, 256*8);	
		struct aura_buffer *iobuf_dst = aura_buffer_request(n, 256*8);	
		memcpy(iobuf_src->data,src,256*8);	
		memcpy(iobuf_dst->data,dst,256*8);	
		struct aura_buffer *retbuf; 
		ret =  aura_call(n, "nmppsFFT256FwdInitAlloc", &retbuf,  iobuf_src, iobuf_dst, specHandle); 
		if (ret != 0) 
			BUG(n, "Call nmppsFFT256FwdInitAllocH failed!"); 
		*ret = aura_buffer_get_u32(retbuf);
		aura_buffer_release(n, iobuf_src); 
		aura_buffer_release(n, iobuf_dst); 
		aura_buffer_release(n, retbuf); 
		slog(0, SLOG_INFO, "ARM: Call nmppsFFT256FwdInitAllocH -ok"); 

		#endif
		*/
		return ret;
	}








//};

