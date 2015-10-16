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
//#include "vec.h"
//#include "tnmvector.h"
//#include "tnmmatrix.h"
#include "nmtype.h"
#include "nmtl.h"
/////////////////////////////////////////////////////////////////////////////////////////
// Multiplying 32-bit mtr  by vec of 8 shorts
void MTR_ProdV(
		nm8s*		pSrcMtr,
		nm64s*		pSrcVec,
			nm64s*		pDstVec,
			int			nHeight,	
			int			nWidth
		)

{
	nmmtr8s SrcMtr((nm8s*)pSrcMtr,nHeight,nWidth);
	nmvec64s SrcVec((nm64s*)pSrcVec,nWidth);
	nmvec64s DstVec((nm64s*)pDstVec,nHeight);
	DstVec=SrcMtr*SrcVec;
}

void MTR_ProdV(
		nm16s*		pSrcMtr,
		nm64s*		pSrcVec,
			nm64s*		pDstVec,
			int			nHeight,	
			int			nWidth
		)

{
	nmmtr16s SrcMtr((nm16s*)pSrcMtr,nHeight,nWidth);
	nmvec64s SrcVec((nm64s*)pSrcVec,nWidth);
	nmvec64s DstVec((nm64s*)pDstVec,nHeight);
	DstVec=SrcMtr*SrcVec;
}

void MTR_ProdV(
		nm32s*		pSrcMtr,
		nm64s*		pSrcVec,
			nm64s*		pDstVec,
			int			nHeight,	
			int			nWidth
		)

{
	nmmtr32s SrcMtr((nm32s*)pSrcMtr,nHeight,nWidth);
	nmvec64s SrcVec((nm64s*)pSrcVec,nWidth);
	nmvec64s DstVec((nm64s*)pDstVec,nHeight);
	DstVec=SrcMtr*SrcVec;
}

void MTR_ProdV(
		v8nm8s*		pSrcMtr,
		v8nm16s*		pSrcVec,
			nm16s*		pDstVec,
			int			nHeight
		)

{
	nmmtr8s SrcMtr((nm8s*)pSrcMtr,nHeight,8);
	nmvec16s SrcVec((nm16s*)pSrcVec,8);
	nmvec16s DstVec((nm16s*)pDstVec,nHeight);
	DstVec=SrcMtr*SrcVec;
}

void MTR_ProdV(
		v8nm16s*		pSrcMtr,
		v8nm16s*		pSrcVec,
			nm16s*		pDstVec,
			int			nHeight
		)

{
	nmmtr16s SrcMtr((nm16s*)pSrcMtr,nHeight,8);
	nmvec16s SrcVec((nm16s*)pSrcVec,8);
	nmvec16s DstVec((nm16s*)pDstVec,nHeight);
	DstVec=SrcMtr*SrcVec;
}


void MTR_ProdV( nm64sc *pSrcMtr,  nm64sc *pSrcVec, nm64sc *pDstVec, int Height, int Width, void*tmp)
{
	int i,j;
	for(i=0;i<Height;i++)
	{
		pDstVec[i].re = 0;
		pDstVec[i].im = 0;
		for(j=0;j<Width;j++)
		{
//			if(IsMultOverflow(&pSrcMtr[i*Width+j].re, &pSrcVec[j].re))
//				printf("MTR_ProdV overflow(r1, r2)\n");
			pDstVec[i].re += (pSrcMtr[i*Width+j].re * pSrcVec[j].re - pSrcMtr[i*Width+j].im * pSrcVec[j].im);
			pDstVec[i].im += (pSrcMtr[i*Width+j].re * pSrcVec[j].im + pSrcMtr[i*Width+j].im * pSrcVec[j].re);
		}
	}
}

void MTR_ProdV_Zero( nm64sc *pSrcMtr,  nm64sc *pSrcVec, nm64sc *pDstVec, int nStart, int nQuantity, int Height, int Width, void*tmp)
{
	int i,j;
	for(i=0;i<Height;i++)
	{
		pDstVec[i].re = 0;
		pDstVec[i].im = 0;
		for(j=0;j<nQuantity;j++)
		{
//			if(IsMultOverflow(&pSrcMtr[i*Width+j+nStart].re, &pSrcVec[j].re))
//				printf("MTR_ProdV_Zero overflow(r1, r2)\n");
//			if(IsMultOverflow(&pSrcMtr[i*Width+j+nStart].im, &pSrcVec[j].im))
//				printf("MTR_ProdV_Zero overflow(c1, c2)\n");
			pDstVec[i].re += (pSrcMtr[i*Width+j+nStart].re * pSrcVec[j].re - pSrcMtr[i*Width+j+nStart].im * pSrcVec[j].im);
//			if(IsMultOverflow(&pSrcMtr[i*Width+j+nStart].re, &pSrcVec[j].im))
//				printf("MTR_ProdV_Zero overflow(r1, c2)\n");
//			if(IsMultOverflow(&pSrcMtr[i*Width+j+nStart].im, &pSrcVec[j].re))
//				printf("MTR_ProdV_Zero overflow(c1, r2)\n");
			pDstVec[i].im += (pSrcMtr[i*Width+j+nStart].re * pSrcVec[j].im + pSrcMtr[i*Width+j+nStart].im * pSrcVec[j].re);
		}
	}
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
//					printf("MTR_ProdM overflow(r1, r2)\n");
			#endif
			pDstMtr[i*nSize+j].re = (+ pSrcVec[i].re * pSrcVec[j].re + pSrcVec[i].im * pSrcVec[j].im);
			pDstMtr[i*nSize+j].im = (- pSrcVec[i].re * pSrcVec[j].im + pSrcVec[i].im * pSrcVec[j].re);
		}
	}
}

void MTR_ProdV_AddC(v2nm32s* pSrcMtr, v2nm32s* pSrcVec, int nAddVal, nm32s* pDstVec, int nHeight)
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