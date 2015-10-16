
//------------------------------------------------------------------------
//
//  $Workfile:: CompareMinV. $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2013/01/24 13:50:16 $
//
//! \if file_doc
//!
//! \file   VEC_MinNV.cpp
//! \author Сергей Мушкаев
//! \brief  Функции сравнения.
//!
//! \endif
//!
//------------------------------------------------------------------------
#include "nmplv.h"

/*void VEC_MinNV(nm8s7b**   pSrcVecs, int numVecs, nm8s7b*   pDstMinVec, int nSize);
void VEC_MinNV(nm16s15b** pSrcVecs, int numVecs, nm16s15b* pDstMinVec, int nSize);
void VEC_MinNV(nm32s31b** pSrcVecs, int numVecs, nm32s31b* pDstMinVec, int nSize);
void VEC_MinNV(nm64s63b** pSrcVecs, int numVecs, nm64s63b* pDstMinVec, int nSize);*/



void VEC_MinNV(nm8s7b**  pSrcVecs, int numVecs,  nm8s7b*  pDstMinVec, int nSize)
{
	int s1,s2,mask;
	nm8s * pVec0=pSrcVecs[0];
	nm8s * pVec1=pSrcVecs[1];
	for(int i=0;i<nSize;i++)
	{
		s1=pVec0[i];
		s2=pVec1[i];
		mask=((s1-s2)<<24)>>31;
		pDstMinVec[i]=(s1&mask)|(s2&(~mask));
	}
	
	for(int i=0;i<nSize;i++){
		for(int k=2; k<numVecs; k++){
			nm8s * pVec=pSrcVecs[k];
			s2=pVec[i];
			s1=pDstMinVec[i];
			mask=((s1-s2)<<24)>>31;
			pDstMinVec[i]=(s1&mask)|(s2&(~mask));
		}
	}
	
}
// test2test s1<=>s2
void VEC_MinNV(nm16s15b**  pSrcVecs, int numVecs,  nm16s15b*  pDstMinVec, int nSize)
{
	int s1,s2,mask;
	nm16s * pVec0=pSrcVecs[0];
	nm16s * pVec1=pSrcVecs[1];
	for(int i=0;i<nSize;i++)
	{
		s1=pVec0[i];
		s2=pVec1[i];
		mask=((s1-s2)<<16)>>31;
		pDstMinVec[i]=(s1&mask)|(s2&(~mask));
	}
	
	for(int i=0;i<nSize;i++){
		for(int k=2; k<numVecs; k++){
			nm16s * pVec=pSrcVecs[k];
			s2=pVec[i];
			s1=pDstMinVec[i];
			mask=((s1-s2)<<16)>>31;
			pDstMinVec[i]=(s1&mask)|(s2&(~mask));
		}
	}
	
}
void VEC_MinNV(nm32s31b**  pSrcVecs, int numVecs,  nm32s31b*  pDstMinVec, int nSize)
{
	int s1,s2,mask;
	nm32s * pVec0=pSrcVecs[0];
	nm32s * pVec1=pSrcVecs[1];
	for(int i=0;i<nSize;i++)
	{
		s1=pVec0[i];
		s2=pVec1[i];
		mask=(s1-s2)>>31;
		pDstMinVec[i]=(s1&mask)|(s2&(~mask));
	}
	
	for(int i=0;i<nSize;i++){
		for(int k=2; k<numVecs; k++){
			nm32s * pVec=pSrcVecs[k];
			s2=pVec[i];
			s1=pDstMinVec[i];
			mask=(s1-s2)>>31;
			pDstMinVec[i]=(s1&mask)|(s2&(~mask));
		}
	}
	
}
void VEC_MinNV(nm64s63b**  pSrcVecs, int numVecs,  nm64s63b*  pDstMinVec, int nSize)
{
	nm64s s1,s2,mask;
	nm64s * pVec0=pSrcVecs[0];
	nm64s * pVec1=pSrcVecs[1];
	for(int i=0;i<nSize;i++)
	{
		s1=pVec0[i];
		s2=pVec1[i];
		mask=(s1-s2)>>63;
		pDstMinVec[i]=(s1&mask)|(s2&(~mask));
	}
	
	for(int i=0;i<nSize;i++){
		for(int k=2; k<numVecs; k++){
			nm64s * pVec=pSrcVecs[k];
			s2=pVec[i];
			s1=pDstMinVec[i];
			mask=(s1-s2)>>63;
			pDstMinVec[i]=(s1&mask)|(s2&(~mask));
		}
	}
	
}
