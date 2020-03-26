//------------------------------------------------------------------------
//
//  $Workfile:: InitRand.cp $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:02 $
//
//! \if file_doc
//!
//! \file   InitRand.cpp
//! \author Сергей Мушкаев
//! \brief  Функции инициализации и копирования для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------
#include "nmtype.h"
////////////////////////////////////////////////////////////////////////////
//  Random initalization of 32-bit buffer

 
//! 
//! \perfinclude _nmppsRandUniform__FPUiiUi_.html
//! 

extern "C"{
static long long				Randomize=-1;
////////////////////////////////////////////////////////////////////////////
//  Random initialization of 64-bit Buffer
void nmppsRand_32f(
		nm32f*			pDstVec,		// array									:int Global [SizeInt]
		int				nSize, 		// nSize of Source array in 64-bit elements	:nSize=    [0,1,2,3,4...]
		float low,
		float hi
		)
{
	int i;
	int r;
	unsigned int rounder;
	float k,temp;
	float* pointer_float;
	int* pointer;
	const float range = 1.0/(float)(0x100000000);
	float b = 0.5*(hi+low);
	if((low == 0)&(hi == 0)){return;}
	k = (hi-low)*range;
	for(i=0;i<nSize;i++)
	{
		unsigned long long R=Randomize<<63;
		Randomize>>=1;
		Randomize|=R;
		Randomize=1664525*Randomize+1013904223;
		r=Randomize;
		temp = k*r+b;
		pointer = (int*)&temp;
		rounder = *pointer;
		rounder += 0x1;
		rounder>>=11;
		rounder<<=11;
		pointer_float = (float*)&rounder;
		pDstVec[i] = *pointer_float;
	}
	
	return;
	//Randomize=Rand;
}

};
