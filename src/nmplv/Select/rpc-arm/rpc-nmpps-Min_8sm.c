#include "rpc-host.h"
#include "nmtype.h"

int nmppsMin_8sm (const nm8s*  src, int size, int8b*  pMinValue, nm16s* tmp)
{
	int ret;	
	struct aura_buffer *iobuf_src = aura_buffer_request(n, size*1);	
	memcpy(iobuf_src->data,src,size*1);	
	struct aura_buffer *retbuf; 
	ret = aura_call(n, "nmppsMin_8sm", &retbuf,  iobuf_src, size); 
	if (ret != 0) {
		BUG(n, "Call:nmppsMin_8sm failed!"); 
	}
	*pMinValue = aura_buffer_get_u32(retbuf);
	ret = aura_buffer_get_u32(retbuf);
	aura_buffer_release( iobuf_src);
	aura_buffer_release( retbuf); 
	slog(3, SLOG_INFO, "ARM: Call nmppsMin_8sm -ok"); 
	return ret;
}	
