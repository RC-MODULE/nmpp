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
#include "rpc-host.h"
#include "nmtype.h"

#ifdef RPC
extern "C" {
#else

#include "nmtl/tmatrix.h"
#include "nmtl/tnmmtr.h"

#endif





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
	#ifdef RPC
	RPC_HOST_PPPII("nmppmMul_mv_8s64s",pSrcMtr,pSrcVec,pDstVec,nHeight,nWidth,1,8);
	//RPC_HOST_PIIPPI("nmppmMul_mm_16s16s",pSrcMtr,nHeight, nWidth, pSrcMtr,pDstVec,nWidth,2,2);
	#else
	nmmtr8s SrcMtr((nm8s*)pSrcMtr,nHeight,nWidth);
	nmvec64s SrcVec((nm64s*)pSrcVec,nWidth);
	nmvec64s DstVec((nm64s*)pDstVec,nHeight);
	DstVec=SrcMtr*SrcVec;
	#endif	
}

void nmppmMul_mv_16s64s(
		nm16s*		pSrcMtr,
		nm64s*		pSrcVec,
			nm64s*		pDstVec,
			int			nHeight,	
			int			nWidth
		)

{
	#ifdef RPC
	RPC_HOST_PPPII("nmppmMul_mv_16s64s",pSrcMtr,pSrcVec,pDstVec,nHeight,nWidth,2,8);
	#else
	nmmtr16s SrcMtr((nm16s*)pSrcMtr,nHeight,nWidth);
	nmvec64s SrcVec((nm64s*)pSrcVec,nWidth);
	nmvec64s DstVec((nm64s*)pDstVec,nHeight);
	DstVec=SrcMtr*SrcVec;
	#endif	
	
	
}

void nmppmMul_mv_32s64s(
		nm32s*		pSrcMtr,
		nm64s*		pSrcVec,
			nm64s*		pDstVec,
			int			nHeight,	
			int			nWidth
		)

{
	#ifdef RPC
	RPC_HOST_PPPII("nmppmMul_mv_32s64s",pSrcMtr,pSrcVec,pDstVec,nHeight,nWidth,4,8);
	#else
	nmmtr32s SrcMtr((nm32s*)pSrcMtr,nHeight,nWidth);
	nmvec64s SrcVec((nm64s*)pSrcVec,nWidth);
	nmvec64s DstVec((nm64s*)pDstVec,nHeight);
	DstVec=SrcMtr*SrcVec;
	#endif	
}

void MTR_ProdSelfV( nm64sc *pSrcVec, nm64sc *pDstMtr, int nSize, void* pTmp)
{
	int i,j;
	for(i=0;i<nSize;i++)
	{
		for(j=0;j<nSize;j++)
		{
			#ifdef FLOAT_BASE
			#else
//				if(IsMultOverflow(&pSrcVec[i].re, &pSrcVec[j].re))
//					printf("nmppmMul_mm_ overflow(r1, r2)\n");
			#endif
			pDstMtr[i*nSize+j].re = (+ pSrcVec[i].re * pSrcVec[j].re + pSrcVec[i].im * pSrcVec[j].im);
			pDstMtr[i*nSize+j].im = (- pSrcVec[i].re * pSrcVec[j].im + pSrcVec[i].im * pSrcVec[j].re);
		}
	}
}


/*
void nmppmMul_mv_AddC_32s(v2nm32s* pSrcMtr, v2nm32s* pSrcVec, int nAddVal, nm32s* pDstVec, int nHeight)
{
	nmmtr32s SrcMtr((nm32s*)pSrcMtr,nHeight,2);
	nmvec32s SrcVec((nm32s*)pSrcVec,2);
	nmvec32s DstVec((nm32s*)pDstVec,nHeight);
	

	DstVec=SrcMtr*SrcVec;
	for(int i=0; i<nHeight; i++)
		DstVec[i]+=nAddVal;
	

//    int i,j;
//    for(i=0, j=0; i<nHeight; i++, j+=2)
//    {
//        pDstVec[i] = pSrcMtr[j] * pSrcVec2[0] + 
//                     pSrcMtr[j+1] * pSrcVec2[1] + nAddVal;
//    }
}
*/

#ifdef RPC
};
#endif