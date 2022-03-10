#include "nmpp.h"
#include "minrep.h"
#include "stdio.h"


int main()
{
	
	int maxW0=70;
	int maxH0=70;
	int maxW1=70;

	nm16s* src0=nmppsMalloc_16s(maxW0*maxH0);
	nm64s* src1=nmppsMalloc_64s(maxW0);
	nm64s* dst =nmppsMalloc_64s(maxH0+1);
	if ((src0==0)||(src1==0)||(dst==0)) return -1;

	unsigned int crc = 0;
	nmppsRandUniform_32u((nm32u*)src0,maxW0*maxH0/2);
	nmppsRandUniform_32u((nm32u*)src1,maxW0*2);
	nmppsSet_32s((int)0xCCCCCCCC,(nm32s*)dst,(maxH0+1)*2);
	
	int w1=0;
	for(int h0=1; h0<=maxH0; h0+=1){
		for(int w0=4; w0<=maxW0; w0+=4){
			//printf("h0=%d w0=%d w1=%d %x\n",h0,w0,w1,crc);
			nmppmMul_mv_16s64s(src0,src1, dst,h0,w0);				
			nmppsCrcAcc_64s (dst, (h0+1),&crc);
		}
	}

	nmppsFree(src0);
	nmppsFree(src1);
	nmppsFree(dst);
	

	return crc>>2;
}
