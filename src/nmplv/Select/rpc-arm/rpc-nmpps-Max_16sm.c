#include "rpc-host.h"
#include "nmtype.h"


int nmppsMax_16sm (const nm16s*  src, int size, int16b*  pMaxValue, nm32s* tmp)
{
	int ret;	
	struct aura_buffer *iobuf_src = aura_buffer_request(n, size*2);	
	memcpy(iobuf_src->data,src,size*2);	
	struct aura_buffer *retbuf; 
	ret = aura_call(n, "nmppsMax_16sm", &retbuf,  iobuf_src, size); 
	if (ret != 0) {
		BUG(n, "Call:nmppsMax_16sm failed!"); 
	}
	*pMaxValue = aura_buffer_get_u32(retbuf);
	ret = aura_buffer_get_u32(retbuf);
	aura_buffer_release( iobuf_src);
	aura_buffer_release( retbuf); 
	slog(0, SLOG_INFO, "ARM: Call nmppsMax_16sm -ok"); 
	return ret;
}	
