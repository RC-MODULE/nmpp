//------------------------------------------------------------------------
//
//  $Workfile:: Abs.cpp    $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:15 $
//
//! \if file_doc
//!
//! \file   Abs.cpp
//! \author Сергей Мушкаев
//! \brief  Арифметические функции 
//!
//! \endif
//!
//------------------------------------------------------------------------
#include "nmpp.h"
/////////////////////////////////////////////////////////////////////////////////////////
// Absolute value calculation
void nmppsAbs_4s(
		nm4s*			pSrcVec,		// input buffer		:long Local [VecSize/8]
		nm4s*			pDstVec,		// output buffer	:long Global[VecSize/8]
		int				nSize		// size of input buffer in 8 bit elements. nSize=[8,16,32...]
		)
{
	nm8s v,m;
	int i=0;
	for(i=0; i<nSize/2; i++)
	{
		v=((nm8s*)pSrcVec)[i];
		//m=((v>>7)<<4)|(((v<<4)>>7)&0xF);
		m = (((v<<24)>>31)&0xF0)|(((v<<28)>>31)&0xF);
		v^=m;
		v+=(0x11&m);
		((nm8s*)pDstVec)[i]=v;
	}
}

void nmppsAbs_8s(
		nm8s*			pSrcVec,		// input buffer		:long Local [VecSize/8]
		nm8s*			pDstVec,		// output buffer	:long Global[VecSize/8]
		int				nSize		// size of input buffer in 8 bit elements. nSize=[8,16,32...]
		)
{
	int i=0;
	for(i=0; i<nSize; i++)
		pDstVec[i] = ABS(pSrcVec[i]);
	// No IPP analog
}

/////////////////////////////////////////////////////////////////////////////////////////
// Absolute value calculation
void nmppsAbs_16s(
		nm16s*			pSrcVec,		// input buffer		:long Local [VecSize/4]
		nm16s*			pDstVec,		// output buffer	:long Global[VecSize/4]
		int				nSize		// size of input buffer in 8 bit elements. nSize=[0,4,8,..]
		)
{
	int i=0;
	for(i=0; i<nSize; i++)
		pDstVec[i] = ABS(pSrcVec[i]);
}


/////////////////////////////////////////////////////////////////////////////////////////
// Absolute value calculation
void nmppsAbs_32s(
		nm32s*			pSrcVec,		// input buffer		:long Local [VecSize/2]
		nm32s*			pDstVec,		// output buffer	:long Global[VecSize/2]
		int				nSize		// size of input buffer in 32 bit elements. nSize=[2,4,6...]
		)
{
	int i=0;
	for(i=0; i<nSize; i++)
		pDstVec[i] = ABS(pSrcVec[i]);
}


/////////////////////////////////////////////////////////////////////////////////////////
// Absolute value calculation
void nmppsAbs_64s(
		nm64s*			pSrcVec,		// input buffer		:long Local [VecSize/2]
		nm64s*			pDstVec,		// output buffer	:long Global[VecSize/2]
		int				nSize		// size of input buffer in 32 bit elements. nSize=[2,4,6...]
		)
{
	int i=0;
	for(i=0; i<nSize; i++)
		pDstVec[i] = ABS(pSrcVec[i]);
}

