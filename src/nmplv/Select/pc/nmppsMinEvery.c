//------------------------------------------------------------------------
//
//  $Workfile:: CompareMinV. $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:16 $
//
//! \if file_doc
//!
//! \file   pcCompare.cpp
//! \author Сергей Мушкаев
//! \brief  Функции сравнения.
//!
//! \endif
//!
//------------------------------------------------------------------------
#include "nmplv.h"


void nmppsMinEvery_8s(nm8s7b*  pSrcVec1, nm8s7b* pSrcVec2,  nm8s7b*  pDstMin, int nSize)
{
	#ifdef RPC
	//RPC_HOST_PPI(nmppsAbs1_4s,pSrcVec,pDstVec,nSize);
	#else

	nm8s s1,s2,mask;
	int i;
	for (i=0;i<nSize;i++)
	{
		s1=pSrcVec1[i];
		s2=pSrcVec2[i];
		mask=(s1-s2)>>7;
		pDstMin[i]=(s1&mask)|(s2&(~mask));
	}

	#endif
}
void nmppsMinEvery_16s(nm16s15b* pSrcVec1, nm16s15b* pSrcVec2, nm16s15b* pDstMin, int nSize)
{
	#ifdef RPC
	//RPC_HOST_PPI(nmppsAbs1_4s,pSrcVec,pDstVec,nSize);
	#else

	nm16s s1,s2,mask;
	int i;
	for (i=0;i<nSize;i++)
	{
		s1=pSrcVec1[i];
		s2=pSrcVec2[i];
		mask=(s1-s2)>>15;
		pDstMin[i]=(s1&mask)|(s2&(~mask));
	}

	#endif
}

void nmppsMinEvery_32s(nm32s31b* pSrcVec1, nm32s31b* pSrcVec2, nm32s31b* pDstMin, int nSize)
{
	#ifdef RPC
	//RPC_HOST_PPI(nmppsAbs1_4s,pSrcVec,pDstVec,nSize);
	#else

	nm32s s1,s2,mask;
	int i;
	for (i=0;i<nSize;i++)
	{
		s1=pSrcVec1[i];
		s2=pSrcVec2[i];
		mask=(s1-s2)>>31;
		pDstMin[i]=(s1&mask)|(s2&(~mask));
	}

	#endif
}

void nmppsMinEvery_64s(nm64s63b* pSrcVec1, nm64s63b* pSrcVec2, nm64s63b* pDstMin, int nSize)
{
	#ifdef RPC
	//RPC_HOST_PPI(nmppsAbs1_4s,pSrcVec,pDstVec,nSize);
	#else

	nm64s s1,s2,mask;
	int i;
	for (i=0;i<nSize;i++)
	{
		s1=pSrcVec1[i];
		s2=pSrcVec2[i];
		mask=(s1-s2)>>63;
		pDstMin[i]=(s1&mask)|(s2&(~mask));
	}

	#endif
}

