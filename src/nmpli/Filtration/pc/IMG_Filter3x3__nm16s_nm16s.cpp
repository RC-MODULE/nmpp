//------------------------------------------------------------------------
//
//  $Workfile:: Filter3x3.cp $
//
//  Библиотека обработки изображений
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/02/10 12:36:40 $
//
//! \if file_doc
//!
//! \file   Convert16_WxH.cpp
//! \author S. Mushkaev
//! \brief  Функции векторного ядра.
//! 
//! \endif
//!
//------------------------------------------------------------------------

#include "nmpli.h"
#include "nmtl.h"

void IMG_SetFilter3x3_8s16s(  nm32s * weightsMask,nm64s* pKernel)
{
	memcpy(pKernel, weightsMask, 3*3*sizeof(int));
}

void IMG_SetFilter3x3_8s16s(  nm16s * weightsMask,nm64s* pKernel)
{
	memcpy(pKernel, weightsMask, 3*3*sizeof(short));
}



void IMG_Filter3x3(  nm16s * pSrc, int nSrcStride, nm32s *pDst,  int nDstStride, int nWidth, int nHeight ,nm64s* pKernel)
{
	nmmtr32s mDst(pDst,nHeight,nWidth,nDstStride);
	nmmtr32s mKernel((nm32s*)pKernel,3,3);
	nmmtr32s mDst3x3(3,3);

	for(int y=0; y<nHeight; y++)
        for(int x=0; x<nWidth; x++)
		{
			nmmtr16s mSrc3x3(pSrc+(y-1)*nSrcStride+x-1,3,3,nSrcStride);
			DotMul(mSrc3x3,mKernel,mDst3x3);
			GetSum(mDst3x3,mDst[y][x]);
        }
}


void IMG_Filter3x3(  nm8s * pSrc, int nSrcStride, nm16s *pDst,  int nDstStride, int nWidth, int nHeight, nm64s* pKernel)
{
	nmmtr16s mDst(pDst,nHeight,nWidth,nDstStride);
	nmmtr16s mKernel((nm16s*)pKernel,3,3);
	nmmtr16s mDst3x3(3,3);

	for(int y=0; y<nHeight; y++)
        for(int x=0; x<nWidth; x++)
		{
			nmmtr8s mSrc3x3(pSrc+(y-1)*nSrcStride+x-1,3,3,nSrcStride);
			DotMul(mSrc3x3,mKernel,mDst3x3);
			GetSum(mDst3x3,mDst[y][x]);
        }
}

void IMG_Filter3x3(  nm16s * pSrc, int nSrcStride, nm16s *pDst,  int nDstStride, int nWidth, int nHeight , nm64s* pKernel)
{
	nmmtr16s mDst(pDst,nHeight,nWidth,nDstStride);
	nmmtr16s mKernel((nm16s*)pKernel,3,3);
	nmmtr16s mDst3x3(3,3);

	for(int y=0; y<nHeight; y++)
        for(int x=0; x<nWidth; x++)
		{
			nmmtr16s mSrc3x3(pSrc+(y-1)*nSrcStride+x-1,3,3,nSrcStride);
			DotMul(mSrc3x3,mKernel,mDst3x3);
			GetSum(mDst3x3,mDst[y][x]);
        }
}
