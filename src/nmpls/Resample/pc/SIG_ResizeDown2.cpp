//------------------------------------------------------------------------
//
//  $Workfile:: ResampleDown2.cp $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/01/12 14:09:08 $
//
//! \if file_doc
//!
//! \file   ResampleDown2.cpp
//! \author Сергей Мушкаев
//! \brief  Функции изменения размера для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------

#include "nmtype.h"

/////////////////////////////////////////////////////////////////////////////////////////
void SIG_ResampleDown2(
		nm16u15b*		pSrc,	// input buffer		:long Local	[len/8]
		nm16u15b*		pDst,	// output buffer	:long Global[len/4/2]
		int				len,		// size of input buffer in 16 bit elements. nSize=[0,2,4,...]
		nm64s*			pKernel
		)
{
	for(int i=0;i<(len/8)*4;i++)
		((nm16s*)pDst)[i] = ((unsigned short)(((nm16u*)pSrc)[2*i]+((nm16u*)pSrc)[2*i+1])>>1);
}
/////////////////////////////////////////////////////////////////////////////////////////
void SIG_ResampleDown2(
		nm8u7b*			pSrc,	// input buffer		:long Local	[len/8]
		nm8u7b*			pDst,	// output buffer	:long Global[len/4/2]
		int				len,	// size of input buffer in 16 bit elements. nSize=[0,2,4,...]
		nm64s*			pKernel
		)
{
	for(int i=0;i<(len/16)*8;i++)
		((nm8u*)pDst)[i] = \
		((unsigned char)(((nm8u*)pSrc)[2*i]+((nm8u*)pSrc)[2*i+1])>>1);
}
/////////////////////////////////////////////////////////////////////////////////////////

int SIG_SetResampleDown2_16u16u(nm64s* pKernel)
{
	return 0;
}

int SIG_SetResampleUp3Down2_8u8u(nm64s* pKernel)
{
	return 0;
}