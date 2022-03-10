#include "rpc/rpc-nmc.h"
#include "nmpp.h"

void rpc_nmppsMax_16sm(void *in, void *out) 
{ 
	int16b Max;
	aura_buffer buf_src = aura_get_buf(); 
	int *src  = aura_buffer_to_ptr(buf_src); 
	unsigned size = aura_get_u32(); 
	int err = nmppsMax_16sm ((nm16s*)src, size, &Max, 0);
	aura_put_u32(Max);
	aura_put_u32(err);
}
