#include "rpc-host.h"
#include "nmplv.h"
#include "malloc32.h"
#include "time.h"




int nmppsCmpLt_32s8um (nm32s* src1, nm32s* src2, nm8u* dst,  int size)
{
	#ifdef RPC
		int ret;	
		struct aura_buffer *iobuf_src1 = aura_buffer_request(n, size*4);	
		struct aura_buffer *iobuf_src2 = aura_buffer_request(n, size*4);	
		struct aura_buffer *iobuf_dst  = aura_buffer_request(n, size*1);	
		memcpy(iobuf_src1->data,src1,size*4);	
		memcpy(iobuf_src2->data,src2,size*4);	
		struct aura_buffer *retbuf; 
		ret = aura_call(n, "nmppsCmpLt_32s8um", &retbuf,  iobuf_src1,  iobuf_src2, iobuf_dst, size); 
		if (ret != 0) {
			printf ("bug = %d\r\n",ret);
			BUG(n, "Call:nmppsCmpLt_32s8um failed!"); 
		}
		memcpy(dst,iobuf_dst->data,size*1); 
		aura_buffer_release(n, iobuf_dst); 
		aura_buffer_release(n, iobuf_src2);
		aura_buffer_release(n, iobuf_src1);
		aura_buffer_release(n, retbuf); 
		slog(0, SLOG_INFO, "ARM: Call nmppsCmpLt_32s8um -ok"); 
	#else

	Tmp2BuffSpec s;
	Tmp2BuffSpec* spec=&s;
	
	spec->buffer0=nmppsMalloc_64s(size);
	spec->buffer1=nmppsMalloc_64s(size);
		
	if (nmppsMallocSuccess()){
			nmppsConvert_32s64s  ((nm32s*)src1,(nm64s*)spec->buffer0,size);
			nmppsConvert_32s64s  ((nm32s*)src2,(nm64s*)spec->buffer1,size);
			nmppsCmpLt_64s       ((nm64s*)spec->buffer0,(nm64s*)spec->buffer1,(nm64s*)spec->buffer1,size);
			nmppsConvert_64s16s  ((nm64s*)spec->buffer1,(nm16s*) spec->buffer0,size);
			nmppsConvert_16s8s   ((nm16s*)spec->buffer0,(nm8s*) spec->buffer1,size);
			nmppsSubCRev_8s      ((nm8s*)spec->buffer1,0,(nm8s*)dst,size);
		}
	
	nmppsFree(spec->buffer0);
	nmppsFree(spec->buffer1);
	
	#endif
	
	
	return 0;
}