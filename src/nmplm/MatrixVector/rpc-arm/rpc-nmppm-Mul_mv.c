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

