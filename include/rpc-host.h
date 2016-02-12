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
	if (ret != 0) {\
		printf ("bug = %d\r\n",ret);\
		BUG(n, "Call " #func " failed!"); }\
	memcpy(dst,iobuf_dst->data,size*k); \
	aura_buffer_release(n, iobuf_dst); \
	aura_buffer_release(n, iobuf_src); \
	aura_buffer_release(n, retbuf); \
	slog(0, SLOG_INFO, "ARM: Call " #func " -ok"); 

#define RPC_HOST_PPI_R64_k0k1(func,src0,src1,size,ret,k0,k1) \
	int ret;	\
    struct aura_buffer *iobuf_src0 = aura_buffer_request(n, size*k0);	\
	struct aura_buffer *iobuf_src1 = aura_buffer_request(n, size*k1);	\
	memcpy(iobuf_src0->data,src0,size*k0);	\
	memcpy(iobuf_src1->data,src1,size*k1);	\
	struct aura_buffer *retbuf; \
	ret = aura_call(n, func, &retbuf,  iobuf_src0,iobuf_src1, size); \
	if (ret != 0) {\
		printf ("bug = %d\r\n",ret);\
		BUG(n, "Call " #func " failed!"); }\
	*res = aura_buffer_get_u32(retbuf);\
	aura_buffer_release(n, iobuf_src0); \
	aura_buffer_release(n, iobuf_src1); \
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
	if (ret != 0) {\
		printf ("bug = %d\r\n",ret);\
		BUG(n, "Call " #func " failed!"); }\
	memcpy(dst,iobuf_dst->data,size*k); \
	aura_buffer_release(n, iobuf_dst); \
	aura_buffer_release(n, iobuf_src); \
	aura_buffer_release(n, retbuf); \
	slog(0, SLOG_INFO, "ARM: Call " #func " -ok"); 

#define RPC_HOST_PLPI(func,src,val,dst,size,k) \
	int ret;	\
    struct aura_buffer *iobuf_src = aura_buffer_request(n, size*k);	\
	struct aura_buffer *iobuf_dst = aura_buffer_request(n, size*k);	\
	memcpy(iobuf_src->data,src,size*k);	\
	struct aura_buffer *retbuf; \
	ret = aura_call(n, func, &retbuf,  iobuf_src, val, iobuf_dst, size); \
	if (ret != 0) {\
		printf ("bug = %d\r\n",ret);\
		BUG(n, "Call " #func " failed!"); }\
	memcpy(dst,iobuf_dst->data,size*k); \
	aura_buffer_release(n, iobuf_dst); \
	aura_buffer_release(n, iobuf_src); \
	aura_buffer_release(n, retbuf); \
	slog(0, SLOG_INFO, "ARM: Call " #func " -ok"); 

#define RPC_HOST_PPLI(func,src,val,dst,size,k) \
	int ret;	\
    struct aura_buffer *iobuf_src = aura_buffer_request(n, size*k);	\
	struct aura_buffer *iobuf_dst = aura_buffer_request(n, size*k);	\
	memcpy(iobuf_src->data,src,size*k);	\
	struct aura_buffer *retbuf; \
	ret = aura_call(n, func, &retbuf,  iobuf_src, iobuf_dst, val, size); \
	if (ret != 0) {\
		printf ("bug = %d\r\n",ret);\
		BUG(n, "Call " #func " failed!"); }\
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
	
	//memcpy(iobuf_src1->data,pSrcMtr,nHeight*nWidth*k1);	
#define RPC_HOST_PPPII(func,pSrcMtr,pSrcVec,pDstVec,nHeight,nWidth,k1,k2) \
	int ret,i,j;	\
    struct aura_buffer *iobuf_src1 = aura_buffer_request(n, nHeight*nWidth*k1);	\
	struct aura_buffer *iobuf_src2 = aura_buffer_request(n, nWidth*k2 );	\
	struct aura_buffer *iobuf_dst  = aura_buffer_request(n, nHeight*k2);	\
	for (i = 0; i < nHeight; i++) { \
		for (j = 0; j < nWidth; j++) { \
			memcpy(iobuf_src1->data+(j + nWidth * i)*k1,pSrcMtr+(nHeight * j + i),k1); \
		} \
	} \
	memcpy(iobuf_src2->data,pSrcVec,nWidth*k2 );	\
	struct aura_buffer *retbuf; \
	ret = aura_call(n, func, &retbuf,  iobuf_src1, iobuf_src2 ,iobuf_dst, nHeight, nWidth); \
	if (ret != 0) {\
		slog(0, SLOG_ERROR, "bug = %d", ret);\
		BUG(n, "Call " #func " failed!"); } \
	memcpy(pDstVec, iobuf_dst->data, nHeight*k2);	\
	aura_buffer_release(n, iobuf_src1); \
	aura_buffer_release(n, iobuf_src2); \
	aura_buffer_release(n, iobuf_dst); \
	aura_buffer_release(n, retbuf); \
	slog(0, SLOG_INFO, "ARM: Call " #func " -ok"); 
	
	//memcpy(iobuf_src1->data,pSrcMtr1,nHeight1*nWidth1*k1);	\
	//memcpy(iobuf_src2->data,pSrcMtr2,nWidth1*nWidth2*k2 );	
	// memcpy(pDstMtr, iobuf_dst->data, nHeight1*nWidth2*k2);	
	
#define	RPC_HOST_PIIPPI(func,pSrcMtr1,nHeight1, nWidth1, pSrcMtr2,pDstMtr,nWidth2,k1,k2) \
	int ret, i, j;	\
    struct aura_buffer *iobuf_src1 = aura_buffer_request(n, nHeight1*nWidth1*k1);	\
	struct aura_buffer *iobuf_src2 = aura_buffer_request(n, nWidth1 *nWidth2*k2 );	\
	struct aura_buffer *iobuf_dst  = aura_buffer_request(n, nHeight1*nWidth2*k2);	\
	for (i = 0; i < nHeight1; i++) { \
		for (j = 0; j < nWidth1; j++) { \
			memcpy(iobuf_src1->data+(j + nWidth1 * i)*k1,pSrcMtr1+(nHeight1 * j + i),k1); \
		} \
	} \
	for (i = 0; i < nWidth1; i++) { \
		for (j = 0; j < nWidth2; j++) { \
			memcpy(iobuf_src2->data+(j + nWidth2 * i)*k2,pSrcMtr2+(nWidth1 * j + i),k2); \
		} \
	} \
	struct aura_buffer *retbuf; \
	ret = aura_call(n, func, &retbuf,  iobuf_src1, nHeight1, nWidth1, iobuf_src2 ,iobuf_dst, nWidth2); \
	if (ret != 0) {\
		slog(0, SLOG_ERROR, "bug = %d", ret);\
		BUG(n, "Call " #func " failed!"); } \
	for (i = 0; i < nWidth2; i++) { \
		for (j = 0; j < nHeight1; j++) { \
			memcpy(pDstMtr+(j + nHeight1 * i),iobuf_dst->data+(nWidth2 * j + i)*k2,k2); \
		} \
	} \
	aura_buffer_release(n, iobuf_src1); \
	aura_buffer_release(n, iobuf_src2); \
	aura_buffer_release(n, iobuf_dst); \
	aura_buffer_release(n, retbuf); \
	slog(0, SLOG_INFO, "ARM: Call " #func " -ok"); 
	
#define	RPC_HOST_PPIR64(func,srcVec0,srcVec1, size, dst,k1,k2) \
	int ret;	\
    struct aura_buffer *iobuf_src1 = aura_buffer_request(n, size*k1);	\
	struct aura_buffer *iobuf_src2 = aura_buffer_request(n, size*k2 );	\
	memcpy(iobuf_src1->data,srcVec0,size*k1);	\
	memcpy(iobuf_src2->data,srcVec1,size*k2);	\
	struct aura_buffer *retbuf; \
	ret = aura_call(n, func, &retbuf,  iobuf_src1, iobuf_src2, size); \
	if (ret != 0) {\
		slog(0, SLOG_ERROR, "bug = %d", ret);\
		BUG(n, "Call " #func " failed!"); } \
	*dst = aura_buffer_get_u64(retbuf); \
	aura_buffer_release(n, iobuf_src1); \
	aura_buffer_release(n, iobuf_src2); \
	aura_buffer_release(n, retbuf); \
	slog(0, SLOG_INFO, "ARM: Call " #func " -ok"); 

	
#endif
