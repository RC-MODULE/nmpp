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

#include "nmplv.h"

//!
//! \perfinclude _VEC_Remap__FPUcPUcPiiiPvPv.html
//! 


void VEC_Remap(nm8u* pSrcVec, nm8u* pDstVec, nm32s* pRemapTable, int nSrcVecSize, int nDstVecSize, void* pTmpBuf1, void* pTmpBuf2)


{
	VEC_Cnv((nm8u*)pSrcVec,(nm32u*)pTmpBuf1,nSrcVecSize);
	VEC_Remap  ((nm32u*)pTmpBuf1,(nm32u*)pTmpBuf2,pRemapTable,nDstVecSize);
	VEC_Cnv((nm32s*)pTmpBuf2,(nm8s*)pDstVec,nDstVecSize);
}

