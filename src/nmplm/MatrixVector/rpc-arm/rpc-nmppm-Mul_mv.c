//------------------------------------------------------------------------
//
//  $Workfile:: mProdV.cpp        $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.2 $      $Date: 2005/06/23 15:15:15 $
//
//! \if file_doc
//!
//! \file   mProdV.cpp
//! \author Сергей Мушкаев
//! \brief  Функции умножения матрицы на вектор.
//!
//! \endif
//!
//------------------------------------------------------------------------
#include "nmtype.h"
#include "rpc-host.h"

#define RPC_HOST_PPPII(func,pSrcMtr,pSrcVec,pDstVec,nHeight,nWidth,k1,k2) \
	int ret,i,j;	\
    struct aura_buffer *iobuf_src1 = aura_buffer_request(n, nHeight*nWidth*k1);	\
	struct aura_buffer *iobuf_src2 = aura_buffer_request(n, nWidth*k2 );	\
	struct aura_buffer *iobuf_dst  = aura_buffer_request(n, nHeight*k2);	\
	memcpy(iobuf_src1->data,pSrcMtr,nWidth * nHeight * k1); \
	memcpy(iobuf_src2->data,pSrcVec,nWidth*k2 );	\
	struct aura_buffer *retbuf; \
	ret = aura_call(n, func, &retbuf,  iobuf_src1, iobuf_src2 ,iobuf_dst, nHeight, nWidth); \
	if (ret != 0) {\
		slog(0, SLOG_ERROR, "bug = %d", ret);\
		BUG(n, "Call " #func " failed!"); } \
	memcpy(pDstVec, iobuf_dst->data, nHeight*k2);	\
	aura_buffer_release( iobuf_src1); \
	aura_buffer_release( iobuf_src2); \
	aura_buffer_release( iobuf_dst); \
	aura_buffer_release( retbuf); \
	slog(0, SLOG_INFO, "ARM: Call " #func " -ok"); 
	
/////////////////////////////////////////////////////////////////////////////////////////
// Multiplying 32-bit mtr  by vec of 8 shorts
void nmppmMul_mv_8s64s(
		nm8s*		pSrcMtr,
		nm64s*		pSrcVec,
			nm64s*		pDstVec,
			int			nHeight,	
			int			nWidth
		)

{
	RPC_HOST_PPPII("nmppmMul_mv_8s64s",pSrcMtr,pSrcVec,pDstVec,nHeight,nWidth,1,8);
}

void nmppmMul_mv_16s64s(
		nm16s*		pSrcMtr,
		nm64s*		pSrcVec,
			nm64s*		pDstVec,
			int			nHeight,	
			int			nWidth
		)

{
	RPC_HOST_PPPII("nmppmMul_mv_16s64s",pSrcMtr,pSrcVec,pDstVec,nHeight,nWidth,2,8);
	
}

void nmppmMul_mv_32s64s(
		nm32s*		pSrcMtr,
		nm64s*		pSrcVec,
			nm64s*		pDstVec,
			int			nHeight,	
			int			nWidth
		)

{
	RPC_HOST_PPPII("nmppmMul_mv_32s64s",pSrcMtr,pSrcVec,pDstVec,nHeight,nWidth,4,8);
}

