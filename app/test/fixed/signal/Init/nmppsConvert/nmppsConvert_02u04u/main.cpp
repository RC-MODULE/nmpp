#include "nmpp.h"
//#include "minrep.h"
#include "stdio.h"
#include "time.h"
/////////////////////////////////////////////////////////////////////////////////
int KB=1024/8;

int main()
{
	
	int maxSize64=32*KB;
	int maxSize=maxSize64*8;
	clock_t t0,t1;
	nm2u* src=nmppsMalloc_2u(maxSize);
	nm4u* dst=nmppsMalloc_4u(maxSize);
	if ((src==0)||(dst==0)) return -1;


	unsigned int crc = 0;
	nmppsRandUniform_64u((nm64u*)src,maxSize/32);
	nmppsSet_32s((0xCCCCCCCC),(nm32s*)dst,maxSize/16*2);
	for(int testSize=0;testSize<maxSize-16;testSize+=32)
	{
		t0=clock();
		nmppsConvert_2u4u((nm2u*)src,(nm4u*)dst,testSize);	
		t1=clock();
		nmppsCrcAcc_32s((nm32s*)dst,testSize/16*2+2,&crc);
		if ((testSize&(testSize-1)) == 0 && testSize)
			printf("size=%8d %f\n",testSize, (t1-t0)*1.0/testSize);
	}
	//! \fn void nmppsConvert_8u(nm8u* pSrc,nm16u* pDst,int)	


	nmppsFree(src);
	nmppsFree(dst);
	

	return crc>>2;
}

