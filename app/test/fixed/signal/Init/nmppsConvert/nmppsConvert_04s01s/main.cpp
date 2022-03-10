#include "nmpp.h"
//#include "minrep.h"
#include "stdio.h"
#include "time.h"
/////////////////////////////////////////////////////////////////////////////////
int KB=1024/8;

int main()
{
	
	int maxSize64=64*KB;
	int maxSize=maxSize64*8;
	clock_t t0,t1;
	nm4s* src=nmppsMalloc_4s(maxSize);
	nm1* dst=nmppsMalloc_1 (maxSize+2*64);
	if ((src==0)||(dst==0)) return -1;


	unsigned int crc = 0;
	nmppsRandUniform_64s((nm64s*)src,maxSize/16);
	//nmppsSet_64s(0x0000111100001111,(nm64s*)src, maxSize / 16);
	nmppsSet_32s((0xCDCDCDCD),(nm32s*)dst,maxSize/32+2);
	for(int testSize=0;testSize<maxSize-16;testSize+=64)
	{
		//int testSize = 64*31;
		//t0=clock();
		nmppsConvert_4s1s((nm4s*)src,(nm1*)dst,testSize);	
		//t1=clock();
		nmppsCrcAcc_32s((nm32s*)dst,testSize/32,&crc);
		//if ((testSize&(testSize-1)) == 0 && testSize)
			//printf("size=%8d %f\n",testSize, (t1-t0)*1.0/testSize);
	}
	//! \fn void nmppsConvert_8u(nm8u* pSrc,nm16u* pDst,int)	


	nmppsFree(src);
	nmppsFree(dst);
	

	return crc>>2;
}

