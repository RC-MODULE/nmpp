#include <easynmc/easynmc.h>
#include <easynmc/aura-exportfile.h>
#include "aura-exports.h"

#ifdef RPC_nmppsAbs_64s
AURA_METHOD(rpc_nmppsAbs_64s, nmppsAbs_64s, 
	    BUFFER BUFFER U32,
	    "");
#endif 

#ifdef RPC_nmppsAbs_32s
AURA_METHOD(rpc_nmppsAbs_32s, nmppsAbs_32s, 
	    BUFFER BUFFER U32,
	    "");
#endif 
		
#ifdef RPC_nmppsAbs_16s
AURA_METHOD(rpc_nmppsAbs_16s, nmppsAbs_16s, 
	    BUFFER BUFFER U32,
	    "");
#endif 

#ifdef RPC_nmppsAbs_8s
AURA_METHOD(rpc_nmppsAbs_8s, nmppsAbs_8s, 
	    BUFFER BUFFER U32,
	    "");
#endif 

#ifdef RPC_nmppsAdd_32s		
AURA_METHOD(rpc_nmppsAdd_32s, nmppsAdd_32s, 
		BUFFER BUFFER BUFFER U32,
	    "");
#endif 


// int  nmppsFFT256FwdInitAlloc(Malloc32Func* allocate,  Free32Func* free, NmppsFFTSpec* spec);
#ifdef RPC_nmppsFFT256Fwd

AURA_METHOD(rpc_nmppsFFT256FwdOptimize, nmppsFFT256FwdInitAlloc, 
		BUFFER BUFFER BUFFER,
	    U32);
		
AURA_METHOD(rpc_nmppsFFT256Fwd, nmppsFFT256Fwd, 
	    BUFFER BUFFER BUFFER,
	    "");
		
AURA_METHOD(rpc_nmppsFFTFree, nmppsFFTFree, 
	    BUFFER,
	    "");
		
#endif 




struct aura_object g_aura_eof;
