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
// Absolute difference calculation
void nmppsAbsDiff_8s(
		const nm8s*			pSrcVec1,	// input buffer		:long Local			[VecSize/8]
		const nm8s*			pSrcVec2,	// input buffer		:long Local/Global	[VecSize/8]
		nm8s*			pDstVec,		// output buffer	:long Global		[VecSize/8]
		int				nSize		// size of input buffer in 32 bit elements. nSize=[0,8,16,32...]
		)
{
	RPC_HOST_PPPI("nmppsAbsDiff_8s",pSrcVec1,pSrcVec2,pDstVec,nSize,1);
}


/////////////////////////////////////////////////////////////////////////////////////////
// Absolute difference calculation
// pDstVec[i]=|pSrcVec1[i]-pSrcVec2[i]|
void nmppsAbsDiff_16s(
		const nm16s*			pSrcVec1,		// input buffer		:long Local	[VecSize/4]
		const nm16s*			pSrcVec2,		// input buffer		:long Any   [VecSize/4]
		nm16s*			pDstVec,			// output buffer	:long Global[VecSize/4]
		int				nSize			// size of input buffer in 32 bit elements. nSize=[0,4,8...]
		)
{
	RPC_HOST_PPPI("nmppsAbsDiff_16s",pSrcVec1,pSrcVec2,pDstVec,nSize,2);
}


/////////////////////////////////////////////////////////////////////////////////////////
// Absolute difference calculation
// pDstVec[i]=|pSrcVec1[i]-pSrcVec2[i]|
void nmppsAbsDiff_32s(
		const nm32s*			pSrcVec1,		// input buffer		:long Local	[VecSize/2]
		const nm32s*			pSrcVec2,		// input buffer		:long Any   [VecSize/2]
		nm32s*			pDstVec,			// output buffer	:long Global[VecSize/2]
		int				nSize			// size of input buffer in 32 bit elements. nSize=[0,2,4..]
		)
{
	RPC_HOST_PPPI("nmppsAbsDiff_32s",pSrcVec1,pSrcVec2,pDstVec,nSize,4);

}



/////////////////////////////////////////////////////////////////////////////////////////
// Absolute difference calculation
// pDstVec[i]=|pSrcVec1[i]-pSrcVec2[i]|
void nmppsAbsDiff_64s(
		const nm64s*			pSrcVec1,		// input buffer		:long Local	[VecSize/2]
		const nm64s*			pSrcVec2,		// input buffer		:long Any   [VecSize/2]
		nm64s*			pDstVec,		// output buffer	:long Global[VecSize/2]
		int				nSize			// size of input buffer in 32 bit elements. nSize=[0,2,4..]
		)
{
	RPC_HOST_PPPI("nmppsAbsDiff_64s",pSrcVec1,pSrcVec2,pDstVec,nSize,8);
}


/////////////////////////////////////////////////////////////////////////////////////////
// Logical absolute difference calculation
void nmppsAbsDiff1_8s(
		const nm8s*			pSrcVec1,	// input buffer		:long Local			[VecSize/8]
		const nm8s*			pSrcVec2,	// input buffer		:long Local/Global	[VecSize/8]
		nm8s*			pDstVec,	// output buffer	:long Global		[VecSize/8]
		int				nSize		// size of input buffer in 32 bit elements. nSize=[0,8,16,32...]
		)
{
	RPC_HOST_PPPI("nmppsAbsDiff1_8s",pSrcVec1,pSrcVec2,pDstVec,nSize,1);
}



