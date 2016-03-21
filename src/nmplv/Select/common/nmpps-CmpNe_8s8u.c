#include "rpc-host.h"
#include "nmplv.h"
#include "malloc32.h"
#include "time.h"
int nmppsCmpNe_8s8um (nm8s* src1,nm8s* src2, nm8u* dst, int size)
{
	#ifdef RPC
		int ret;	
		printf ("ARM in nmppsCmpNe_8s8um \r\n");
		struct aura_buffer *iobuf_src1 = aura_buffer_request(n, size*1);	
		struct aura_buffer *iobuf_src2 = aura_buffer_request(n, size*1);	
		struct aura_buffer *iobuf_dst  = aura_buffer_request(n, size*1);	
		memcpy(iobuf_src1->data,src1,size*1);	
		memcpy(iobuf_src2->data,src2,size*1);	
		
		printf ("ARM in nmppsCmpNe_8s8um 2\r\n");
		
		struct aura_buffer *retbuf; 
		ret = aura_call(n, "nmppsCmpNe_8s8um", &retbuf,  iobuf_src1,  iobuf_src2, iobuf_dst, size); 
		if (ret != 0) {
			printf ("bug = %d\r\n",ret);
			BUG(n, "Call nmppsCmpNe_8s8um failed!"); 
		}
		printf ("ARM in nmppsCmpNe_8s8um 3\r\n");
		memcpy(dst,iobuf_dst->data,size); 
		printf ("ARM in nmppsCmpNe_8s8um 4\r\n");
		aura_buffer_release( iobuf_dst); 
		aura_buffer_release( iobuf_src2);
		aura_buffer_release( iobuf_src1);
		aura_buffer_release( retbuf); 
		slog(0, SLOG_INFO, "ARM: Call nmppsCmpNe_8s8um -ok"); 
	#else
		
		Tmp2BuffSpec s;
		Tmp2BuffSpec* spec=&s;
		
		spec->buffer0=nmppsMalloc_8s(size);
		
			
		if (nmppsMallocSuccess()){
			
			nmppsCmpNe_8s   ((nm8s*)src1,(nm8s*)src2,(nm8s*)spec->buffer0,size);
			nmppsSubCRev_8s ((nm8s*)spec->buffer0,0,(nm8s*)dst,size);
		}
		
		nmppsFree(spec->buffer0);
	
	#endif
	
	return 0;
}



