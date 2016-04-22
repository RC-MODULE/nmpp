#include "nmpp.h"

void nmppsWeightedSum_8s16s(nm8s* pSrcVec1,int W1,nm8s* pSrcVec2,int W2, nm16s* pDstVec, int nSize)
{
	int i;
	for (i=0;i<nSize;i++)	
	{
		pDstVec[i]=W1*pSrcVec1[i]+W2*pSrcVec2[i];	
	}
  return;	
}

void nmppsWeightedSum_16s32s(nm16s* pSrcVec1,int W1,nm16s* pSrcVec2,int W2, nm32s* pDstVec, int nSize)
{
	int i;
	for (i=0;i<nSize;i++)	
	{
		pDstVec[i]=W1*pSrcVec1[i]+W2*pSrcVec2[i];	
	}
  return;	
}

void nmppsWeightedSum_32s64s(nm32s* pSrcVec1,nm64s W1,nm32s* pSrcVec2,nm64s W2, nm64s* pDstVec, int nSize)
{
	int i;
	for (i=0;i<nSize;i++)	
	{
		pDstVec[i]=W1*pSrcVec1[i]+W2*pSrcVec2[i];	
	}
  return;	
}

