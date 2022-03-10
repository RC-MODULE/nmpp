//------------------------------------------------------------------------
//
//  $Workfile:: mtrAccess.cp $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/01/12 14:05:15 $
//
//! \if file_doc
//!
//! \file   mtrAccess.cpp
//! \author Сергей Мушкаев
//! \brief  Функции доступа к элементам матрицы.
//!
//! \endif
//!
//------------------------------------------------------------------------
//#include "crtdbg2.h"
#include "nmtype.h"

void MTR_GetM(
   			nm8s*	SrcMtr,
			int		nSrcStride,
			int		nSrcRowIndex,
			int		nSrcOffset,
			nm8s*	DstMtr,
			int		nDstHeight,
			int		nDstWidth
			)
{
//	_ASSERTE(nSrcRows>0);
//	ASSERTE(nSrcStride>0);
//	ASSERTE(nDstHeight>0);
//	ASSERTE(nDstWidth>0);

	nSrcStride>>=2;
	for(int row=nSrcRowIndex,r=0;r<nDstHeight;row++,r++)
		for(int col=nSrcOffset,c=0;c<nDstWidth;col++,c++)
			DstMtr[r*nDstWidth+c]=SrcMtr[row*nSrcStride+col];
}


void MTR_GetCol( nm64sc *pSrcMtr, nm64sc *pDstVec, int nCol, int nHeight, int nWidth)
{
	int i;
	for(i=0;i<nHeight;i++)
		pDstVec[i] = pSrcMtr[i*nWidth+nCol];
}

void MTR_GetCol( nm16sc *pSrcMtr, nm16sc *pDstVec, int nCol, int nHeight, int nWidth)
{
	int i;
	for(i=0;i<nHeight;i++)
		pDstVec[i] = pSrcMtr[i*nWidth+nCol];
}
