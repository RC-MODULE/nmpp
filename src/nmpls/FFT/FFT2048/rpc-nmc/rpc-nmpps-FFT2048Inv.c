#include "fft.h"
#include "rpc/rpc-nmc.h"


void rpc_nmppsFFT2048InvInitAlloc(void *in, void *out) 
{
	NmppsFFTSpec* spec;
	aura_buffer buf_src  = aura_get_buf(); 
	aura_buffer buf_dst  = aura_get_buf(); 
	int opt = aura_get_u32(); 
	int *src   = aura_buffer_to_ptr(buf_src); 
	int *dst   = aura_buffer_to_ptr(buf_dst);  
	int ret = nmppsFFT2048InvInitAlloc(&spec,src,dst,opt);
	aura_put_u32((int)spec); 
	aura_put_u32(ret); 
}
	
void rpc_nmppsFFT2048Inv(void *in, void *out) 
{ 
	aura_buffer buf_src = aura_get_buf(); 
	aura_buffer buf_dst = aura_get_buf(); 
	int *src = aura_buffer_to_ptr(buf_src); 
	int *dst = aura_buffer_to_ptr(buf_dst);	
	unsigned spec = aura_get_u32(); 
	nmppsFFT2048Inv((nm32sc*)src, (nm32sc*) dst, (NmppsFFTSpec*) spec);
}

