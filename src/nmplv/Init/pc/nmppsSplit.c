//------------------------------------------------------------------------
//
//  $Workfile:: pcConvert.cp $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:15 $
//
//! \if file_doc
//!
//! \file   pcConvert.cpp
//! \author Сергей Мушкаев
//! \brief  Функции для преобразования запакованных данных.
//!
//! \endif
//!
//------------------------------------------------------------------------
//#include "vec.h"
#include "nmpp.h"
//*****************************************************************************
void nmppsSplitTmp_8s(const nm8s* src, nm8s* dst1, nm8s* dst2, int sizeSrc, nm8s* tmpSizeofDst)
{
	int i;
	for (i=0;i<sizeSrc/2;i++){
		dst1[i]=src[2*i];
		dst2[i]=src[2*i+1];
	}
}

void nmppsSplit_8s(const nm8s* src, nm8s* dst1, nm8s* dst2, int sizeSrc)
{
	int i;
	for (i=0;i<sizeSrc/2;i++){
		dst1[i]=src[2*i];
		dst2[i]=src[2*i+1];
	}
}

void nmppsSplit_16s(const nm16s* src, nm16s* dst1, nm16s* dst2, int sizeSrc)
{
	int i;
	for (i=0;i<sizeSrc/2;i++){
		dst1[i]=src[2*i];
		dst2[i]=src[2*i+1];
	}
}

void nmppsSplit_32s(const nm32s* src, nm32s* dst1, nm32s* dst2, int sizeSrc)
{
	int i;
	for (i=0;i<sizeSrc/2;i++){
		dst1[i]=src[2*i];
		dst2[i]=src[2*i+1];
	}
}

void nmppsSplit_32fcr(const nm32fcr* pSrcVec, nm32fcr* pDstVec1, nm32fcr* pDstVec2, int sizeSrc)
{
	int i;
	for (i = 0; i < sizeSrc / 2; i++) {
		pDstVec1[i].re = pSrcVec[2 * i].re;
		pDstVec1[i].im = pSrcVec[2 * i].im;
		pDstVec2[i].re = pSrcVec[2 * i + 1].re;
		pDstVec2[i].im = pSrcVec[2 * i + 1].im;
	}
}