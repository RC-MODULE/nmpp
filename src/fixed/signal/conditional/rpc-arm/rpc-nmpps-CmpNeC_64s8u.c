#include "rpc-host.h"
#include "nmtype.h"
int nmppsCmpNeC_64s8um (const nm64s* src,  int64b  nCmpVal, nm8u* dst,  int size,  struct NmppsTmpSpec* spec)
{
	int ret;	
	struct aura_buffer *iobuf_src = aura_buffer_request(n, size*8);	
	struct aura_buffer *iobuf_dst = aura_buffer_request(n, size*1);	
	memcpy(iobuf_src->data,src,size*8);	
	struct aura_buffer *retbuf; 
	ret = aura_call(n, "nmppsCmpNeC_64s8um", &retbuf,  iobuf_src, nCmpVal, iobuf_dst, size); 
	if (ret != 0) {
		BUG(n, "Call:nmppsCmpNeC_64s8um failed!"); 
	}
	memcpy(dst,iobuf_dst->data,size); 
	aura_buffer_release( iobuf_dst); 
	aura_buffer_release( iobuf_src);
	aura_buffer_release( retbuf); 
	slog(3, SLOG_INFO, "ARM: Call nmppsCmpNeC_64s8um -ok"); 
	
	return 0;
}