#include "rpc-host.h"
#include "nmplv.h"
#include "malloc32.h"
#include "time.h"
int nmppsCmpLt_8s8u (nm8s* src1,nm8s* src2, nm8u* dst, int size)
{
	#ifdef RPC
		int ret;	
		printf ("ARM in nmppsCmpLt_8s8u \r\n");
		struct aura_buffer *iobuf_src1 = aura_buffer_request(n, size*1);	
		struct aura_buffer *iobuf_src2 = aura_buffer_request(n, size*1);	
		struct aura_buffer *iobuf_dst  = aura_buffer_request(n, size*1);	
		memcpy(iobuf_src1->data,src1,size*1);	
		memcpy(iobuf_src2->data,src2,size*1);	
		
		printf ("ARM in nmppsCmpLt_8s8u 2\r\n");
		
		struct aura_buffer *retbuf; 
		ret = aura_call(n, "nmppsCmpLt_8s8u", &retbuf,  iobuf_src1,  iobuf_src2, iobuf_dst, size); 
		if (ret != 0) {
			printf ("bug = %d\r\n",ret);
			BUG(n, "Call nmppsCmpLt_8s8u failed!"); 
		}
		printf ("ARM in nmppsCmpLt_8s8u 3\r\n");
		memcpy(dst,iobuf_dst->data,size); 
		printf ("ARM in nmppsCmpLt_8s8u 4\r\n");
		aura_buffer_release(n, iobuf_dst); 
		aura_buffer_release(n, iobuf_src2);
		aura_buffer_release(n, iobuf_src1);
		aura_buffer_release(n, retbuf); 
		slog(0, SLOG_INFO, "ARM: Call nmppsCmpLt_8s8u -ok"); 
	#else
		
		Tmp2BuffSpec s;
		Tmp2BuffSpec* spec=&s;
		
		spec->buffer0=nmppsMalloc_16s(size);
		spec->buffer1=nmppsMalloc_16s(size);
		
			
		if (nmppsMallocSuccess()){
			nmppsConvert_8s16s   ((nm8s*)src1,(nm16s*)spec->buffer0,size);
			nmppsConvert_8s16s   ((nm8s*)src2,(nm16s*)spec->buffer1,size);
			nmppsCmpLt_16s       ((nm16s*)spec->buffer0,(nm16s*)spec->buffer1,(nm16s*)spec->buffer1,size);
			nmppsConvert_16s8s   ((nm16s*)spec->buffer1,(nm8s*)spec->buffer0,size);
			nmppsSubCRev_8s      ((nm8s*)spec->buffer0,0,(nm8s*)dst,size);
		}
		
		nmppsFree(spec->buffer0);
		nmppsFree(spec->buffer1);
	
	#endif
	
	return 0;
}



