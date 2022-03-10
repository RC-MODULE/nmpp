//------------------------------------------------------------------------
//
//  $Workfile:: Quant.cp $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:14 $
//
//! \if file_doc
//!
//! \file   Quant.cpp
//! \author Сергей Мушкаев
//! \brief  Функции деления для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////
#include "nmtype.h"
/////////////////////////////////////////////////////////////////////////////////
//	Quantization in pairs of 32-bit signed words
void nmppsQuant_By2Int_32s(nm32s*	pSrcVec,			// Input array 					:long Global[Count/2*SrcReadStep/2]
			nm32s*	DstBuffer,			// Output qunatized array		:long Global[Count/2*DstWriteStep/2]
			nm32s*	Quantizers,			// pArray of two quantizers		:long Any	[2/2]; Quantizers[0,1]=[1,2,3...128]
			int		Count,				// Number of 32-bit elements to be quantized	:=[0,1,2,3...]
			void*	TmpBuffer,			// First  Temporary array		:long Local [Count/2]
			int		SrcReadStep,		// long to long reading step (in 32-bit words)	:=[-2,0,2,4,6...]
			int		DstWriteStep,		// long to long writing step (in 32-bit words)	:=[-2,0,2,4,6...] 
			int		PreShift,			// Right preshifting by even number of bits		:=[0,2,4...30]
			int		UsePostShift		// if =0 - Skip result scaling down by 2^19 
			)						

{
	int i, j, k;


	int Q0=(1<<18)/Quantizers[0]+1;
	int DQ0=1<<17;
	int Q1=(1<<18)/Quantizers[1]+1;
	int DQ1=1<<17;
	j = k = 0;
	for(i=0; i<Count>>1; i++)
	{
		DstBuffer[j] =  (pSrcVec[k]  >>PreShift)*Q0+DQ0;
		DstBuffer[j+1]= (pSrcVec[k+1]>>PreShift)*Q1+DQ1;
		if (UsePostShift)
		{
			DstBuffer[j]  >>=18;
			DstBuffer[j+1]>>=18;
		}
		//DstBuffer[j] =  (pSrcVec[k] >> PreShift ) /Quantizers[0];
		//DstBuffer[j+1]= (pSrcVec[k+1] >>PreShift) /Quantizers[1];
		
		j += DstWriteStep;
		k += SrcReadStep;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
void nmppsDequant_By2Int_32s(nm32s*	pSrcVec,			// Input array 					:long Global[NumbersOfPairs*SrcPairReadStep/2]
			nm32s*	pDstVec,			// Output qunatized array		:long Local [NumbersOfPairs*DstPairWriteStep/2]
			nm32s*	PairOfQuantizers,	// pArray of two quantizers		:long Local [2/2]
			int		NumbersOfPairs,		// Numbers of input pairs should be quantized: =[1,2,3...]
			int		SrcReadStep,		// Reading step (in 32-bit words) between two input pairs to be quantized: =[2,4,6...]
			int		DstWriteStep		// Writing step (in 32-bit words) between two output quantized pairs:      =[2,4,6...] 
			)
{
	int i, j, k;

	j = k = 0;
	for(i=0; i<NumbersOfPairs; i++)
	{
		pDstVec[j] = PairOfQuantizers[0] * pSrcVec[k];
		pDstVec[j+1] = PairOfQuantizers[1] * pSrcVec[k+1];
		j += DstWriteStep;
		k += SrcReadStep;
	}
}

