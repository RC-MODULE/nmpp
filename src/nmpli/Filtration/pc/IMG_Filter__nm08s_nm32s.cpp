//------------------------------------------------------------------------
//
//  $Workfile:: IMG_Filter_8s8s.cpp             $
//
//  <�������� ����������>
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/02/10 12:36:40 $
//
//! \if file_doc
//!
//! \file   IMG_Filter_8s8s.cpp
//! \author S. Mushkaev
//! \brief  <������� ��������>
//!
//! \endif
//!
//------------------------------------------------------------------------

#include "nmpli.h"
#include "nmtl.h"


void IMG_Filter( nm8s * pSrcImg, nm32s* pDstImg, int nWidth, int nHeight, nm64s* pKernel)
{
	S_IMG_FilterKernel* psKernel=(S_IMG_FilterKernel*) pKernel;
	int nKerWidth =psKernel->nKerWidth;
	int nKerHeight=psKernel->nKerHeight;
	
	//int nKerWidth =((nm32s*)pKernel)[0];
	//int nKerHeight=((nm32s*)pKernel)[1];

	mtr<nm32s> mDst(pDstImg,nHeight,nWidth,nWidth);
	mtr<nm32s> mKer(nKerHeight,nKerWidth);
	mtr<nm32s> mDstWxH(nKerHeight,nKerWidth);

	for(int i=0;i <nKerHeight*nKerWidth; i++)
		//mKer.m_data[i]=((nm32s*)pKernel)[2+i];
		mKer.m_data[i]=psKernel->pWeightMatrix[i];

	for(int y=0; y<nHeight; y++){
        for(int x=0; x<nWidth; x++){
			mtr<nm8s> mSrcWxH(pSrcImg+(y-(nKerHeight>>1))*nWidth+x-(nKerWidth>>1),nKerHeight,nKerWidth,nWidth);
			DotMul(mSrcWxH,mKer,mDstWxH);
			nm32s Sum;
			GetSum(mDstWxH,Sum);
			mDst[y][x]=Sum;
        }
	}
}

