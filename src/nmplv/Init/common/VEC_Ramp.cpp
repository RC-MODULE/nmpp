//------------------------------------------------------------------------
//
//  $Workfile:: InitRamp.cpp            $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:02 $
//
//! \if file_doc
//!
//! \file   InitRamp.cpp
//! \author Sergey V. Vaganov esq.
//! \brief  Функции инициализации векторов элементами арифметической прогрессии.
//!
//! \endif
//!
//------------------------------------------------------------------------
#include "nmtype.h"
#include "nmplv.h"
//!
//! \perfinclude _VEC_Ramp__FPciii.html
//!


void VEC_Ramp(nm8s* pVec, int8b nOffset, int8b nSlope, int nSize)
{
	for(int i=0; i<nSize; i++, nOffset+=nSlope)
		VEC_SetVal(pVec, i, nOffset); 
}

//!
//! \perfinclude _VEC_Ramp__FPSsiii.html
//!

void VEC_Ramp(nm16s* pVec, int16b nOffset, int16b nSlope, int nSize)
{
	for(int i=0; i<nSize; i++, nOffset+=nSlope)
		VEC_SetVal(pVec, i, nOffset); 
}

//!
//! \perfinclude _VEC_Ramp__FPiiii.html
//!

void VEC_Ramp(nm32s* pVec, int32b nOffset, int32b nSlope, int nSize)
{
	for(int i=0; i<nSize; i++, pVec++, nOffset+=nSlope)
		*pVec=nOffset;
}

//!
//! \perfinclude _VEC_Ramp__FPllli.html
//!

void VEC_Ramp(nm64s* pVec, int64b nOffset, int64b nSlope, int nSize)
{
	for(int i=0; i<nSize; i++, pVec++, nOffset+=nSlope)
		*pVec=nOffset;
}
