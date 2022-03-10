//------------------------------------------------------------------------
//
//  $Workfile:: Sum.cpp  $
//
//  ��������-��������� ����������
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:15 $
//
//! \if file_doc
//!
//! \file   Sum.cpp
//! \author ������ �������
//! \brief  �������������� ������� 
//!
//! \endif
//!
//------------------------------------------------------------------------

#include "nmtype.h"


unsigned ByteArray[256]={0, 1, 1, 2, 1, 2, 2, 3, 
												 1, 2, 2, 3, 2, 3, 3, 4, 
												 1, 2, 2, 3, 2, 3, 3, 4, 
												 2, 3, 3, 4, 3, 4, 4, 5, 
												 1, 2, 2, 3, 2, 3, 3, 4, 
												 2, 3, 3, 4, 3, 4, 4, 5, 
												 2, 3, 3, 4, 3, 4, 4, 5, 
												 3, 4, 4, 5, 4, 5, 5, 6, 
												 1, 2, 2, 3, 2, 3, 3, 4, 
												 2, 3, 3, 4, 3, 4, 4, 5, 
												 2, 3, 3, 4, 3, 4, 4, 5, 
												 3, 4, 4, 5, 4, 5, 5, 6, 
												 2, 3, 3, 4, 3, 4, 4, 5, 
												 3, 4, 4, 5, 4, 5, 5, 6, 
												 3, 4, 4, 5, 4, 5, 5, 6, 
												 4, 5, 5, 6, 5, 6, 6, 7, 
												 1, 2, 2, 3, 2, 3, 3, 4, 
												 2, 3, 3, 4, 3, 4, 4, 5, 
												 2, 3, 3, 4, 3, 4, 4, 5, 
												 3, 4, 4, 5, 4, 5, 5, 6, 
												 2, 3, 3, 4, 3, 4, 4, 5, 
												 3, 4, 4, 5, 4, 5, 5, 6, 
												 3, 4, 4, 5, 4, 5, 5, 6, 
												 4, 5, 5, 6, 5, 6, 6, 7, 
												 2, 3, 3, 4, 3, 4, 4, 5, 
												 3, 4, 4, 5, 4, 5, 5, 6, 
												 3, 4, 4, 5, 4, 5, 5, 6, 
												 4, 5, 5, 6, 5, 6, 6, 7, 
												 3, 4, 4, 5, 4, 5, 5, 6, 
												 4, 5, 5, 6, 5, 6, 6, 7, 
												 4, 5, 5, 6, 5, 6, 6, 7, 
												 5, 6, 6, 7, 6, 7, 7, 8 };





/////////////////////////////////////////////////////////////////////////////////////////
// Count bits in 64-bit vectors. Each amount store in the 64 bit vec. 
void		nmppsSum_1s(
const 	nm1*	pSrcVec,			// input buffer		:long Local [nSize]
		int		nSize,			// size of input buffer in 64-bit elements. nSize=[0,1,2,3...]
		int *   pnRes, 
		void*	pTmpBuf
		)
{

	int sum=0;
/*
	nm64u x;
	nm64u* Src=(nm64u*) pSrcVec;
	int i;
	for (i=0;i<nSize>>6;i++)
	{
		x=Src[i];
		int j;
		for(j=0;j<64;j++)
			sum+=(x>>j)&1;
		
	}
*/

	nm8u x;
	nm8u* Src=(nm8u*) pSrcVec;
/*
	int i;
	for (i=0;i<nSize>>3;i++)
	{
		x=Src[i];
		sum+=((x&1)+(x&2)+(x&4)+(x&8)+(x&16)+(x&32)+(x&64)+(x&128));
	}
*/
	int i;
	for (i=0;i<nSize>>3;i++)
	{
		x=Src[i];
		sum+=ByteArray[x];
	}

	*pnRes=sum;


}


/////////////////////////////////////////////////////////////////////////////////////////
// Summation of all elements in array
void nmppsSum_8s(
const 	nm8s*	pSrcVec,
		int		nSize,
		int *   pnRes
		)
{
	int sum = 0;
	int i;
	for (i=0; i<nSize; i++)
		sum += (int)pSrcVec[i];
	*pnRes=sum;

}


/////////////////////////////////////////////////////////////////////////////////////////
// Summation of all elements in array
void nmppsSum_16s(
const 	nm16s*		pSrcVec,
		int			nSize,
		int64b *   	pnRes
		)
{
	int64b sum = 0;
	int i;
	for (i=0; i<nSize; i++)
		sum += pSrcVec[i];
	*pnRes=sum;

}

/////////////////////////////////////////////////////////////////////////////////////////
// Summation of all elements in array
void nmppsSum_32s(
const 	nm32s*		pSrcVec,
		int			nSize,
		int64b *   	pnRes
		)
{
	int64b sum = 0;
	int i;
	for (i=0; i<nSize; i++)
		sum += pSrcVec[i];
	*pnRes=sum;

}

/////////////////////////////////////////////////////////////////////////////////////////
// Summation of all elements in array
void nmppsSum_64s(
const 	nm64s*		pSrcVec,
		int			nSize,
		int64b *   	pnRes
		)
{
	int64b sum = 0;
	int i;
	for (i=0; i<nSize; i++)
		sum += pSrcVec[i];
	*pnRes=sum;

}

