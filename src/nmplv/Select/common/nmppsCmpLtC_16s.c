#include "rpc-host.h"
#include "nmplv.h"
#include "malloc32.h"
#include "time.h"
#include "stdio.h"


int nmppsCmpLtC_16s (nm16s* src,  int16b  nCmpVal, nm16s* dst,  int size, Tmp2BuffSpec *pspec)
{
	#ifdef RPC
	RPC_HOST_PIPI("nmppsCmpLtC_16s",src,nCmpVal,dst,size,2);
	#else

	Tmp2BuffSpec s;
	Tmp2BuffSpec* spec=&s;
	
	spec->buffer0=nmppsMalloc_32s(size);
	spec->buffer1=nmppsMalloc_32s(size);
		
	if (nmppsMallocSuccess()){
		nmppsConvert_16s32s (src, (nm32s*)spec->buffer0, size);
		nmppsCmpLtC_32s31b ((nm32s*)spec->buffer0,nCmpVal,(nm32s*)spec->buffer1,size);
		nmppsConvert_32s16s ((nm32s*)spec->buffer1,dst,size);
	}
	
	nmppsFree(spec->buffer0);
	nmppsFree(spec->buffer1);
	
	#endif
	
	return 0;
}


int nmppsCmpLtC_16s8u (nm16s* src,  int16b  nCmpVal, nm8u* dst,  int size)
{
	#ifdef RPC
		int ret;	
		struct aura_buffer *iobuf_src = aura_buffer_request(n, size*2);	
		struct aura_buffer *iobuf_dst = aura_buffer_request(n, size*1);	
		memcpy(iobuf_src->data,src,size*2);	
		struct aura_buffer *retbuf; 
		ret = aura_call(n, "nmppsCmpLtC_16s8u", &retbuf,  iobuf_src, nCmpVal, iobuf_dst, size); 
		if (ret != 0) {
			printf ("bug = %d\r\n",ret);
			BUG(n, "Call:nmppsCmpLtC_16s8u failed!"); 
		}
		memcpy(dst,iobuf_dst->data,size); 
		aura_buffer_release(n, iobuf_dst); 
		aura_buffer_release(n, iobuf_src);
		aura_buffer_release(n, retbuf); 
		slog(0, SLOG_INFO, "ARM: Call nmppsCmpLtC_16s8u -ok"); 
	#else

		Tmp2BuffSpec s;
		Tmp2BuffSpec* spec=&s;
		
		spec->buffer0=nmppsMalloc_32s(size);
		spec->buffer1=nmppsMalloc_32s(size);

		if (nmppsMallocSuccess()){
			nmppsConvert_16s32s (src, (nm32s*)spec->buffer0, size);
			nmppsCmpLtC_32s31b ((nm32s*)spec->buffer0,nCmpVal,(nm32s*)spec->buffer1,size);
			nmppsConvert_32s8s ((nm32s*)spec->buffer1,(nm8s*)spec->buffer0,size);
			nmppsSubCRev_8s    ((nm8s*)spec->buffer0,0,(nm8s*)dst,size);
		}
		
		nmppsFree(spec->buffer0);
		nmppsFree(spec->buffer1);
	
	#endif
	
	return 0;
}
