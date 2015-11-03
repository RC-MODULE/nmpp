//------------------------------------------------------------------------
//
//  $Workfile:: Copy.cp $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:15 $
//
//! \if file_doc
//!
//! \file   Copy.cpp
//! \author Сергей Мушкаев
//! \brief  Функции инициализации и копирования для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------
//#include "Vector.h"
#include "nmplv.h"
#include "memory.h"


void nmppsCopy_64s(nm64s*	pSrcVec,		// Source array
			nm64s*	pDstVec,		// Destination array
			int			SizeInt64	// nSize of Source array in 64-bit longs; nSize=[0,1,2...]
		)
{
	//for(int idx=0;idx<SizeInt64;idx++)
	//	pDstVec[idx]=pSrcVec[idx];
	memcpy(pDstVec,pSrcVec,SizeInt64*8);
}

void nmppsCopy_32s(nm32s*	pSrcVec,		// Source array							:long Global[SizeInt32/2]
			nm32s*	pDstVec,		// Destination array					:long Local [SizeInt32/2]
			int		SizeInt32	// nSize of Source array in 32-bit ints; :SizeInt32= [0,2,4.....]
		)
{
//	for(int idx=0;idx<SizeInt32;idx++)
//		pDstVec[idx]=pSrcVec[idx];
	memcpy(pDstVec,pSrcVec,SizeInt32*4);
}

void nmppsCopy_16s(nm16s*	pSrcVec,		// Source array							:long Global[SizeInt16/4]
			nm16s*	pDstVec,		// Destination array					:long Local [SizeInt16/4]
			int		SizeInt16	// nSize of Source array in 16-bit shorts:SizeInt16= [0,4,8....]
		)
{
	//for(int idx=0;idx<SizeInt16;idx++)
	//	pDstVec[idx]=pSrcVec[idx];
	memcpy(pDstVec,pSrcVec,SizeInt16*2);
}
		
void nmppsCopy_8s(nm8s*	pSrcVec,		// Source array							:long Global[SizeInt8/8]
			nm8s*	pDstVec,		// Destination array					:long Local [SizeInt8/8]
			int		SizeInt8	// nSize of Source array in 8-bit chars; :SizeInt8=  [0,8,16.....]
		)
{
	//for(int idx=0;idx<SizeInt8;idx++)
	//	pDstVec[idx]=pSrcVec[idx];
	memcpy(pDstVec,pSrcVec,SizeInt8);
}

void nmppsCopyua_8s(nm8s*			pSrcVec,		// input buffer		:long Long[...]
		int				nOffset,	// start copy from index SrcVecIndx	:[0,1,2,3,4...]
		nm8s*			pDstVec,		// output buffer	:long Long[DstVecSize>>3]	
		int				nSize		// buffer size in 8-bit elemetns	:[0,8,16,24...]
		)
{
	int i;
	for (i=0;i<nSize;i++)
		pDstVec[i]=pSrcVec[nOffset+i];
}
