#include "rpc-host.h"
#include "nmplv.h"
#include "malloc32.h"
#include "time.h"




int nmppsCmpNeC_32s8u (nm32s* src,  int32b  nCmpVal, nm8u* dst,  int size)
{
	#ifdef RPC
		int ret;	
		struct aura_buffer *iobuf_src = aura_buffer_request(n, size*4);	
		struct aura_buffer *iobuf_dst = aura_buffer_request(n, size*1);	
		memcpy(iobuf_src->data,src,size*4);	
		struct aura_buffer *retbuf; 
		ret = aura_call(n, "nmppsCmpNeC_32s8u", &retbuf,  iobuf_src, nCmpVal, iobuf_dst, size); 
		if (ret != 0) {
			printf ("bug = %d\r\n",ret);
			BUG(n, "Call:nmppsCmpNeC_32s8u failed!"); 
		}
		memcpy(dst,iobuf_dst->data,size); 
		aura_buffer_release(n, iobuf_dst); 
		aura_buffer_release(n, iobuf_src);
		aura_buffer_release(n, retbuf); 
		slog(0, SLOG_INFO, "ARM: Call nmppsCmpNeC_32s8u -ok"); 
	#else

		Tmp2BuffSpec s;
		Tmp2BuffSpec* spec=&s;
		
		spec->buffer0=nmppsMalloc_32s(size);
		spec->buffer1=nmppsMalloc_8s(size);
		
		if (nmppsMallocSuccess()){
			nmppsCmpNeC_32s    ((nm32s*)src,nCmpVal,(nm32s*)spec->buffer0,size);
			nmppsConvert_32s8s ((nm32s*)spec->buffer0,(nm8s*)spec->buffer1,size);
			nmppsSubCRev_8s    ((nm8s*) spec->buffer1,0,(nm8s*)dst,size);
		}
		
		nmppsFree(spec->buffer0);
		nmppsFree(spec->buffer1);
			
	#endif
	
	return 0;
}