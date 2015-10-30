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

//#include "vec.h"
#include "nmplv.h"
//#include "nmtl.h"
#include "nmtype.h"

//extern "C"{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//}
/////////////////////////////////////////////////////////////////////////////////////////
// Subtraction of two char buffers
// 2826 ticks per 10240 elements with C++ call (0.276 clocks per element)
// The order of intermediate data transmissions in function is:
//		Buf1[],Buf2			=> pDstVec[]				- Subtraction	(in-place is supported)
void nmppsSub(
		nm8s*			pSrcVec1,	// input buffer		:long Local [VecSize/8]
		nm8s*			pSrcVec2,	// input buffer		:long Local [VecSize/8]
		nm8s*			pDstVec,		// output buffer	:long Global[VecSize/8]
		int				nSize		// size of input buffer in 32 bit elements. nSize=[8,16,32...]
		)
{
	
	//if (CHECK_OVERFLOW())
	//{
	//	nmvec8s SrcVecA(pSrcVec1,nSize);
	//	nmvec8s SrcVecB(pSrcVec2,nSize);
	//	nmvec8s DstVec(pDstVec,nSize);
	//	DstVec=SrcVecA-SrcVecB;
	//}
	//else
		for(int i=0; i<nSize; i++)
			pDstVec[i] = pSrcVec1[i] - pSrcVec2[i];
	
//IppStatus ippsSub_8u_Sfs(const Ipp8u* pSrc1, const Ipp8u* pSrc2,Ipp8u* pDst, int len, int scaleFactor);
//IppStatus ippsSub_8u_ISfs(const Ipp8u* pSrc, Ipp8u* pSrcDst, int len, int scaleFactor);
		// ???
	
}


//////////////////////////////////////////////////////////////////////////////////////
// Subtraction of two short vectors
void nmppsSub(
		nm16s*			pSrcVec1,		// input buffer		:long Local [VecSize/4]
		nm16s*			pSrcVec2,		// input buffer		:long Local [VecSize/4]
		nm16s*			pDstVec,			// output buffer	:long Global[VecSize/4]
		int				nSize			// size of input buffer in 16-bit elements. nSize=[0,4,8,12..]
		)
{
#ifndef USE_IPP
	//if (CHECK_OVERFLOW())
	//{
	//	nmvec16s SrcVecA(pSrcVec1,nSize);
	//	nmvec16s SrcVecB(pSrcVec2,nSize);
	//	nmvec16s DstVec(pDstVec,nSize);
	//	DstVec=SrcVecA-SrcVecB;
	//}
	//else
		for(int i=0; i<nSize; i++)
			pDstVec[i] = pSrcVec1[i] - pSrcVec2[i];

#else
	if (pSrcVec2==pDstVec)
		ippsSub_16s_I(pSrcVec1,pSrcVec2,nSize);
	else
		if (pSrcVec1==pDstVec)
			ippsSub_16s_I(pSrcVec2,pSrcVec1,nSize);
		else
			ippsSub_16s(pSrcVec1,pSrcVec2,pDstVec,nSize);
#endif	
}

//////////////////////////////////////////////////////////////////////////////////////
// Subtraction of two int vectors
void nmppsSub(
		nm32s*			pSrcVec1,		// input buffer		:long Local [VecSize/2]
		nm32s*			pSrcVec2,		// input buffer		:long Local [VecSize/2]
		nm32s*			pDstVec,			// output buffer	:long Global[VecSize/2]
		int				nSize			// size of input buffer in 32-bit elements. nSize=[0,2,4,6...]
		)
{
#ifndef USE_IPP
	//if (CHECK_OVERFLOW())
	//{
	//	nmvec32s SrcVecA(pSrcVec1,nSize);
	//	nmvec32s SrcVecB(pSrcVec2,nSize);
	//	nmvec32s DstVec(pDstVec,nSize);
	//	DstVec=SrcVecA-SrcVecB;
	//}
	//else
		for(int i=0; i<nSize; i++)
			pDstVec[i] = pSrcVec1[i] - pSrcVec2[i];
#else
	if (pSrcVec2==pDstVec)
		ippsSub_32s_ISfs(pSrcVec1,pSrcVec2,nSize,0);
	else
		if (pSrcVec1==pDstVec)
			ippsSub_32s_ISfs(pSrcVec2,pSrcVec1,nSize,0);
		else
			ippsSub_32s_Sfs(pSrcVec1,pSrcVec2,pDstVec,nSize,0);
#endif
	
}
//////////////////////////////////////////////////////////////////////////////////////
// Subtraction of two __int64 vectors
void nmppsSub(
	  nm64s*			pSrcVec1,		// input buffer		:long Local [nSize]
	  nm64s*			pSrcVec2,		// input buffer		:long Local [nSize]
	  nm64s*			pDstVec,			// output buffer	:long Global[nSize]
		int				nSize			// size of input buffer in 32-bit elements. nSize=[0,1,2,3,4...]
		)
{
	//if (CHECK_OVERFLOW())
	//{
	//	nmvec64s SrcVecA(pSrcVec1,nSize);
	//	nmvec64s SrcVecB(pSrcVec2,nSize);
	//	nmvec64s DstVec(pDstVec,nSize);
	//	DstVec=SrcVecA-SrcVecB;
	//}
	//else
		for(int i=0; i<nSize; i++)
			pDstVec[i] = pSrcVec1[i] - pSrcVec2[i];
	
	// No IPP analog
}

//////////////////////////////////////////////////////////////////////////////////////
// Subtraction of two __int64 complex vectors
void nmppsSub(nm64sc *pSrcVec1, nm64sc *pSrcVec2, nm64sc *pDstVec, int nSize)
{
	int i;
	for(i=0;i<nSize;i++)
	{
		pDstVec[i].re = pSrcVec1[i].re - pSrcVec2[i].re;
		pDstVec[i].im = pSrcVec1[i].im - pSrcVec2[i].im;
	}
}


/////////////////////////////////////////////////////////////////////////////////////////
// Decrement of vec elements by constant value
// pDstVec[i]=pSrcVec[i]-Decrement
void nmppsSubC(
		nm8s*			pSrcVec,			// input buffer		:long Local [VecSize/8]
		int8b			nVal,				// decrement		:
		nm8s*			pDstVec,			// output buffer	:long Global[VecSize/8]
		int				nSize		// size of input buffer in 8-bit elements. nSize=[0,8,16,32...]
		)
{
	nVal=char(nVal);
	//if (CHECK_OVERFLOW())
	//{
	//	nmvec8s SrcVec(pSrcVec,nSize);
	//	nmint8s C(nVal);
	//	nmvec8s DstVec(pDstVec,nSize);
	//	for(int i=0; i<nSize; i++)
	//		DstVec[i] = SrcVec[i] - C;
	//}
	//else
		for(int i=0; i<nSize; i++)
			pDstVec[i] = pSrcVec[i] - nVal;
	// IppStatus ippsSubC_8u_Sfs(const Ipp8u* pSrc, Ipp8u val, Ipp8u* pDst,int len, int scaleFactor);
	// ???

}

/////////////////////////////////////////////////////////////////////////////////////////
// Decrement of vec elements by constant value
// pDstVec[i]=pSrcVec[i]-Decrement
void nmppsSubC(
		nm16s*			pSrcVec,			// input buffer		:long Local [VecSize/4]
		int16b			nVal,				// decrement		:
		nm16s*			pDstVec,			// output buffer	:long Global[VecSize/4]
		int				nSize		// size of input buffer in 8-bit elements. nSize=[0,4,8,12...]
		)
{
	nVal=short(nVal);
#ifndef USE_IPP
	//if (CHECK_OVERFLOW())
	//{
	//	nmvec16s SrcVec(pSrcVec,nSize);
	//	nmint16s C(nVal);
	//	nmvec16s DstVec(pDstVec,nSize);
	//	for(int i=0; i<nSize; i++)
	//		DstVec[i] = SrcVec[i] - C;
	//}
	//else
		for(int i=0; i<nSize; i++)
			pDstVec[i] = pSrcVec[i] - nVal;
#else
	if (pSrcVec!=pDstVec)
		ippsSubC_16s_Sfs(pSrcVec,nVal,pDstVec,nSize,0);
	else
		ippsSubC_16s_ISfs(nVal,pSrcVec,nSize,0);
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////
// Decrement of vec elements by constant value
// pDstVec[i]=pSrcVec[i]-Decrement
void nmppsSubC(
		nm32s*			pSrcVec,			// input buffer		:long Local [VecSize/2]
		int32b			nVal,				// decrement		:
		nm32s*			pDstVec,			// output buffer	:long Global[VecSize/2]
		int				nSize		// size of input buffer in 32-bit elements. nSize=[0,2,4,6...]
		)
{
#ifndef USE_IPP
	//if (CHECK_OVERFLOW())
	//{
	//	nmvec32s SrcVec(pSrcVec,nSize);
	//	nmint32s C(nVal);
	//	nmvec32s DstVec(pDstVec,nSize);
	//	for(int i=0; i<nSize; i++)
	//		DstVec[i] = SrcVec[i] - C;
	//}
	//else
		for(int i=0; i<nSize; i++)
			pDstVec[i] = pSrcVec[i] - nVal;
#else
	if (pSrcVec!=pDstVec)
		ippsSubC_32s_Sfs(pSrcVec,nVal,pDstVec,nSize,0);
	else
		ippsSubC_32s_ISfs(nVal,pSrcVec,nSize,0);
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////
// pDstVec[i]=pSrcVec[i]-Decrement
void nmppsSubC(
		nm64s*			pSrcVec,			// input buffer		:long Local [VecSize/2]
		nm64s*			pnVal,				// decrement		:
		nm64s*			pDstVec,			// output buffer	:long Global[VecSize/2]
		int				nSize		// size of input buffer in 32-bit elements. nSize=[0,2,4,6...]
		)
{
	//if (CHECK_OVERFLOW())
	//{
	//	nmvec64s SrcVec(pSrcVec,nSize);
	//	nmint64s C(*pnVal);
	//	nmvec64s DstVec(pDstVec,nSize);
	//	for(int i=0; i<nSize; i++)
	//		DstVec[i] = SrcVec[i] - C;
	//}
	//else
		for(int i=0; i<nSize; i++)
			pDstVec[i] = pSrcVec[i] - *pnVal;
}


/////////////////////////////////////////////////////////////////////////////////////////
// pDstVec[i]=Decrement-pSrcVec[i]
void nmppsSubCRev(
		nm8s*			pSrcVec,			// input buffer		:long Local [VecSize/8]
		int8b			nVal,				// decrement		:
		nm8s*			pDstVec,			// output buffer	:long Global[VecSize/8]
		int				nSize		// size of input buffer in 8-bit elements. nSize=[0,8,16,32...]
		)
{
	nVal=char(nVal);
	//if (CHECK_OVERFLOW())
	//{
	//	nmvec8s SrcVec(pSrcVec,nSize);
	//	nmint8s C(nVal);
	//	nmvec8s DstVec(pDstVec,nSize);
	//	for(int i=0; i<nSize; i++)
	//		DstVec[i] = C-SrcVec[i];
	//}
	//else
		for(int i=0; i<nSize; i++)
			pDstVec[i] = nVal-pSrcVec[i];
	// No IPP analog
}

/////////////////////////////////////////////////////////////////////////////////////////
// pDstVec[i]=Decrement-pSrcVec[i]
void nmppsSubCRev(
		nm16s*			pSrcVec,			// input buffer		:long Local [VecSize/4]
		int16b			nVal,				// decrement		:
		nm16s*			pDstVec,			// output buffer	:long Global[VecSize/4]
		int				nSize		// size of input buffer in 8-bit elements. nSize=[0,4,8,12...]
		)
{
	nVal=short(nVal);
#ifndef USE_IPP
	//if (CHECK_OVERFLOW())
	//{
	//	nmvec16s SrcVec(pSrcVec,nSize);
	//	nmint16s C(nVal);
	//	nmvec16s DstVec(pDstVec,nSize);
	//	for(int i=0; i<nSize; i++)
	//		DstVec[i] = C-SrcVec[i];
	//}
	//else
		for(int i=0; i<nSize; i++)
			pDstVec[i] = nVal-pSrcVec[i];
#else
	if (pSrcVec!=pDstVec)
		ippsSubCRev_16s_Sfs(pSrcVec, nVal,pDstVec,nSize,0);
	else
		ippsSubCRev_16s_ISfs(nVal,pSrcVec,nSize,0);
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////
// pDstVec[i]=Decrement-pSrcVec[i]
void nmppsSubCRev(
		nm32s*			pSrcVec,			// input buffer		:long Local [VecSize/2]
		int32b			nVal,				// decrement		:
		nm32s*			pDstVec,			// output buffer	:long Global[VecSize/2]
		int				nSize		// size of input buffer in 32-bit elements. nSize=[0,2,4,6...]
		)
{
	
#ifndef USE_IPP
	//if (CHECK_OVERFLOW())
	//{
	//	nmvec32s SrcVec(pSrcVec,nSize);
	//	nmint32s C(nVal);
	//	nmvec32s DstVec(pDstVec,nSize);
	//	for(int i=0; i<nSize; i++)
	//		DstVec[i] = C-SrcVec[i];
	//}
	//else
		for(int i=0; i<nSize; i++)
			pDstVec[i] = nVal-pSrcVec[i];
#else
	if (pSrcVec!=pDstVec)
		ippsSubCRev_32s_Sfs(pSrcVec, nVal,pDstVec,nSize,0);
	else
		ippsSubCRev_32s_ISfs(nVal,pSrcVec,nSize,0);
#endif
	
}
/////////////////////////////////////////////////////////////////////////////////////////
// pDstVec[i]=Decrement-pSrcVec[i]
void nmppsSubCRev(
		nm64s*			pSrcVec,			// input buffer		:long Local [VecSize/2]
		nm64s*				pnVal,				// decrement		:
		nm64s*			pDstVec,			// output buffer	:long Global[VecSize/2]
		int				nSize		// size of input buffer in 32-bit elements. nSize=[0,2,4,6...]
		)
{
	//if (CHECK_OVERFLOW())
	//{
	//	nmvec64s SrcVec(pSrcVec,nSize);
	//	nmint64s C(*pnVal);
	//	nmvec64s DstVec(pDstVec,nSize);
	//	for(int i=0; i<nSize; i++)
	//		DstVec[i] = C-SrcVec[i];
	//}
	//else
		for(int i=0; i<nSize; i++)
			pDstVec[i] = *pnVal-pSrcVec[i];
	// No IPP analog
}


/////////////////////////////////////////////////////////////////////////////////////////
// Absolute difference calculation
void nmppsAbsDiff(
		nm8s*			pSrcVec1,	// input buffer		:long Local			[VecSize/8]
		nm8s*			pSrcVec2,	// input buffer		:long Local/Global	[VecSize/8]
		nm8s*			pDstVec,		// output buffer	:long Global		[VecSize/8]
		int				nSize		// size of input buffer in 32 bit elements. nSize=[0,8,16,32...]
		)
{
	nmppsSub(pSrcVec1,pSrcVec2,pDstVec,nSize);
	nmppsAbs_8s(pDstVec,pDstVec,nSize);
}

/////////////////////////////////////////////////////////////////////////////////////////
// Absolute difference calculation
// pDstVec[i]=|pSrcVec1[i]-pSrcVec2[i]|
void nmppsAbsDiff(
		nm16s*			pSrcVec1,		// input buffer		:long Local	[VecSize/4]
		nm16s*			pSrcVec2,		// input buffer		:long Any   [VecSize/4]
		nm16s*			pDstVec,			// output buffer	:long Global[VecSize/4]
		int				nSize			// size of input buffer in 32 bit elements. nSize=[0,4,8...]
		)
{
	nmppsSub(pSrcVec1,pSrcVec2,pDstVec,nSize);
	nmppsAbs_16s(pDstVec,pDstVec,nSize);
}

/////////////////////////////////////////////////////////////////////////////////////////
// Absolute difference calculation
// pDstVec[i]=|pSrcVec1[i]-pSrcVec2[i]|
void nmppsAbsDiff(
		nm32s*			pSrcVec1,		// input buffer		:long Local	[VecSize/2]
		nm32s*			pSrcVec2,		// input buffer		:long Any   [VecSize/2]
		nm32s*			pDstVec,			// output buffer	:long Global[VecSize/2]
		int				nSize			// size of input buffer in 32 bit elements. nSize=[0,2,4..]
		)
{
	nmppsSub(pSrcVec1,pSrcVec2,pDstVec,nSize);
	nmppsAbs_32s(pDstVec,pDstVec,nSize);
}


/////////////////////////////////////////////////////////////////////////////////////////
// Absolute difference calculation
// pDstVec[i]=|pSrcVec1[i]-pSrcVec2[i]|
void nmppsAbsDiff(
		nm64s*			pSrcVec1,		// input buffer		:long Local	[VecSize/2]
		nm64s*			pSrcVec2,		// input buffer		:long Any   [VecSize/2]
		nm64s*			pDstVec,		// output buffer	:long Global[VecSize/2]
		int				nSize			// size of input buffer in 32 bit elements. nSize=[0,2,4..]
		)
{
	nmppsSub(pSrcVec1,pSrcVec2,pDstVec,nSize);
	nmppsAbs_64s(pDstVec,pDstVec,nSize);
}

/////////////////////////////////////////////////////////////////////////////////////////
// Logical absolute difference calculation
void nmppsAbsDiff1(
		nm8s*			pSrcVec1,	// input buffer		:long Local			[VecSize/8]
		nm8s*			pSrcVec2,	// input buffer		:long Local/Global	[VecSize/8]
		nm8s*			pDstVec,	// output buffer	:long Global		[VecSize/8]
		int				nSize		// size of input buffer in 32 bit elements. nSize=[0,8,16,32...]
		)
{
	nmppsSub(pSrcVec1,pSrcVec2,pDstVec,nSize);
	nmppsAbs1(pDstVec,pDstVec,nSize);
}


/////////////////////////////////////////////////////////////////////////////////////////
void nmppsSub(
		nm8u*			pSrcVec1,	
		nm8u*			pSrcVec2,	
		nm16s*			pDstVec,	
		int				nSize		
		)
{
	nm16s* pTmp1=(nm16s*)malloc(2*nSize);
	nm16s* pTmp2=(nm16s*)malloc(2*nSize);
	nmppsCnv_8u16u(pSrcVec1,(nm16u*)pTmp1,nSize);
	nmppsCnv_8u16u(pSrcVec2,(nm16u*)pTmp2,nSize);
	nmppsSub(pTmp1,pTmp2,pDstVec,nSize);
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
	for(int i=0; i<(VecSize/8)*8; )
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
	for(int i=0; i<(VecSize/16)*16; )
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
	for(int i=0; i<(VecSize/16)*16; )
	{
		for (int j=0;j<16;j++)
			{	pDstVec[i] = (pSrcVec[i] - SrcN16[i%16]);pDstVec[i] = ABS(pDstVec[i]);i++;}
	}
}
*/
/////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
