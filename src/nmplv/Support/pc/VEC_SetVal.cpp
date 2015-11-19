//------------------------------------------------------------------------
//
//  $Workfile:: Access.cp $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:16 $
//
//! \if file_doc
//!
//! \file   Access.cpp
//! \author Сергей Мушкаев
//! \brief  Функции доступа для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------
#include "nmpp.h"

//================= nmppsSet_ ===========================================    

void nmppsPut_1(nm1*  pVec,  int nIndex, int1b nVal)
{
	nm32u nBase=(nm32u(nIndex))/32;
	nm32u nDisp=(nm32u(nIndex))%32;
	int*  pSrc=((int*)pVec)+nBase;
	int   nSrc=*pSrc;
	int	  nMask=1<<nDisp;
	nSrc&=~nMask;
	nSrc|=(nVal&1)<<nDisp;
	*pSrc=nSrc;
}

void nmppsPut_2s(nm2s* pVec,  int nIndex, int2b nVal)
{
	nm32u nBase=(nm32u(nIndex))/16;
	nm32u nDisp=(nm32u(nIndex))%16;
	nDisp*=2;
	int*  pSrc=((int*)pVec)+nBase;
	int   nSrc=*pSrc;
	int	  nMask=3<<nDisp;
	nSrc&=~nMask;
	nSrc|=(nVal&3)<<nDisp;
	*pSrc=nSrc;
}

void nmppsPut_4s(nm4s* pVec,  int nIndex, int4b nVal)
{
	nm32u nBase=(nm32u(nIndex))/8;
	nm32u nDisp=(nm32u(nIndex))%8;
	nDisp*=4;
	int*  pSrc=((int*)pVec)+nBase;
	int   nSrc=*pSrc;
	int	  nMask=15<<nDisp;
	nSrc&=~nMask;
	nSrc|=(nVal&15)<<nDisp;
	*pSrc=nSrc;
}

void nmppsPut_8s(nm8s* pArray,  int Index, int8b Val)
{
	pArray[Index]=Val;
}

void nmppsPut_16s(nm16s* pArray, int Index, int16b Val)
{
	pArray[Index]=Val;
}
