//------------------------------------------------------------------------
//
//  $Workfile:: ResampleDown2_C.cp $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/01/12 14:09:07 $
//
//! \if file_doc
//!
//! \file   ResampleDown2_C.cpp
//! \author Сергей Мушкаев
//! \brief  Функции изменения размеров для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------

#include "nmpls.h"
//#include "nmpp.h"
#include "nmplv/vInit.h"
#include "nmpls/sResample.h"
/////////////////////////////////////////////////////////////////////////////////////////

//!
//! \perfinclude _SIG_ResampleDown2__FPUcPUsPvi.html
//!
void nmppsResampleDown2_8u16u(
		nm8u*			pSrcVec,	// input buffer		:long Local	[h*w/8]
		nm16u*			pDstVec,	// output buffer	:long Global[h*w/16]
		void*			pTmpBuf,	// output buffer	:long Global[h*w/4]	
		int				nSize		// lenght
		)
{
    nmppsConvert_8s16s((nm8s*)pSrcVec,(nm16s*)pTmpBuf,nSize);
	nm64s* pKernel;
	nmppsCreateResampleDown2_16u16u(&pKernel,MEM_LOCAL);
    nmppsResampleDown2_16u16u((nm16u15b*)pTmpBuf,(nm16u15b*)pDstVec,nSize,pKernel);
}
/////////////////////////////////////////////////////////////////////////////////////////
