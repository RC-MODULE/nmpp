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
// pDstVec[i]=Decrement-pSrcVec[i]
void nmppsSubCRev_8s(
		nm8s*			pSrcVec,			// input buffer		:long Local [VecSize/8]
		int8b			nVal,				// decrement		:
		nm8s*			pDstVec,			// output buffer	:long Global[VecSize/8]
		int				nSize		// size of input buffer in 8-bit elements. nSize=[0,8,16,32...]
		)
{
	int i;
	nVal=(char)nVal;

	for (i=0; i<nSize; i++)
		pDstVec[i] = nVal-pSrcVec[i];
}


/////////////////////////////////////////////////////////////////////////////////////////
// pDstVec[i]=Decrement-pSrcVec[i]
void nmppsSubCRev_16s(
		nm16s*			pSrcVec,			// input buffer		:long Local [VecSize/4]
		int16b			nVal,				// decrement		:
		nm16s*			pDstVec,			// output buffer	:long Global[VecSize/4]
		int				nSize		// size of input buffer in 8-bit elements. nSize=[0,4,8,12...]
		)
{
	int i;
	nVal=(short)nVal;

	for (i=0; i<nSize; i++)
		pDstVec[i] = nVal-pSrcVec[i];

}


/////////////////////////////////////////////////////////////////////////////////////////
// pDstVec[i]=Decrement-pSrcVec[i]
void nmppsSubCRev_32s(
		nm32s*			pSrcVec,			// input buffer		:long Local [VecSize/2]
		int32b			nVal,				// decrement		:
		nm32s*			pDstVec,			// output buffer	:long Global[VecSize/2]
		int				nSize		// size of input buffer in 32-bit elements. nSize=[0,2,4,6...]
		)
{
	int i;

	for (i=0; i<nSize; i++)
		pDstVec[i] = nVal-pSrcVec[i];
}

/////////////////////////////////////////////////////////////////////////////////////////
// pDstVec[i]=Decrement-pSrcVec[i]
void nmppsSubCRev_64s(
		nm64s*			pSrcVec,			// input buffer		:long Local [VecSize/2]
		int64b			nVal,				// decrement		:
		nm64s*			pDstVec,			// output buffer	:long Global[VecSize/2]
		int				nSize		// size of input buffer in 32-bit elements. nSize=[0,2,4,6...]
		)
{
	int i;
	for (i=0; i<nSize; i++)
		pDstVec[i] = nVal-pSrcVec[i];
}


