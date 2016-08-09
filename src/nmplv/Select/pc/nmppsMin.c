//------------------------------------------------------------------------
//
//  $Workfile:: GetMin.cp $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:16 $
//
//! \if file_doc
//!
//! \file   GetMin.cpp
//! \author Сергей Мушкаев
//! \brief  Статистические функции для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------
#include "nmplv.h"
/////////////////////////////////////////////////////////////////////////////////////////
// Search of Minimum value in 8-bit buffer
void nmppsMin_8s7b(
		const	nm8s7b*		pSrcVec,	// input buffer					:long Local [Size/8]
				int			nSize,		// buffer size in 8-bit words	:nSize=[512,768,1024.....]
				int8b*		pMinValue)	// Minimum
{
	int i;
	
	nm8s7b* pSrcValue=pSrcVec+1;
	*pMinValue=pSrcVec[0];
	for(i=1; i<nSize; i++,pSrcValue++){
		signed char mask=((*pSrcValue)-(*pMinValue));
		mask>>=7;
		*pMinValue=((mask)&(*pSrcValue))|((~mask)&(*pMinValue));
	}

}
/////////////////////////////////////////////////////////////////////////////////////////
// Search of Minimum value in 16-bit buffer
void nmppsMin_16s15b(
		const	nm16s15b*		pSrcVec,	// input buffer					:long Local [Size/4]
				int			nSize,		// buffer size in 16-bit words	:nSize=[256,384,512...]
				int16b*		pMinValue)	// Minimum
{
	int i;
	
	nm16s15b* pSrcValue=pSrcVec+1;
	*pMinValue=pSrcVec[0];
	for(i=1; i<nSize; i++,pSrcValue++){
		signed short mask=((*pSrcValue)-(*pMinValue));
		mask>>=15;
		*pMinValue=((mask)&(*pSrcValue))|((~mask)&(*pMinValue));
	}
}
/////////////////////////////////////////////////////////////////////////////////////////
// Search of Minimum value in 32-bit buffer
void nmppsMin_32s31b(
		const	nm32s31b*		pSrcVec,	// input buffer					:long Local [Size/2]
				int			nSize,		// buffer size in 32-bit words	:nSize=[128,192,256..]
				int*		pMinValue)	// Minimum
{
	int i;
	nm32s31b* pSrcValue=pSrcVec+1;
	*pMinValue=pSrcVec[0];
	
	for(i=1; i<nSize; i++,pSrcValue++){
		signed int mask=((*pSrcValue)-(*pMinValue));
		mask>>=31;
		*pMinValue=((mask)&(*pSrcValue))|((~mask)&(*pMinValue));
	}
}
/////////////////////////////////////////////////////////////////////////////////////////
// Search of Minimum value in 64-bit buffer
void nmppsMin_64s63b(
		const	nm64s63b*	pSrcVec,	// input buffer					:long Local [Size/2]
				int			nSize,		// buffer size in 32-bit words	:nSize=[128,192,256..]
				int64b*		pMinValue)	// Minimum
{
	int i;
	
	nm64s63b* pSrcValue=pSrcVec+1;
	*pMinValue=pSrcVec[0];
	for(i=1; i<nSize; i++,pSrcValue++){
		signed long long mask=((*pSrcValue)-(*pMinValue));
		mask >>=63;
		*pMinValue=((mask)&(*pSrcValue))|((~mask)&(*pMinValue));
	}
}

