#include "rpc/rpc-nmc.h"
#include "nmpp.h"
#include "fft2.h"
void rpc_nmppsFFTFree(void *in, void *out) 
{ 
	unsigned p = aura_get_u32(); 
	nmppsFFTFree((void*)p); 
}

