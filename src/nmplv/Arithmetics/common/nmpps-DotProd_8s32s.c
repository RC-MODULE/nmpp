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
#include "rpc-host.h"
//#include ".h"
#include "nmtype.h"
#include "nmplv/vArithmetics.h"
#include "nmplv/vInit.h"
/////////////////////////////////////////////////////////////////////////////////////////
// Scalar multiplication of two vectors
/*
int	nmppsDotProd_32s(
			nm32s*		pSrcVec1,		// input  32-bit vec		:long -----[Size/2]
			nm32s*		pSrcVec2,		// input  32-bit vec		:long -----[Size/2]
			int			nSize			// size of input buffers	:nSize=[0,2,4...]
		)
{
	#ifdef RPC
	RPC_PPI(pSrcVec,pDstVec,nSize);
	#else

	int Res=0;
	int i;
	for (i=0;i<nSize;i++)
		Res+=pSrcVec1[i]*pSrcVec2[i];
	return Res;

	//ippsDotProd_32s_Sfs(const Ipp32s* pSrc1, const Ipp32s*pSrc2, int len, Ipp32s* pDp, int scaleFactor);

	#endif
}
*/
#define S64 1

//////////////////////////////////////////////////////////////////////////////////////
void nmppsDotProd_32s32s(
	nm32s*		srcVec0,	//Input0 buffer		:long Local [Size].
	nm32s*		srcVec1,	//Input1 buffer		:long Global[Size].
	int			size,		//Size of input vec
	int64b*		dst,		//Output buffer		:long Any
	SpecTmp1*	spec		//Temporary Buffer	:long Local [nSize*8].

	)
{
	#ifdef RPC
	//RPC_HOST_PPIP("nmppsDotProd_32s32s",srcVec0,srcVec1,size,dst,4,4);
	#else
	if (spec){
		//if (spec->state&FIRST_TIME){
		//	if (spec->state & OPT_ONCE){
		//		for(int i)
		//			if (spec->buffer0=nmppsMalloc_64s(size)){
		//				nmppsDotProd_32s32s(srcVec0,srcVec1,size,dst,spec,0);
		//				nmppsFree(spec->buffer0);
		//			}
		//			
		//	}
		//		
		//}
		//else {
		//	nmppsConvert_32s64s(srcVec1,(nm64s*)spec->buffer,size);
		//	nmppsDotProd_32s64s(srcVec0,(nm64s*)spec->buffer,size,dst);
		//}
	}
	else {
		/*
	SpecTmp1	spec;
	if (spec.buffer0=nmppsMalloc_64s(size)){
		
		nmppsConvert_32s64s(srcVec1,(nm64s*)spec.buffer,size);
		nmppsDotProd_32s64s(srcVec0,(nm64s*)spec.buffer,size,dst);
		nmppsFreeSpec1(&spec);
	}*/
	}
	#endif
}
/*
// Варинат 1

static *spec = 
nmppsDotProdOptimizeAlloc_32s32s(srcVec0,srcVec1,size,OPTIMIZE|ALLOC_ROUTE|FREE_BUFFERS|ONE_TIME);
nmppsDotProdInitAlloc_32s32s(&spec);
nmppsDotProdFree_32s32s (spec);

// Вариант 2 
static *spec = nmppsDotProdInitAlloc_32s32s(&spec,srcVec0,srcVec1,size,OPTIMIZE|ALLOC_ROUTE|FREE_BUFFERS|ONE_TIME);
nmppsDotProd_32s32s (src0,src1,10,dst,spec);
nmppsDotProdFree_32s32s (spec);

//
static spec;
spec.buffer[0]=malloc(1);
spec.buffer[1]=malloc(1);

c = nmppsDotProdInitAlloc_32s32s (src0,src1,10,dst,spec, OPTIMIZE_BUFFERS|ALLOC_BUFFERS|FREE_BUFFERS|ONE_TIME_CALL);
nmppsDotProd_32s32s (src0,src1,10,dst,spec);
*/
//
//stitic spec; 
//spec.state=);

//nmppsDotProd_32s32s (src0,src1,10,dst,&spec,OPT_ONCE|NO_EXEC|ALLOC_ONCE|FREE_ONCE);
//////////////////////////////////////////////////////////////////////////////////////
void nmppsDotProd_16s32s(
	nm16s*		srcVec0,	//Input0 buffer		:long Local [Size].
	nm32s*		srcVec1,	//Input1 buffer		:long Global[Size].
	int			size,		//Size of input vec
	nm64s*		dst,		//Output buffer		:long Any
	SpecTmp1*	spec		//Temporary Buffer	:long Local [nSize*8].
	)
{
	#ifdef RPC
	RPC_HOST_PPIP("nmppsDotProd_16s32s",srcVec0,srcVec1,size,dst,2,4);
	#else
	if (spec){
		nmppsConvert_32s64s(srcVec1,(nm64s*)spec->buffer,size);
		nmppsDotProd_16s64s(srcVec0,(nm64s*)spec->buffer,size,dst);
	}
	else {
		SpecTmp1	spec;
		if (nmppsMallocSpec1(&spec,size,S64,0)){
			nmppsConvert_32s64s(srcVec1,(nm64s*)spec.buffer,size);
			nmppsDotProd_16s64s(srcVec0,(nm64s*)spec.buffer,size,dst);
			nmppsFreeSpec1(&spec);
		}
	}
	#endif
}

//////////////////////////////////////////////////////////////////////////////////////
void nmppsDotProd_8s32s(
	nm8s*		srcVec0,	//Input0 buffer		:long Local [Size].
	nm32s*		srcVec1,	//Input1 buffer		:long Global[Size].
	int			size,		//Size of input vec
	nm64s*		dst,		//Output buffer		:long Any
	SpecTmp1*	spec		//Temporary Buffer	:long Local [nSize*8].
	)
{
	#ifdef RPC
	RPC_HOST_PPIP("nmppsDotProd_8s32s",srcVec0,srcVec1,size,dst,1,4);
	#else
	if (spec){
		nmppsConvert_32s64s(srcVec1,(nm64s*)spec->buffer,size);
		nmppsDotProd_8s64s (srcVec0,(nm64s*)spec->buffer,size,dst);
	}
	else {
		SpecTmp1	spec;
		if (nmppsMallocSpec1(&spec,size,S64,0)){
			nmppsConvert_32s64s(srcVec1,(nm64s*)spec.buffer,size);
			nmppsDotProd_8s64s (srcVec0,(nm64s*)spec.buffer,size,dst);
			nmppsFreeSpec1(&spec);
		}
	}
	#endif
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
void nmppsDotProd_16s16s(
	nm16s*		srcVec0,	//Input0 buffer		:long Local [Size].
	nm16s*		srcVec1,	//Input1 buffer		:long Global[Size].
	int			size,		//Size of input vec
	nm64s*		dst,		//Output buffer		:long Any
	SpecTmp1*	spec		//Temporary Buffer	:long Local [nSize*8].
	)
{
	#ifdef RPC
	RPC_HOST_PPIP("nmppsDotProd_16s16s",srcVec0,srcVec1,size,dst,2,2);
	#else
	if (spec){
		nmppsConvert_16s64s(srcVec1,(nm64s*)spec->buffer,size);
		nmppsDotProd_16s64s(srcVec0,(nm64s*)spec->buffer,size,dst);
	}
	else {
		SpecTmp1	spec;
		if (nmppsMallocSpec1(&spec,size,S64,0)){
			nmppsConvert_16s64s(srcVec1,(nm64s*)spec.buffer,size);
			nmppsDotProd_16s64s(srcVec0,(nm64s*)spec.buffer,size,dst);
			nmppsFreeSpec1(&spec);
		}
	}
	#endif
}

//////////////////////////////////////////////////////////////////////////////////////
void nmppsDotProd_8s16s(
	nm8s*		srcVec0,	//Input0 buffer		:long Local [Size].
	nm16s*		srcVec1,	//Input1 buffer		:long Global[Size].
	int			size,		//Size of input vec
	nm64s*		dst,		//Output buffer		:long Any
	SpecTmp1*	spec		//Temporary Buffer	:long Local [nSize*8].
	)
{
	#ifdef RPC
	RPC_HOST_PPIP("nmppsDotProd_8s16s",srcVec0,srcVec1,size,dst,1,2);
	#else
	if (spec){
		nmppsConvert_16s64s(srcVec1,(nm64s*)spec->buffer,size);
		nmppsDotProd_8s64s (srcVec0,(nm64s*)spec->buffer,size,dst);
	}
	else {
		SpecTmp1	spec;
		if (nmppsMallocSpec1(&spec,size,S64,0)){
			nmppsConvert_16s64s(srcVec1,(nm64s*)spec.buffer,size);
			nmppsDotProd_8s64s (srcVec0,(nm64s*)spec.buffer,size,dst);
			nmppsFreeSpec1(&spec);
		}
	}
	#endif
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
void nmppsDotProd_8s8s(
	nm8s*		srcVec0,	//Input0 buffer		:long Local [Size].
	nm8s*		srcVec1,	//Input1 buffer		:long Global[Size].
	int			size,		//Size of input vec
	nm64s*		dst,		//Output buffer		:long Any
	SpecTmp1*	spec		//Temporary Buffer	:long Local [nSize*8].
	)
{
	#ifdef RPC
	RPC_HOST_PPIP("nmppsDotProd_8s8s",srcVec0,srcVec1,size,dst,1,1);
	#else
	if (spec){
		nmppsConvert_8s64s(srcVec1,(nm64s*)spec->buffer,size);
		nmppsDotProd_8s64s(srcVec0,(nm64s*)spec->buffer,size,dst);
	}
	else {
		SpecTmp1	spec;
		if (nmppsMallocSpec1(&spec,size,S64,0)){
			nmppsConvert_8s64s(srcVec1,(nm64s*)spec.buffer,size);
			nmppsDotProd_8s64s(srcVec0,(nm64s*)spec.buffer,size,dst);
			nmppsFreeSpec1(&spec);
		}
	}
	#endif
}

//////////////////////////////////////////////////////////////////////////////////////
/*
// With first argument conjuction
void nmppsDotProd_64sc64sc(nm64sc *pSrcVec1, nm64sc *pSrcVec2, int nSize, nm64sc *pDstRes)
{
	#ifdef RPC
	RPC_PPI(pSrcVec,pDstVec,nSize);
	#else

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

	#endif
}

*/
