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

//extern "C"{
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//}
/////////////////////////////////////////////////////////////////////////////////////////
// Subtraction of two char buffers
// 2826 ticks per 10240 elements with C++ call (0.276 clocks per element)
// The order of intermediate data transmissions in function is:
//		Buf1[],Buf2			=> pDstVec[]				- Subtraction	(in-place is supported)
void nmppsSub_8s(
		nm8s*			pSrcVec1,	// input buffer		:long Local [VecSize/8]
		nm8s*			pSrcVec2,	// input buffer		:long Local [VecSize/8]
		nm8s*			pDstVec,		// output buffer	:long Global[VecSize/8]
		int				nSize		// size of input buffer in 32 bit elements. nSize=[8,16,32...]
		)
{
	#ifdef RPC
	RPC_HOST_PPPI("nmppsSub_8s",pSrcVec1,pSrcVec2,pDstVec,nSize,1);
	#else

	int i;
	for (i=0; i<nSize; i++)
		pDstVec[i] = pSrcVec1[i] - pSrcVec2[i];


	#endif
}



//////////////////////////////////////////////////////////////////////////////////////
// Subtraction of two short vectors
void nmppsSub_16s(
		nm16s*			pSrcVec1,		// input buffer		:long Local [VecSize/4]
		nm16s*			pSrcVec2,		// input buffer		:long Local [VecSize/4]
		nm16s*			pDstVec,			// output buffer	:long Global[VecSize/4]
		int				nSize			// size of input buffer in 16-bit elements. nSize=[0,4,8,12..]
		)
{
	#ifdef RPC
	RPC_HOST_PPPI("nmppsSub_16s",pSrcVec1,pSrcVec2,pDstVec,nSize,2);
	#else

	int i;
	for (i=0; i<nSize; i++)
		pDstVec[i] = pSrcVec1[i] - pSrcVec2[i];

	#endif
}


//////////////////////////////////////////////////////////////////////////////////////
// Subtraction of two int vectors
void nmppsSub_32s(
		nm32s*			pSrcVec1,		// input buffer		:long Local [VecSize/2]
		nm32s*			pSrcVec2,		// input buffer		:long Local [VecSize/2]
		nm32s*			pDstVec,			// output buffer	:long Global[VecSize/2]
		int				nSize			// size of input buffer in 32-bit elements. nSize=[0,2,4,6...]
		)
{
	#ifdef RPC
	RPC_HOST_PPPI("nmppsSub_32s",pSrcVec1,pSrcVec2,pDstVec,nSize,4);
	#else

	int i;
	for (i=0; i<nSize; i++)
		pDstVec[i] = pSrcVec1[i] - pSrcVec2[i];

	#endif
}

//////////////////////////////////////////////////////////////////////////////////////
// Subtraction of two __int64 vectors
void nmppsSub_64s(
	  nm64s*			pSrcVec1,		// input buffer		:long Local [nSize]
	  nm64s*			pSrcVec2,		// input buffer		:long Local [nSize]
	  nm64s*			pDstVec,			// output buffer	:long Global[nSize]
		int				nSize			// size of input buffer in 32-bit elements. nSize=[0,1,2,3,4...]
		)
{
	#ifdef RPC
	RPC_HOST_PPPI("nmppsSub_64s",pSrcVec1,pSrcVec2,pDstVec,nSize,8);
	#else

	int i;
	for (i=0; i<nSize; i++)
		pDstVec[i] = pSrcVec1[i] - pSrcVec2[i];
	
	// No IPP analog

	#endif
}


//////////////////////////////////////////////////////////////////////////////////////
// Subtraction of two __int64 complex vectors
void nmppsSub_64sc(nm64sc *pSrcVec1, nm64sc *pSrcVec2, nm64sc *pDstVec, int nSize)
{
	#ifdef RPC
	RPC_HOST_PPPI("nmppsSub_64sc",pSrcVec1,pSrcVec2,pDstVec,nSize,16);
	#else

	int i;
	for(i=0;i<nSize;i++)
	{
		pDstVec[i].re = pSrcVec1[i].re - pSrcVec2[i].re;
		pDstVec[i].im = pSrcVec1[i].im - pSrcVec2[i].im;
	}

	#endif
}



/////////////////////////////////////////////////////////////////////////////////////////
// Decrement of vec elements by constant value
// pDstVec[i]=pSrcVec[i]-Decrement
void nmppsSubC_8s(
		nm8s*			pSrcVec,			// input buffer		:long Local [VecSize/8]
		int8b			nVal,				// decrement		:
		nm8s*			pDstVec,			// output buffer	:long Global[VecSize/8]
		int				nSize		// size of input buffer in 8-bit elements. nSize=[0,8,16,32...]
		)
{
	#ifdef RPC
	RPC_HOST_PIPI("nmppsSubC_8s",pSrcVec,nVal,pDstVec,nSize,1);
	#else

	int i;
	nVal=(char)nVal;
	for (i=0; i<nSize; i++)
		pDstVec[i] = pSrcVec[i] - nVal;



	#endif
}


/////////////////////////////////////////////////////////////////////////////////////////
// Decrement of vec elements by constant value
// pDstVec[i]=pSrcVec[i]-Decrement
void nmppsSubC_16s(
		nm16s*			pSrcVec,			// input buffer		:long Local [VecSize/4]
		int16b			nVal,				// decrement		:
		nm16s*			pDstVec,			// output buffer	:long Global[VecSize/4]
		int				nSize		// size of input buffer in 8-bit elements. nSize=[0,4,8,12...]
		)
{
	#ifdef RPC
	RPC_HOST_PIPI("nmppsSubC_16s",pSrcVec,nVal,pDstVec,nSize,2);
	#else

	int i;
	nVal=(short)nVal;
	for (i=0; i<nSize; i++)
		pDstVec[i] = pSrcVec[i] - nVal;

	#endif
}


/////////////////////////////////////////////////////////////////////////////////////////
// Decrement of vec elements by constant value
// pDstVec[i]=pSrcVec[i]-Decrement
void nmppsSubC_32s(
		nm32s*			pSrcVec,			// input buffer		:long Local [VecSize/2]
		int32b			nVal,				// decrement		:
		nm32s*			pDstVec,			// output buffer	:long Global[VecSize/2]
		int				nSize		// size of input buffer in 32-bit elements. nSize=[0,2,4,6...]
		)
{
	#ifdef RPC
	RPC_HOST_PIPI("nmppsSubC_32s",pSrcVec,nVal,pDstVec,nSize,4);
	#else

	int i;
	for (i=0; i<nSize; i++)
		pDstVec[i] = pSrcVec[i] - nVal;


	#endif
}


/////////////////////////////////////////////////////////////////////////////////////////
// pDstVec[i]=pSrcVec[i]-Decrement
void nmppsSubC_64s(
		nm64s*			pSrcVec,			// input buffer		:long Local [VecSize/2]
		nm64s*			pnVal,				// decrement		:
		nm64s*			pDstVec,			// output buffer	:long Global[VecSize/2]
		int				nSize		// size of input buffer in 32-bit elements. nSize=[0,2,4,6...]
		)
{
	#ifdef RPC
	//RPC_HOST_PPI(pSrcVec,nVal,pDstVec,nSize,8);
	#else

	int i;
	for (i=0; i<nSize; i++)
		pDstVec[i] = pSrcVec[i] - *pnVal;

	#endif
}



/////////////////////////////////////////////////////////////////////////////////////////
// pDstVec[i]=Decrement-pSrcVec[i]
void nmppsSubCRev_8s(
		nm8s*			pSrcVec,			// input buffer		:long Local [VecSize/8]
		int8b			nVal,				// decrement		:
		nm8s*			pDstVec,			// output buffer	:long Global[VecSize/8]
		int				nSize		// size of input buffer in 8-bit elements. nSize=[0,8,16,32...]
		)
{
	#ifdef RPC
	RPC_HOST_PIPI("nmppsSubCRev_8s",pSrcVec,nVal,pDstVec,nSize,1);
	#else

	int i;
	nVal=(char)nVal;

	for (i=0; i<nSize; i++)
		pDstVec[i] = nVal-pSrcVec[i];

	#endif
}


/////////////////////////////////////////////////////////////////////////////////////////
// pDstVec[i]=Decrement-pSrcVec[i]
void nmppsSubCRev_16s(
		nm16s*			pSrcVec,			// input buffer		:long Local [VecSize/4]
		int16b			nVal,				// decrement		:
		nm16s*			pDstVec,			// output buffer	:long Global[VecSize/4]
		int				nSize		// size of input buffer in 8-bit elements. nSize=[0,4,8,12...]
		)
{
	#ifdef RPC
	RPC_HOST_PIPI("nmppsSubCRev_16s",pSrcVec,nVal,pDstVec,nSize,2);
	#else

	int i;
	nVal=(short)nVal;

	for (i=0; i<nSize; i++)
		pDstVec[i] = nVal-pSrcVec[i];

	#endif
}


/////////////////////////////////////////////////////////////////////////////////////////
// pDstVec[i]=Decrement-pSrcVec[i]
void nmppsSubCRev_32s(
		nm32s*			pSrcVec,			// input buffer		:long Local [VecSize/2]
		int32b			nVal,				// decrement		:
		nm32s*			pDstVec,			// output buffer	:long Global[VecSize/2]
		int				nSize		// size of input buffer in 32-bit elements. nSize=[0,2,4,6...]
		)
{
	#ifdef RPC
	RPC_HOST_PIPI("nmppsSubCRev_32s",pSrcVec,nVal,pDstVec,nSize,4);
	#else


	int i;

	for (i=0; i<nSize; i++)
		pDstVec[i] = nVal-pSrcVec[i];


	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////
// pDstVec[i]=Decrement-pSrcVec[i]
void nmppsSubCRev_64s(
		nm64s*			pSrcVec,			// input buffer		:long Local [VecSize/2]
		nm64s*			pnVal,				// decrement		:
		nm64s*			pDstVec,			// output buffer	:long Global[VecSize/2]
		int				nSize		// size of input buffer in 32-bit elements. nSize=[0,2,4,6...]
		)
{
	#ifdef RPC
	//RPC_HOST_PIPI(pSrcVec,pDstVec,nSize,8);
	#else

	int i;
	for (i=0; i<nSize; i++)
		pDstVec[i] = *pnVal-pSrcVec[i];

	#endif
}



/////////////////////////////////////////////////////////////////////////////////////////
// Absolute difference calculation
void nmppsAbsDiff_8s(
		nm8s*			pSrcVec1,	// input buffer		:long Local			[VecSize/8]
		nm8s*			pSrcVec2,	// input buffer		:long Local/Global	[VecSize/8]
		nm8s*			pDstVec,		// output buffer	:long Global		[VecSize/8]
		int				nSize		// size of input buffer in 32 bit elements. nSize=[0,8,16,32...]
		)
{
	#ifdef RPC
	RPC_HOST_PPPI("nmppsAbsDiff_8s",pSrcVec1,pSrcVec2,pDstVec,nSize,1);
	#else

	nmppsSub_8s(pSrcVec1,pSrcVec2,pDstVec,nSize);
	nmppsAbs_8s(pDstVec,pDstVec,nSize);

	#endif
}


/////////////////////////////////////////////////////////////////////////////////////////
// Absolute difference calculation
// pDstVec[i]=|pSrcVec1[i]-pSrcVec2[i]|
void nmppsAbsDiff_16s(
		nm16s*			pSrcVec1,		// input buffer		:long Local	[VecSize/4]
		nm16s*			pSrcVec2,		// input buffer		:long Any   [VecSize/4]
		nm16s*			pDstVec,			// output buffer	:long Global[VecSize/4]
		int				nSize			// size of input buffer in 32 bit elements. nSize=[0,4,8...]
		)
{
	#ifdef RPC
	RPC_HOST_PPPI("nmppsAbsDiff_16s",pSrcVec1,pSrcVec2,pDstVec,nSize,2);
	#else

	nmppsSub_16s(pSrcVec1,pSrcVec2,pDstVec,nSize);
	nmppsAbs_16s(pDstVec,pDstVec,nSize);

	#endif
}


/////////////////////////////////////////////////////////////////////////////////////////
// Absolute difference calculation
// pDstVec[i]=|pSrcVec1[i]-pSrcVec2[i]|
void nmppsAbsDiff_32s(
		nm32s*			pSrcVec1,		// input buffer		:long Local	[VecSize/2]
		nm32s*			pSrcVec2,		// input buffer		:long Any   [VecSize/2]
		nm32s*			pDstVec,			// output buffer	:long Global[VecSize/2]
		int				nSize			// size of input buffer in 32 bit elements. nSize=[0,2,4..]
		)
{
	#ifdef RPC
	RPC_HOST_PPPI("nmppsAbsDiff_32s",pSrcVec1,pSrcVec2,pDstVec,nSize,4);
	#else

	nmppsSub_32s(pSrcVec1,pSrcVec2,pDstVec,nSize);
	nmppsAbs_32s(pDstVec,pDstVec,nSize);

	#endif
}



/////////////////////////////////////////////////////////////////////////////////////////
// Absolute difference calculation
// pDstVec[i]=|pSrcVec1[i]-pSrcVec2[i]|
void nmppsAbsDiff_64s(
		nm64s*			pSrcVec1,		// input buffer		:long Local	[VecSize/2]
		nm64s*			pSrcVec2,		// input buffer		:long Any   [VecSize/2]
		nm64s*			pDstVec,		// output buffer	:long Global[VecSize/2]
		int				nSize			// size of input buffer in 32 bit elements. nSize=[0,2,4..]
		)
{
	#ifdef RPC
	RPC_HOST_PPPI("nmppsAbsDiff_64s",pSrcVec1,pSrcVec2,pDstVec,nSize,8);
	#else

	nmppsSub_64s(pSrcVec1,pSrcVec2,pDstVec,nSize);
	nmppsAbs_64s(pDstVec,pDstVec,nSize);

	#endif
}


/////////////////////////////////////////////////////////////////////////////////////////
// Logical absolute difference calculation
void nmppsAbsDiff1_8s(
		nm8s*			pSrcVec1,	// input buffer		:long Local			[VecSize/8]
		nm8s*			pSrcVec2,	// input buffer		:long Local/Global	[VecSize/8]
		nm8s*			pDstVec,	// output buffer	:long Global		[VecSize/8]
		int				nSize		// size of input buffer in 32 bit elements. nSize=[0,8,16,32...]
		)
{
	#ifdef RPC
	RPC_HOST_PPPI("nmppsAbsDiff1_8s",pSrcVec1,pSrcVec2,pDstVec,nSize,1);
	#else

	nmppsSub_8s(pSrcVec1,pSrcVec2,pDstVec,nSize);
	nmppsAbs1_8s(pDstVec,pDstVec,nSize);

	#endif
}



/////////////////////////////////////////////////////////////////////////////////////////
void nmppsSub_8u16s(
		nm8u*			pSrcVec1,	
		nm8u*			pSrcVec2,	
		nm16s*			pDstVec,	
		int				nSize		
		)
{
	#ifdef RPC
	//RPC_HOST_PPPI(pSrcVec1,pSrcVec2,pDstVec,nSize,1);
	//RPC_HOST_PPI(pSrcVec,pDstVec,nSize,1);
	#else

	nm16s* pTmp1=(nm16s*)malloc(2*nSize);
	nm16s* pTmp2=(nm16s*)malloc(2*nSize);
	nmppsConvert_8u16u(pSrcVec1,(nm16u*)pTmp1,nSize);
	nmppsConvert_8u16u(pSrcVec2,(nm16u*)pTmp2,nSize);
	nmppsSub_16s(pTmp1,pTmp2,pDstVec,nSize);
	free(pTmp1);
	free(pTmp2);

	#endif
}



/*
/////////////////////////////////////////////////////////////////////////////////////////
// Absolute difference calculation
// pDstVec[i]=|pSrcVec1[i]-pSrcVec2[i]|
void nmppsSubN8_Abs(
		nm32s*			pSrcVec,			// input buffer		:long Local [VecSize/8]
		nm32s*			SrcN8,			// decrement		:long [1]
		nm32s*			pDstVec,			// output buffer	:long Global[VecSize/8]
		int				nSize		// size of input buffer in 8-bit elements. nSize=[8,16,32...]
		)
{
	#ifdef RPC
	RPC_HOST_PPI(pSrcVec,pDstVec,nSize);
	#else

	int i;
	for (i=0; i<(VecSize/8)*8; )
	{
		pDstVec[i] = abs(pSrcVec[i] - SrcN8[0]);i++;
		pDstVec[i] = abs(pSrcVec[i] - SrcN8[1]);i++;
		pDstVec[i] = abs(pSrcVec[i] - SrcN8[2]);i++;
		pDstVec[i] = abs(pSrcVec[i] - SrcN8[3]);i++;
		pDstVec[i] = abs(pSrcVec[i] - SrcN8[4]);i++;
		pDstVec[i] = abs(pSrcVec[i] - SrcN8[5]);i++;
		pDstVec[i] = abs(pSrcVec[i] - SrcN8[6]);i++;
		pDstVec[i] = abs(pSrcVec[i] - SrcN8[7]);i++;
	}

	#endif
}


////////////////////////////////////////////////////////////////////////////////////////
// Absolute difference calculation
// pDstVec[i]=|pSrcVec1[i]-pSrcVec2[i]|
void nmppsSubN16_Abs(
		nm32s*			pSrcVec,			// input buffer		:long Local [VecSize/8]
		nm32s*			SrcN16,			// decrement		:long [1]
		nm32s*			pDstVec,			// output buffer	:long Global[VecSize/8]
		int				nSize		// size of input buffer in 8-bit elements. nSize=[8,16,32...]
		)
{
	#ifdef RPC
	RPC_HOST_PPI(pSrcVec,pDstVec,nSize);
	#else

	int i;
	for (i=0; i<(VecSize/16)*16; )
	{

		for (int j=0;j<16;j++)
			{	pDstVec[i] = abs(pSrcVec[i] - SrcN16[i%16]);i++;}
	}

	#endif
}



/////////////////////////////////////////////////////////////////////////////////////////
// Absolute difference calculation
// pDstVec[i]=|pSrcVec1[i]-pSrcVec2[i]|
void nmppsSubN16_Abs(
		nm8s*			pSrcVec,			// input buffer		:long Local [VecSize/8]
		nm8s*			SrcN16,			// decrement		:long [1]
		nm8s*			pDstVec,			// output buffer	:long Global[VecSize/8]
		int				nSize		// size of input buffer in 8-bit elements. nSize=[8,16,32...]
		)
{
	#ifdef RPC
	RPC_HOST_PPI(pSrcVec,pDstVec,nSize);
	#else

	int i;
	for (i=0; i<(VecSize/16)*16; )
	{
		for (int j=0;j<16;j++)
			{	pDstVec[i] = (pSrcVec[i] - SrcN16[i%16]);pDstVec[i] = ABS(pDstVec[i]);i++;}
	}

	#endif
}

*/
/////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
