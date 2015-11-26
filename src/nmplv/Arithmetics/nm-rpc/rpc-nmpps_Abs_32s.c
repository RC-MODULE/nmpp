#include <easynmc/aura.h>
#include "nmpp.h"
#include "rpc-nmc.h"



NMC_RPC_PPI(nmppsAbs_32s);

/*
void rpc_nmppsAbs_32s(void *in, void *out)
{
	int i=0;
	int sum=0;
	
	aura_buffer buf_src = aura_get_buf();
	int *src  =aura_buffer_to_ptr(buf_src);
	aura_buffer buf_dst = aura_get_buf();
	int *dst =aura_buffer_to_ptr(buf_dst);	
	unsigned size = aura_get_u32();

	nmppsAbs_32s(src,dst,size);
	printf("NMC: hello from aura_nmc_nmppsAbs_32s\n");
	//aura_put_u32( 0x600DBEEF);
}

#pragma data_section ".aura_rpc_exports"
AURA_METHOD(rpc_nmppsAbs_32s, nmppsAbs_32s, 
	    BUFFER BUFFER U32,
	    ""
	    );

*/