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
unsigned nmppsRandomize_=1;

//! 
//! \perfinclude _nmppsRand__Fiii_.html
//! 

int nmppsRand_(
		int Min,
		int Max)
{
	unsigned int R=nmppsRand();
	R%=unsigned(Max-Min+1);
	int X=int(R)+Min;
	return X;
}

int nmppsRand_(
		int Min,
		int Max,
		int	Divisible)
{
	unsigned int R=nmppsRand();
	R%=unsigned(Max-Min+1);
	int X=int(R)+Min;
	X/=Divisible;
	X*=Divisible;
	return X;
}

////////////////////////////////////////////////////////////////////////////
//  Random initalization of 32-bit buffer

//! 
//! \perfinclude _nmppsRand__Fv_.html
//! 

int nmppsRand_()
{

	nmppsRandomize_=1664525L*nmppsRandomize_+1013904223L;
	unsigned int R=nmppsRandomize_>>16;
	nmppsRandomize_=1664525L*nmppsRandomize_+1013904223L;
	R|=(nmppsRandomize_&0xFFFF0000);
	return R;
}
