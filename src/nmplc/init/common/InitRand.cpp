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
#include "nmplc.h"
////////////////////////////////////////////////////////////////////////////
//  Random initalization of 32-bit buffer
unsigned SCL_Randomize=1;

//! 
//! \perfinclude _SCL_Rand__Fiii.html
//! 

int SCL_Rand(
		int Min,
		int Max)
{

	unsigned int R=SCL_Rand();
	R%=unsigned(Max-Min+1);
	int X=int(R)+Min;
	return X;
}

int SCL_Rand(
		int Min,
		int Max,
		int	Divisible)
{
	unsigned int R=SCL_Rand();
	R%=unsigned(Max-Min+1);
	int X=int(R)+Min;
	X/=Divisible;
	X*=Divisible;
	return X;
}

////////////////////////////////////////////////////////////////////////////
//  Random initalization of 32-bit buffer

//! 
//! \perfinclude _SCL_Rand__Fv.html
//! 

int SCL_Rand()
{

	SCL_Randomize=1664525L*SCL_Randomize+1013904223L;
	unsigned int R=SCL_Randomize>>16;
	SCL_Randomize=1664525L*SCL_Randomize+1013904223L;
	R|=(SCL_Randomize&0xFFFF0000);
	return R;
}
