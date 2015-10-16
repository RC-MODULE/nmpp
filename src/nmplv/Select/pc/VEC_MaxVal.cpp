//------------------------------------------------------------------------
//
//  $Workfile:: GetMax.cp $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.2 $      $Date: 2005/07/13 14:19:56 $
//
//! \if file_doc
//!
//! \file   GetMax.cpp
//! \author Сергей Мушкаев
//! \brief  Статистические функции.
//!
//! \endif
//!
//------------------------------------------------------------------------

#include "nmplv.h"
#include "nmtl.h"

/////////////////////////////////////////////////////////////////////////////////////////
// Search of maximum value in 8-bit buffer
void VEC_MaxVal(
				nm8s*		pSrcVec,	// input buffer					:long Local [Size/8]
				int			nSize,		// buffer size in 8-bit words	:nSize=[512,768,1024.....]
				int8b&		MaxValue)	// Maximum
{
	MaxValue=char(MaxValue);
	int i;
	nmvec8s Buff(pSrcVec, nSize);
	nmint8s Max, Tmp;
	Max=Buff[0];
	for(i=1; i<nSize; i++)
	{
		Tmp = Max-Buff[i]; 
		if(Tmp < 0)
			Max=Buff[i];
	}
	MaxValue=(char)Max.m_value;

}
/////////////////////////////////////////////////////////////////////////////////////////
// Search of maximum value in 16-bit buffer
void VEC_MaxVal(
				nm16s*		pSrcVec,	// input buffer					:long Local [Size/4]
				int			nSize,		// buffer size in 16-bit words	:nSize=[256,384,512...]
				int16b&		MaxValue)	// Maximum
{
	MaxValue=short(MaxValue);
	int i;
	nmvec16s Buff(pSrcVec, nSize);
	nmint16s Max, Tmp;
	Max=Buff[0];
	for(i=1; i<nSize; i++)
	{
		Tmp = Max-Buff[i]; 
		if(Tmp < 0)
			Max=Buff[i];
	}
	MaxValue=(short)Max.m_value;
}
/////////////////////////////////////////////////////////////////////////////////////////
// Search of maximum value in 32-bit buffer
void VEC_MaxVal(
				nm32s*		pSrcVec,	// input buffer					:long Local [Size/2]
				int			nSize,		// buffer size in 32-bit words	:nSize=[128,192,256..]
				int&		MaxValue)	// Maximum
{
	int i;
	nmvec32s Buff(pSrcVec, nSize);
	nmint32s Max, Tmp;
	Max=Buff[0];
	for(i=1; i<nSize; i++)
	{
		Tmp = Max-Buff[i]; 
		if(Tmp < 0)
			Max=Buff[i];
	}
	MaxValue=(int)Max.m_value;
}
/////////////////////////////////////////////////////////////////////////////////////////
// Search of maximum value in 64-bit buffer
void VEC_MaxVal(
				nm64s63b*		pSrcVec,	// input buffer					:long Local [Size/2]
				int			nSize,		// buffer size in 32-bit words	:nSize=[128,192,256..]
				int64b&		MaxValue)	// Maximum
{
	int i;
	nmvec64s Buff(pSrcVec, nSize);
	nmint64s Max, Tmp;
	Max=Buff[0];
	for(i=1; i<nSize; i++)
	{
		Tmp = Max-Buff[i]; 
		if(Tmp < 0)
			Max=Buff[i];
	}
	MaxValue=Max.m_value;
}

/////////////////////////////////////////////////////////////////////////////////////////
// Function searches Maximum of array,
// returns Index of Maximum where it placed in the input array,
// and creates BitMap of Maximum precence in the input array for custom search of Maximum.
//void VEC_MaxPos(
//		nm16s*			SrcBuff,	// input buffer		:long Local [Size/4]
//		nm1*			MaxBitMap,	// output buffer	:long Global[Size/64] 
//		int				nSize,		// size of input buffer in 16-bit elements. nSize=[16,32...]
//		int &     Index,
//		int16b&			Maximum,	// Maximum element in array, position of wich is searched in the input buffer
//		void*			TmpBuff,	// temp  buffer		:long Local [Size/4]
//									// BitMap of Maximum presence at apropriate positions in the input array
//									// bit "1" - Maximum is present at this position
//									// bit "0" - approriate element in input array is not equal to Maximum
//		int				SearchDir	// Maximum search direction 
//									// =1 forward search of first maximum from the begining
//									// =0 don't search (custom search)
//									// =-1 backward search of first maximum from the end
//		)
//{
//	int i, j;
//	nm16s*cur = (nm16s*)MaxBitMap;
//
//	//Find maximum value.	
//	VEC_MaxVal(SrcBuff, nSize, Maximum);
//
//	//Create MaxBitMap. 
//	for(i=0; i<nSize/16; i++)
//	{
//		cur[i] = 0;
//		for(j=0; j<16; j++)
//		{
//			cur[i] <<= 1;
//			if(SrcBuff[i*16+j] == Maximum)
//				cur[i]++;
//		}
//	}
//
//	//Find maximum position.
//	if(SearchDir > 0)
//	{
//		for(i=0; i<nSize; i++)
//			if(SrcBuff[i] == Maximum)
//			{
//				Index=i;
//				break;
//			}
//	}
//	else if(SearchDir < 0)
//	{
//		for(i=nSize-1; i>=0; i--)
//			if(SrcBuff[i] == Maximum)
//			{
//				Index=i;
//				break;
//			}
//	}
//}
