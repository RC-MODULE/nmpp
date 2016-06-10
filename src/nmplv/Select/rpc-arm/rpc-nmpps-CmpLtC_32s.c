#include "rpc-host.h"
#include "nmtype.h"

int nmppsCmpLtC_32s (const nm32s* pSrcVec,  int32b  nCmpVal, nm32s* pDstVec,  int nSize)
{
	RPC_HOST_PIPI("nmppsCmpLtC_32s",pSrcVec,nCmpVal,pDstVec,nSize,4);
	return 0;
}



int nmppsCmpLtC_32s8um (const nm32s* src,  int32b  nCmpVal, nm8u* dst,  int size, struct NmppsTmpSpec* spec)
{
	int ret;	
	struct aura_buffer *iobuf_src = aura_buffer_request(n, size*4);	
	struct aura_buffer *iobuf_dst = aura_buffer_request(n, size*1);	
	memcpy(iobuf_src->data,src,size*4);	
	struct aura_buffer *retbuf; 
	ret = aura_call(n, "nmppsCmpLtC_32s8um", &retbuf,  iobuf_src, nCmpVal, iobuf_dst, size); 
	if (ret != 0) {
		BUG(n, "Call:nmppsCmpLtC_32s8um failed!"); 
	}
	memcpy(dst,iobuf_dst->data,size); 
	aura_buffer_release( iobuf_dst); 
	aura_buffer_release( iobuf_src);
	aura_buffer_release( retbuf); 
	slog(0, SLOG_INFO, "ARM: Call nmppsCmpLtC_32s8um -ok"); 
	
	return 0;
}