#include "rpc-host.h"
#include "nmtype.h"

int nmppsCmpNeC_16s8um (const nm16s* src,  int16b  nCmpVal, nm8u* dst,  int size,  struct NmppsTmpSpec* spec)
{
	int ret;	
	struct aura_buffer *iobuf_src = aura_buffer_request(n, size*2);	
	struct aura_buffer *iobuf_dst = aura_buffer_request(n, size*1);	
	memcpy(iobuf_src->data,src,size*2);	
	struct aura_buffer *retbuf; 
	ret = aura_call(n, "nmppsCmpNeC_16s8u", &retbuf,  iobuf_src, nCmpVal, iobuf_dst, size); 
	if (ret != 0) {
		BUG(n, "Call:nmppsCmpNeC_16s8u failed!"); 
	}
	memcpy(dst,iobuf_dst->data,size); 
	aura_buffer_release( iobuf_dst); 
	aura_buffer_release( iobuf_src);
	aura_buffer_release( retbuf); 
	slog(0, SLOG_INFO, "ARM: Call nmppsCmpNeC_16s8u -ok"); 
	
	return 0;
}
