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
//#include "vec.h"
#include "nmplv.h"
#include "nmtl.h"
/////////////////////////////////////////////////////////////////////////////////////////
// Element-wise multiplication of two vectors
void nmppsMulV_32s(nm32s*		pSrcVec1,		// input  32-bit vec		:long -----[Size/2]
			nm32s*		pSrcVec2,		// input  32-bit vec		:long -----[Size/2]
			nm32s*		pDstVec,			// output 32-bit vec		:long -----[Size/2]
			int			nSize			// size of input buffers	:nSize=[0,2,4...]
		)
{
#ifndef USE_IPP
	//if (CHECK_OVERFLOW())
	//{
	//	nmvec32s SrcVecA(pSrcVec1,nSize);
	//	nmvec32s SrcVecB(pSrcVec2,nSize);
	//	nmvec32s DstVec(pDstVec,nSize);
	//	for(int i=0;i<nSize;i++)
	//		DstVec[i]=SrcVecA[i]*SrcVecB[i];
	//}
	//else
		for(int i=0;i<nSize;i++)
			pDstVec[i]=pSrcVec1[i]*pSrcVec2[i];
#else
	if (pSrcVec2!=pDstVec)
		ippsMul_32s_Sfs(pSrcVec1, pSrcVec2,pDstVec, nSize,0);
	else
		ippsMul_32s_ISfs(pSrcVec1,pSrcVec2,nSize,0);
#endif

}



