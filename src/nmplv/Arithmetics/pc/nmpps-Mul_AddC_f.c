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
//! \author Иван Жиленков
//! \brief  Функции умножения для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------
#include "nmtype.h"
/////////////////////////////////////////////////////////////////////////////////////////
// Element-wise multiplication of two vectors
void nmppsMul_AddC_32f(
			const nm32f*		pSrcVec1,		// input  32-bit vec		:long -----[Size/2]
			const nm32f*		pSrcVec2,		// input  32-bit vec		:long -----[Size/2]
			float 				pnC,
			nm32f*				pDstVec,			// output 32-bit vec		:long -----[Size/2]
			int					nSize			// size of input buffers	:nSize=[0,2,4...]
		)
{
	int i;
	for (i=0;i<nSize;i++)
		pDstVec[i]=pSrcVec1[i]*pSrcVec2[i] + pnC;

}




