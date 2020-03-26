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
#include "nmpp.h"
//!
//! \perfinclude _nmppsRamp__FPciii_.html
//!

extern "C"{
void nmppsRamp_8s(nm8s* pVec, int8b nOffset, int8b nSlope, int nSize)
{
	int i;
	for(i=0; i<nSize; i++, nOffset+=nSlope)
		nmppsPut_8s(pVec, i, nOffset); 
}

//!
//! \perfinclude _nmppsRamp__FPSsiii_.html
//!

void nmppsRamp_16s(nm16s* pVec, int16b nOffset, int16b nSlope, int nSize)
{
	int i;
	for(i=0; i<nSize; i++, nOffset+=nSlope)
		nmppsPut_16s(pVec, i, nOffset); 
}

//!
//! \perfinclude _nmppsRamp__FPiiii_.html
//!

void nmppsRamp_32s(nm32s* pVec, int32b nOffset, int32b nSlope, int nSize)
{
	int i;
	for(i=0; i<nSize; i++, pVec++, nOffset+=nSlope)
		*pVec=nOffset;
}

//!
//! \perfinclude _nmppsRamp__FPllli_.html
//!

void nmppsRamp_64s(nm64s* pVec, int64b nOffset, int64b nSlope, int nSize)
{
	int i;
	for(i=0; i<nSize; i++, pVec++, nOffset+=nSlope)
		*pVec=nOffset;
}
};
