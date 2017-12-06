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
void nmppsSplit_8s(nm8s* src, nm8s* dst1, nm8s* dst2, int sizeSrc, nm8s* tmpSizeofDst)
{
	int i;
	for (i=0;i<sizeSrc/2;i++){
		dst1[i]=src[2*i];
		dst2[i]=src[2*i+1];
	}
}

void nmppsSplitEco_8s(nm8s* src, nm8s* dst1, nm8s* dst2, int sizeSrc)
{
	int i;
	for (i=0;i<sizeSrc/2;i++){
		dst1[i]=src[2*i];
		dst2[i]=src[2*i+1];
	}
}
