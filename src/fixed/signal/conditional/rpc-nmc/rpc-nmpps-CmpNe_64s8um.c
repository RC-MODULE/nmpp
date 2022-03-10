#include "rpc/rpc-nmc.h"
#include "nmpp.h"

void rpc_nmppsCmpNe_64s8um(void *in, void *out) 
{ 
	aura_buffer buf_src0 = aura_get_buf(); 
	aura_buffer buf_src1 = aura_get_buf(); 
	aura_buffer buf_dst  = aura_get_buf(); 
	int *src0  = aura_buffer_to_ptr(buf_src0); 
	int *src1  = aura_buffer_to_ptr(buf_src1); 
	int *dst   = aura_buffer_to_ptr(buf_dst);  
	unsigned size = aura_get_u32(); 
	int err = nmppsCmpNe_64s8um ((const nm64s*) src0,(const nm64s*) src1, (nm8u*) dst, size, 0);
}


