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

#include "nmpp.h"


void nmppsMerge_8s(const nm8s* src0, const nm8s* src1, nm8s* dst, int sizeSrc)
{
	int i;
	for (i=0;i<sizeSrc;i++){
		dst[2*i]  =src0[i];
		dst[2*i+1]=src1[i];
	}
}
void nmppsMerge_16s(const nm16s* src0, const nm16s* src1, nm16s* dst, int sizeSrc)
{
	int i;
	for (i=0;i<sizeSrc;i++){
		dst[2*i]  =src0[i];
		dst[2*i+1]=src1[i];
	}
}

void nmppsMerge_32s(const nm32s* src0, const nm32s* src1, nm32s* dst, int sizeSrc)
{
	int i;
	for (i=0;i<sizeSrc;i++){
		dst[2*i]  =src0[i];
		dst[2*i+1]=src1[i];
	}
}



