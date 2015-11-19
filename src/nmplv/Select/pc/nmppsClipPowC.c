//------------------------------------------------------------------------
//
//  $Workfile:: Clip.cp $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:15 $
//
//! \if file_doc
//!
//! \file   Clip.cpp
//! \author Сергей Мушкаев
//! \brief  Функции насышения для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------
#include <crtdbg2.h>
#include "nmplv.h"
/////////////////////////////////////////////////////////////////////
// ClipEdgeIndx	ClippingRange
// 1			-2..1
// 2			-4..3
// 3			-8..7
// 4			-16..15
// 5			-32..31
// 6			-64..63
// 7			-128..127
// 8			-256..255
// 9			-512..511
// 10			-1024..1023		
// 11			-2048..2047
// ...
// 16           -0..0xFFFF
// 31         
void nmppsClipPowC_64s(nm64s*pSrcVec, int ClipEdgeIndx, nm64s*pDstVec, int nSize)
{
	int idx;
	long long  MaxValue,MinValue,Tmp;
	//ASSERTE(0<ClipEdgeIndx&&ClipEdgeIndx<64);
	MaxValue=0xFFFFFFFFFFFFFFFF>>(64-ClipEdgeIndx);
	MinValue=-MaxValue-1;

	for(idx=0;idx<nSize;idx++)
	{
		Tmp=pSrcVec[idx];
		if (Tmp > MaxValue )
			pDstVec[idx]=MaxValue;
		else
			if (Tmp < MinValue )
				pDstVec[idx]=MinValue;
			else 
				pDstVec[idx]=Tmp;
	}
}

/////////////////////////////////////////////////////////////////////
// ClipEdgeIndx	ClippingRange
// 1			-2..1
// 2			-4..3
// 3			-8..7
// 4			-16..15
// 5			-32..31
// 6			-64..63
// 7			-128..127
// 8			-256..255
// 9			-512..511
// 10			-1024..1023		
// 11			-2048..2047
// ...
// 16           -0..0xFFFF
// 31         
void nmppsClipPowC_32s(nm32s*pSrcVec, int ClipEdgeIndx, nm32s*pDstVec, int nSize)
{
	//ASSERTE(0<ClipEdgeIndx&&ClipEdgeIndx<32);
	int  MaxValue,MinValue,Tmp, idx;
	MaxValue=0xFFFFFFFF>>(32-ClipEdgeIndx);
	MinValue=-MaxValue-1;
									
	for(idx=0;idx<nSize;idx++)
	{
		Tmp=pSrcVec[idx];
		if (Tmp > MaxValue )
			pDstVec[idx]=MaxValue;
		else
			if (Tmp < MinValue )
				pDstVec[idx]=MinValue;
			else 
				pDstVec[idx]=Tmp;
	}
}
/////////////////////////////////////////////////////////////////////

// ClipEdgeIndx	ClippingRange
// 1			0..1
// 2			0..3
// 3			0..7
// 4			0..15
// 5			0..31
// 6			0..63
// 7			0..127
// 8			0..255
// 9			0..511
// 10			0..1023	
// 11			0..2047	
// ...
// 16           0..0xFFFF
void nmppsClipPowC0_32s(nm32s*pSrcVec, int ClipEdgeIndx, nm32u* pDstVec,  int nSize)
{
	int Tmp, idx;	
	unsigned int  Mask;
	ASSERTE(0<ClipEdgeIndx&&ClipEdgeIndx<32);
	Mask=0xFFFFFFFF;			
	if (ClipEdgeIndx!=0)			
		Mask>>=(32-ClipEdgeIndx);	
									

	for(idx=0;idx<nSize;idx++)
	{
		Tmp=pSrcVec[idx];
		if (Tmp<0) 
			pDstVec[idx]=0;
		else
			if (Tmp>Mask) 
				pDstVec[idx]=Mask;
			else
				pDstVec[idx]=Tmp;
	}
}
/////////////////////////////////////////////////////////////////////
// ClipEdgeIndx	ClippingRange
// 1			-2..1
// 2			-4..3
// 3			-8..7
// 4			-16..15
// 5			-32..31
// 6			-64..63
// 7			-128..127
// 8			-256..255
// 9			-512..511
// 10			-1024..1023		
// 11			-2048..2047
// ...
// 15           -32767..32767
   
void nmppsClipPowC_16s(nm16s*pSrcVec, int ClipEdgeIndx, nm16s*pDstVec, int nSize)
{
	short  MaxValue,MinValue,Tmp;
	int idx;
	ASSERTE(0<ClipEdgeIndx&&ClipEdgeIndx<16);

	MaxValue=0xFFFF>>(16-ClipEdgeIndx);
	MinValue=-MaxValue-1;
									
	for(idx=0;idx<nSize;idx++)
	{
		Tmp=pSrcVec[idx];
		if (Tmp > MaxValue )
			pDstVec[idx]=MaxValue;
		else
			if (Tmp < MinValue )
				pDstVec[idx]=MinValue;
			else 
				pDstVec[idx]=Tmp;
	}
}
/////////////////////////////////////////////////////////////////////
// ClipEdgeIndx	ClippingRange
// 1			0..1
// 2			0..3
// 3			0..7
// 4			0..15
// 5			0..31
// 6			0..63
// 7			0..127
// 8			0..255
// 9			0..511
// 10			0..1023	
// 11			0..2047	
// ...
// 15			0..32767
void nmppsClipPowC0_16s(nm16s*pSrcVec, int ClipEdgeIndx, nm16u*pDstVec,  int nSize)
{
	short Tmp;
	unsigned short  Mask;
	int idx;
	ASSERTE(0<ClipEdgeIndx&&ClipEdgeIndx<16);

	Mask=0xFFFF;			
	if (ClipEdgeIndx!=0)			
		Mask>>=(16-ClipEdgeIndx);	
									
	
	for(idx=0;idx<nSize;idx++)
	{
		Tmp=pSrcVec[idx];
		if (Tmp<0) 
			pDstVec[idx]=0;
		else
			if (Tmp>Mask) 
				pDstVec[idx]=Mask;
			else
				pDstVec[idx]=Tmp;
	}
}
/////////////////////////////////////////////////////////////////////////////////
// Clippig of 8 bit signed integer values to the range -2^ClipEdgeIndx to 2^ClipEdgeIndx-1
// 1			-2..1
// 2			-4..3
// 3			-8..7
// 4			-16..15
// 5			-32..31
// 6			-64..63
// 7			-128..127
void nmppsClipPowC_8s(							
			nm8s*		pSrcVec,		// Input Buffer								:long Local [Size/8]
			int			ClipEdgeIndx, // Index of the clippig edges				:ClipEdgeIndx=[1,2,...7]
			nm8s*		pDstVec,		// Output Buffer							:long Global[Size/8]
			int			nSize		// size of input buffer in 32 bit elements.	:nSize=[8,16,24,...]
			)

{
	char  MaxValue,MinValue,Tmp;
	int idx;
	ASSERTE(0<ClipEdgeIndx&&ClipEdgeIndx<8);
	MaxValue=0xFF>>(8-ClipEdgeIndx);
	MinValue=-MaxValue-1;
									
	for(idx=0;idx<nSize;idx++)
	{
		Tmp=pSrcVec[idx];
		if (Tmp > MaxValue )
			pDstVec[idx]=MaxValue;
		else
			if (Tmp < MinValue )
				pDstVec[idx]=MinValue;
			else 
				pDstVec[idx]=Tmp;
	}
}
/////////////////////////////////////////////////////////////////////
// ClipEdgeIndx	ClippingRange
// 1			0..1
// 2			0..3
// 3			0..7
// 4			0..15
// 5			0..31
// 6			0..63
// 7			0..127
void nmppsClipPowC0_8s(nm8s*pSrcVec, int ClipEdgeIndx, nm8u*pDstVec,  int nSize)
{
	unsigned char  Mask;
	char Tmp;
	int idx;
	ASSERTE(0<ClipEdgeIndx&&ClipEdgeIndx<8);
	Mask=0xFF;			
	if (ClipEdgeIndx!=0)			
		Mask>>=(8-ClipEdgeIndx);	
									
	
	for(idx=0;idx<nSize;idx++)
	{
		Tmp=pSrcVec[idx];
		if (Tmp<0) 
			pDstVec[idx]=0;
		else
			if (Tmp>Mask) 
				pDstVec[idx]=Mask;
			else
				pDstVec[idx]=Tmp;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////
// Extended clippig of 32 bit signed integer values to the range [NegThreshold...PosThrehold]
void nmppsClipCC_32s(							
			nm32s*	pSrcVec,			// Input vec			:long Global[Size/2]
			int		NegThreshold,	// Upper threshold		:=[0...2^16-1]
			int		PosThreshold,	// Lower threshold		:=[-2^16....0]
			nm32s*	pDstVec,			// Output vec		:long Local[Size/2]
			int		nSize		// nSize of vec 32 bit elements. nSize=[0,2,4,6...]
			)
{
	int v;
	int i;
	for (i=0;i<nSize;i++)
	{
		v=pSrcVec[i];
		if (v>PosThreshold)
			pDstVec[i]=PosThreshold;
		else
			if (v<NegThreshold)
				pDstVec[i]=NegThreshold;
			else
				pDstVec[i]=v;
	}
}

/////////////////////////////////////////////////////////////////////

void nmppsClipArshCnv_AddC_16s8s(nm16s* pSrcVec, int nClipFactor,int nShift, int8b nAddValue,nm8s* pDstVec, int nSize)
{
	int i;
	nm16s* pTmp=nmppsMalloc_16s(nSize);
    nmppsClipPowC_16s(pSrcVec, nClipFactor, pTmp, nSize);
    nmppsRShiftC_16s(pTmp, nShift, pTmp, nSize);



    for (i=0; i <nSize; i++)
    {
        pDstVec[i] = (char) pTmp[i] + nAddValue;
    }
	
	nmppsFree(pTmp);
}
