#include "fft.h"
#include "time.h"
#include "malloc32.h"

#include "fft2.h"

void nmppsFFT256Inv(nm32sc* src, nm32sc* dst, NmppsFFTSpec* spec);
	int  nmppsFFT256InvInitAllocM(NmppsFFTSpec** spec, Malloc32Func* allocate, Free32Func* free );
	int  nmppsFFT256InvInitAlloc (NmppsFFTSpec** spec, void* src, void* dst);
	void nmppsFFT256InvOptimize  (void* src, void* dst, fseq64* allocOrder) ;
	
	/*

extern "C" {
#include "rpc-host.h"	

	void nmppsFFT256Inv(nm32sc* src, nm32sc* dst, NmppsFFTSpec* spec)
	{
	#ifdef RPC
		int ret;	
		int size=256;
		int k=8;
		struct aura_buffer *iobuf_src = aura_buffer_request(n, size*k);	
		struct aura_buffer *iobuf_dst = aura_buffer_request(n, size*k);	
		memcpy(iobuf_src->data,src,size*k);	
		struct aura_buffer *retbuf; 
		ret = aura_call(n, "nmppsFFT256Inv", &retbuf,  iobuf_src, iobuf_dst, spec); 
		if (ret != 0) {
			slog(0, SLOG_ERROR, "call nmppsFFT256Inv  failed, reason: %d\n", ret);
			BUG(n, "Call nmppsFFT256Inv failed!"); 
		}
		memcpy(dst,iobuf_dst->data,size*k);
		aura_buffer_release(n, iobuf_dst); 
		aura_buffer_release(n, iobuf_src); 
		aura_buffer_release(n, retbuf); 
		slog(0, SLOG_INFO, "ARM: Call nmppsFFT256Inv -ok"); 
	#else 
		FFT_Inv256(src, dst, spec->buffer[0], spec->buffer[1], spec->shift[0]);
	#endif
	}

	int nmppsFFT256FwdInitAllocCustom(  NmppsFFTSpec** spec, Malloc32Func* allocate, Free32Func* free)
	{
		*spec=allocate(sizeof32(NmppsFFTSpec));
		if (*spec==0) return -1;
		*spec->buffer[0]=allocate(256*2*3);
		*spec->buffer[1]=allocate(256*2*2);
		*spec->buffer[2]=0;
		*spec->buffer[3]=0;
		*spec->shift [0]=-1;
		*spec->free=free;
		if (spec->buffer[0]==0) return -1;
		if (spec->buffer[1]==0) return -1;
		return 0;
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


				route =0xF000|(heapIndx1<<8)|(heapIndx0<<4)|(0); 
				nmppsMallocSetRouteMode(route);
				NmppsFFTSpec* spec;
				nmppsFFT256FwdInitAllocCustom(&spec, nmppsMalloc32, nmppsFree32 );

				if (nmppsMallocSpec.status==0){
					t0=clock();
					nmppsFFT256Inv((nm32sc*)src, (nm32sc*)dst, spec);
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
	}

	int nmppsFFT256InvInitAlloc( NmppsFFTSpec** spec, void* src, void* dst, )
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

	int nmppsFFT256FwdInitAllocH(void* src, void* dst, int* specHandle){
		int ret=-1;		
		#ifdef RPC
		struct aura_buffer *iobuf_src = aura_buffer_request(n, 256*8);	
		struct aura_buffer *iobuf_dst = aura_buffer_request(n, 256*8);	
		//memcpy(iobuf_src->data,src,256*8);	
		//memcpy(iobuf_dst->data,dst,256*8);	
		struct aura_buffer *retbuf; 
		ret =  aura_call(n, "nmppsFFT256FwdInitAllocH", &retbuf,  iobuf_src, iobuf_dst); 
		if (ret != 0) 
			BUG(n, "Call nmppsFFT256FwdInitAllocH failed!"); 
		*specHandle = aura_buffer_get_u32(retbuf);
		ret         = aura_buffer_get_u32(retbuf);
		aura_buffer_release(n, iobuf_src); 
		aura_buffer_release(n, iobuf_dst); 
		aura_buffer_release(n, retbuf); 
		slog(0, SLOG_INFO, "ARM: Call nmppsFFT256FwdInitAllocH -ok"); 

		#else 
		*specHandle = (int) malloc(sizeof(NmppsFFTSpec));
		if (*specHandle==0) return -1;
		nmppsFFT256FwdInitAlloc(src, dst, (NmppsFFTSpec*) *specHandle );
		#endif
		return ret;
	}

};
*/
