//------------------------------------------------------------------------
//
//  $Workfile:: ConvertRGB32nm10u_Gray32.cpp             $
//
//  <�������� ����������>
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/02/10 12:36:40 $
//
//! \if file_doc
//!
//! \file   ConvertRGB32nm10u_Gray32.cpp
//! \author S. Mushkaev
//! \brief  �������������� �� RGB � Gray
//!
//! \endif
//!
//------------------------------------------------------------------------
#include "nmpli.h"

void nmppiRsh2(RGB32_nm10u* pSrcImg, RGB32_nm10u* pDstImg, int nSize)
{
	for (int i=0; i<nSize; i++)
	{ 
		pDstImg[i].nB= pSrcImg[i].nB>>2;
		pDstImg[i].nG= pSrcImg[i].nG>>2;
		pDstImg[i].nR= pSrcImg[i].nR>>2;
		pDstImg[i].nA= 0;
	}
}
