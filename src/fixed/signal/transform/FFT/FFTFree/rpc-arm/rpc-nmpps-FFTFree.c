#include "fft.h"
#include "rpc-host.h"	


void nmppsFFTFree(NmppsFFTSpec* spec )
{
	int ret;	
	struct aura_buffer *retbuf; 
	ret = aura_call(n, "nmppsFFTFree", &retbuf, spec); 
	if (ret != 0) 
	    BUG(n, "Call nmppsFFTFree failed!"); 
	aura_buffer_release( retbuf); 
	slog(3, SLOG_INFO, "ARM: Call nmppsFFTFree ok"); 

}	

