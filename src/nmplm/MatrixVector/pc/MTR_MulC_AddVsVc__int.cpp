//------------------------------------------------------------------------
//
//  $Workfile:: mtrMulMN.cp $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/01/12 14:05:15 $
//
//! \if file_doc
//!
//! \file   mtrMulMN.cpp
//! \author Сергей Мушкаев
//! \brief  Функции умножения матрицы на матрицу.
//!
//! \endif
//!
//------------------------------------------------------------------------
#include "nmpp.h"


void MTR_MulC_AddVsVc_32s(
			int			MulN,
			nm32s*		SrcMtr,
			nm32s*		SrcVecStr,
			nm32s*		SrcVecCol,
			nm32s*		DstMtr,
			int			nHeight,
			int			nWidth)

{
	for(int row=0;row<nHeight;row++)
		nmppsMulC_AddV_AddC_32s(SrcMtr+row*nWidth,MulN,SrcVecStr,SrcVecCol[row],DstMtr+row*nWidth,nWidth);
}
