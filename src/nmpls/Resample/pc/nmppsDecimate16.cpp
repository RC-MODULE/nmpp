#include "nmtype.h"
void nmppsDecimate16_8s(nm8s* pSrcVec,nm8s* pDstVec,int nDstSize)
{
	for(int i=0;i<nDstSize;i++)
	{
		pDstVec[i]=pSrcVec[i<<4];
	}
}

void nmppsDecimate16_16s(nm16s* pSrcVec,nm16s* pDstVec,int nDstSize)
{
	for(int i=0;i<nDstSize;i++)
	{
		pDstVec[i]=pSrcVec[i<<4];
	}
}

void nmppsDecimate16_32s(nm32s* pSrcVec,nm32s* pDstVec,int nDstSize)
{
	for(int i=0;i<nDstSize;i++)
	{
		pDstVec[i]=pSrcVec[i<<4];
	}
}

void nmppsDecimate16_64s(nm64s* pSrcVec,nm64s* pDstVec,int nDstSize)
{
	for(int i=0;i<nDstSize;i++)
	{
		pDstVec[i]=pSrcVec[i<<4];
	}
}