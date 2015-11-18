#include "time.h"
#include "malloc32.h"
#include "fft.h"

extern "C" {
	
int nmppsFFT256FwdInitAlloc(Malloc32Func allocate, Free32Func free, struct NmppsFFTSpec* spec )
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

void nmppsFFT256Fwd(nm32sc* src, nm32sc* dst, NmppsFFTSpec* spec){

	FFT_Fwd256(src,dst,spec->buffer[0],spec->buffer[1],spec->shift[0]);
}

void nmppsFFT256FwdOptimize(void* src, void* dst, fseq64* allocOrder) 
{
	unsigned heapIndx0;
	unsigned heapIndx1;
	fseq64   route;
	clock_t t0,t1,bestTime=0x1000000;
		
	for(heapIndx0=0; heapIndx0<4; heapIndx0++){
		for(heapIndx1=0; heapIndx1<4; heapIndx1++){
			
			
			route =0xF00|(heapIndx1<<4)|(heapIndx0); 
			nmppsMalloc32SetRouteMode(route);

			NmppsFFTSpec spec;
			nmppsFFT256FwdInitAlloc(nmppsMalloc32, nmppsFree32, &spec );
			
			if (nmppsMalloc32Spec.status==0){
				t0=clock();
				nmppsFFT256Fwd((nm32sc*)src, (nm32sc*)dst, &spec);
				t1=clock();
				
				if (bestTime>t1-t0){
					bestTime=t1-t0;
					nmppsMalloc32GetHistory(allocOrder,2);
				}
			}
			//nmppsMalloc32Spec.status=0;
			nmppsFFTFree(&spec);
		}
	}
}

};

