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
#include "nmpp.h"


/////////////////////////////////////////////////////////////////////////////////////////
// Absolute difference calculation
void nmppsAbsDiff_8s(
		const nm8s*			pSrcVec1,	// input buffer		:long Local			[VecSize/8]
		nm8s*			pSrcVec2,	// input buffer		:long Local/Global	[VecSize/8]
		nm8s*			pDstVec,		// output buffer	:long Global		[VecSize/8]
		int				nSize		// size of input buffer in 32 bit elements. nSize=[0,8,16,32...]
		)
{
	nmppsSub_8s(pSrcVec1,pSrcVec2,pDstVec,nSize);
	nmppsAbs_8s(pDstVec,pDstVec,nSize);
}


/////////////////////////////////////////////////////////////////////////////////////////
// Absolute difference calculation
// pDstVec[i]=|pSrcVec1[i]-pSrcVec2[i]|
void nmppsAbsDiff_16s(
		const nm16s*			pSrcVec1,		// input buffer		:long Local	[VecSize/4]
		nm16s*			pSrcVec2,		// input buffer		:long Any   [VecSize/4]
		nm16s*			pDstVec,			// output buffer	:long Global[VecSize/4]
		int				nSize			// size of input buffer in 32 bit elements. nSize=[0,4,8...]
		)
{
	nmppsSub_16s(pSrcVec1,pSrcVec2,pDstVec,nSize);
	nmppsAbs_16s(pDstVec,pDstVec,nSize);
}


/////////////////////////////////////////////////////////////////////////////////////////
// Absolute difference calculation
// pDstVec[i]=|pSrcVec1[i]-pSrcVec2[i]|
void nmppsAbsDiff_32s(
		const nm32s*			pSrcVec1,		// input buffer		:long Local	[VecSize/2]
		nm32s*			pSrcVec2,		// input buffer		:long Any   [VecSize/2]
		nm32s*			pDstVec,			// output buffer	:long Global[VecSize/2]
		int				nSize			// size of input buffer in 32 bit elements. nSize=[0,2,4..]
		)
{
	nmppsSub_32s(pSrcVec1,pSrcVec2,pDstVec,nSize);
	nmppsAbs_32s(pDstVec,pDstVec,nSize);
}



/////////////////////////////////////////////////////////////////////////////////////////
// Absolute difference calculation
// pDstVec[i]=|pSrcVec1[i]-pSrcVec2[i]|
void nmppsAbsDiff_64s(
		const nm64s*			pSrcVec1,		// input buffer		:long Local	[VecSize/2]
		nm64s*			pSrcVec2,		// input buffer		:long Any   [VecSize/2]
		nm64s*			pDstVec,		// output buffer	:long Global[VecSize/2]
		int				nSize			// size of input buffer in 32 bit elements. nSize=[0,2,4..]
		)
{
	nmppsSub_64s(pSrcVec1,pSrcVec2,pDstVec,nSize);
	nmppsAbs_64s(pDstVec,pDstVec,nSize);
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
	nmppsSub_8s(pSrcVec1,pSrcVec2,pDstVec,nSize);
	nmppsAbs1_8s(pDstVec,pDstVec,nSize);
}



/////////////////////////////////////////////////////////////////////////////////////////
void nmppsSub_8u16s(
		nm8u*			pSrcVec1,	
		nm8u*			pSrcVec2,	
		nm16s*			pDstVec,	
		int				nSize		
		)
{
	nm16s* pTmp1=(nm16s*)malloc(2*nSize);
	nm16s* pTmp2=(nm16s*)malloc(2*nSize);
	nmppsConvert_8u16u(pSrcVec1,(nm16u*)pTmp1,nSize);
	nmppsConvert_8u16u(pSrcVec2,(nm16u*)pTmp2,nSize);
	nmppsSub_16s(pTmp1,pTmp2,pDstVec,nSize);
	free(pTmp1);
	free(pTmp2);
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
	int i;
	for (i=0; i<(VecSize/16)*16; )
	{

		for (int j=0;j<16;j++)
			{	pDstVec[i] = abs(pSrcVec[i] - SrcN16[i%16]);i++;}
	}

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

	int i;
	for (i=0; i<(VecSize/16)*16; )
	{
		for (int j=0;j<16;j++)
			{	pDstVec[i] = (pSrcVec[i] - SrcN16[i%16]);pDstVec[i] = ABS(pDstVec[i]);i++;}
	}

}

*/
/////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
