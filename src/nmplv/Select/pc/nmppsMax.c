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
#include "rpc-host.h"
#include "nmplv.h"


/////////////////////////////////////////////////////////////////////////////////////////
// Search of maximum value in 8-bit buffer
void nmppsMax_8s(
				nm8s*		pSrcVec,	// input buffer					:long Local [Size/8]
				int			nSize,		// buffer size in 8-bit words	:nSize=[512,768,1024.....]
				int8b*		pMaxValue)	// Maximum
{
	#ifdef RPC
	RPC_HOST_PIR("nmppsMax_8s",pSrcVec,nSize,pMaxValue,1);
	#else

	int i;
	*pMaxValue=pSrcVec[0];
	for(i=1; i<nSize; i++){
		if(	*pMaxValue<pSrcVec[i])
			*pMaxValue= pSrcVec[i];
	}

	#endif
}
/////////////////////////////////////////////////////////////////////////////////////////
// Search of maximum value in 16-bit buffer
void nmppsMax_16s(
				nm16s*		pSrcVec,	// input buffer					:long Local [Size/4]
				int			nSize,		// buffer size in 16-bit words	:nSize=[256,384,512...]
				int16b*		pMaxValue)	// Maximum
{
	#ifdef RPC
	RPC_HOST_PIR("nmppsMax_16s",pSrcVec,nSize,pMaxValue,2);
	#else

	int i;
	*pMaxValue=pSrcVec[0];
	for(i=1; i<nSize; i++){
		if(	*pMaxValue<pSrcVec[i])
			*pMaxValue= pSrcVec[i];
	}

	#endif
}
/////////////////////////////////////////////////////////////////////////////////////////
// Search of maximum value in 32-bit buffer
void nmppsMax_32s(
				nm32s*		pSrcVec,	// input buffer					:long Local [Size/2]
				int			nSize,		// buffer size in 32-bit words	:nSize=[128,192,256..]
				int*		pMaxValue)	// Maximum
{
	#ifdef RPC
	RPC_HOST_PIR("nmppsMax_32s",pSrcVec,nSize,pMaxValue,4);
	#else

	int i;
	*pMaxValue=pSrcVec[0];
	for(i=1; i<nSize; i++){
		if(	*pMaxValue<pSrcVec[i])
			*pMaxValue= pSrcVec[i];
	}

	#endif
}
/////////////////////////////////////////////////////////////////////////////////////////
// Search of maximum value in 64-bit buffer
void nmppsMax_64s(
				nm64s63b*	pSrcVec,	// input buffer					:long Local [Size/2]
				int			nSize,		// buffer size in 32-bit words	:nSize=[128,192,256..]
				int64b*		pMaxValue)	// Maximum
{
	#ifdef RPC
	RPC_HOST_PIR64("nmppsMax_64s",pSrcVec,nSize,pMaxValue,8);
	#else

	int i;
	*pMaxValue=pSrcVec[0];
	for(i=1; i<nSize; i++){
		if( *pMaxValue<pSrcVec[i])
			*pMaxValue= pSrcVec[i];
	}

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////
// Function searches Maximum of array,
// returns Index of Maximum where it placed in the input array,
// and creates BitMap of Maximum precence in the input array for custom search of Maximum.
//void nmppsMaxPos(
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
//	nmppsMaxVal(SrcBuff, nSize, Maximum);
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
