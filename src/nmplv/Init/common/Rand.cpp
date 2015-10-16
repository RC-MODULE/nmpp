//------------------------------------------------------------------------
//
//  $Workfile:: InitRand.cp $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/01/12 13:30:01 $
//
//! \if file_doc
//!
//! \file   InitRand.cpp
//! \author Сергей Мушкаев
//! \brief  Функции инициализации для скаляров.
//!
//! \endif
//!
//------------------------------------------------------------------------
#include "nmtype.h"
#include "nmplv.h"


////////////////////////////////////////////////////////////////////////////
//  Random initalization of 32-bit buffer
unsigned VEC_Randomize=1;

//! 
//! \perfinclude _VEC_Rand__Fiii.html
//! 

int VEC_Rand(
		int Min,
		int Max)
{
	unsigned int R=VEC_Rand();
	R%=unsigned(Max-Min+1);
	int X=int(R)+Min;
	return X;
}

int VEC_Rand(
		int Min,
		int Max,
		int	Divisible)
{
	unsigned int R=VEC_Rand();
	R%=unsigned(Max-Min+1);
	int X=int(R)+Min;
	X/=Divisible;
	X*=Divisible;
	return X;
}

////////////////////////////////////////////////////////////////////////////
//  Random initalization of 32-bit buffer

//! 
//! \perfinclude _VEC_Rand__Fv.html
//! 

int VEC_Rand()
{

	VEC_Randomize=1664525L*VEC_Randomize+1013904223L;
	unsigned int R=VEC_Randomize>>16;
	VEC_Randomize=1664525L*VEC_Randomize+1013904223L;
	R|=(VEC_Randomize&0xFFFF0000);
	return R;
}
