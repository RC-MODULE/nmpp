#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <easynmc/easynmc.h>
#include <easynmc/aura.h>
#include "nmpp.h"
#include "rpc-nmc.h"
 
NMC_RPC_PPPI(nmppsAdd_32s);
/*
void rpc_nmppsAdd_32s(void *in, void *out)
{
	int i=0;
	int sum=0;
	
	aura_buffer buf_src0 = aura_get_buf();
	aura_buffer buf_src1 = aura_get_buf();
	int *src0  =aura_buffer_to_ptr(buf_src0);
	int *src1  =aura_buffer_to_ptr(buf_src1);
	aura_buffer buf_dst = aura_get_buf();
	int *dst =aura_buffer_to_ptr(buf_dst);	
	unsigned size = aura_get_u32();
	nmppsAdd_32s(src0,src1,dst,size);
	printf("NMC: hello from rpc_nmppsAdd_s32\n");
	//aura_put_u32( 0x600DBEEF);
}
*/
/*
#pragma data_section ".aura_rpc_exports"
AURA_METHOD(rpc_nmppsAdd_32s, nmppsAdd_32s, 
		BUFFER BUFFER BUFFER U32,
	    ""
		);
*/