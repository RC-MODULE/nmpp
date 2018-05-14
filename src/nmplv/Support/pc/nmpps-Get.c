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
#include "nmtype.h"

//================= nmppsGetVal_ ===========================================    
int2b	nmppsGet_2s(const nm2s*  pVec, int nIndex)
{
	nm32u nBase=((nm32u)nIndex)/16;
	nm32u nDisp=((nm32u)nIndex)%16;
	nm32s nVal=((nm32s*)pVec)[nBase];
	nDisp<<=1;
	nVal<<=(32-2-nDisp);
	nVal>>=30;
	return nVal;
}

int4b			nmppsGet_4s(const nm4s*  pVec, int nIndex)
{
	nm32u nBase=((nm32u)nIndex)/8;
	nm32u nDisp=((nm32u)nIndex)%8;
	nm32s nVal=((nm32s*)pVec)[nBase];
	nDisp<<=2;
	nVal<<=(32-4-nDisp);
	nVal>>=28;
	return nVal;
}

int8b	nmppsGet_8s(const nm8s*  pVec, int nIndex)
{
	return pVec[nIndex];
}

int16b	nmppsGet_16s(nm16s* pVec, int nIndex)
{
	return pVec[nIndex];
}

//---------------- uint ------------------------------------ 
uint1b	nmppsGet_1 (const nm1*   pVec, int nIndex)
{
	nm32u nBase=((nm32u)nIndex)/32;
	nm32u nDisp=((nm32u)nIndex)%32;
	nm32u nVal=((nm32u*)pVec)[nBase];
	nVal>>=nDisp;
	nVal&=1;
	return nVal;
}
uint2b	nmppsGet_2u(const nm2u*  pVec, int nIndex)
{
	nm32u nBase=((nm32u)nIndex)/16;
	nm32u nDisp=((nm32u)nIndex)%16;
	nm32u nVal=((nm32u*)pVec)[nBase];
	nVal>>=nDisp*2;
	nVal&=3;
	return nVal;
}


uint4b	nmppsGet_4u(const nm4u*  pVec, int nIndex)
{
	nm32u nBase=((nm32u)nIndex)/8;
	nm32u nDisp=((nm32u)nIndex)%8;
	nm32u nVal=((nm32u*)pVec)[nBase];
	nVal>>=nDisp*4;
	nVal&=15;
	return nVal;
}

uint8b	nmppsGet_8u(const nm8u*  pVec, int nIndex)
{
	return pVec[nIndex];
}

uint16b	nmppsGet_16u(const nm16u* pVec, int nIndex)
{
	return pVec[nIndex];
}

//---------------- uint ------------------------------------ 
void nmppsGetVal_1(const nm1*  pArray, int Index, int1b* nVal)
{
	*nVal=nmppsGet_1(pArray,Index);
	*nVal<<=31;
	*nVal>>=31;
}

void nmppsGetVal_2s(const nm2s*  pArray, int Index, int2b *nVal)
{
	*nVal=nmppsGet_2s(pArray,Index);
}
void nmppsGetVal_4s(const nm4s* pArray, int Index, int4b *nVal)
{
	*nVal=nmppsGet_4s(pArray,Index);
}

void nmppsGetVal_8s(const nm8s*  pArray, int Index, int8b *nVal)
{
	*nVal=pArray[Index];
}
void nmppsGetVal_16s(const nm16s* pArray, int Index, int16b *nVal)
{
	*nVal=pArray[Index];
}

//---------------- int ------------------------------------ 
/*
void nmppsGetVal_1_1*(nm1*  pArray, int Index, uint1b *nVal)
{
	nVal=nmppsGetVal_(pArray,Index);
}*/

void nmppsGetVal_2u(const nm2u*  pArray, int Index, uint2b *nVal)
{
	*nVal=nmppsGet_2u(pArray,Index);
}

void nmppsGetVal_4u(const nm4u* pArray, int Index, uint4b *nVal)
{
	*nVal=nmppsGet_4u(pArray,Index);
}

void nmppsGetVal_8u(const nm8u*  pArray, int Index, uint8b *nVal)
{
	*nVal=pArray[Index];
}
void nmppsGetVal_16u(const nm16u* pArray, int Index, uint16b *nVal)
{
	*nVal=pArray[Index];
}
