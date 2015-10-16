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
#include "nmplv.h"

//================= VEC_GetVal ===========================================    
int2b	VEC_GetVal(nm2s*  pVec, int nIndex)
{
	nm32u nBase=(nm32u(nIndex))/16;
	nm32u nDisp=(nm32u(nIndex))%16;
	nm32s nVal=((nm32s*)pVec)[nBase];
	nDisp<<=1;
	nVal<<=(32-2-nDisp);
	nVal>>=30;
	return nVal;
}

int4b			VEC_GetVal(nm4s*  pVec, int nIndex)
{
	nm32u nBase=(nm32u(nIndex))/8;
	nm32u nDisp=(nm32u(nIndex))%8;
	nm32s nVal=((nm32s*)pVec)[nBase];
	nDisp<<=2;
	nVal<<=(32-4-nDisp);
	nVal>>=28;
	return nVal;
}

int8b	VEC_GetVal(nm8s*  pVec, int nIndex)
{
	return pVec[nIndex];
}

int16b	VEC_GetVal(nm16s* pVec, int nIndex)
{
	return pVec[nIndex];
}

//---------------- uint ------------------------------------ 
uint1b	VEC_GetVal(nm1*   pVec, int nIndex)
{
	nm32u nBase=(nm32u(nIndex))/32;
	nm32u nDisp=(nm32u(nIndex))%32;
	nm32u nVal=((nm32u*)pVec)[nBase];
	nVal>>=nDisp;
	nVal&=1;
	return nVal;
}
uint2b	VEC_GetVal(nm2u*  pVec, int nIndex)
{
	nm32u nBase=(nm32u(nIndex))/16;
	nm32u nDisp=(nm32u(nIndex))%16;
	nm32u nVal=((nm32u*)pVec)[nBase];
	nVal>>=nDisp*2;
	nVal&=3;
	return nVal;
}


uint4b	VEC_GetVal(nm4u*  pVec, int nIndex)
{
	nm32u nBase=(nm32u(nIndex))/8;
	nm32u nDisp=(nm32u(nIndex))%8;
	nm32u nVal=((nm32u*)pVec)[nBase];
	nVal>>=nDisp*4;
	nVal&=15;
	return nVal;
}

uint8b	VEC_GetVal(nm8u*  pVec, int nIndex)
{
	return pVec[nIndex];
}

uint16b	VEC_GetVal(nm16u* pVec, int nIndex)
{
	return pVec[nIndex];
}

//---------------- uint ------------------------------------ 
void VEC_GetVal(nm1*  pArray, int Index, int1b &nVal)
{
	nVal=VEC_GetVal(pArray,Index);
	nVal<<=31;
	nVal>>=31;
}

void VEC_GetVal(nm2s*  pArray, int Index, int2b &nVal)
{
	nVal=VEC_GetVal(pArray,Index);
}
void VEC_GetVal(nm4s* pArray, int Index, int4b &nVal)
{
	nVal=VEC_GetVal(pArray,Index);
}

void VEC_GetVal(nm8s*  pArray, int Index, int8b &nVal)
{
	nVal=pArray[Index];
}
void VEC_GetVal(nm16s* pArray, int Index, int16b &nVal)
{
	nVal=pArray[Index];
}

//---------------- int ------------------------------------ 

void VEC_GetVal(nm1*  pArray, int Index, uint1b &nVal)
{
	nVal=VEC_GetVal(pArray,Index);
}

void VEC_GetVal(nm2u*  pArray, int Index, uint2b &nVal)
{
	nVal=VEC_GetVal(pArray,Index);
}

void VEC_GetVal(nm4u* pArray, int Index, uint4b &nVal)
{
	nVal=VEC_GetVal(pArray,Index);
}

void VEC_GetVal(nm8u*  pArray, int Index, uint8b &nVal)
{
	nVal=pArray[Index];
}
void VEC_GetVal(nm16u* pArray, int Index, uint16b &nVal)
{
	nVal=pArray[Index];
}
