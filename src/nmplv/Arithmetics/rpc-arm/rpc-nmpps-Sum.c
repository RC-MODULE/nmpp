//------------------------------------------------------------------------
//
//  $Workfile:: Sum.cpp  $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:15 $
//
//! \if file_doc
//!
//! \file   Sum.cpp
//! \author Сергей Мушкаев
//! \brief  Арифметические функции 
//!
//! \endif
//!
//------------------------------------------------------------------------

//#include "vec.h"

#include "rpc-host.h"
#include "nmtype.h"


/////////////////////////////////////////////////////////////////////////////////////////
// Summation of all elements in array
void nmppsSum_8s(
		const nm8s*			pSrcVec,
		int				nSize,
		int *   pnRes
		)
{
	RPC_HOST_PIR("nmppsSum_8s",pSrcVec,nSize,pnRes,1);
}


/////////////////////////////////////////////////////////////////////////////////////////
// Summation of all elements in array
void nmppsSum_16s(
		const nm16s*			pSrcVec,
		int				nSize,
		int64b*   pnRes
		)
{
	RPC_HOST_PIR64("nmppsSum_16s",pSrcVec,nSize,pnRes,2);
}

/////////////////////////////////////////////////////////////////////////////////////////
// Summation of all elements in array
void nmppsSum_32s(
		const nm32s*			pSrcVec,
		int				nSize,
		int64b*   pnRes
		)
{
	RPC_HOST_PIR64("nmppsSum_32s",pSrcVec,nSize,pnRes,4);
}

/////////////////////////////////////////////////////////////////////////////////////////
// Summation of all elements in array
void nmppsSum_64s(
		const nm64s*			pSrcVec,
		int				nSize,
		int64b *   pnRes
		)
{
	RPC_HOST_PIR64("nmppsSum_64s",pSrcVec,nSize,pnRes,8);
}

