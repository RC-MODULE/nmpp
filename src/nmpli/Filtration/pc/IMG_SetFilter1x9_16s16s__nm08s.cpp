//------------------------------------------------------------------------
//
//  $Workfile:: FilterWxH.cp $
//
//  Библиотека обработки изображений
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/02/10 12:36:40 $
//
//! \if file_doc
//!
//! \file   Cnv16_WxH.cpp
//! \author Дмитрий Рыжов
//! \brief  Функции векторного ядра.
//! 
//! \endif
//!
//------------------------------------------------------------------------

#include "nmpli.h"

void IMG_SetFilter7x5_16s32s(  nm32s * pWeights, nm64s ** pKernel)
{
	int *Mask=(int*)(*pKernel);

//	memcpy(Mask, pWeights, 7*5*sizeof(int));
	for(int j=0; j<5; j++)
		for(int i=0; i<7; i++)
			Mask[13*j+i]=pWeights[7*j+i];
//		return 65;
}

void IMG_SetFilter5x9_16s32s(  nm32s * pWeights, nm64s ** pKernel)
{
	int *Mask=(int*)(*pKernel);
//	memcpy(Mask, pWeights, 5*9*sizeof(int));
	for(int j=0; j<9; j++)
		for(int i=0; i<5; i++)
			Mask[13*j+i]=pWeights[5*j+i];
//		return 13*9;
}


void IMG_SetFilter9x5_16s32s(  nm32s * pWeights, nm64s ** pKernel)
{
	int *Mask=(int*)(*pKernel);
//	memcpy(Mask, pWeights, 9*5*sizeof(int));
	for(int j=0; j<5; j++)
		for(int i=0; i<9; i++)
			Mask[13*j+i]=pWeights[9*j+i];
//		return 65;
}

void IMG_SetFilter7x9_16s32s(  nm32s * pWeights, nm64s ** pKernel)
{
	int *Mask=(int*)(*pKernel);
//	memcpy(Mask, pWeights, 7*9*sizeof(int));
	for(int j=0; j<9; j++)
		for(int i=0; i<7; i++)
			Mask[13*j+i]=pWeights[7*j+i];
//		return 13*9;
}

void IMG_SetFilter9x9_16s32s(  nm32s * pWeights, nm64s ** pKernel)
{
	int *Mask=(int*)(*pKernel);
//	memcpy(Mask, pWeights, 9*9*sizeof(int));
	for(int j=0; j<9; j++)
		for(int i=0; i<9; i++)
			Mask[13*j+i]=pWeights[9*j+i];
//		return 13*9;
}

void IMG_SetFilter11x5_16s32s(  nm32s * pWeights, nm64s ** pKernel)
{
	int *Mask=(int*)(*pKernel);
//	memcpy(Mask, pWeights, 11*5*sizeof(int));
	for(int j=0; j<5; j++)
		for(int i=0; i<11; i++)
			Mask[13*j+i]=pWeights[11*j+i];
//		return 65;
}

void IMG_SetFilter13x5_16s32s(  nm32s * pWeights, nm64s ** pKernel)
{
	int *Mask=(int*)(*pKernel);
//	memcpy(Mask, pWeights, 13*5*sizeof(int));
	for(int j=0; j<5; j++)
		for(int i=0; i<13; i++)
			Mask[13*j+i]=pWeights[13*j+i];
//		return 65;
}

void IMG_SetFilter1x9_16s16s( nm8s * pWeights, nm8s * pKernel)
{
	//VEC_Cnv(pWeights,(nm16s*)*pKernel,9);
	VEC_Copy(pWeights,pKernel,16);
}

