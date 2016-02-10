#include "rpc-host.h"
#include "nmplv.h"
#include "malloc32.h"
#include "time.h"


int nmppsCmpLtC_32s (nm32s* pSrcVec,  int32b  nCmpVal, nm32s* pDstVec,  int nSize, Tmp2BuffSpec *pspec)
{
	#ifdef RPC
	RPC_HOST_PIPI("nmppsCmpLtC_32s",pSrcVec,nCmpVal,pDstVec,nSize,4);
	#else

	Tmp2BuffSpec s;
	Tmp2BuffSpec* spec=&s;
	
	spec->buffer0=nmppsMalloc_64s(nSize);
	spec->buffer1=nmppsMalloc_64s(nSize);
		
	if (nmppsMallocSuccess()){
		nmppsConvert_32s64s (pSrcVec, (nm64s*)spec->buffer0, nSize);
		nmppsCmpLtC_64s63b ((nm64s*)spec->buffer0,nCmpVal,(nm64s*)spec->buffer1,nSize);
		nmppsConvert_64s32s ((nm64s*)spec->buffer1,pDstVec,nSize);
	}
	
	nmppsFree(spec->buffer0);
	nmppsFree(spec->buffer1);
	
	#endif
	
	return 0;
}



int nmppsCmpLtC_32s8u (nm32s* src,  int32b  nCmpVal, nm8u* dst,  int size)
{
	#ifdef RPC
		int ret;	
		struct aura_buffer *iobuf_src = aura_buffer_request(n, size*4);	
		struct aura_buffer *iobuf_dst = aura_buffer_request(n, size*1);	
		memcpy(iobuf_src->data,src,size*4);	
		struct aura_buffer *retbuf; 
		ret = aura_call(n, "nmppsCmpLtC_32s8u", &retbuf,  iobuf_src, nCmpVal, iobuf_dst, size); 
		if (ret != 0) {
			printf ("bug = %d\r\n",ret);
			BUG(n, "Call:nmppsCmpLtC_32s8u failed!"); 
		}
		memcpy(dst,iobuf_dst->data,size); 
		aura_buffer_release(n, iobuf_dst); 
		aura_buffer_release(n, iobuf_src);
		aura_buffer_release(n, retbuf); 
		slog(0, SLOG_INFO, "ARM: Call nmppsCmpLtC_32s8u -ok"); 
	#else

		Tmp2BuffSpec s;
		Tmp2BuffSpec* spec=&s;
		
		spec->buffer0=nmppsMalloc_64s(size);
		spec->buffer1=nmppsMalloc_64s(size);
		
		if (nmppsMallocSuccess()){
			nmppsConvert_32s64s (src, (nm64s*)spec->buffer0, size);
			nmppsCmpLtC_64s63b ((nm64s*)spec->buffer0,nCmpVal,(nm64s*)spec->buffer1,size);
			nmppsConvert_64s16s ((nm64s*)spec->buffer1,(nm16s*)spec->buffer0,size);
			nmppsConvert_16s8s ((nm16s*) spec->buffer0,(nm8s*)spec->buffer1,size);
			nmppsSubCRev_8s    ((nm8s*) spec->buffer1,0,(nm8s*)dst,size);
		}
		
		nmppsFree(spec->buffer0);
		nmppsFree(spec->buffer1);
			
	#endif
	
	return 0;
}