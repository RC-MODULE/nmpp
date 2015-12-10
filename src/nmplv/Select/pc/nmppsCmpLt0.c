//------------------------------------------------------------------------
//
//  $Workfile:: pcCompare.cp $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:15 $
//
//! \if file_doc
//!
//! \file   pcCompare.cpp
//! \author Сергей Мушкаев
//! \brief  Функции сравнения.
//!
//! \endif
//!
//------------------------------------------------------------------------
#include "nmplv.h"


///////////////////////////////////////////////////////////////////////////////
//	Performs logic activation of 64-bit elements by setting 
//	negative numbers to "-1" and positive numbers to "0"
void nmppsCmpLt0_64s(
	nm64s*	pSrcVec,		// Input Buffer
	nm64s*	pDstVec,		// Output Buffer
	int			nSize		// size of input buffer in 64 bit elements. nSize={1,2,..,n}
	)
{
	#ifdef RPC
	//RPC_HOST_PPI(nmppsAbs1_4s,pSrcVec,pDstVec,nSize);
	#else

	int i;
	for (i=0; i<nSize; i++)
		pDstVec[i]=pSrcVec[i]>>63;
		//if(pSrcVec[i] < 0)
		//	pDstVec[i] = -1;
		//else
		//	pDstVec[i] = 0;

	#endif
}
///////////////////////////////////////////////////////////////////////////////
//	Performs logic activation of 32-bit elements by setting 
//	negative numbers to "-1" and positive numbers to "0"
void nmppsCmpLt0_32s(
	nm32s*		pSrcVec,		// Input Buffer
	nm32s*		pDstVec,		// Output Buffer
	int			nSize		// size of input buffer in 32 bit elements. nSize={2,4,..,n*2}
	)
{
	#ifdef RPC
	//RPC_HOST_PPI(nmppsAbs1_4s,pSrcVec,pDstVec,nSize);
	#else

	int i;
	for (i=0; i<nSize; i++)
		pDstVec[i]=pSrcVec[i]>>31;
		//if(pSrcVec[i] < 0)
		//	pDstVec[i] = -1;
		//else
		//	pDstVec[i] = 0;

	#endif
}
///////////////////////////////////////////////////////////////////////////////
//	Performs logic activation of 16-bit elements by setting 
//	negative numbers to "-1" and positive numbers to "0"
void nmppsCmpLt0_16s(
	nm16s*		pSrcVec,		// Input Buffer
	nm16s*		pDstVec,		// Output Buffer
	int			nSize		// size of input buffer in 16 bit elements. nSize={4,8,..,n*4}
	)
{
	#ifdef RPC
	//RPC_HOST_PPI(nmppsAbs1_4s,pSrcVec,pDstVec,nSize);
	#else

	int i;
	for (i=0; i<nSize; i++)
		pDstVec[i]=pSrcVec[i]>>15;
		//if(pSrcVec[i] < 0)
		//	pDstVec[i] = -1;
		//else
		//	pDstVec[i] = 0;

	#endif
}
///////////////////////////////////////////////////////////////////////////////
//	Performs logic activation of 8-bit elements by setting 
//	negative numbers to "-1" and positive numbers to "0"
void nmppsCmpLt0_8s(
	nm8s*		pSrcVec,		// Input Buffer
	nm8s*		pDstVec,		// Output Buffer
	int			nSize		// size of input buffer in 8 bit elements. nSize={8,16,..,n*8}
	)
{
	#ifdef RPC
	//RPC_HOST_PPI(nmppsAbs1_4s,pSrcVec,pDstVec,nSize);
	#else

	int i;
	for (i=0; i<nSize; i++)
		pDstVec[i]=pSrcVec[i]>>7;
		//if(pSrcVec[i] < 0)
		//	pDstVec[i] = -1;
		//else
		//	pDstVec[i] = 0;

	#endif
}

