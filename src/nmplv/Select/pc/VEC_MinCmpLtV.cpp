//------------------------------------------------------------------------
//
//  $Workfile:: GetMin.cp $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:16 $
//
//! \if file_doc
//!
//! \file   GetMin.cpp
//! \author Сергей Мушкаев
//! \brief  Статистические функции для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------
#include "nmplv.h"

void nmppsMinCmpLtV_16s(nm16s15b *pSrcVec1, nm16s15b *pSrcVec2, nm16s15b *pDstMin, nm16s15b *pDstSignMask, int nSize)
{
	nmppsSub_16s(pSrcVec1, pSrcVec2, pDstSignMask, nSize);
	nmppsCmpLt0_16s(pDstSignMask, pDstSignMask, nSize);
	nmppsMaskV_64u((nm64u*)pSrcVec1,(nm64u*)pSrcVec2,(nm64u*)pDstSignMask,(nm64u*)pDstMin,nSize>>2);
}



