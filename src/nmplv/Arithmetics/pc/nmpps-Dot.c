//------------------------------------------------------------------------
//
//  $Workfile:: Mul_VxxVxx.cp $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:15 $
//
//! \if file_doc
//!
//! \file   Mul_VxxVxx.cpp
//! \author Сергей Мушкаев
//! \brief  Функции умножения для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------

#include "nmtype.h"


//////////////////////////////////////////////////////////////////////////////////////
// Vector multiplication
//////////////////////////////////////////////////////////////////////////////////////
void nmppsDotProd_64s64s(
const	nm64s*	srcVec0,	//Input0 buffer		:long Local [Size].
const	nm64s*	srcVec1,	//Input1 buffer		:long Global[Size].
		int		size,		//Size of input vec
		int64b*	dst			//Output buffer		:long Any
	)
{

	int i;
	*dst=0;
	for (i=0; i<size; i++)
		*dst += ((nm64s)srcVec0[i])*((nm64s)srcVec1[i]);

}

//////////////////////////////////////////////////////////////////////////////////////
void nmppsDotProd_32s64s(
const	nm32s*	srcVec0,	//Input0 buffer		:long Local [Size].
const	nm64s*	srcVec1,	//Input1 buffer		:long Global[Size].
		int		size,		//Size of input vec
		int64b*	dst			//Output buffer		:long Any
	)
{
	int i;
	*dst = 0;
	for (i=0; i<size; i++)
		*dst += ((nm64s)srcVec0[i])*((nm64s)srcVec1[i]);

}

//////////////////////////////////////////////////////////////////////////////////////
void nmppsDotProd_16s64s(
const	nm16s*	srcVec0,	//Input0 buffer		:long Local [Size].
const	nm64s*	srcVec1,	//Input1 buffer		:long Global[Size].
		int		size,		//Size of input vec
		int64b*	dst			//Output buffer		:long Any
	)
{
	int i;
	*dst = 0;
	for (i=0; i<size; i++)
		*dst += ((nm64s)srcVec0[i])*((nm64s)srcVec1[i]);
}

//////////////////////////////////////////////////////////////////////////////////////
void nmppsDotProd_8s64s(
const	nm8s*	srcVec0,	//Input0 buffer		:long Local [Size].
const	nm64s*	srcVec1,	//Input1 buffer		:long Global[Size].
		int		size,		//Size of input vec
		int64b*	dst			//Output buffer		:long Any
	)
{
	int i;
	*dst = 0;
	for (i=0; i<size; i++)
		*dst += ((nm64s)srcVec0[i])*((nm64s)srcVec1[i]);

}

