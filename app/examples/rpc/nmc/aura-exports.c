#include <easynmc/easynmc.h>
#include <easynmc/aura-exportfile.h>




AURA_METHOD(rpc_nmppsAbs_32s, nmppsAbs_32s, 
	    BUFFER BUFFER U32,
	    ""
	    );

AURA_METHOD(rpc_nmppsAdd_32s, nmppsAdd_32s, 
		BUFFER BUFFER BUFFER U32,
	    ""
		);


AURA_METHOD(rpc_nmppsFFT256Fwd, nmppsFFT256Fwd, 
	    BIN(2048), 
	    BIN(2048));





struct aura_object g_aura_eof;
