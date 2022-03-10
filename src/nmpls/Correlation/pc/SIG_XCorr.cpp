//------------------------------------------------------------------------
//
//  $Workfile:: Convolution.cp $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/01/12 14:09:08 $
//
//! \if file_doc
//!
//! \file   Convolution.cpp
//! \author Mushkaev S.
//! \brief  Функции свертки для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------
#include "nmpls.h"


/////////////////////////////////////////////////////////////////////////////////////////
// Convolution calculation
// pDstVec[i]=pSrcVec[i]*pKernel[i]+pSrcVec[i+1]*pKernel[i%n+1]+...+pSrcVec[i+n]*pKernel[i%n+n]
void SIG_XCorr(
		nm32s*			 pSrcVec,		// input buffer			:long Local	[nSrcVecSize/2]
		int				 nSrcVecSize,	// size of input buffer in 32 bit elements. nSize=[2,4,6...]
		nm32s*			 pKernel,		// input buffer			:long Any   [nKernelSize/2]
		int				 nKernelSize,	// size of input buffer in 32 bit elements. nSize=[1,2,3...]
		nm32s*			 pDstVec,		// output buffer		:long Local	[(nSrcVecSize - nKernelSize)/2]
		void*			 pTmpBuff		// input/output buffer	:long Global[nKernelSize + 2]
		)
{
	int i;
	for(i=0; i<nSrcVecSize-nKernelSize+1;i++){
 		int sum=0;
		for (int j=0;j<nKernelSize;j++){
			sum+= ((int)pSrcVec[i+j]*pKernel[j]);
		}
		pDstVec[i] = sum;
	}
}


/////////////////////////////////////////////////////////////////////////////////////////
// Convolution calculation
// pDstVec[i]=pSrcVec[i]*pKernel[i]+pSrcVec[i+1]*pKernel[i%n+1]+...+pSrcVec[i+n]*pKernel[i%n+n]
void SIG_XCorr(
		nm16s*			 pSrcVec,		// input buffer		:long Local	[nSrcVecSize/2]
		int				 nSrcVecSize,	// size of input buffer in 32 bit elements. nSize=[4,8...]
		nm32s*			 pKernel,		// input buffer		:long Any   [nKernelSize/2]
		int				 nKernelSize,	// size of input buffer in 32 bit elements. nSize=[1,2,3...]
		nm32s*			 pDstVec,		// output buffer	:long Any	[(nSrcVecSize - nKernelSize)/2]
		void*			 pTmpBuff		// input/output buffer	:long Global[nKernelSize + 6]
		)
{
	int i;
	for(i=0; i<nSrcVecSize-nKernelSize+1;i++){
 		int sum=0;
		for (int j=0;j<nKernelSize;j++){
			sum+= ((int)pSrcVec[i+j]*pKernel[j]);
		}
		pDstVec[i] = sum;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
// Convolution calculation
// pDstVec[i]=pSrcVec[i]*pKernel[i]+pSrcVec[i+1]*pKernel[i%n+1]+...+pSrcVec[i+n]*pKernel[i%n+n]
void SIG_XCorr(
		nm8s*			 pSrcVec,			// input buffer		:long Local	[nSrcVecSize/2]
		int				 nSrcVecSize,		// size of input buffer in 32 bit elements. nSize=[8,16,..]
		nm32s*			 pKernel,			// input buffer		:long Any   [nKernelSize/2]
		int				 nKernelSize,		// size of input buffer in 32 bit elements. nSize=[1,2,3...]
		nm32s*			 pDstVec,			// output buffer	:long Any	[(nSrcVecSize - nKernelSize)/2]
		void*			 pTmpBuff			// input/output buffer	:long Global[nKernelSize + 14]
		)
{
	int i;
	for(i=0; i<nSrcVecSize-nKernelSize+1;i++){
 		int sum=0;
		for (int j=0;j<nKernelSize;j++){
			sum+= ((int)pSrcVec[i+j]*pKernel[j]);
		}
		pDstVec[i] = sum;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
// Faltung calculation
// pDstVec[i]=pSrcVec1[i]*pSrcVec2[i]+pSrcVec1[i+1]*pSrcVec2[i%8+1]+...+pSrcVec1[i+7]*pSrcVec2[i%8+7]
//void nmppsFaltung_(
//		nm32s*			pSrcVec1,		// input buffer		:long Local	[Size/8]
//		nm32s*			pSrcVec2,		// input buffer		:long Any   [2]
//		nm32s*			pDstVec,		// output buffer	:long Global[Size/4]
//		int				FaltungSize,	// size of input buffer in 8 bit elements. nSize=[8,16,32...]
//		int				nSrcVecSize	// size of input buffer in 8 bit elements. nSize=[8,16,32...]
//		)
//{
//
//int z,c,v,i;
//
//z = ((nSrcVecSize-FaltungSize)/2)*2;
//
//	for(i=0; i<z;i++)
//	{
//			pDstVec[i] = 0;
//		for (int j=0;j<FaltungSize;j++)
//			{
//			pDstVec[i] += (pSrcVec1[i+j]*pSrcVec2[j]);
//			}
//	}
//
//c = (MIN(FaltungSize,nSrcVecSize)/2)*2;
//v = (MIN(FaltungSize,nSrcVecSize)/2)*2+i;
//	
//	for(;i<v;i++)
//	{
//		pDstVec[i] = 0;
//		for (int j=0;j<c;j++)
//			pDstVec[i] += (pSrcVec1[i+j]*pSrcVec2[j]);
//
//		c--;
//	}
//
//}
