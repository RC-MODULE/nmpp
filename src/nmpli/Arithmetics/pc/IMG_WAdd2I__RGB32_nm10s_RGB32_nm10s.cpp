//------------------------------------------------------------------------
//
//  $Workfile:: nmppiWAdd.cpp             $
//
//  <�������� ����������>
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/02/10 12:36:40 $
//
//! \if file_doc
//!
//! \file   nmppiWAdd.cpp
//! \author S. Mushkaev
//! \brief  ���������� ������������ ���� ������
//!
//! \endif
//!
//------------------------------------------------------------------------
#include "nmpli.h"

void nmppiWAdd2I(RGB32_nm10s* pSrcImg1, int nMulVal1, RGB32_nm10s* pSrcImg2, int nMulVal2, int nAddVal, RGB32_nm10s* pDstImg, int nSize)
{
	for(int i=0; i<nSize;i++)
	{
		pDstImg[i].nB=pSrcImg1[i].nB*nMulVal1+pSrcImg2[i].nB*nMulVal2+nAddVal;
		pDstImg[i].nG=pSrcImg1[i].nG*nMulVal1+pSrcImg2[i].nG*nMulVal2+nAddVal;
		pDstImg[i].nR=pSrcImg1[i].nR*nMulVal1+pSrcImg2[i].nR*nMulVal2+nAddVal;
		pDstImg[i].nA=0;
	}
}

