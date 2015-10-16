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

void VEC_MinCmpLtV (nm16s15b *pSrcVec1, nm16s15b *pSrcVec2, nm16s15b *pDstMin, nm16s15b *pDstSignMask, int nSize)
{
	VEC_SubV(pSrcVec1, pSrcVec2, pDstSignMask, nSize);
	VEC_CmpLt0(pDstSignMask, pDstSignMask, nSize);
	VEC_MaskV((nm64u*)pSrcVec1,(nm64u*)pSrcVec2,(nm64u*)pDstSignMask,(nm64u*)pDstMin,nSize>>2);
}



