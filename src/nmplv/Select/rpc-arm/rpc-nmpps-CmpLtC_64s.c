#include "rpc-host.h"
#include "nmtype.h"

int nmppsCmpLtC_64s (const nm64s* pSrcVec,  int64b  nCmpVal, nm64s* pDstVec,  int nSize, Tmp2BuffSpec *pspec)
{
	RPC_HOST_PLPI("nmppsCmpLtC_64s",pSrcVec,nCmpVal,pDstVec,nSize,8,8);
	return 0;
}


int nmppsCmpLtC_64s8um(const nm64s* src,  int64b  nCmpVal, nm8u* dst,  int size,  struct NmppsTmpSpec* spec)
{
	int ret;	
	struct aura_buffer *iobuf_src = aura_buffer_request(n, size*8);	
	struct aura_buffer *iobuf_dst = aura_buffer_request(n, size*1);	
	memcpy(iobuf_src->data,src,size*8);	
	struct aura_buffer *retbuf; 
	ret = aura_call(n, "nmppsCmpLtC_64s8u", &retbuf,  iobuf_src, nCmpVal, iobuf_dst, size); 
	if (ret != 0) {
		BUG(n, "Call:nmppsCmpLtC_64s8u failed!"); 
	}
	memcpy(dst,iobuf_dst->data,size); 
	aura_buffer_release( iobuf_dst); 
	aura_buffer_release( iobuf_src);
	aura_buffer_release( retbuf); 
	slog(0, SLOG_INFO, "ARM: Call nmppsCmpLtC_64s8u -ok"); 
	
	return 0;
}