#include "rpc-host.h"
#include "nmplv.h"
#include "malloc32.h"
#include "time.h"
#include "stdio.h"


int nmppsCmpNeC_16s8u (nm16s* src,  int16b  nCmpVal, nm8u* dst,  int size)
{
	#ifdef RPC
		int ret;	
		struct aura_buffer *iobuf_src = aura_buffer_request(n, size*2);	
		struct aura_buffer *iobuf_dst = aura_buffer_request(n, size*1);	
		memcpy(iobuf_src->data,src,size*2);	
		struct aura_buffer *retbuf; 
		ret = aura_call(n, "nmppsCmpNeC_16s8u", &retbuf,  iobuf_src, nCmpVal, iobuf_dst, size); 
		if (ret != 0) {
			printf ("bug = %d\r\n",ret);
			BUG(n, "Call:nmppsCmpNeC_16s8u failed!"); 
		}
		memcpy(dst,iobuf_dst->data,size); 
		aura_buffer_release( iobuf_dst); 
		aura_buffer_release( iobuf_src);
		aura_buffer_release( retbuf); 
		slog(0, SLOG_INFO, "ARM: Call nmppsCmpNeC_16s8u -ok"); 
	#else

		Tmp2BuffSpec s;
		Tmp2BuffSpec* spec=&s;
		
		spec->buffer0=nmppsMalloc_16s(size);
		spec->buffer1=nmppsMalloc_8s(size);
				
		if (nmppsMallocSuccess()){
			nmppsCmpNeC_16s    ((nm16s*)src,nCmpVal,(nm16s*) spec->buffer0,size);
			nmppsConvert_16s8s ((nm16s*)spec->buffer0,(nm8s*)spec->buffer1,size);
			nmppsSubCRev_8s    ((nm8s*)spec->buffer1,0,(nm8s*)dst,size);
		}
		
		nmppsFree(spec->buffer0);
		nmppsFree(spec->buffer1);

	
	#endif
	
	return 0;
}
