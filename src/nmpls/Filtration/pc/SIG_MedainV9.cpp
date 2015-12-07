#include "nmpls.h"

template<class T>  __INLINE__ void CompareSwap(T& a,T& b)
{
	if (a>b)
	{
		T t=a;
		a=b;
		b=t;
	}
}

template<class T>  __INLINE__ void Max(T& a,T &b)
{
	if (a<b)
	{
		a=b;
	}
}

template<class T>  __INLINE__ void Min(T& a,T &b)
{
	if (a>b)
	{
		a=b;
	}
}

template<class T>  __INLINE__ T Median9(T* pVec)
{
	CompareSwap(pVec[0],pVec[1]);
	CompareSwap(pVec[3],pVec[4]);
	CompareSwap(pVec[6],pVec[7]);

	CompareSwap(pVec[1],pVec[2]);
	CompareSwap(pVec[4],pVec[5]);
	CompareSwap(pVec[7],pVec[8]);

	CompareSwap(pVec[0],pVec[1]);
	CompareSwap(pVec[3],pVec[4]);
	CompareSwap(pVec[6],pVec[7]);

	Max(pVec[0],pVec[3]);
	Min(pVec[8],pVec[5]);

	CompareSwap(pVec[1],pVec[4]);

	Max(pVec[0],pVec[6]);
	Min(pVec[8],pVec[2]);
	Min(pVec[4],pVec[7]);
	Max(pVec[4],pVec[1]);

	CompareSwap(pVec[0],pVec[4]);
	Min(pVec[4],pVec[8]);
	Max(pVec[4],pVec[0]);
	
	return pVec[4];
}

int SIG_Median_V9(nm8s* pVec)
{
	return Median9(pVec);
}

int SIG_Median_V9(nm16s* pVec)
{
	return Median9(pVec);
}

int SIG_Median_V9(nm32s* pVec)
{
	return Median9(pVec);
}

nm64s SIG_Median_V9(nm64s* pVec)
{
	return Median9(pVec);
}
