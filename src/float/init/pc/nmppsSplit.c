//------------------------------------------------------------------------
//
//  $Workfile:: pcConvert.cp $
//
//  ��������-��������� ����������
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:15 $
//
//! \if file_doc
//!
//! \file   pcConvert.cpp
//! \author ������ �������
//! \brief  ������� ��� �������������� ������������ ������.
//!
//! \endif
//!
//------------------------------------------------------------------------
//#include "vec.h"
#include "nmpp.h"
//*****************************************************************************

void nmppsSplit_32fcr(const nm32fcr* pSrcVec, nm32fcr* pDstVec1, nm32fcr* pDstVec2, int sizeSrc)
{
	int i;
	for (i = 0; i < sizeSrc / 2; i++) {
		pDstVec1[i].re = pSrcVec[2 * i].re;
		pDstVec1[i].im = pSrcVec[2 * i].im;
		pDstVec2[i].re = pSrcVec[2 * i + 1].re;
		pDstVec2[i].im = pSrcVec[2 * i + 1].im;
	}
}