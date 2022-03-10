
#include "nmpp.h"
#include "time.h"
#include "stdio.h"


int main()
{
	clock_t t0,t1;
	int size = 1024;
//	nmppsMallocSpec.route[0]=0x2031;
//	nmppsMallocSetRouteMode();
	nm64u* src = nmppsMalloc_64u(size);
	nm64u* dst = nmppsMalloc_64u(size);
	nmppsRandUniform_64u (src,size);
	unsigned int crc = 0;
//	t0=clock();
	nm64u pnBits = -1;
	//////////////////////////////////////////////////
	for (int isize =1;isize<size;isize++)
	{
		for(int nBits =1;nBits<63;nBits++)
		{
			nmppsFwdShiftBitstream(src, dst,&pnBits,nBits, isize);
			nmppsCrcAcc_64u(dst,isize,&crc);
		}
	}
	//////////////////////////////////////////////////
//	t1=clock();

	nmppsFree(src);
	nmppsFree(dst);
	return crc>>2;	
//	return t1-t0;	
}
