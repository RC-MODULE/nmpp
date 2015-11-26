#include <easynmc/easynmc.h>
#include <easynmc/aura-exportfile.h>
#include "aura-exports.h"

#ifdef RPC_nmppsAbs_32s
AURA_METHOD(rpc_nmppsAbs_32s, nmppsAbs_32s, 
	    BUFFER BUFFER U32,
	    "");
#endif 
		

#ifdef RPC_nmppsAdd_32s		
AURA_METHOD(rpc_nmppsAdd_32s, nmppsAdd_32s, 
		BUFFER BUFFER BUFFER U32,
	    "");
#endif 


#ifdef RPC_nmppsFFT256Fwd
AURA_METHOD(rpc_nmppsFFT256Fwd, nmppsFFT256Fwd, 
	    BIN(2048), 
	    BIN(2048));
#endif 




struct aura_object g_aura_eof;
