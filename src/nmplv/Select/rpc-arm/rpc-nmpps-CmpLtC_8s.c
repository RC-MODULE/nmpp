#include "rpc-host.h"
#include "nmtype.h"
int nmppsCmpLtC_8s (const nm8s* pSrcVec,  int8b  nCmpVal, nm8s* pDstVec,  int nSize)
{
	RPC_HOST_PIPI("nmppsCmpLtC_8s",pSrcVec,nCmpVal,pDstVec,nSize,1);
	return 0;
}

	
int nmppsCmpLtC_8s8um (const nm8s* src,  int32b  nCmpVal, nm8u* dst,  int size, struct NmppsTmpSpec* spec)
{
	int ret;	
	struct aura_buffer *iobuf_src = aura_buffer_request(n, size*1);	
	struct aura_buffer *iobuf_dst = aura_buffer_request(n, size*1);	
	memcpy(iobuf_src->data,src,size*1);	
	struct aura_buffer *retbuf; 
	ret = aura_call(n, "nmppsCmpLtC_8s8u", &retbuf,  iobuf_src, nCmpVal, iobuf_dst, size); 
	if (ret != 0) {
		BUG(n, "Call:nmppsCmpLtC_8s8u failed!"); 
	}
	memcpy(dst,iobuf_dst->data,size); 
	aura_buffer_release( iobuf_dst); 
	aura_buffer_release( iobuf_src);
	aura_buffer_release( retbuf); 
	slog(0, SLOG_INFO, "ARM: Call nmppsCmpLtC_8s8u -ok"); 
	return 0;
}	