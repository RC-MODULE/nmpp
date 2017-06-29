//------------------------------------------------------------------------
//
//  $Workfile:: Mul_VxxVxx.cp $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:15 $
//
//! \if file_doc
//!
//! \file   Mul_VxxVxx.cpp
//! \author Сергей Мушкаев
//! \brief  Функции умножения для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------
#include "nmtype.h"
/////////////////////////////////////////////////////////////////////////////////////////
// Element-wise multiplication of two vectors
void nmppsMul_AddC_64s(
			const nm64s*		pSrcVec1,		// input  32-bit vec		:long -----[Size/2]
			const nm64s*		pSrcVec2,		// input  32-bit vec		:long -----[Size/2]
			const nm64s* 		pnC,
			nm64s*				pDstVec,			// output 32-bit vec		:long -----[Size/2]
			int					nSize			// size of input buffers	:nSize=[0,2,4...]
		)
{
	int i;
	for (i=0;i<nSize;i++)
		pDstVec[i]=pSrcVec1[i]*pSrcVec2[i] + *pnC;

}




