#include "rpc-host.h"
#include "nmtype.h"

int nmppsCmpLt_64s8um (nm64s* src1,nm64s* src2, nm8u* dst,  int size)
{
	int ret;	
	struct aura_buffer *iobuf_src1 = aura_buffer_request(n, size*8);	
	struct aura_buffer *iobuf_src2 = aura_buffer_request(n, size*8);	
	struct aura_buffer *iobuf_dst = aura_buffer_request(n, size*1);	
	memcpy(iobuf_src1->data,src1,size*8);	
	memcpy(iobuf_src2->data,src2,size*8);	
	struct aura_buffer *retbuf; 
	ret = aura_call(n, "nmppsCmpLt_64s8um", &retbuf,  iobuf_src1, iobuf_src2, iobuf_dst, size); 
	if (ret != 0) {
		BUG(n, "Call:nmppsCmpLt_64s8um failed!"); 
	}
	memcpy(dst,iobuf_dst->data,size); 
	aura_buffer_release( iobuf_dst); 
	aura_buffer_release( iobuf_src1);
	aura_buffer_release( iobuf_src2);
	aura_buffer_release( retbuf); 
	slog(0, SLOG_INFO, "ARM: Call nmppsCmpLt_64s8um -ok"); 

	return 0;
}