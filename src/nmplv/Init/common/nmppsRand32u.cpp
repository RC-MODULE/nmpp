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
static long long 				Randomize=-1;
////////////////////////////////////////////////////////////////////////////
//  Random initalization of 32-bit buffer

 
//! 
//! \perfinclude _nmppsRandUniform__FPUiiUi_.html
//! 
extern "C"{

void nmppsRandUniform_32f_integer(
		nm32f*	pDstVec,		// array									:int Global [SizeInt]
		int		nSize,		// nSize of Source array in 32-bit elements	:nSize=    [0,1,2,3,4...]
		int     hi,
		int     low
		)
{
	const int range = (int)(1.0/(0x100000000));
	int i;
	int r;
	int result_int;
	unsigned int R;
	int b = (int) (0.5*(hi+low));
	int k = (hi-low)*range;
	if((low == 0)&(hi == 0)){return;}
	
	for(i=0;i<nSize;i++){
		R=(unsigned int)(Randomize<<63);
		Randomize>>=1;
		Randomize|=R;
		Randomize=1664525*Randomize+1013904223;
		r=(unsigned int)Randomize;
		result_int = k*r+b;
		pDstVec[i] = (float)result_int; 
	}
	return;
}

};