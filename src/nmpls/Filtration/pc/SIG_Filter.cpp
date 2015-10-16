//------------------------------------------------------------------------
//
//  $Workfile:: pcFilter.cp $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2005/01/12 14:09:08 $
//
//! \if file_doc
//!
//! \file   pcFilter.cpp
//! \author Сергей Мушкаев
//! \brief  Функции фильтрации для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------

//#include "tnmint.h"
//#include "vec.h"
#include "nmplv.h"
/*
int SIG_SetFilter_32s32s(int* pWeights, int nSize, nm64s* pKernel)
{
	pKernel[0]=nSize;
	memcpy(pKernel+1,pWeights,nSize<<2);
	return nSize;
}

int SIG_SetFilter_16s16s(int* pWeights, int nSize, nm64s* pKernel)
{
	pKernel[0]=nSize;
	memcpy(pKernel+1,pWeights,nSize<<2);
	return nSize;
}

int SIG_SetFilter_16s32s(int* pWeights, int nSize, nm64s* pKernel)
{
	pKernel[0]=nSize;
	memcpy(pKernel+1,pWeights,nSize<<2);
	return nSize;
}

int SIG_SetFilter_8s32s(int* pWeights, int nSize, nm64s* pKernel)
{
	pKernel[0]=nSize;
	memcpy(pKernel+1,pWeights,nSize<<2);
	return nSize;
}

int SIG_SetFilter_8s16s(int* pWeights, int nSize, nm64s* pKernel)
{
	pKernel[0]=nSize;
	memcpy(pKernel+1,pWeights,nSize<<2);
	return nSize;
}

int SIG_SetFilter_8s8s(int* pWeights, int nSize, nm64s* pKernel)
{
	pKernel[0]=nSize;
	memcpy(pKernel+1,pWeights,nSize<<2);
	return nSize;
}


void SIG_CreateFilter_32s32s(int* pWeights, int nSize, nm64s** pKernel, int hint)
{
	VEC_Malloc(pKernel,nSize,hint);
	SIG_SetFilter_32s32s(pWeights, nSize, *pKernel);
}

void SIG_CreateFilter_16s16s(int* pWeights, int nSize, nm64s** pKernel, int hint)
{
	VEC_Malloc(pKernel,nSize,hint);
	SIG_SetFilter_16s16s(pWeights, nSize, *pKernel);
}

void SIG_CreateFilter_16s32s(int* pWeights, int nSize, nm64s** pKernel, int hint)
{
	VEC_Malloc(pKernel,nSize,hint);
	SIG_SetFilter_16s32s(pWeights, nSize, *pKernel);
}

void SIG_CreateFilter_8s32s(int* pWeights, int nSize, nm64s** pKernel, int hint)
{
	VEC_Malloc(pKernel,nSize,hint);
	SIG_SetFilter_8s32s(pWeights, nSize, *pKernel);
}

void SIG_CreateFilter_8s16s(int* pWeights, int nSize, nm64s** pKernel, int hint)
{
	VEC_Malloc(pKernel,nSize,hint);
	SIG_SetFilter_8s16s(pWeights, nSize, *pKernel);
}

void SIG_CreateFilter_8s8s(int* pWeights, int nSize, nm64s** pKernel, int hint)
{
	VEC_Malloc(pKernel,nSize,hint);
	SIG_SetFilter_8s8s(pWeights, nSize, *pKernel);
}
*/

/////////////////////////////////////////////////////////////////////////////////////////
void SIG_Filter(
		nm32s*			 pSrcVec,	
		nm32s*			 pDstVec,	
		int				 nSize,		
		nm64s*			 pKernel	
		)
{
	nm32s* pWeights=(nm32s*)(pKernel+1);
	int	   nWeights=pKernel[0];
	int	   nDisp=nWeights/2;
	for(int i=0; i<(nSize&(~1));i++)
	{
 		int nSum=0;
		for (int j=0;j<nWeights;j++){
			nSum += pSrcVec[i+j-nDisp]*pWeights[j];
		}
		pDstVec[i]=nSum;
	}

}

/////////////////////////////////////////////////////////////////////////////////////////
void SIG_Filter(
		nm16s*			 pSrcVec,	
		nm16s*			 pDstVec,	
		int				 nSize,		
		nm64s*			 pKernel	
		)
{
	nm32s* pWeights=(nm32s*)(pKernel+1);
	int	   nWeights=pKernel[0];
	int	   nDisp=nWeights/2;
	for(int i=0; i<(nSize&(~3));i++)
	{
 		int nSum=0;
		for (int j=0;j<nWeights;j++){
			nSum += pSrcVec[i+j-nDisp]*pWeights[j];
		}
		pDstVec[i]=nSum;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////
void SIG_Filter(
		nm16s*			 pSrcVec,	
		nm32s*			 pDstVec,	
		int				 nSize,		
		nm64s*			 pKernel	
		)
{
	nm32s* pWeights=(nm32s*)(pKernel+1);
	int	   nWeights=pKernel[0];
	int	   nDisp=nWeights/2;
	for(int i=0; i<(nSize&(~3));i++)
	{
 		int nSum=0;
		for (int j=0;j<nWeights;j++){
			nSum += pSrcVec[i+j-nDisp]*pWeights[j];
		}
		pDstVec[i]=nSum;
	}

}

/////////////////////////////////////////////////////////////////////////////////////////
void SIG_Filter(
		nm8s*			 pSrcVec,	
		nm8s*			 pDstVec,	
		int				 nSize,		
		nm64s*			 pKernel	
		)
{
	nm32s* pWeights=(nm32s*)(pKernel+1);
	int	   nWeights=pKernel[0];
	int	   nDisp=nWeights/2;
	for(int i=0; i<(nSize&(~7));i++)
	{
 		int nSum=0;
		for (int j=0;j<nWeights;j++){
			nSum += pSrcVec[i+j-nDisp]*pWeights[j];
		}
		pDstVec[i]=nSum;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////
void SIG_Filter(
		nm8s*			 pSrcVec,	
		nm16s*			 pDstVec,	
		int				 nSize,		
		nm64s*			 pKernel	
		)
{
	nm32s* pWeights=(nm32s*)(pKernel+1);
	int	   nWeights=pKernel[0];
	int	   nDisp=nWeights/2;
	for(int i=0; i<(nSize&(~7));i++)
	{
 		int nSum=0;
		for (int j=0;j<nWeights;j++){
			nSum += pSrcVec[i+j-nDisp]*pWeights[j];
		}
		pDstVec[i]=nSum;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////
void SIG_Filter(
		nm8s*			 pSrcVec,	
		nm32s*			 pDstVec,	
		int				 nSize,		
		nm64s*			 pKernel	
		)
{
	nm32s* pWeights=(nm32s*)(pKernel+1);
	int	   nWeights=pKernel[0];
	int	   nDisp=nWeights/2;
	for(int i=0; i<(nSize&(~7));i++)
	{
 		int nSum=0;
		for (int j=0;j<nWeights;j++){
			nSum += pSrcVec[i+j-nDisp]*pWeights[j];
		}
		pDstVec[i]=nSum;
	}
}


