//------------------------------------------------------------------------
//
//  $Workfile:: Add.cpp    $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:15 $
//
//! \if file_doc
//!
//! \file   Remap.cpp
//! \author Сергей Мушкаев
//! \brief  Арифметические функции 
//!
//! \endif
//!
//------------------------------------------------------------------------
#include "rpc-host.h"
#include "nmtype.h"





/////////////////////////////////////////////////////////////////////////////////////////
// Summation of two char vectors
void nmppsAdd_8s(
		const nm8s*			pSrcVec1,		// input buffer		:long Local [VecSize/8]
		const nm8s*			pSrcVec2,		// input buffer		:long Local [VecSize/8]
		nm8s*			pDstVec,			// output buffer	:long Global[VecSize/8]
		int				nSize			// size of input buffer in 8 bit elements. nSize=[0,8,16,24...]
		)
{
	RPC_HOST_PPPI("nmppsAdd_8s",pSrcVec1,pSrcVec2,pDstVec,nSize,1);
}

/////////////////////////////////////////////////////////////////////////////////////////
// Summation of two short vectors
void nmppsAdd_16s(
		const nm16s*			pSrcVec1,		// input buffer		:long Local [VecSize/4]
		const nm16s*			pSrcVec2,		// input buffer		:long Local [VecSize/4]
		nm16s*			pDstVec,			// output buffer	:long Global[VecSize/4]
		int				nSize			// size of input buffer in 16-bit elements. nSize=[0,4,8,12..]
		)
{
	RPC_HOST_PPPI("nmppsAdd_16s",pSrcVec1,pSrcVec2,pDstVec,nSize,2);
}

/////////////////////////////////////////////////////////////////////////////////////////
// Summation of two int vectors
void nmppsAdd_32s(
		const nm32s*			pSrcVec1,		// input buffer		:long Local [VecSize/2]
		const nm32s*			pSrcVec2,		// input buffer		:long Local [VecSize/2]
		nm32s*			pDstVec,			// output buffer	:long Global[VecSize/2]
		int				nSize			// size of input buffer in 32-bit elements. nSize=[0,2,4,6...]
		)
{
	RPC_HOST_PPPI("nmppsAdd_32s",pSrcVec1,pSrcVec2,pDstVec,nSize,4);
}

/////////////////////////////////////////////////////////////////////////////////////////
// Summation of two long vectors
void nmppsAdd_64s(
		const nm64s*		pSrcVec1,		// input buffer		:long Local [nSize]
		const nm64s*		pSrcVec2,		// input buffer		:long Local [nSize]
		nm64s*		pDstVec,			// output buffer	:long Global[nSize]
		int				nSize			// size of input buffer in 64-bit elements. nSize=[0,1,2,3...]
		)
{
	RPC_HOST_PPPI("nmppsAdd_64s",pSrcVec1,pSrcVec2,pDstVec,nSize,8);
}


/////////////////////////////////////////////////////////////////////////////////////////
// Summation of two long complex vectors
void nmppsAdd_64sc(const nm64sc *pSrcVec1, const nm64sc *pSrcVec2, nm64sc *pDstVec, int nSize)
{
	RPC_HOST_PPPI("nmppsAdd_64sc",pSrcVec1,pSrcVec2,pDstVec,nSize,16);
}


