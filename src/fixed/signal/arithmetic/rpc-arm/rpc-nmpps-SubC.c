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
// Decrement of vec elements by constant value
// pDstVec[i]=pSrcVec[i]-Decrement
void nmppsSubC_8s(
		const nm8s*			pSrcVec,			// input buffer		:long Local [VecSize/8]
		int8b			nVal,				// decrement		:
		nm8s*			pDstVec,			// output buffer	:long Global[VecSize/8]
		int				nSize		// size of input buffer in 8-bit elements. nSize=[0,8,16,32...]
		)
{
	RPC_HOST_PIPI("nmppsSubC_8s",pSrcVec,nVal,pDstVec,nSize,1);
}


/////////////////////////////////////////////////////////////////////////////////////////
// Decrement of vec elements by constant value
// pDstVec[i]=pSrcVec[i]-Decrement
void nmppsSubC_16s(
		const nm16s*			pSrcVec,			// input buffer		:long Local [VecSize/4]
		int16b			nVal,				// decrement		:
		nm16s*			pDstVec,			// output buffer	:long Global[VecSize/4]
		int				nSize		// size of input buffer in 8-bit elements. nSize=[0,4,8,12...]
		)
{
	RPC_HOST_PIPI("nmppsSubC_16s",pSrcVec,nVal,pDstVec,nSize,2);
}


/////////////////////////////////////////////////////////////////////////////////////////
// Decrement of vec elements by constant value
// pDstVec[i]=pSrcVec[i]-Decrement
void nmppsSubC_32s(
		const nm32s*			pSrcVec,			// input buffer		:long Local [VecSize/2]
		int32b			nVal,				// decrement		:
		nm32s*			pDstVec,			// output buffer	:long Global[VecSize/2]
		int				nSize		// size of input buffer in 32-bit elements. nSize=[0,2,4,6...]
		)
{
	RPC_HOST_PIPI("nmppsSubC_32s",pSrcVec,nVal,pDstVec,nSize,4);
}


/////////////////////////////////////////////////////////////////////////////////////////
// pDstVec[i]=pSrcVec[i]-Decrement
void nmppsSubC_64s(
		const nm64s*			pSrcVec,			// input buffer		:long Local [VecSize/2]
		int64b			nVal,				// decrement		:
		nm64s*			pDstVec,			// output buffer	:long Global[VecSize/2]
		int				nSize		// size of input buffer in 32-bit elements. nSize=[0,2,4,6...]
		)
{
	RPC_HOST_PIPI("nmppsSubC_64s",pSrcVec,nVal,pDstVec,nSize,8);
}


