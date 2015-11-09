//------------------------------------------------------------------------
//
//  $Workfile:: Mul_VxxVxx.cp $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:15 $
//
//! \if file_doc
//!
//! \file   Mul_VxxVxx.cpp
//! \author Сергей Мушкаев
//! \brief  Функции умножения для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------
//#include "vec.h"
#include "nmpp.h"
/////////////////////////////////////////////////////////////////////////////////////////
// Scalar multiplication of two vectors
int	nmppsDotProd_32s(
			nm32s*		pSrcVec1,		// input  32-bit vec		:long -----[Size/2]
			nm32s*		pSrcVec2,		// input  32-bit vec		:long -----[Size/2]
			int			nSize			// size of input buffers	:nSize=[0,2,4...]
		)
{
	int Res=0;
	int i;
	for (i=0;i<nSize;i++)
		Res+=pSrcVec1[i]*pSrcVec2[i];
	return Res;

	//ippsDotProd_32s_Sfs(const Ipp32s* pSrc1, const Ipp32s*pSrc2, int len, Ipp32s* pDp, int scaleFactor);
}
#include "nmpp.h"

//////////////////////////////////////////////////////////////////////////////////////
// Vector multiplication
//////////////////////////////////////////////////////////////////////////////////////
void nmppsDotProd_64s(
	nm64s*	SrcVec0,	//Input0 buffer		:long Local [Size].
	nm64s*	SrcVec1,	//Input1 buffer		:long Global[Size].
	int		nSize,		//Size of input vec
	nm64s*	DstVec		//Output buffer		:long Any
	)
{
	int i;
	DstVec[0] = 0;
	for (i=0; i<nSize; i++)
		DstVec[0] += ((nm64s)SrcVec0[i])*((nm64s)SrcVec1[i]);
}
//////////////////////////////////////////////////////////////////////////////////////
void nmppsDotProd_32s64s64s(
	nm32s*	SrcVec0,	//Input0 buffer		:long Local [Size].
	nm64s*	SrcVec1,	//Input1 buffer		:long Global[Size].
	int		nSize,		//Size of input vec
	nm64s*	DstVec		//Output buffer		:long Any
	)
{
	int i;
	DstVec[0] = 0;
	for (i=0; i<nSize; i++)
		DstVec[0] += ((nm64s)SrcVec0[i])*((nm64s)SrcVec1[i]);
}
//////////////////////////////////////////////////////////////////////////////////////
void nmppsDotProd_16s64s64s(
	nm16s*	SrcVec0,	//Input0 buffer		:long Local [Size].
	nm64s*	SrcVec1,	//Input1 buffer		:long Global[Size].
	int		nSize,		//Size of input vec
	nm64s*	DstVec		//Output buffer		:long Any
	)
{
	int i;
	DstVec[0] = 0;
	for (i=0; i<nSize; i++)
		DstVec[0] += ((nm64s)SrcVec0[i])*((nm64s)SrcVec1[i]);
}
//////////////////////////////////////////////////////////////////////////////////////
void nmppsDotProd_8s64s64s(
	nm8s*	SrcVec0,	//Input0 buffer		:long Local [Size].
	nm64s*	SrcVec1,	//Input1 buffer		:long Global[Size].
	int		nSize,		//Size of input vec
	nm64s*	DstVec		//Output buffer		:long Any
	)
{
	int i;
	DstVec[0] = 0;
	for (i=0; i<nSize; i++)
		DstVec[0] += ((nm64s)SrcVec0[i])*((nm64s)SrcVec1[i]);
}
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
void nmppsDotProd_32s32s64s(
	nm32s*	SrcVec0,	//Input0 buffer		:long Local [Size].
	nm32s*	SrcVec1,	//Input1 buffer		:long Global[Size].
	int		nSize,		//Size of input vec
	nm64s*	DstVec,		//Output buffer		:long Any
	void*	pTmpBuf		//Temporary Buffer	:long Local [nSize*8].
	)
{
	int i;
	DstVec[0] = 0;
	for (i=0; i<nSize; i++)
		DstVec[0] += ((nm64s)SrcVec0[i])*((nm64s)SrcVec1[i]);
}
//////////////////////////////////////////////////////////////////////////////////////
void nmppsDotProd_16s32s64s(
	nm16s*	SrcVec0,	//Input0 buffer		:long Local [Size].
	nm32s*	SrcVec1,	//Input1 buffer		:long Global[Size].
	int		nSize,		//Size of input vec
	nm64s*	DstVec,		//Output buffer		:long Any
	void*	pTmpBuf		//Temporary Buffer	:long Local [nSize*8].
	)
{
	int i;
	DstVec[0] = 0;
	for (i=0; i<nSize; i++)
		DstVec[0] += ((nm64s)SrcVec0[i])*((nm64s)SrcVec1[i]);
}
//////////////////////////////////////////////////////////////////////////////////////
void nmppsDotProd_8s32s64s(
	nm8s*	SrcVec0,	//Input0 buffer		:long Local [Size].
	nm32s*	SrcVec1,	//Input1 buffer		:long Global[Size].
	int		nSize,		//Size of input vec
	nm64s*	DstVec,		//Output buffer		:long Any
	void*	pTmpBuf		//Temporary Buffer	:long Local [nSize*8].
	)
{
	int i;
	DstVec[0] = 0;
	for (i=0; i<nSize; i++)
		DstVec[0] += ((nm64s)SrcVec0[i])*((nm64s)SrcVec1[i]);
}
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
void nmppsDotProd_16s16s64s(
	nm16s*	SrcVec0,	//Input0 buffer		:long Local [Size].
	nm16s*	SrcVec1,	//Input1 buffer		:long Global[Size].
	int		nSize,		//Size of input vec
	nm64s*	DstVec,		//Output buffer		:long Any
	void*	pTmpBuf		//Temporary Buffer	:long Local [nSize*8].
	)
{
	int i;
	DstVec[0] = 0;
	for (i=0; i<nSize; i++)
		DstVec[0] += ((nm64s)SrcVec0[i])*((nm64s)SrcVec1[i]);
}
//////////////////////////////////////////////////////////////////////////////////////
void nmppsDotProd_8s16s64s(
	nm8s*	SrcVec0,	//Input0 buffer		:long Local [Size].
	nm16s*	SrcVec1,	//Input1 buffer		:long Global[Size].
	int		nSize,		//Size of input vec
	nm64s*	DstVec,		//Output buffer		:long Any
	void*	pTmpBuf		//Temporary Buffer	:long Local [nSize*8].
	)
{
	int i;
	DstVec[0] = 0;
	for (i=0; i<nSize; i++)
		DstVec[0] += ((nm64s)SrcVec0[i])*((nm64s)SrcVec1[i]);
}
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
void nmppsDotProd_8s8s64s(
	nm8s*	SrcVec0,	//Input0 buffer		:long Local [Size].
	nm8s*	SrcVec1,	//Input1 buffer		:long Global[Size].
	int		nSize,		//Size of input vec
	nm64s*	DstVec,		//Output buffer		:long Any
	void*	pTmpBuf		//Temporary Buffer	:long Local [nSize*8].
	)
{
	int i;
	DstVec[0] = 0;
	for (i=0; i<nSize; i++)
		DstVec[0] += ((nm64s)SrcVec0[i])*((nm64s)SrcVec1[i]);
}
//////////////////////////////////////////////////////////////////////////////////////

// With first argument conjuction
void nmppsDotProd_64sc64sc64sc(nm64sc *pSrcVec1, nm64sc *pSrcVec2, int nSize, nm64sc *pDstRes)
{
	int i;
	pDstRes->re = 0;
	pDstRes->im = 0;
	for(i=0;i<nSize;i++)
	{

//		if(IsMultOverflow(&pSrcVec1[i].re, &pSrcVec2[i].re))
//			printf("nmppsDotProd overflow(r1, r2)\n");
//		if(IsMultOverflow(&pSrcVec1[i].im, &pSrcVec2[i].im))
//			printf("nmppsDotProd overflow(c1, c2)\n");
		pDstRes->re += pSrcVec1[i].re*pSrcVec2[i].re + pSrcVec1[i].im*pSrcVec2[i].im;
//		if(IsMultOverflow(&pSrcVec1[i].re, &pSrcVec2[i].im))
//			printf("nmppsDotProd overflow(r1, c2)\n");
//		if(IsMultOverflow(&pSrcVec1[i].im, &pSrcVec2[i].re))
//			printf("nmppsDotProd overflow(c1, r2)\n");
		pDstRes->im += pSrcVec1[i].re*pSrcVec2[i].im - pSrcVec1[i].im*pSrcVec2[i].re;
	}
}

