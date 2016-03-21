#include "rpc-host.h"
#include "nmplv.h"

#include "malloc32.h"
#include "time.h"

int nmppsCmpNe_64s8um (nm64s* src1,nm64s* src2, nm8u* dst,  int size)
{
	#ifdef RPC
		int ret;	
		struct aura_buffer *iobuf_src1 = aura_buffer_request(n, size*8);	
		struct aura_buffer *iobuf_src2 = aura_buffer_request(n, size*8);	
		struct aura_buffer *iobuf_dst = aura_buffer_request(n, size*1);	
		memcpy(iobuf_src1->data,src1,size*8);	
		memcpy(iobuf_src2->data,src2,size*8);	
		struct aura_buffer *retbuf; 
		ret = aura_call(n, "nmppsCmpNe_64s8um", &retbuf,  iobuf_src1, iobuf_src2, iobuf_dst, size); 
		if (ret != 0) {
			printf ("bug = %d\r\n",ret);
			BUG(n, "Call:nmppsCmpNe_64s8um failed!"); 
		}
		memcpy(dst,iobuf_dst->data,size); 
		aura_buffer_release( iobuf_dst); 
		aura_buffer_release( iobuf_src1);
		aura_buffer_release( iobuf_src2);
		aura_buffer_release( retbuf); 
		slog(0, SLOG_INFO, "ARM: Call nmppsCmpNe_64s8um -ok"); 
	#else

		Tmp2BuffSpec s;
		Tmp2BuffSpec* spec=&s;
		
		spec->buffer0=nmppsMalloc_64s(size);
		spec->buffer1=nmppsMalloc_16s(size);
		
		if (nmppsMallocSuccess()){
			nmppsCmpNe_64s    ((nm64s*)src1,(nm64s*)src2, (nm64s*)spec->buffer0,size);
			nmppsConvert_64s16s((nm64s*)spec->buffer0,  (nm16s*)spec->buffer1,size);
			nmppsConvert_16s8s ((nm16s*)spec->buffer1,  (nm8s*) spec->buffer0,size);
			nmppsSubCRev_8s    ((nm8s*) spec->buffer0,0,(nm8s*) dst,size);
		}
		nmppsFree(spec->buffer1);		
		nmppsFree(spec->buffer0);		
		
			
	#endif
	
	return 0;
}