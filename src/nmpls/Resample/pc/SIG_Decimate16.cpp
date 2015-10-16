#include "nmtype.h"
void SIG_Decimate16(nm8s* pSrcVec,nm8s* pDstVec,int nDstSize)
{
	for(int i=0;i<nDstSize;i++)
	{
		pDstVec[i]=pSrcVec[i<<4];
	}
}

void SIG_Decimate16(nm16s* pSrcVec,nm16s* pDstVec,int nDstSize)
{
	for(int i=0;i<nDstSize;i++)
	{
		pDstVec[i]=pSrcVec[i<<4];
	}
}

void SIG_Decimate16(nm32s* pSrcVec,nm32s* pDstVec,int nDstSize)
{
	for(int i=0;i<nDstSize;i++)
	{
		pDstVec[i]=pSrcVec[i<<4];
	}
}

void SIG_Decimate16(nm64s* pSrcVec,nm64s* pDstVec,int nDstSize)
{
	for(int i=0;i<nDstSize;i++)
	{
		pDstVec[i]=pSrcVec[i<<4];
	}
}