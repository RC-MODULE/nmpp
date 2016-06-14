#include "rpc/rpc-nmc.h"
#include "nmpp.h"

void rpc_nmppsMax_32sm(void *in, void *out) 
{ 
	int32b Max;
	aura_buffer buf_src = aura_get_buf(); 
	int *src  = aura_buffer_to_ptr(buf_src); 
	unsigned size = aura_get_u32(); 

	int err = nmppsMax_32sm ((nm32s*)src, size, &Max, 0);
	aura_put_u32(Max);
	aura_put_u32(err);
}


