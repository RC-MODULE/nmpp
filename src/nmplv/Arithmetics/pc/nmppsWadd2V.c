#include "nmplv.h"


void nmppsWeightedSum(nm8s* pSrcVec1,int W1,nm8s* pSrcVec2,int W2, nm16s* pDstVec, int nSize)
{
	for(int i=0;i<nSize;i++)	
	{
		pDstVec[i]=W1*pSrcVec1[i]+W2*pSrcVec2[i];	
	}
  return;	
}
void nmppsWeightedSum(nm16s* pSrcVec1,int W1,nm16s* pSrcVec2,int W2, nm32s* pDstVec, int nSize)
{
	for(int i=0;i<nSize;i++)	
	{
		pDstVec[i]=W1*pSrcVec1[i]+W2*pSrcVec2[i];	
	}
  return;	
}
void nmppsWeightedSum(nm32s* pSrcVec1,nm64s W1,nm32s* pSrcVec2,nm64s W2, nm64s* pDstVec, int nSize)
{
	for(int i=0;i<nSize;i++)	
	{
		pDstVec[i]=W1*pSrcVec1[i]+W2*pSrcVec2[i];	
	}
  return;	
}
