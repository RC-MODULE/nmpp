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
#include "nmpp.h"




/////////////////////////////////////////////////////////////////////////////////////////
// Multiple Summation of several arrays with accumulation of result
void nmppsAdd4V_16s(
		nm16s**			Vectors,		// array of pointers to buffers	:nm8s*  Any  [NumberOfBuffer]
		nm16s*			pDstVec,		// result buffer				:long Local  [VecSize/4]
		int				nSize			// buffer size in 8-bit elements:nSize    =[256,512,..]
		)								// Buffer - char packed array	:long Global [VecSize/8]
{
	int i, j;
	for(i=0; i<nSize; i++)
	{
		pDstVec[i] = 0;
		for(j=0; j<4; j++)
			pDstVec[i] += (short)(Vectors[j][i]);
	}
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
	int i, j;
	for(i=0; i<nSize; i++)
	{
		pDstVec[i] = 0;
		for(j=0; j<VecNumber; j++)
			pDstVec[i] += (short)(Vectors[j][i]);
	}
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
	int i;
	nmppsAdd_16s(Vectors[0],Vectors[1],pDstVec,nSize);
	for (i=2;i<VecNumber;i++)
		nmppsAdd_16s(Vectors[i],pDstVec,pDstVec,nSize); // with IPP use
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
	nmppsAdd_32s(SrcVecA,SrcVecB,pDstVec,nSize);
	nmppsAddC_32s(pDstVec,nVal,pDstVec,nSize);

}

