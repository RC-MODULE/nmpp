#include "rpc-host.h"
#include "nmtype.h"

int nmppsMax_32sm (const nm32s*  src, int size, int32b*  pMaxValue, nm64s* tmp)
{
	int ret;	
	struct aura_buffer *iobuf_src = aura_buffer_request(n, size*4);	
	memcpy(iobuf_src->data,src,size*4);	
	struct aura_buffer *retbuf; 
	ret = aura_call(n, "nmppsMax_32sm", &retbuf,  iobuf_src, size); 
	if (ret != 0) {
		BUG(n, "Call:nmppsMax_32sm failed!"); 
	}
	*pMaxValue = aura_buffer_get_u32(retbuf);
	ret = aura_buffer_get_u32(retbuf);
	aura_buffer_release( iobuf_src);
	aura_buffer_release( retbuf); 
	slog(3, SLOG_INFO, "ARM: Call nmppsMax_32sm -ok"); 
	return ret;
}	
