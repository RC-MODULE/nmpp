//------------------------------------------------------------------------
//
//  $Workfile:: Median3x3.cp $
//
//  Библиотека обработки изображений
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/02/10 12:36:40 $
//
//! \if file_doc
//!
//! \file   Median3x3.cpp
//! \author S. Mushkaev
//! \brief  Median 3x3 filter
//! 
//! \endif
//!
//------------------------------------------------------------------------

#include "nmpli.h"
#include "nmpls.h"
#include "nmtl.h"
//#include <memory.h>
//
//template<class T> static inline void CompareSwap(T& a,T& b)
//{
//	if (a>b)
//	{
//		T t=a;
//		a=b;
//		b=t;
//	}
//}
//
//template<class T> static inline void Max(T& a,T &b)
//{
//	if (a<b)
//	{
//		a=b;
//	}
//}
//
//template<class T> static inline void Min(T& a,T &b)
//{
//	if (a>b)
//	{
//		a=b;
//	}
//}
//
//template<class T> static inline T Median9(T* pVec)
//{
//	CompareSwap(pVec[0],pVec[1]);
//	CompareSwap(pVec[3],pVec[4]);
//	CompareSwap(pVec[6],pVec[7]);
//
//	CompareSwap(pVec[1],pVec[2]);
//	CompareSwap(pVec[4],pVec[5]);
//	CompareSwap(pVec[7],pVec[8]);
//
//	CompareSwap(pVec[0],pVec[1]);
//	CompareSwap(pVec[3],pVec[4]);
//	CompareSwap(pVec[6],pVec[7]);
//
//	Max(pVec[0],pVec[3]);
//	Min(pVec[8],pVec[5]);
//
//	CompareSwap(pVec[1],pVec[4]);
//
//	Max(pVec[0],pVec[6]);
//	Min(pVec[8],pVec[8]);
//	Min(pVec[4],pVec[7]);
//	Max(pVec[4],pVec[1]);
//
//	CompareSwap(pVec[0],pVec[4]);
//	Min(pVec[4],pVec[8]);
//	Max(pVec[4],pVec[0]);
//	
//	return pVec[4];
//}
//
//nm8s SIG_Median_V9(nm8s* pVec)
//{
//	return Median9(pVec);
//}
//
//nm16s SIG_Median_V9(nm16s* pVec)
//{
//	return Median9(pVec);
//}
//
//nm32s SIG_Median_V9(nm32s* pVec)
//{
//	return Median9(pVec);
//}
//
//nm64s SIG_Median_V9(nm64s* pVec)
//{
//	return Median9(pVec);
//}

void IMG_Median3x3( nm8s7b * pSrc, nm8s7b *pDst, int nWidth, int nHeight, void* pLTmp , void* pGTmp)
{
	nmmtr8s  mSrc((nm8s*)pSrc,nHeight,nWidth);
	nmmtr8s  mDst((nm8s*)pDst,nHeight,nWidth);

	for(int row=0; row<nHeight; row++)
        for(int col=0; col<nWidth; col++)
		{
			nmmtr8s  mSrc3x3(mSrc.addr(row-1,col-1),3,3,mSrc.m_stride);
			nmmtr8s  mTmp3x3(mSrc3x3);

            //nmSrc.GetMtr(row-1,col-1,nmSrc3x3);
			
//			CompareSwap(pVec[0],pVec[1]);
//			CompareSwap(pVec[3],pVec[4]);
//			CompareSwap(pVec[6],pVec[7]);
//
//			CompareSwap(pVec[1],pVec[2]);
//			CompareSwap(pVec[4],pVec[5]);
//			CompareSwap(pVec[7],pVec[8]);
//
//			CompareSwap(pVec[0],pVec[1]);
//			CompareSwap(pVec[3],pVec[4]);
//			CompareSwap(pVec[6],pVec[7]);
//
//			Max(pVec[0],pVec[3]);
//			Min(pVec[8],pVec[5]);
//
//			CompareSwap(pVec[1],pVec[4]);
//
//			Max(pVec[0],pVec[6]);
//			Min(pVec[8],pVec[8]);
//			Min(pVec[4],pVec[7]);
//			Max(pVec[4],pVec[1]);
//
//			CompareSwap(pVec[0],pVec[4]);
//			Min(pVec[4],pVec[8]);
//			Max(pVec[4],pVec[0]);
			
//			nmDst[row][col]=pVec[4];
			mDst[row][col]=SIG_Median_V9(mTmp3x3.m_data);

        }
}
