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

