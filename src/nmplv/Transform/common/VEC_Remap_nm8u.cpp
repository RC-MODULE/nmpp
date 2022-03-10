//------------------------------------------------------------------------
//
//  $Workfile:: Remap.cp $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:03 $
//
//! \if file_doc
//!
//! \file   Remap.cpp
//! \author Сергей Мушкаев
//! \brief  Функции перетаскивания по таблице для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------

#include "nmpp.h"

//!
//! \perfinclude _nmppsRemap__FPUcPUcPiiiPvPv_.html
//! 


void nmppsRemap_8u(nm8u* pSrcVec, nm8u* pDstVec, nm32s* pRemapTable, int nSrcVecSize, int nDstVecSize, void* pTmpBuf1, void* pTmpBuf2)


{
	nmppsConvert_8u32u((nm8u*)pSrcVec,(nm32u*)pTmpBuf1,nSrcVecSize);
	nmppsRemap_32u((nm32u*)pTmpBuf1,(nm32u*)pTmpBuf2,pRemapTable,nDstVecSize);
	nmppsConvert_32s8s((nm32s*)pTmpBuf2,(nm8s*)pDstVec,nDstVecSize);
}

