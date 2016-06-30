#include "rpc-host.h"
#include "nmtype.h"



int nmppsCmpLtC_16s (const nm16s* src,  int16b  nCmpVal, nm16s* dst,  int size)
{
	RPC_HOST_PIPI("nmppsCmpLtC_16s",src,nCmpVal,dst,size,2);
	return 0;
}


int nmppsCmpLtC_16s8um(const nm16s* src,  int16b  nCmpVal, nm8u* dst,  int size, struct NmppsTmpSpec* spec)
{
	int ret;	
	struct aura_buffer *iobuf_src = aura_buffer_request(n, size*2);	
	struct aura_buffer *iobuf_dst = aura_buffer_request(n, size*1);	
	memcpy(iobuf_src->data,src,size*2);	
	struct aura_buffer *retbuf; 
	ret = aura_call(n, "nmppsCmpLtC_16s8um", &retbuf,  iobuf_src, nCmpVal, iobuf_dst, size); 
	if (ret != 0) {
		printf ("bug = %d\r\n",ret);
		BUG(n, "Call:nmppsCmpLtC_16s8um failed!"); 
	}
	memcpy(dst,iobuf_dst->data,size); 
	aura_buffer_release( iobuf_dst); 
	aura_buffer_release( iobuf_src);
	aura_buffer_release( retbuf); 
	slog(3, SLOG_INFO, "ARM: Call nmppsCmpLtC_16s8um -ok"); 
	return 0;
}
