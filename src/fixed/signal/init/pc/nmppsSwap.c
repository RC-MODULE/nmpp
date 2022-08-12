//------------------------------------------------------------------------
//
//  $Workfile:: Access.cp $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:15 $
//
//! \if file_doc
//!
//! \file   Access.cpp
//! \author Сергей Мушкаев
//! \brief  Функции доступа для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------
#include "nmpp.h"

/////////////////////////////////////////////////////////////////////////////////
//  Swap of two vectors
void nmppsSwap_64s(nm64s*		pSrcVec1,		// input buffer		:long Long[...]
		nm64s*		pSrcVec2,		// output buffer	:long Long[DstVecSize>>3]	
		int				nSize	// buffer size in 8-bit elemetns	:[0,8,16,24...]
		)
{
	__int64 buff;
	int i;
	for (i=0;i<nSize;i++)
	{
		buff=pSrcVec1[i];
		pSrcVec1[i]=pSrcVec2[i];
		pSrcVec2[i]=buff;
	}
}
