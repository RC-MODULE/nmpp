//------------------------------------------------------------------------
//
//  $Workfile:: ConvertRGB32nm10u_Gray32.cpp             $
//
//  <Название библиотеки>
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/02/10 12:36:40 $
//
//! \if file_doc
//!
//! \file   ConvertRGB32nm10u_Gray32.cpp
//! \author S. Mushkaev
//! \brief  Преобразование из RGB в Gray
//!
//! \endif
//!
//------------------------------------------------------------------------
#include "nmpli.h"
int pCoeff_RGB2Gray[4]={ 0x1d2f,0x9646,0x4c8b,0 };
void IMG_RGB32ToGray(RGB32_nm10s * pRGB, nm32u* pDstGray, int nSize)
{  
	unsigned nY;
	for (int i=0; i<nSize; i++)
	{ 
		nY= pRGB[i].nB*pCoeff_RGB2Gray[0];
		nY+=pRGB[i].nG*pCoeff_RGB2Gray[1];
		nY+=pRGB[i].nR*pCoeff_RGB2Gray[2];
		pDstGray[i]=nY;
	}
}
void IMG_RGB32ToGray(RGB32_nm10s * pRGB, nm32s* pDstGray, int nSize)
{
	int nY;
	for (int i=0; i<nSize; i++)
	{ 
		nY= pRGB[i].nB*pCoeff_RGB2Gray[0];
		nY+=pRGB[i].nG*pCoeff_RGB2Gray[1];
		nY+=pRGB[i].nR*pCoeff_RGB2Gray[2];
		pDstGray[i]=nY-0x800000;
	}
}

void IMG_RGB24ToGray(RGB24_nm8u* pRGB, nm8u* pDstGray, int nSize)
{
	unsigned nY;
	for (int i=0; i<nSize; i++)
	{ 
		nY= pRGB[i].nB*pCoeff_RGB2Gray[0];
		nY+=pRGB[i].nG*pCoeff_RGB2Gray[1];
		nY+=pRGB[i].nR*pCoeff_RGB2Gray[2];
		pDstGray[i]=nY>>16;
	}
}

