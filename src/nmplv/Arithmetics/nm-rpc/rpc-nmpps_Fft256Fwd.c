#include <string.h>
#include <easynmc/easynmc.h>
#include <easynmc/aura.h>
#include "fft.h"

void rpc_nmppsFFT256Fwd(void *in, void *out)
{
	int i=0;
	int sum=0;
	nm32sc *dst ;	
	nm32sc *src = aura_get_bin(256*2*4);
	
	clock_t t0,t1,t;
	
	
	dst= nmppsMalloc32(256*2*4);	

	NmppsFFTSpec spec;
	fseq64 route;
	nmppsFFT256FwdOptimize(src,dst, &route);
	
	nmppsMallocSetRouteMode(route);
	nmppsFFT256FwdInitAlloc(nmppsMalloc32, nmppsFree, &spec);
	t0=clock();
	nmppsFFT256Fwd(src,dst,&spec);
	t1=clock();
	t=t1-t0;
	nmppsFFTFree(&spec);
	printf("NMC: route is: 0x%X \n", route);
	printf("NMC: Time is: %d\n", t);

	printf("NMC: hello from aura_nmc_nmppsFFT256Fwd\n");
	aura_put_bin(dst, 256*4);
	nmppsFree(dst);
}
/*
#pragma data_section ".aura_rpc_exports"
AURA_METHOD(rpc_nmppsFFT256Fwd, nmppsFFT256Fwd, 
	    BIN(2048), 
	    BIN(2048));

*/