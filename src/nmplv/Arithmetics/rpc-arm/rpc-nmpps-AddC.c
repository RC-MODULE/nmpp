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
// Increment of vec elements by constant value
// pDstVec[i]=pSrcVec[i]+Increment
void nmppsAddC_8s(
		const nm8s*			pSrcVec,			// input buffer		:long Local [VecSize/8]
		int8b			nVal,				// increment		:Increment=[-128...+127]
		nm8s*			pDstVec,			// output buffer	:long Global[VecSize/8]
		int				nSize			// size of input buffer in 8 bit elements. nSize=[8,16,32...]
		)
{
	RPC_HOST_PIPI("nmppsAddC_8s",pSrcVec,nVal,pDstVec,nSize,1);
}


/////////////////////////////////////////////////////////////////////////////////////////
// Increment of vec elements by constant value
// pDstVec[i]=Increment+pSrcVec[i]
void nmppsAddC_16s(
		const nm16s*			pSrcVec,				// input buffer		:long Local [VecSize/4]
		int16b			nVal,					// increment		:
		nm16s*			pDstVec,				// output buffer	:long Global[VecSize/4]
		int				nSize				// size of input buffer in 16-bit elements. nSize=[0,4,8,12...]
		)
{
	RPC_HOST_PIPI("nmppsAddC_16s",pSrcVec,nVal,pDstVec,nSize,2);
}



/////////////////////////////////////////////////////////////////////////////////////////
// Increment of vec elements by constant value
// pDstVec[i]=pSrcVec[i]+Increment
void nmppsAddC_32s(
		const nm32s*			pSrcVec,			// input buffer		:long Local [VecSize/2]
		int				nVal,				// increment		:
		nm32s*			pDstVec,			// output buffer	:long Global[VecSize/2]
		int				nSize			// size of input buffer in 32-bit elements. nSize=[0,2,4,6...]
		)
{
	RPC_HOST_PIPI("nmppsAddC_32s",pSrcVec,nVal,pDstVec,nSize,4);
}

void nmppsAddC_64s(
		const nm64s*			src,				// input buffer		:long Local [VecSize/8]
		int64b			val,				// increment		:Increment=[-128...+127]
		nm64s*			dst,				// output buffer	:long Global[VecSize/8]
		int				size				// size of input buffer in 8 bit elements. nSize=[8,16,32...]
		)
{
	RPC_HOST_PIPI("nmppsAddC_64s",src,val,dst,size,8);
}




