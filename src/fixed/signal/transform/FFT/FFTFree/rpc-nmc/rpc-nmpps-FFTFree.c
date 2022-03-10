#include "rpc/rpc-nmc.h"
#include "nmpp.h"
#include "fft.h"
void rpc_nmppsFFTFree(void *in, void *out) 
{ 
	unsigned p = aura_get_u32(); 
	nmppsFFTFree((void*)p); 
}

