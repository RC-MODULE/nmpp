//------------------------------------------------------------------------
//
//  $Workfile:: CompareMaxV. $
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


void nmppsMaxEvery_8s(nm8s7b*  pSrcVec1, nm8s7b* pSrcVec2,  nm8s7b*  pDstMax, int nSize)
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
		mask=(s2-s1)>>7;
		pDstMax[i]=(s1&mask)|(s2&(~mask));
	}

	#endif
}
void nmppsMaxEvery_16s(nm16s15b* pSrcVec1, nm16s15b* pSrcVec2, nm16s15b* pDstMax, int nSize)
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
		mask=(s2-s1)>>15;
		pDstMax[i]=(s1&mask)|(s2&(~mask));
	}

	#endif
}

void nmppsMaxEvery_32s(nm32s31b* pSrcVec1, nm32s31b* pSrcVec2, nm32s31b* pDstMax, int nSize)
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
		mask=(s2-s1)>>31;
		pDstMax[i]=(s1&mask)|(s2&(~mask));
	}

	#endif
}

void nmppsMaxEvery_64s(nm64s63b* pSrcVec1, nm64s63b* pSrcVec2, nm64s63b* pDstMax, int nSize)
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
		mask=(s2-s1)>>63;
		pDstMax[i]=(s1&mask)|(s2&(~mask));
	}

	#endif
}

