//------------------------------------------------------------------------
//
//  $Workfile:: Mul_VxxNxx.cp $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:15 $
//
//! \if file_doc
//!
//! \file   Mul_VxxNxx.cpp
//! \author Сергей Мушкаев
//! \brief  Функции умножения для векторов. 
//!
//! \endif
//!
//------------------------------------------------------------------------

#include "rpc-host.h"
#include "nmtype.h"
/////////////////////////////////////////////////////////////////////////////////////////
// Multiplying 64-bit buffer elements by 64-bit scalar value
void nmppsMulC_64s(
		  nm64s*		pSrcVec,				// input  buffer		:long Local  [nSize]
		  nm64s			MulN,				// 64-bit scalar value
		  nm64s*		pDstVec,				// output buffer		:long Global [nSize]
			int			nSize				// size of input buffer in 64-bit elements. nSize=[0,1,2,3..]
		)
{
	RPC_HOST_PLPI("nmppsMulC_64s",pSrcVec,MulN,pDstVec,nSize,8,8);
}

/////////////////////////////////////////////////////////////////////////////////////////
// Multiplying 32-bit buffer elements by 64-bit scalar value
void nmppsMulC_32s64s(
			nm32s*		pSrcVec,			// input  buffer		:long Local  [VecSize/2]
			nm64s		MulN,			// 64-bit scalar value
			nm64s*		pDstVec,			// output buffer		:long Global [nSize]
			int			nSize			// size of input buffer in 32-bit elements. nSize=[0,2,4,6...]
		)
{
	RPC_HOST_PLPI("nmppsMulC_32s64s",pSrcVec,MulN,pDstVec,nSize,4,8);
}

/////////////////////////////////////////////////////////////////////////////////////////
// Multiplying 16-bit buffer elements by 16-bit scalar value
void nmppsMulC_16s(
			nm16s*		pSrcVec,		// input  buffer		:long Local  [VecSize/4]
			int			MulN,			// 32-bit scalar value
			nm16s*		pDstVec,		// output buffer		:long Global [VecSize/2]
			int			nSize			// size of input buffer in 16-bit elements. nSize=[0,4,8...]
		)
{
	RPC_HOST_PIPI2("nmppsMulC_16s",pSrcVec,MulN,pDstVec,nSize,2,2);
}


/////////////////////////////////////////////////////////////////////////////////////////
// Multiplying 16-bit buffer elements by 32-bit scalar value
void nmppsMulC_16s32s(
			nm16s*		pSrcVec,		// input  buffer		:long Local  [VecSize/4]
			int			MulN,				// 32-bit scalar value
			nm32s*		pDstVec,		// output buffer		:long Global [VecSize/2]
			int			nSize			// size of input buffer in 16-bit elements. nSize=[0,4,8...]
		)
{
	RPC_HOST_PIPI2("nmppsMulC_16s32s",pSrcVec,MulN,pDstVec,nSize,2,4);
}


/////////////////////////////////////////////////////////////////////////////////////////
// Multiplying 32-bit buffer elements by scalar value
void nmppsMulC_32s(
			nm32s*		pSrcVec,			// input vec			:long Local  [VecSize/2]
			int			MulN,				// 32-bit scalar value
			nm32s*		pDstVec,			// output vec		:long Global [VecSize/2]
			int			nSize			// size of input buffer in 32-bit elements. nSize=[0,2,4,6...]
		)
{
	RPC_HOST_PIPI2("nmppsMulC_32s",pSrcVec,MulN,pDstVec,nSize,4,4);
}



/////////////////////////////////////////////////////////////////////////////////////////
// Multiplying 8-bit buffer elements by 16-bit scalar value
void nmppsMulC_8s16s(
			nm8s*		pSrcVec,		// input  buffer					:long Local  [VecSize/8]
			int16b		MulN,				// 16-bit scalar value
			nm16s*		pDstVec,		// output buffer					:long Global [VecSize/4]
			int			nSize			// size of input buffer in 8-bit elements. nSize=[0,8,16...]
		)
{
	RPC_HOST_PIPI2("nmppsMulC_8s16s",pSrcVec,MulN,pDstVec,nSize,1,2);
}


/////////////////////////////////////////////////////////////////////////////////////////
// Multiplying 8-bit buffer elements by 8-bit scalar value
void nmppsMulC_8s(
			nm8s*		pSrcVec,		// input  buffer					:long Local  [VecSize/8]
			int8b		MulN,			// 8-bit scalar value
			nm8s*		pDstVec,		// output buffer					:long Global [VecSize/8]
			int			nSize			// size of input buffer in 8-bit elements. nSize=[0,8,16...]
		)
{
	RPC_HOST_PIPI2("nmppsMulC_8s",pSrcVec,MulN,pDstVec,nSize,1,1);
}



