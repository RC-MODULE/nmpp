#include "nmpls.h"

template<class T> static inline void CompareSwap(T& a,T& b)
{
	if (a>b)
	{
		T t=a;
		a=b;
		b=t;
	}
}

template<class T> static inline void Max(T& a,T &b)
{
	if (a<b)
	{
		a=b;
	}
}

template<class T> static inline void Min(T& a,T &b)
{
	if (a>b)
	{
		a=b;
	}
}


int SIG_Median3(int a,int b, int c)
{
	CompareSwap(a,b);
	Min(b,c);
	Max(a,b);
	return a;
}

unsigned int SIG_Median3(unsigned int a, unsigned int b, unsigned int c)
{
	CompareSwap(a,b);
	Min(b,c);
	Max(a,b);
	return a;
}


/*

int SIG_Median_V3(nm8s* pVec)
{
	return Median3(pVec);
}

int SIG_Median_V3(nm16s* pVec)
{
	return Median3(pVec);
}

int SIG_Median_V3(nm32s* pVec)
{
	return Median3(pVec);
}

nm64s SIG_Median_V3(nm64s* pVec)
{
	return Median3(pVec);
}
*/
