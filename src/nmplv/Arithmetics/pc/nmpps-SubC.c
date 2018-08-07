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
// Decrement of vec elements by constant value
// pDstVec[i]=pSrcVec[i]-Decrement
void nmppsSubC_4s(
const 	nm4s*			pSrcVec,			// input buffer		:long Local [VecSize/8]
		int4b			nVal,				// decrement		:
		nm4s*			pDstVec,			// output buffer	:long Global[VecSize/8]
		int				nSize		// size of input buffer in 4-bit elements. nSize=[0,16,32...]
		)
{
	int i,j;
	int	iSize = nSize>>4;
	int value = nVal & 0xf;
	long long int uiSrc, *puiSrc = (nm64s*)pSrcVec;
	long long int *puiDst = (nm64s*)pDstVec;
	for (i=0; i<iSize; i++)
	{
		uiSrc = puiSrc[i];
		for (j=0;j<16;j++)
		{
			puiDst[i]<<=4;
			puiDst[i] |= ((uiSrc >> 60) - nVal) & 0xf;
			uiSrc<<=4;
		}
	}
}


// Decrement of vec elements by constant value
// pDstVec[i]=pSrcVec[i]-Decrement
void nmppsSubC_8s(
const 	nm8s*			pSrcVec,			// input buffer		:long Local [VecSize/8]
		int8b			nVal,				// decrement		:
		nm8s*			pDstVec,			// output buffer	:long Global[VecSize/8]
		int				nSize		// size of input buffer in 8-bit elements. nSize=[0,8,16,32...]
		)
{
	int i;
	nVal=(char)nVal;
	for (i=0; i<nSize; i++)
		pDstVec[i] = pSrcVec[i] - nVal;
}


/////////////////////////////////////////////////////////////////////////////////////////
// Decrement of vec elements by constant value
// pDstVec[i]=pSrcVec[i]-Decrement
void nmppsSubC_16s(
const 	nm16s*			pSrcVec,			// input buffer		:long Local [VecSize/4]
		int16b			nVal,				// decrement		:
		nm16s*			pDstVec,			// output buffer	:long Global[VecSize/4]
		int				nSize		// size of input buffer in 8-bit elements. nSize=[0,4,8,12...]
		)
{
	int i;
	nVal=(short)nVal;
	for (i=0; i<nSize; i++)
		pDstVec[i] = pSrcVec[i] - nVal;
}


/////////////////////////////////////////////////////////////////////////////////////////
// Decrement of vec elements by constant value
// pDstVec[i]=pSrcVec[i]-Decrement
void nmppsSubC_32s(
const 	nm32s*			pSrcVec,			// input buffer		:long Local [VecSize/2]
		int32b			nVal,				// decrement		:
		nm32s*			pDstVec,			// output buffer	:long Global[VecSize/2]
		int				nSize		// size of input buffer in 32-bit elements. nSize=[0,2,4,6...]
		)
{
	int i;
	for (i=0; i<nSize; i++)
		pDstVec[i] = pSrcVec[i] - nVal;

}


/////////////////////////////////////////////////////////////////////////////////////////
// pDstVec[i]=pSrcVec[i]-Decrement
void nmppsSubC_64s(
const 	nm64s*			pSrcVec,			// input buffer		:long Local [VecSize/2]
		int64b			nVal,				// decrement		:
		nm64s*			pDstVec,			// output buffer	:long Global[VecSize/2]
		int				nSize		// size of input buffer in 32-bit elements. nSize=[0,2,4,6...]
		)
{
	int i;
	for (i=0; i<nSize; i++)
		pDstVec[i] = pSrcVec[i] - nVal;
}


