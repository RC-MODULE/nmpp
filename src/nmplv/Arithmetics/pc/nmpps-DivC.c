//------------------------------------------------------------------------
//
//  $Workfile:: Div.cp $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:15 $
//
//! \if file_doc
//!
//! \file   Div.cpp
//! \author Сергей Мушкаев
//! \brief  Функции деления для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------
#include "nmtype.h"
/////////////////////////////////////////////////////////////////////////////////
void nmppsDivC_32s(
			nm32s*	pSrcVec,			// Input array 					:long Global[VecSize/2]
			int		Divisor,		// Divisor						:[1,2,..128]
			nm32s*	pDstVec,			// Output quantized array		:long Local [VecSize/2]
			int		nSize,		// Vector size in 32-bit elements:[0,2,4,6...]
			void*	TmpBufL,		// Temporary buffer on Local	:long Local [23] 
			void*	TmpBufG			// Temporary buffer	on Global	:long Local [23] 
			)
{
	int i;
	for (i=0;i<nSize;i++)
		pDstVec[i]=pSrcVec[i]/Divisor;

}

