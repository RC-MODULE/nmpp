#include "rpc/rpc-nmc.h"
#include "nmpp.h"


void rpc_nmppsMalloc32(void *in, void *out) 
{
	unsigned i = aura_get_u32(); 
	void* p=nmppsMalloc32(i); 
	aura_put_u32((int)p); 
}


void rpc_nmppsFree(void *in, void *out) 
{ 
	unsigned p = aura_get_u32(); 
	nmppsFree((void*)p); 
}

