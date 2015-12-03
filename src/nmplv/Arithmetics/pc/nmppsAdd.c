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
#include "nmpp.h"





/////////////////////////////////////////////////////////////////////////////////////////
// Summation of two char vectors
void nmppsAdd_8s(
		nm8s*			pSrcVec1,		// input buffer		:long Local [VecSize/8]
		nm8s*			pSrcVec2,		// input buffer		:long Local [VecSize/8]
		nm8s*			pDstVec,			// output buffer	:long Global[VecSize/8]
		int				nSize			// size of input buffer in 8 bit elements. nSize=[0,8,16,24...]
		)
{
	#ifdef RPC
	RPC_HOST_PPPI("nmppsAdd_8s",pSrcVec1,pSrcVec2,pDstVec,nSize,1);
	#else

	int i;
	for (i=0; i<nSize; i++)
		pDstVec[i] = pSrcVec1[i] + pSrcVec2[i];

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////
// Summation of two short vectors
void nmppsAdd_16s(
		nm16s*			pSrcVec1,		// input buffer		:long Local [VecSize/4]
		nm16s*			pSrcVec2,		// input buffer		:long Local [VecSize/4]
		nm16s*			pDstVec,			// output buffer	:long Global[VecSize/4]
		int				nSize			// size of input buffer in 16-bit elements. nSize=[0,4,8,12..]
		)
{
	#ifdef RPC
	RPC_HOST_PPPI("nmppsAdd_16s",pSrcVec1,pSrcVec2,pDstVec,nSize,2);
	#else

	int i;
	for (i=0; i<nSize; i++)
		pDstVec[i] = pSrcVec1[i] + pSrcVec2[i];

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////
// Summation of two int vectors
void nmppsAdd_32s(
		nm32s*			pSrcVec1,		// input buffer		:long Local [VecSize/2]
		nm32s*			pSrcVec2,		// input buffer		:long Local [VecSize/2]
		nm32s*			pDstVec,			// output buffer	:long Global[VecSize/2]
		int				nSize			// size of input buffer in 32-bit elements. nSize=[0,2,4,6...]
		)
{
	#ifdef RPC
	RPC_HOST_PPPI("nmppsAdd_32s",pSrcVec1,pSrcVec2,pDstVec,nSize,4);
	#else

	int i;
	for (i=0; i<nSize; i++)
		pDstVec[i] = pSrcVec1[i] + pSrcVec2[i];

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////
// Summation of two long vectors
void nmppsAdd_64s(
		nm64s*		pSrcVec1,		// input buffer		:long Local [nSize]
		nm64s*		pSrcVec2,		// input buffer		:long Local [nSize]
		nm64s*		pDstVec,			// output buffer	:long Global[nSize]
		int				nSize			// size of input buffer in 64-bit elements. nSize=[0,1,2,3...]
		)
{
	#ifdef RPC
	RPC_HOST_PPPI("nmppsAdd_64s",pSrcVec1,pSrcVec2,pDstVec,nSize,8);
	#else

	int i;
	for (i=0; i<nSize; i++)
		pDstVec[i] = pSrcVec1[i] + pSrcVec2[i];

	#endif
}


/////////////////////////////////////////////////////////////////////////////////////////
// Summation of two long complex vectors
void nmppsAdd_64sc(nm64sc *pSrcVec1, nm64sc *pSrcVec2, nm64sc *pDstVec, int nSize)
{
	#ifdef RPC
	RPC_HOST_PPPI("nmppsAdd_64sc",pSrcVec1,pSrcVec2,pDstVec,nSize,16);
	#else

	int i;
	for(i=0;i<nSize;i++)
	{
		pDstVec[i].re = pSrcVec1[i].re + pSrcVec2[i].re;
		pDstVec[i].im = pSrcVec1[i].im + pSrcVec2[i].im;
	}

	#endif
}


/////////////////////////////////////////////////////////////////////////////////////////
// Multiple Summation of several arrays with accumulation of result
void nmppsSum4_16s(
		nm16s**			Vectors,		// array of pointers to buffers	:nm8s*  Any  [NumberOfBuffer]
		nm16s*			pDstVec,		// result buffer				:long Local  [VecSize/4]
		int				nSize			// buffer size in 8-bit elements:nSize    =[256,512,..]
		)								// Buffer - char packed array	:long Global [VecSize/8]
{
	//#ifdef RPC
	//HOST_RPC_PPI(nmppsAdd_8s,pSrcVec1,pSrcVec2,pDstVec,nSize);
	//#else

	int i, j;
	for(i=0; i<nSize; i++)
	{
		pDstVec[i] = 0;
		for(j=0; j<4; j++)
			pDstVec[i] += (short)(Vectors[j][i]);
	}

	//#endif
}


/////////////////////////////////////////////////////////////////////////////////////////
// Multiple Summation of several arrays with accumulation of result
void nmppsSumN_8s16s(
		nm8s**			Vectors,		// array of pointers to buffers	:nm8s*  Any  [NumberOfBuffer]
		nm16s*			pDstVec,		// result buffer				:long Local  [VecSize/4]
		int				nSize,			// buffer size in 8-bit elements:nSize    =[256,512,..]
		int				VecNumber		// number of being added buffers:NumbersOfVectors=[2,3,4....]
		)								// Buffer - char packed array	:long Global [VecSize/8]
{
	//#ifdef RPC
	//RPC_HOST_PPPI(nmppsAdd_8s,pSrcVec1,pSrcVec2,pDstVec,nSize);
	//#else

	int i, j;
	for(i=0; i<nSize; i++)
	{
		pDstVec[i] = 0;
		for(j=0; j<VecNumber; j++)
			pDstVec[i] += (short)(Vectors[j][i]);
	}

	//#endif
}

/////////////////////////////////////////////////////////////////////////////////////////
// Multiple Summation of several arrays with accumulation of result
// pDstVec[i]=Buffers[0][i]+Buffers[1][i]+...+Buffers[NumberOfBuffers-1][i]
void nmppsSumN_16s(
		nm16s**			Vectors,		// array of pointers to buffers	:nm8s*  Any  [NumberOfBuffer]
		nm16s*			pDstVec,			// result buffer				:long Local  [VecSize/4]
		int				nSize,		// buffer size in 8-bit elements:nSize    =[***,..]
		int				VecNumber		// number of being added buffers:NumbersOfVectors=[2,3,4...256]
		)								// Buffer - char packed array	:long Global [VecSize/8]
{
	//#ifdef RPC
	//RPC_HOST_PPPI(nmppsAdd_8s,pSrcVec1,pSrcVec2,pDstVec,nSize);
	//#else

	int i;
	nmppsAdd_16s(Vectors[0],Vectors[1],pDstVec,nSize);
	for (i=2;i<VecNumber;i++)
		nmppsAdd_16s(Vectors[i],pDstVec,pDstVec,nSize); // with IPP use

	//#endif
}





/////////////////////////////////////////////////////////////////////////////////////////
// Increment of vec elements by constant value
// pDstVec[i]=pSrcVec[i]+Increment
void nmppsAddC_8s(
		nm8s*			pSrcVec,			// input buffer		:long Local [VecSize/8]
		int8b			nVal,				// increment		:Increment=[-128...+127]
		nm8s*			pDstVec,			// output buffer	:long Global[VecSize/8]
		int				nSize			// size of input buffer in 8 bit elements. nSize=[8,16,32...]
		)
{
	#ifdef RPC
	RPC_HOST_PIPI("nmppsAddC_8s",pSrcVec,nVal,pDstVec,nSize,1);
	#else

	int i;
	nVal=(char)nVal;
	for (i=0; i<nSize; i++)
		pDstVec[i] = pSrcVec[i] + nVal;


	#endif
}


/////////////////////////////////////////////////////////////////////////////////////////
// Increment of vec elements by constant value
// pDstVec[i]=Increment+pSrcVec[i]
void nmppsAddC_16s(
		nm16s*			pSrcVec,				// input buffer		:long Local [VecSize/4]
		int16b			nVal,					// increment		:
		nm16s*			pDstVec,				// output buffer	:long Global[VecSize/4]
		int				nSize				// size of input buffer in 16-bit elements. nSize=[0,4,8,12...]
		)
{
	#ifdef RPC
	RPC_HOST_PIPI("nmppsAddC_16s",pSrcVec,nVal,pDstVec,nSize,2);
	#else

	int i;
	nVal=(short)nVal;
	for (i=0; i<nSize; i++)
		pDstVec[i] = pSrcVec[i] + nVal;

	#endif
}



/////////////////////////////////////////////////////////////////////////////////////////
// Increment of vec elements by constant value
// pDstVec[i]=pSrcVec[i]+Increment
void nmppsAddC_32s(
		nm32s*			pSrcVec,			// input buffer		:long Local [VecSize/2]
		int				nVal,				// increment		:
		nm32s*			pDstVec,			// output buffer	:long Global[VecSize/2]
		int				nSize			// size of input buffer in 32-bit elements. nSize=[0,2,4,6...]
		)
{
	#ifdef RPC
	RPC_HOST_PIPI("nmppsAddC_32s",pSrcVec,nVal,pDstVec,nSize,4);
	#else

	int i;
	for (i=0; i<nSize; i++)
		pDstVec[i] = pSrcVec[i] + nVal;

	#endif
}


/////////////////////////////////////////////////////////////////////////////////////////
// Summation of two int vectors with addition of constant
void nmppsAdd_AddC_32s(
		nm32s*			SrcVecA,		// input buffer		:long Local [VecSize/2]
		nm32s*			SrcVecB,		// input buffer		:long Local [VecSize/2]
		int				nVal,				// additional constant
		nm32s*			pDstVec,			// output buffer	:long Global[VecSize/2]
		int				nSize			// size of input buffer in 32-bit elements. nSize=[0,2,4,6...]
		)
{
	//#ifdef RPC
	//RPC_HOST_PPPI(nmppsAdd_8s,pSrcVec1,pSrcVec2,pDstVec,nSize);
	//#else

	nmppsAdd_32s(SrcVecA,SrcVecB,pDstVec,nSize);
	nmppsAddC_32s(pDstVec,nVal,pDstVec,nSize);

	//#endif
}


/////////////////////////////////////////////////////////////////////////////////////////
// Increment of vec elements by constant value
// pDstVec[i]=pSrcVec[i]+Increment
/*
void nmppsAddC_32s(
		nm32s*			pSrcVec,			// input buffer		:long Local [VecSize/8]
		int*			nVal,				// increment		:Increment=[-128...+127]
		nm32s*			pDstVec,			// output buffer	:long Global[VecSize/8]
		int				nSize			// size of input buffer in 8 bit elements. nSize=[8,16,32...]
		)
{
	#ifdef RPC
	RPC_HOST_PPPI(nmppsAdd_8s,pSrcVec1,pSrcVec2,pDstVec,nSize);
	#else

	nmppsAddC(pSrcVec,*nVal,pDstVec,nSize);

	#endif
}

*/
/////////////////////////////////////////////////////////////////////////////////////////
// Increment of vec elements by constant value
// pDstVec[i]=pSrcVec[i]+Increment
void nmppsAddC_64s(
		nm64s*			pSrcVec,			// input buffer		:long Local [VecSize/8]
		nm64s*			nVal,				// increment		:Increment=[-128...+127]
		nm64s*			pDstVec,			// output buffer	:long Global[VecSize/8]
		int				nSize			// size of input buffer in 8 bit elements. nSize=[8,16,32...]
		)
{
	#ifdef RPC
	RPC_HOST_PIPI(nmppsAddC_64s,pSrcVec,nVal,pDstVec,nSize,16);
	#else

	int i;
	for (i=0; i<nSize; i++)
		pDstVec[i] = pSrcVec[i] + *nVal;

	#endif
}


