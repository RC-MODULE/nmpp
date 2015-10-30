//------------------------------------------------------------------------
//
//  $Workfile:: GetMin.cp $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:16 $
//
//! \if file_doc
//!
//! \file   GetMin.cpp
//! \author Сергей Мушкаев
//! \brief  Статистические функции для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------
#include "nmplv.h"
#include "nmtl.h"
/////////////////////////////////////////////////////////////////////////////////////////
// Search of minimum value in 8-bit buffer
void nmppsMinVal_8s(nm8s*		pSrcVec,	// input buffer					:long Global [Size/8]
				int			nSize,		// buffer size in 8-bit words	:nSize=[8,16,24.....]
				int8b&		MinValue)	// Minimum
{
	MinValue=char(MinValue);
	int i;
	nmvec8s Buff(pSrcVec, nSize);
	nmint8s Min, Tmp;
	Min=Buff[0];
	for(i=1; i<nSize; i++)
	{
		Tmp = Buff[i]-Min; 
		if(Tmp < 0)
			Min=Buff[i];
	}
	MinValue=(char)Min.m_value;

}
/////////////////////////////////////////////////////////////////////////////////////////
// Search of minimum value in 16-bit buffer
void nmppsMinVal_16s(nm16s*		pSrcVec,	// input buffer					:long Global [Size/4]
				int			nSize,		// buffer size in 16-bit words	:nSize=[4,8,12....]
				int16b&		MinValue)	// Minimum
{
	MinValue=short(MinValue);
	if (CHECK_OVERFLOW())
	{
		int i;
	nmvec16s Buff(pSrcVec, nSize);
	nmint16s Min, Tmp;
	Min=Buff[0];
	for(i=1; i<nSize; i++)
	{
		Tmp = Buff[i]-Min; 
		if(Tmp < 0)
			Min=Buff[i];
	}
	MinValue=(short)Min.m_value;

	}
	else
	{
		MinValue=pSrcVec[0];
		short Tmp;
		for(int i=1; i<nSize; i++)
		{
			Tmp = pSrcVec[i] - MinValue; 
			if(Tmp < 0)
				MinValue=pSrcVec[i];
		}
	}

}
/////////////////////////////////////////////////////////////////////////////////////////
// Search of minimum value in 32-bit buffer
void nmppsMinVal_32s(nm32s*		pSrcVec,	// input buffer					:long Global [Size/2]
				int			nSize,		// buffer size in 32-bit words	:nSize=[2,4,6....]
				int&		MinValue)	// Minimum
{
	int i;
	nmvec32s Buff(pSrcVec, nSize);
	nmint32s Min, Tmp;
	Min=Buff[0];
	for(i=1; i<nSize; i++)
	{
		Tmp = Buff[i]-Min; 
		if(Tmp < 0)
			Min=Buff[i];
	}
	MinValue=(int)Min.m_value;

}
/////////////////////////////////////////////////////////////////////////////////////////
// Function searches Minimum of array,
// returns Index of Minimum where it placed in the input array,
// and creates BitMap of Minimum precence in the input array for custom search of Maximum.
//void nmppsMinPos_(
//		nm16s*			SrcBuff,	// input buffer		:long Local [Size/4]
//		nm1*			MinBitMap,	// output buffer	:long Global[Size/64] 
//		int				nSize,		// size of input buffer in 16-bit elements. nSize=[16,32...]
//		int&			Index,
//		int16b&			Minimum,	// Minimum element in array, position of wich is searched in the input buffer
//		void*			TmpBuff,	// temp  buffer		:long Local [Size/4]
//									// BitMap of Minimum presence at apropriate positions in the input array
//									// bit "1" - Minimum is present at this position
//									// bit "0" - approriate element in input array is not equal to Minimum
//		int				SearchDir	// Minimum search direction 
//									// =1 forward search of first minimum from the begining
//									// =0 don't search (custom search)
//									// =-1 backward search of first minimum from the end
//		)
//{
//	int i, j;
//	nm16s*cur = (nm16s*)MinBitMap;
//
//	//Find maximum value.	
//	nmppsMinVal_(SrcBuff, nSize, Minimum);
//
//	//Create MaxBitMap. 
//	for(i=0; i<nSize/16; i++)
//	{
//		cur[i] = 0;
//		for(j=0; j<16; j++)
//		{
//			cur[i] <<= 1;
//			if(SrcBuff[i*16+j] == Minimum)
//				cur[i]++;
//		}
//	}
//
//	//Find maximum position.
//	if(SearchDir > 0){
//		for(i=0; i<nSize; i++){
//			if(SrcBuff[i] == Minimum){
//				Index=i;
//				break;
//			}
//		}
//	}
//	
//	else if(SearchDir < 0){
//		for(i=nSize-1; i>=0; i--){
//			if(SrcBuff[i] == Minimum){
//				Index=i;
//				break;
//			}
//		}
//	}
//}




