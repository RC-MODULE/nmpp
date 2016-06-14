#include "rpc/rpc-nmc.h"
#include "nmpp.h"

void rpc_nmppsMin_32sm(void *in, void *out) 
{ 
	int32b min;
	aura_buffer buf_src = aura_get_buf(); 
	int *src  = aura_buffer_to_ptr(buf_src); 
	unsigned size = aura_get_u32(); 

	int err = nmppsMin_32sm ((const nm32s*)src, size, &min, 0);
	aura_put_u32(min);
	aura_put_u32(err);
}


