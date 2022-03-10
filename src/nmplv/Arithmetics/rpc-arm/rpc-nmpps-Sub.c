//------------------------------------------------------------------------
//
//  $Workfile:: Sub.cpp  $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:15 $
//
//! \if file_doc
//!
//! \file   Sub.cpp
//! \author Сергей Мушкаев
//! \brief  Арифметические функции 
//!
//! \endif
//!
//------------------------------------------------------------------------


#include "nmtype.h"
#include "rpc-host.h"

/////////////////////////////////////////////////////////////////////////////////////////
// Subtraction of two char buffers
// 2826 ticks per 10240 elements with C++ call (0.276 clocks per element)
// The order of intermediate data transmissions in function is:
//		Buf1[],Buf2			=> pDstVec[]				- Subtraction	(in-place is supported)
void nmppsSub_8s(
		const nm8s*			pSrcVec1,	// input buffer		:long Local [VecSize/8]
		const nm8s*			pSrcVec2,	// input buffer		:long Local [VecSize/8]
		nm8s*			pDstVec,		// output buffer	:long Global[VecSize/8]
		int				nSize		// size of input buffer in 32 bit elements. nSize=[8,16,32...]
		)
{
	RPC_HOST_PPPI("nmppsSub_8s",pSrcVec1,pSrcVec2,pDstVec,nSize,1);
}



//////////////////////////////////////////////////////////////////////////////////////
// Subtraction of two short vectors
void nmppsSub_16s(
		const nm16s*			pSrcVec1,		// input buffer		:long Local [VecSize/4]
		const nm16s*			pSrcVec2,		// input buffer		:long Local [VecSize/4]
		nm16s*			pDstVec,			// output buffer	:long Global[VecSize/4]
		int				nSize			// size of input buffer in 16-bit elements. nSize=[0,4,8,12..]
		)
{
	RPC_HOST_PPPI("nmppsSub_16s",pSrcVec1,pSrcVec2,pDstVec,nSize,2);
}


//////////////////////////////////////////////////////////////////////////////////////
// Subtraction of two int vectors
void nmppsSub_32s(
		const nm32s*			pSrcVec1,		// input buffer		:long Local [VecSize/2]
		const nm32s*			pSrcVec2,		// input buffer		:long Local [VecSize/2]
		nm32s*			pDstVec,			// output buffer	:long Global[VecSize/2]
		int				nSize			// size of input buffer in 32-bit elements. nSize=[0,2,4,6...]
		)
{
	RPC_HOST_PPPI("nmppsSub_32s",pSrcVec1,pSrcVec2,pDstVec,nSize,4);
}

//////////////////////////////////////////////////////////////////////////////////////
// Subtraction of two __int64 vectors
void nmppsSub_64s(
	  const nm64s*			pSrcVec1,		// input buffer		:long Local [nSize]
	  const nm64s*			pSrcVec2,		// input buffer		:long Local [nSize]
	  nm64s*			pDstVec,			// output buffer	:long Global[nSize]
		int				nSize			// size of input buffer in 32-bit elements. nSize=[0,1,2,3,4...]
		)
{
	RPC_HOST_PPPI("nmppsSub_64s",pSrcVec1,pSrcVec2,pDstVec,nSize,8);
}


//////////////////////////////////////////////////////////////////////////////////////
// Subtraction of two __int64 complex vectors
void nmppsSub_64sc(nm64sc *pSrcVec1, nm64sc *pSrcVec2, nm64sc *pDstVec, int nSize)
{
	RPC_HOST_PPPI("nmppsSub_64sc",pSrcVec1,pSrcVec2,pDstVec,nSize,16);
}


