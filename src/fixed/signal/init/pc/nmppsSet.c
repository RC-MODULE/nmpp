//------------------------------------------------------------------------
//
//  $Workfile:: Init.cp $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:15 $
//
//! \if file_doc
//!
//! \file   Init.cpp
//! \author Сергей Мушкаев
//! \brief  Функции инициализации и копирования для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------
#include "nmpp.h"
////////////////////////////////////////////////////////////////////////////
//  Setting all 64-bit elements of Buffer to const value given by InitValue
void nmppsSet_64sp(
		nm64s*		pVal,	// Init value
		nm64s*		pDst,		// Destination array					:long Global [len64]
		int			len64	// nSize of Source array in 64-bit ints; :len32= [0,1,2,...]
		)
{
	int i;
	for(i=0;i<len64;i++)
		pDst[i]=(*pVal);
}

////////////////////////////////////////////////////////////////////////////
//  Setting all 64-bit elements of Buffer to const value given by InitValue
void nmppsSet_64sc(
		nm64sc	val,	// Init value
		nm64sc*	pDst,		// Destination array					:long Global [len64]
		int		len128	// nSize of Source array in 64-bit ints; :len32= [0,1,2,...]
		)
{
	int i;
	for(i=0;i<len128;i++)
		pDst[i]=val;
}


////////////////////////////////////////////////////////////////////////////
//  Setting all 64-bit elements of pDst to const value given by InitValue
void nmppsSet_64s(
		nm64s	val,	// Init value
		nm64s*	pDst,		// Destination array					:long Global [len64]
		int		len64	// nSize of Source array in 64-bit ints; :len32= [0,1,2,...]
		)
{
	int i;
	for(i=0;i<len64;i++)
		pDst[i]=val;
}


////////////////////////////////////////////////////////////////////////////
//  Setting all 32-bit elements of pDst to const value given by val
void nmppsSet_32s(
		int		val,	// Init value 
		nm32s*	pDst,		// Destination array					:long Global [len32/2]
		int		len32	// nSize of Source array in 32-bit ints; :len32= [0,2,4...]
		)
{
	int i;
	for(i=0;i<len32;i++)
		pDst[i]=val;
}

////////////////////////////////////////////////////////////////////////////
//  Setting all 16-bit elements of pDst to const value given by val
void nmppsSet_16s(
		int		val,	// Init value 
		nm16s*	pDst,		// Destination array					:long Global [len16/4]
		int		len16	// nSize of Source array in 16-bit shorts:len16= [0,4,8,...]
		)
{
	int i;
	for(i=0;i<len16;i++)
		pDst[i]=val;
}


////////////////////////////////////////////////////////////////////////////
//  Setting all 8-bit elements of pDst to const number given by val
void nmppsSet_8s(
		int		val,	// Init value
		nm8s*	pDst,		// Destination array					:long Global [len8/8]
		int		len8	// nSize of Source array in 8-bit chars; :len8=  [0,8,16....]
		)
{
	int i;
	for(i=0;i<len8;i++)
		pDst[i]=val;
}


