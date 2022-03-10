//------------------------------------------------------------------------
//
//  $Workfile:: mProdM.cpp  $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/01/12 14:05:15 $
//
//! \if file_doc
//!
//! \file   mProdM.cpp
//! \author Сергей Мушкаев
//! \brief  Функции умножения матрицы на матрицу.
//!
//! \endif
//!
//------------------------------------------------------------------------

#include "nmtype.h"
#include "rpc-host.h"

#define	RPC_HOST_PIIPPI(func,pSrcMtr1,nHeight1, nWidth1, pSrcMtr2,pDstMtr,nWidth2,k1,k2) \
	int ret, i, j;	\
    struct aura_buffer *iobuf_src1 = aura_buffer_request(n, nHeight1*nWidth1*k1);	\
	struct aura_buffer *iobuf_src2 = aura_buffer_request(n, nWidth1 *nWidth2*k2 );	\
	struct aura_buffer *iobuf_dst  = aura_buffer_request(n, nHeight1*nWidth2*k2);	\
	memcpy(iobuf_src1->data,pSrcMtr1,nHeight1 * nWidth1*k1); \
	memcpy(iobuf_src2->data,pSrcMtr2,nWidth1  * nWidth2*k2); \
	struct aura_buffer *retbuf; \
	ret = aura_call(n, func, &retbuf,  iobuf_src1, nHeight1, nWidth1, iobuf_src2 ,iobuf_dst, nWidth2); \
	if (ret != 0) {\
		slog(0, SLOG_ERROR, "bug = %d", ret);\
		BUG(n, "Call " #func " failed!"); } \
	memcpy(pDstMtr,iobuf_dst->data, nHeight1 * nWidth2 * k2); \
	aura_buffer_release( iobuf_src1); \
	aura_buffer_release( iobuf_src2); \
	aura_buffer_release( iobuf_dst); \
	aura_buffer_release( retbuf); \
	slog(3, SLOG_INFO, "ARM: Call " #func " -ok");
	
void nmppmMul_mm_8s8s( nm8s* pSrcMtr1, int nHeight1, int nWidth1,  nm8s* pSrcMtr2, nm8s* pDstMtr, int nWidth2)
{
	RPC_HOST_PIIPPI("nmppmMul_mm_8s8s",pSrcMtr1,nHeight1, nWidth1, pSrcMtr2,pDstMtr,nWidth2,1,1);
}
void nmppmMul_mm_8s16s( nm8s* pSrcMtr1, int nHeight1, int nWidth1,  nm16s* pSrcMtr2, nm16s* pDstMtr, int nWidth2)
{
	RPC_HOST_PIIPPI("nmppmMul_mm_8s16s",pSrcMtr1,nHeight1, nWidth1, pSrcMtr2,pDstMtr,nWidth2,1,2);
}
void nmppmMul_mm_8s32s( nm8s* pSrcMtr1, int nHeight1, int nWidth1,  nm32s* pSrcMtr2, nm32s* pDstMtr, int nWidth2)
{
	RPC_HOST_PIIPPI("nmppmMul_mm_8s32s",pSrcMtr1,nHeight1, nWidth1, pSrcMtr2,pDstMtr,nWidth2,1,4);

}

void nmppmMul_mm_8s64s( nm8s* pSrcMtr1, int nHeight1, int nWidth1,  nm64s* pSrcMtr2, nm64s* pDstMtr, int nWidth2)
{
	RPC_HOST_PIIPPI("nmppmMul_mm_8s64s",pSrcMtr1,nHeight1, nWidth1, pSrcMtr2,pDstMtr,nWidth2,1,8);
}

void nmppmMul_mm_16s16s( nm16s* pSrcMtr1, int nHeight1, int nWidth1,  nm16s* pSrcMtr2, nm16s* pDstMtr, int nWidth2)
{
	RPC_HOST_PIIPPI("nmppmMul_mm_16s16s",pSrcMtr1,nHeight1, nWidth1, pSrcMtr2,pDstMtr,nWidth2,2,2);

}

void nmppmMul_mm_16s32s( nm16s* pSrcMtr1, int nHeight1, int nWidth1,  nm32s* pSrcMtr2, nm32s* pDstMtr, int nWidth2)
{
	RPC_HOST_PIIPPI("nmppmMul_mm_16s32s",pSrcMtr1,nHeight1, nWidth1, pSrcMtr2,pDstMtr,nWidth2,2,4);

	
}

void nmppmMul_mm_16s64s( nm16s* pSrcMtr1, int nHeight1, int nWidth1,  nm64s* pSrcMtr2, nm64s* pDstMtr, int nWidth2)
{
	RPC_HOST_PIIPPI("nmppmMul_mm_16s64s",pSrcMtr1,nHeight1, nWidth1, pSrcMtr2,pDstMtr,nWidth2,2,8);

}

void nmppmMul_mm_32s32s( nm32s* pSrcMtr1, int nHeight1, int nWidth1,  nm32s* pSrcMtr2, nm32s* pDstMtr, int nWidth2)
{
	RPC_HOST_PIIPPI("nmppmMul_mm_32s32s",pSrcMtr1,nHeight1, nWidth1, pSrcMtr2,pDstMtr,nWidth2,4,4);
}

void nmppmMul_mm_32s64s( nm32s* pSrcMtr1, int nHeight1, int nWidth1,  nm64s* pSrcMtr2, nm64s* pDstMtr, int nWidth2)
{
	RPC_HOST_PIIPPI("nmppmMul_mm_32s64s",pSrcMtr1,nHeight1, nWidth1, pSrcMtr2,pDstMtr,nWidth2,4,8);

}

