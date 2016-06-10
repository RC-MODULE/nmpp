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
#include "nmplv.h"
#include "malloc32.h"

int nmppsDotProd_8s8sm(
	const nm8s*		srcVec0,	//Input0 buffer		:long Local [Size].
	const nm8s*		srcVec1,	//Input1 buffer		:long Global[Size].
	int			size,		//Size of input vec
	nm64s*		dst,		//Output product
	nm64s*		tmp
	)
{
	int alloc=0;
	if (tmp==0){
		tmp = nmppsMalloc_64s(size);
		if (tmp==0) return -1;
		alloc=1;
	}
	
	nmppsConvert_8s64s(srcVec1,tmp,size);
	nmppsDotProd_8s64s(srcVec0,tmp,size,dst);
	
	if (alloc)	
		nmppsFree(tmp);
	return 0;
}
