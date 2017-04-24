#include "nmpp.h"
//#include "minrep.h"
#include "stdio.h"
#include "time.h"
/////////////////////////////////////////////////////////////////////////////////
int KB=1024/8;

int main()
{
	
	clock_t t0,t1;
	int maxSize64=32*KB;
	int maxSize=maxSize64*8;

	nm4s* src=nmppsMalloc_4s(maxSize);
	nm8s* dst=nmppsMalloc_8s(maxSize);
	if ((src==0)||(dst==0)) return -1;


	unsigned int crc = 0;
	nmppsRandUniform_64s((nm64s*)src,maxSize/16);
	nmppsSet_32s((nm32s*)dst,(0xCCCCCCCC),maxSize/8*2);
	for(int testSize=0;testSize<maxSize-16;testSize+=16)
	{
		t0=clock();
		nmppsConvert_4s8s((nm4s*)src,(nm8s*)dst,testSize);	
		t1=clock();
		//nmppsConvert_8u16u((nm8u*)src,(nm16u*)dst,testSize/2);
		//nmppsConvert_2u4u((nm2u*)src,(nm4u*)dst,testSize*2);
		nmppsCrcAcc_32s((nm32s*)dst,testSize/8*2+2,&crc);
		if ((testSize&(testSize-1)) == 0 && testSize)
			printf("size=%8d %f\n",testSize, (t1-t0)*1.0/testSize);
	}
	//! \fn void nmppsConvert_8u(nm8u* pSrc,nm16u* pDst,int)	

	
	nmppsFree(src);
	nmppsFree(dst);
	

	return crc>>2;
}

