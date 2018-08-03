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
#include "nmpp.h"
#include "memory.h"


void nmppsCopy_64s(const nm64s*	pSrcVec,		// Source array
			nm64s*	pDstVec,		// Destination array
			int			sizeInt64	// nSize of Source array in 64-bit longs; nSize=[0,1,2...]
		)
{
	//for(int idx=0;idx<sizeInt64;idx++)
	//	pDstVec[idx]=pSrcVec[idx];
	memcpy(pDstVec,pSrcVec,sizeInt64*8);
}

void nmppsCopy_32s(const nm32s*	pSrcVec,		// Source array							:long Global[sizeInt32/2]
			nm32s*	pDstVec,		// Destination array					:long Local [sizeInt32/2]
			int		sizeInt32	// nSize of Source array in 32-bit ints; :sizeInt32= [0,2,4.....]
		)
{
//	for(int idx=0;idx<sizeInt32;idx++)
//		pDstVec[idx]=pSrcVec[idx];
	memcpy(pDstVec,pSrcVec,sizeInt32*4);
}

void nmppsCopy_16s(const nm16s*	pSrcVec,		// Source array							:long Global[sizeInt16/4]
			nm16s*	pDstVec,		// Destination array					:long Local [sizeInt16/4]
			int		sizeInt16	// nSize of Source array in 16-bit shorts:sizeInt16= [0,4,8....]
		)
{
	//for(int idx=0;idx<sizeInt16;idx++)
	//	pDstVec[idx]=pSrcVec[idx];
	memcpy(pDstVec,pSrcVec,sizeInt16*2);
}
		
void nmppsCopy_8s(const nm8s*	pSrcVec,		// Source array							:long Global[sizeInt8/8]
			nm8s*	pDstVec,		// Destination array					:long Local [sizeInt8/8]
			int		sizeInt8	// nSize of Source array in 8-bit chars; :sizeInt8=  [0,8,16.....]
		)
{
	//for(int idx=0;idx<sizeInt8;idx++)
	//	pDstVec[idx]=pSrcVec[idx];
	memcpy(pDstVec,pSrcVec,sizeInt8);
}

void nmppsCopy_4s(const nm4s*	pSrcVec,		// Source array							:long Global[sizeInt4/16]
			nm4s*	pDstVec,		// Destination array					:long Local [sizeInt4/16]
			int		sizeInt4	// nSize of Source array in 4-bit chars; :sizeInt4=  [0,16,32.....]
		)
{
	//for(int idx=0;idx<sizeInt8;idx++)
	//	pDstVec[idx]=pSrcVec[idx];
	memcpy(pDstVec,pSrcVec,(sizeInt4>>4)<<3);
}

void nmppsCopy_2s(const nm2s*	pSrcVec,		// Source array							:long Global[sizeInt2/32]
			nm2s*	pDstVec,		// Destination array					:long Local [sizeInt2/32]
			int		sizeInt2	// nSize of Source array in 2-bit chars; :sizeInt2=  [0,32,64.....]
		)
{
	//int i,iSize = sizeInt2>>5;
	//long long int *src = pSrcVec;
	//long long int *dst = pDstVec;
	//for(i=0;i<iSize;i++)
	//	dst[i]=src[i];
	memcpy(pDstVec,pSrcVec,(sizeInt2>>5)<<3);
	
}

void nmppsCopyua_8s(const nm8s*			pSrcVec,		// input buffer		:long Long[...]
		int				nOffset,	// start copy from index SrcVecIndx	:[0,1,2,3,4...]
		nm8s*			pDstVec,		// output buffer	:long Long[DstVecSize>>3]	
		int				nSize		// buffer size in 8-bit elemetns	:[0,8,16,24...]
		)
{
	int i;
	for (i=0;i<nSize;i++)
		pDstVec[i]=pSrcVec[nOffset+i];
}
