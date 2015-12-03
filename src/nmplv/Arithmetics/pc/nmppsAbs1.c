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
#include "nmpp.h"

/////////////////////////////////////////////////////////////////////////////////////////
// Absolute value calculation
void nmppsAbs1_4s(
		nm4s*			pSrcVec,		// input buffer		:long Local [VecSize/8]
		nm4s*			pDstVec,		// output buffer	:long Global[VecSize/8]
		int				nSize		// size of input buffer in 8 bit elements. nSize=[8,16,32...]
		)
{
	#ifdef RPC
	//RPC_HOST_PPI(nmppsAbs1_4s,pSrcVec,pDstVec,nSize);
	#else

	nm8s v,m;
	int i;
	for (i=0; i<nSize/2; i++)
	{
		v=((nm8s*)pSrcVec)[i];
		m=((v>>3)&0xF0)|((((char)(v<<4))>>7)&0xF);
		v^=m;
		((nm8s*)pDstVec)[i]=v;
	}

	#endif
}


void nmppsAbs1_8s(
		nm8s*			pSrcVec,		// input buffer		:long Local [VecSize/8]
		nm8s*			pDstVec,		// output buffer	:long Global[VecSize/8]
		int				nSize		// size of input buffer in 8 bit elements. nSize=[8,16,32...]
		)
{
	#ifdef RPC
	RPC_HOST_PPI("nmppsAbs1_8s",pSrcVec,pDstVec,nSize,1);
	#else

	nm8s v;
	int i;
	for (i=0; i<nSize; i++)
	{
		v=pSrcVec[i];
		pDstVec[i] = (v>>7)^v;
	}

	#endif
}


/////////////////////////////////////////////////////////////////////////////////////////
// Absolute value calculation
void nmppsAbs1_16s(
		nm16s*			pSrcVec,		// input buffer		:long Local [VecSize/4]
		nm16s*			pDstVec,		// output buffer	:long Global[VecSize/4]
		int				nSize		// size of input buffer in 8 bit elements. nSize=[0,4,8,..]
		)
{
	#ifdef RPC
	RPC_HOST_PPI("nmppsAbs1_16s",pSrcVec,pDstVec,nSize,2);
	#else

	nm16s v;
	int i;
	for (i=0; i<nSize; i++)
	{
		v=pSrcVec[i];
		pDstVec[i] = (v>>15)^v;
	}

	#endif
}



/////////////////////////////////////////////////////////////////////////////////////////
// Absolute value calculation
void nmppsAbs1_32s(
		nm32s*			pSrcVec,		// input buffer		:long Local [VecSize/2]
		nm32s*			pDstVec,		// output buffer	:long Global[VecSize/2]
		int				nSize		// size of input buffer in 32 bit elements. nSize=[2,4,6...]
		)
{
	#ifdef RPC
	RPC_HOST_PPI("nmppsAbs1_32s",pSrcVec,pDstVec,nSize,4);
	#else

	nm32s v;
	int i;
	for (i=0; i<nSize; i++)
	{
		v=pSrcVec[i];
		pDstVec[i] = (v>>31)^v;
	}

	#endif
}



/////////////////////////////////////////////////////////////////////////////////////////
// Absolute value calculation
void nmppsAbs1_64s(
		nm64s*			pSrcVec,		// input buffer		:long Local [VecSize/2]
		nm64s*			pDstVec,		// output buffer	:long Global[VecSize/2]
		int				nSize		// size of input buffer in 32 bit elements. nSize=[2,4,6...]
		)
{
	#ifdef RPC
	RPC_HOST_PPI("nmppsAbs1_64s",pSrcVec,pDstVec,nSize,8);
	#else

	nm64s v;
	int i;
	for (i=0; i<nSize; i++)
	{
		v=pSrcVec[i];
		pDstVec[i] = (v>>63)^v;
	}

	#endif
}

