#include "rpc-host.h"
#include "nmplv.h"

#include "malloc32.h"
#include "time.h"


int nmppsCmpLtC_64s (nm64s* pSrcVec,  int64b  nCmpVal, nm64s* pDstVec,  int nSize, Tmp2BuffSpec *pspec)
{
	#ifdef RPC
	RPC_HOST_PLPI("nmppsCmpLtC_64s",pSrcVec,nCmpVal,pDstVec,nSize,8,8);
	#else

	nmppsCmpLtC_64s63b(pSrcVec,nCmpVal,pDstVec,nSize);
	
	#endif
	
	return 0;
}


int nmppsCmpLtC_64s8u (nm64s* src,  int64b  nCmpVal, nm8u* dst,  int size)
{
	#ifdef RPC
		int ret;	
		struct aura_buffer *iobuf_src = aura_buffer_request(n, size*8);	
		struct aura_buffer *iobuf_dst = aura_buffer_request(n, size*1);	
		memcpy(iobuf_src->data,src,size*8);	
		struct aura_buffer *retbuf; 
		ret = aura_call(n, "nmppsCmpLtC_64s8u", &retbuf,  iobuf_src, nCmpVal, iobuf_dst, size); 
		if (ret != 0) {
			printf ("bug = %d\r\n",ret);
			BUG(n, "Call:nmppsCmpLtC_64s8u failed!"); 
		}
		memcpy(dst,iobuf_dst->data,size); 
		aura_buffer_release( iobuf_dst); 
		aura_buffer_release( iobuf_src);
		aura_buffer_release( retbuf); 
		slog(0, SLOG_INFO, "ARM: Call nmppsCmpLtC_64s8u -ok"); 
	#else

		Tmp2BuffSpec s;
		Tmp2BuffSpec* spec=&s;
		
		spec->buffer0=nmppsMalloc_64s(size);
		spec->buffer1=nmppsMalloc_64s(size);
		
		if (nmppsMallocSuccess()){
			nmppsCmpLtC_64s63b ((nm64s*)src,nCmpVal,(nm64s*)spec->buffer0,size);
			nmppsConvert_64s16s((nm64s*)spec->buffer0,(nm16s*)spec->buffer1,size);
			nmppsConvert_16s8s ((nm16s*)spec->buffer1,(nm8s*)spec->buffer0,size);
			nmppsSubCRev_8s    ((nm8s*) spec->buffer0,0,(nm8s*)dst,size);
		}
		nmppsFree(spec->buffer1);		
		nmppsFree(spec->buffer0);		
		
			
	#endif
	
	return 0;
}