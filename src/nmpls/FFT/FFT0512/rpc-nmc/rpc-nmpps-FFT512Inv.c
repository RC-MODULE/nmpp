#include "fft2.h"
#include "rpc/rpc-nmc.h"
void rpc_nmppsFFT512InvInitAlloc(void *in, void *out) 
{
	NmppsFFTSpec* spec;
	aura_buffer buf_src  = aura_get_buf(); 
	aura_buffer buf_dst  = aura_get_buf(); 
	int opt = aura_get_u32(); 
	int *src   = aura_buffer_to_ptr(buf_src); 
	int *dst   = aura_buffer_to_ptr(buf_dst);  
	int ret = nmppsFFT512InvInitAlloc(&spec,src,dst,opt);
	aura_put_u32((int)spec); 
	aura_put_u32(ret); 
}
	
NMC_RPC_PPI(nmppsFFT512Inv);
