//------------------------------------------------------------------------
//
//  $Workfile:: Sub.cpp  $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:15 $
//
//! \if file_doc
//!
//! \file   Sub.cpp
//! \author Сергей Мушкаев
//! \brief  Арифметические функции 
//!
//! \endif
//!
//------------------------------------------------------------------------


#include "nmtype.h"
/////////////////////////////////////////////////////////////////////////////////////////
// Subtraction of two char buffers
void nmppsSub_8s(
		const nm8s*			pSrcVec1,		// input buffer		:long Local [VecSize/4]
		const nm8s*			pSrcVec2,		// input buffer		:long Local [VecSize/4]
		nm8s*			pDstVec,			// output buffer	:long Global[VecSize/4]
		int				nSize			// size of input buffer in 16-bit elements. nSize=[0,4,8,12..]
		)
{
	int i;
	for (i=0; i<nSize; i++)
		pDstVec[i] = pSrcVec1[i] - pSrcVec2[i];

}



//////////////////////////////////////////////////////////////////////////////////////
// Subtraction of two short vectors
void nmppsSub_16s(
		const nm16s*			pSrcVec1,		// input buffer		:long Local [VecSize/4]
		const nm16s*			pSrcVec2,		// input buffer		:long Local [VecSize/4]
		nm16s*			pDstVec,			// output buffer	:long Global[VecSize/4]
		int				nSize			// size of input buffer in 16-bit elements. nSize=[0,4,8,12..]
		)
{
	int i;
	for (i=0; i<nSize; i++)
		pDstVec[i] = pSrcVec1[i] - pSrcVec2[i];

}


//////////////////////////////////////////////////////////////////////////////////////
// Subtraction of two int vectors
void nmppsSub_32s(
		const nm32s*			pSrcVec1,		// input buffer		:long Local [VecSize/2]
		const nm32s*			pSrcVec2,		// input buffer		:long Local [VecSize/2]
		nm32s*			pDstVec,			// output buffer	:long Global[VecSize/2]
		int				nSize			// size of input buffer in 32-bit elements. nSize=[0,2,4,6...]
		)
{
	int i;
	for (i=0; i<nSize; i++)
		pDstVec[i] = pSrcVec1[i] - pSrcVec2[i];

}

//////////////////////////////////////////////////////////////////////////////////////
// Subtraction of two __int64 vectors
void nmppsSub_64s(
		const nm64s*			pSrcVec1,		// input buffer		:long Local [nSize]
		const nm64s*			pSrcVec2,		// input buffer		:long Local [nSize]
		nm64s*			pDstVec,			// output buffer	:long Global[nSize]
		int				nSize			// size of input buffer in 32-bit elements. nSize=[0,1,2,3,4...]
		)
{
	int i;
	for (i=0; i<nSize; i++)
		pDstVec[i] = pSrcVec1[i] - pSrcVec2[i];
}


//////////////////////////////////////////////////////////////////////////////////////
// Subtraction of two __int64 complex vectors
void nmppsSub_64sc(
		const nm64sc *pSrcVec1, 
		const nm64sc *pSrcVec2, 
		nm64sc *pDstVec, int nSize)
{
	int i;
	for(i=0;i<nSize;i++)
	{
		pDstVec[i].re = pSrcVec1[i].re - pSrcVec2[i].re;
		pDstVec[i].im = pSrcVec1[i].im - pSrcVec2[i].im;
	}
}


