#ifdef RPC
#include <aura/aura.h>
#include <ion/ion.h>
#include <memory.h>

extern struct aura_node *n;
/*
#define RPC_HOST_P(func) \
	int ret;	\
    struct aura_buffer *iobuf_src = aura_buffer_request(n, size);	\
	memcpy(iobuf_src->data,src,size);	\
	struct aura_buffer *retbuf; \
	ret = aura_call(n, func, &retbuf,  iobuf_src, iobuf_dst, size); \
	if (ret != 0) \
	    BUG(n, "Call func failed!"); \
	memcpy(dst,iobuf_dst->data,size); \
	aura_buffer_release(n, iobuf_src); \
	aura_buffer_release(n, retbuf); \
	slog(0, SLOG_INFO, "ARM: Call func ok"); 

	
#define RPC_HOST_PI(func,ptr) \
	int ret;	\
    struct aura_buffer *iobuf_src = aura_buffer_request(n, size);	\
	struct aura_buffer *iobuf_dst = aura_buffer_request(n, size);	\
	memcpy(iobuf_src->data,src,size);	\
	struct aura_buffer *retbuf; \
	ret = aura_call(n, func, &retbuf,  iobuf_src, iobuf_dst, size); \
	if (ret != 0) \
	    BUG(n, "Call func failed!"); \
	memcpy(dst,iobuf_dst->data,size*k); \
	aura_buffer_release(n, iobuf_dst); \
	aura_buffer_release(n, iobuf_src); \
	aura_buffer_release(n, retbuf); \
	slog(0, SLOG_INFO, "ARM: Call " #func " -ok"); 
*/
#define RPC_HOST_I(func, val) \
	int ret;	\
	struct aura_buffer *retbuf; \
	ret = aura_call(n, func, &retbuf, val); \
	if (ret != 0) \
	    BUG(n, "Call" #func "failed!"); \
	aura_buffer_release(n, retbuf); \
	slog(0, SLOG_INFO, "ARM: Call func ok"); 
	
#define RPC_HOST_PPI(func,src,dst,size,k) \
	int ret;	\
    struct aura_buffer *iobuf_src = aura_buffer_request(n, size*k);	\
	struct aura_buffer *iobuf_dst = aura_buffer_request(n, size*k);	\
	memcpy(iobuf_src->data,src,size*k);	\
	struct aura_buffer *retbuf; \
	ret = aura_call(n, func, &retbuf,  iobuf_src, iobuf_dst, size); \
	if (ret != 0) \
	    BUG(n, "Call " #func " failed!"); \
	memcpy(dst,iobuf_dst->data,size*k); \
	aura_buffer_release(n, iobuf_dst); \
	aura_buffer_release(n, iobuf_src); \
	aura_buffer_release(n, retbuf); \
	slog(0, SLOG_INFO, "ARM: Call " #func " -ok"); 



#define RPC_HOST_PPPI(func,src0,src1,dst,size,k) \
	int ret;	\
    struct aura_buffer *iobuf_src0 = aura_buffer_request(n, size*k);	\
	struct aura_buffer *iobuf_src1 = aura_buffer_request(n, size*k);	\
	struct aura_buffer *iobuf_dst = aura_buffer_request(n, size*k);	\
	memcpy(iobuf_src0->data,src0,size*k);	\
	memcpy(iobuf_src1->data,src1,size*k);	\
	struct aura_buffer *retbuf; \
	ret = aura_call(n, func, &retbuf,  iobuf_src0, iobuf_src1, iobuf_dst, size); \
	if (ret != 0) \
	    BUG(n, "Call " #func " failed!"); \
	memcpy(dst,iobuf_dst->data,size*k); \
	aura_buffer_release(n, iobuf_dst); \
	aura_buffer_release(n, iobuf_src1); \
	aura_buffer_release(n, iobuf_src0); \
	aura_buffer_release(n, retbuf); \
	slog(0, SLOG_INFO, "ARM: Call " #func " -ok"); 

	
#define RPC_HOST_PIPI(func,src,val,dst,size,k) \
	int ret;	\
    struct aura_buffer *iobuf_src = aura_buffer_request(n, size*k);	\
	struct aura_buffer *iobuf_dst = aura_buffer_request(n, size*k);	\
	memcpy(iobuf_src->data,src,size*k);	\
	struct aura_buffer *retbuf; \
	ret = aura_call(n, func, &retbuf,  iobuf_src, val, iobuf_dst, size); \
	if (ret != 0) \
	    BUG(n, "Call " #func " failed!"); \
	memcpy(dst,iobuf_dst->data,size*k); \
	aura_buffer_release(n, iobuf_dst); \
	aura_buffer_release(n, iobuf_src); \
	aura_buffer_release(n, retbuf); \
	slog(0, SLOG_INFO, "ARM: Call " #func " -ok"); 

#define RPC_HOST_PIR(func,src,size,res,k) \
	int ret;	\
	slog(0, SLOG_INFO, "ARM: Enter Call " #func " -ok"); \
    struct aura_buffer *iobuf_src = aura_buffer_request(n, size*k);	\
	memcpy(iobuf_src->data,src,size*k);	\
	struct aura_buffer *retbuf; \
	ret = aura_call(n, func, &retbuf,  iobuf_src, size); \
	if (ret != 0) \
	    BUG(n, "Call " #func " failed!"); \
	*res = aura_buffer_get_u32(retbuf);\
	aura_buffer_release(n, iobuf_src); \
	aura_buffer_release(n, retbuf); \
	slog(0, SLOG_INFO, "ARM: Call " #func " -ok"); 

#define RPC_HOST_PPI_I(func,src,dst,handle,ret,k) \
	int ret;	\
    struct aura_buffer *iobuf_src = aura_buffer_request(n, size*k);	\
	struct aura_buffer *iobuf_dst = aura_buffer_request(n, size*k);	\
	memcpy(iobuf_src->data,src,size*k);	\
	memcpy(iobuf_dst->data,dst,size*k);	\
	struct aura_buffer *retbuf; \
	ret = aura_call(n, func, &retbuf,  iobuf_src, iobuf_dst, handle); \
	if (ret != 0) \
	    BUG(n, "Call " #func " failed!"); \
	*res = aura_buffer_get_u32(retbuf);\
	aura_buffer_release(n, iobuf_src); \
	aura_buffer_release(n, iobuf_dst); \
	aura_buffer_release(n, retbuf); \
	slog(0, SLOG_INFO, "ARM: Call " #func " -ok"); 

	
#define RPC_HOST_PIR64(func,src,size,res,k) \
	int ret;	\
    struct aura_buffer *iobuf_src = aura_buffer_request(n, size*k);	\
	memcpy(iobuf_src->data,src,size*k);	\
	struct aura_buffer *retbuf; \
	ret = aura_call(n, func, &retbuf,  iobuf_src, size); \
	if (ret != 0) \
	    BUG(n, "Call " #func " failed!"); \
	*res = aura_buffer_get_u64(retbuf);\
	aura_buffer_release(n, iobuf_src); \
	aura_buffer_release(n, retbuf); \
	slog(0, SLOG_INFO, "ARM: Call " #func " -ok"); 
	
#endif
