//------------------------------------------------------------------------
//
//  $Workfile:: Abs.cpp    $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:15 $
//
//! \if file_doc
//!
//! \file   Abs.cpp
//! \author Сергей Мушкаев
//! \brief  Арифметические функции 
//!
//! \endif
//!
//------------------------------------------------------------------------
#include "rpc-host.h"
#include "nmtype.h"

/////////////////////////////////////////////////////////////////////////////////////////
// Absolute value calculation
//void nmppsAbs_4s(
//		nm4s*			pSrcVec,		// input buffer		:long Local [VecSize/8]
//		nm4s*			pDstVec,		// output buffer	:long Global[VecSize/8]
//		int				nSize		// size of input buffer in 8 bit elements. nSize=[8,16,32...]
//		)
//{
//	RPC_HOST_PPI("nmppsAbs_4s",pSrcVec,pDstVec,nSize/2);
//}


void nmppsAbs_8s(
		const nm8s*			pSrcVec,		// input buffer		:long Local [VecSize/8]
		nm8s*			pDstVec,		// output buffer	:long Global[VecSize/8]
		int				nSize		// size of input buffer in 8 bit elements. nSize=[8,16,32...]
		)
{
	RPC_HOST_PPI("nmppsAbs_8s",pSrcVec,pDstVec,nSize,1);
}


/////////////////////////////////////////////////////////////////////////////////////////
// Absolute value calculation
void nmppsAbs_16s(
		const nm16s*			pSrcVec,		// input buffer		:long Local [VecSize/4]
		nm16s*			pDstVec,		// output buffer	:long Global[VecSize/4]
		int				nSize		// size of input buffer in 8 bit elements. nSize=[0,4,8,..]
		)
{
	RPC_HOST_PPI("nmppsAbs_16s",pSrcVec,pDstVec,nSize,2);
}



/////////////////////////////////////////////////////////////////////////////////////////
// Absolute value calculation
void nmppsAbs_32s(
		const nm32s*			pSrcVec,		// input buffer		:long Local [VecSize/2]
		nm32s*			pDstVec,		// output buffer	:long Global[VecSize/2]
		int				nSize		// size of input buffer in 32 bit elements. nSize=[2,4,6...]
		)
{
	RPC_HOST_PPI("nmppsAbs_32s",pSrcVec,pDstVec,nSize,4);
}



/////////////////////////////////////////////////////////////////////////////////////////
// Absolute value calculation
void nmppsAbs_64s(
		const nm64s*			pSrcVec,		// input buffer		:long Local [VecSize/2]
		nm64s*			pDstVec,		// output buffer	:long Global[VecSize/2]
		int				nSize		// size of input buffer in 32 bit elements. nSize=[2,4,6...]
		)
{
	RPC_HOST_PPI("nmppsAbs_64s",pSrcVec,pDstVec,nSize,8);
}


