#include "nmpp.h"
//#include "minrep.h"

/////////////////////////////////////////////////////////////////////////////////
int KB=1024/8;

int main()
{
	
	int maxSize64=64*KB;
	int maxSize=maxSize64/8;

	nm4s* src=nmppsMalloc_4s(maxSize);
	nm2s* dst=nmppsMalloc_2s(maxSize);
	if ((src==0)||(dst==0)) return -1;


	unsigned int crc = 0;
	nmppsRandUniform_64s((nm64s*)src,maxSize/16);
	nmppsSet_32s((nm32s*)dst,(0xCCCCCCCC),maxSize/32*2);
	for(int testSize=0;testSize<maxSize-16;testSize+=32)
	{
		nmppsConvert_4s2s((nm4s*)src,(nm2s*)dst,testSize);	
		nmppsCrcAcc_32s((nm32s*)dst,testSize/32*2+2,&crc);
	}
	//! \fn void nmppsConvert_8u(nm8u* pSrc,nm16u* pDst,int)	


	nmppsFree(src);
	nmppsFree(dst);
	

	return crc>>2;
}

