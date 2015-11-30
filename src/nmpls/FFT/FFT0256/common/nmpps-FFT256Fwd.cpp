#include "time.h"
#include "malloc32.h"
#include "fft.h"
#include "fft2.h"
#include "rpc-host.h"

extern "C" {
/*
#ifdef RPC
int nmppsFFT256FwdInitAlloc(NmppsFFTSpec* spec )
{
	RPC_HOST_P("nmppsFFT256FwdInitAlloc");	
}
#else
	#endif
*/
int nmppsFFT256FwdInitAlloc(Malloc32Func* allocate, Free32Func* free,  NmppsFFTSpec* spec )
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
#ifdef RPC
	//RPC_HOST_P("NmppsFFTSpec");	
#else 
	spec->free(spec->buffer[0]);
	spec->free(spec->buffer[1]);
	spec->free(spec->buffer[2]);
	spec->free(spec->buffer[3]);
#endif
}	


void nmppsFFT256Fwd(nm32sc* src, nm32sc* dst, NmppsFFTSpec* spec)
{
#ifdef RPC
//	RPC_HOST_PPP("nmppsFFT256Fwd",src,dst,spec);
#else 
	FFT_Fwd256(src,dst,spec->buffer[0],spec->buffer[1],spec->shift[0]);
#endif
	
}

void nmppsFFT256FwdOptimize(void* src, void* dst, fseq64* allocOrder) 
{
#ifdef RPC
	//RPC_HOST_PPP("nmppsFFT256FwdOptimize",src,dst,allocOrder);
#else	
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
			nmppsFFT256FwdInitAlloc(nmppsMalloc32, nmppsFree32, &spec );
			
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
#endif	
}

};

