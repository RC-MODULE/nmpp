//------------------------------------------------------------------------
//
//  $Workfile:: Mul_VxxVxx.cp $
//
//  ��������-��������� ����������
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:15 $
//
//! \if file_doc
//!
//! \file   Mul_VxxVxx.cpp
//! \author ������ �������
//! \brief  ������� ��������� ��� ��������.
//!
//! \endif
//!
//------------------------------------------------------------------------
#include "nmplv.h"
#include "malloc32.h"

int nmppsDotProd_32s32sm(
	const nm32s*		srcVec0,	//Input0 buffer		:long Local [Size].
	const nm32s*		srcVec1,	//Input1 buffer		:long Global[Size].
	int			size,		//Size of input vec
	nm64s*		dst,		//Output product
	nm64s*		tmp			//temporary buffer nm64s[size]
	)
{
	int alloc=0;
	if (tmp==0){
		tmp = nmppsMalloc_64s(size);
		if (tmp==0) return -1;
		alloc=1;
	}
	
	nmppsConvert_32s64s(srcVec1,tmp,size);
	nmppsDotProd_32s64s(srcVec0,tmp,size,dst);
	
	if (alloc)	
		nmppsFree(tmp);
	return 0;
}