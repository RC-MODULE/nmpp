//------------------------------------------------------------------------
//
//  $Workfile:: Add.cpp    $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:15 $
//
//! \if file_doc
//!
//! \file   Remap.cpp
//! \author Сергей Мушкаев
//! \brief  Арифметические функции 
//!
//! \endif
//!
//------------------------------------------------------------------------
#include "nmtype.h"


/////////////////////////////////////////////////////////////////////////////////////////
void nmppsAdd_4s(
		const nm4s*			pSrcVec1,		// input buffer		:long Local [VecSize/16]
		const nm4s*			pSrcVec2,		// input buffer		:long Local [VecSize/16]
		nm4s*			pDstVec,			// output buffer	:long Global[VecSize/16]
		int				nSize			// size of input buffer in 8 bit elements. nSize=[0,16,32...]
		)
{
	int i,j;
	int iSize=nSize/16;
	nm64s* psrc1 = (nm64s*) pSrcVec1;
	nm64s* psrc2 = (nm64s*) pSrcVec2;
	long long int uiSrcVec1, uiSrcVec2,*pdst  = (nm64s*) pDstVec;
	for (i=0; i<iSize; i++)
	{
		uiSrcVec1 = psrc1[i];
		uiSrcVec2 = psrc2[i];
		for(j=0;j<16;j++)
		{
			pdst[i] <<=4;
			pdst[i] |= ((uiSrcVec1>>60) + (uiSrcVec2>>60)) & 0x0f;
			uiSrcVec1 <<= 4;
			uiSrcVec2 <<= 4;
		}
	}
}

// Summation of two char vectors
void nmppsAdd_8s(
		const nm8s*			pSrcVec1,		// input buffer		:long Local [VecSize/8]
		const nm8s*			pSrcVec2,		// input buffer		:long Local [VecSize/8]
		nm8s*			pDstVec,			// output buffer	:long Global[VecSize/8]
		int				nSize			// size of input buffer in 8 bit elements. nSize=[0,8,16,24...]
		)
{
	int i;
	for (i=0; i<nSize; i++)
		pDstVec[i] = pSrcVec1[i] + pSrcVec2[i];

}

/////////////////////////////////////////////////////////////////////////////////////////
// Summation of two short vectors
void nmppsAdd_16s(
		const nm16s*			pSrcVec1,		// input buffer		:long Local [VecSize/4]
		const nm16s*			pSrcVec2,		// input buffer		:long Local [VecSize/4]
		nm16s*			pDstVec,			// output buffer	:long Global[VecSize/4]
		int				nSize			// size of input buffer in 16-bit elements. nSize=[0,4,8,12..]
		)
{
	int i;
	for (i=0; i<nSize; i++)
		pDstVec[i] = pSrcVec1[i] + pSrcVec2[i];

}

/////////////////////////////////////////////////////////////////////////////////////////
// Summation of two int vectors
void nmppsAdd_32s(
		const nm32s*			pSrcVec1,		// input buffer		:long Local [VecSize/2]
		const nm32s*			pSrcVec2,		// input buffer		:long Local [VecSize/2]
		nm32s*			pDstVec,			// output buffer	:long Global[VecSize/2]
		int				nSize			// size of input buffer in 32-bit elements. nSize=[0,2,4,6...]
		)
{
	int i;
	for (i=0; i<nSize; i++)
		pDstVec[i] = pSrcVec1[i] + pSrcVec2[i];

}

/////////////////////////////////////////////////////////////////////////////////////////
// Summation of two long vectors
void nmppsAdd_64s(
		const nm64s*		pSrcVec1,		// input buffer		:long Local [nSize]
		const nm64s*		pSrcVec2,		// input buffer		:long Local [nSize]
		nm64s*		pDstVec,			// output buffer	:long Global[nSize]
		int				nSize			// size of input buffer in 64-bit elements. nSize=[0,1,2,3...]
		)
{
	int i;
	for (i=0; i<nSize; i++)
		pDstVec[i] = pSrcVec1[i] + pSrcVec2[i];

}


/////////////////////////////////////////////////////////////////////////////////////////
// Summation of two long complex vectors
void nmppsAdd_64sc(
		const nm64sc *pSrcVec1, 
		const nm64sc *pSrcVec2, 
		nm64sc *pDstVec, int nSize)
{
	int i;
	for(i=0;i<nSize;i++)
	{
		pDstVec[i].re = pSrcVec1[i].re + pSrcVec2[i].re;
		pDstVec[i].im = pSrcVec1[i].im + pSrcVec2[i].im;
	}
}

void nmppsAddEx_64s (const nm64s *pSrcVec1, int srcStep1, const nm64s *pSrcVec2, int srcStep2, nm64s *pDstVec, int dstStep, int nSize  )
{
	int i;
	for (i=0; i<nSize; i++){
		*pDstVec = *pSrcVec1 + *pSrcVec2;
		pDstVec +=dstStep;
		pSrcVec1+=srcStep1;
		pSrcVec2+=srcStep2;
	}
}

