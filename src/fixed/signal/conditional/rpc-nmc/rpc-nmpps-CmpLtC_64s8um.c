#include "rpc/rpc-nmc.h"
#include "nmpp.h"

void rpc_nmppsCmpLtC_64s8um(void *in, void *out) 
{ 
	aura_buffer buf_src  = aura_get_buf(); 
	unsigned val  = aura_get_u32(); 
	aura_buffer buf_dst  = aura_get_buf(); 
	int *src   = aura_buffer_to_ptr(buf_src); 
	int *dst   = aura_buffer_to_ptr(buf_dst);  
	unsigned size = aura_get_u32(); 
	int err = nmppsCmpLtC_64s8um((const nm64s*) src,  val, (nm8u*) dst,  size, 0);
}