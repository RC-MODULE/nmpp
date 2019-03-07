#include "nmpp.h"
#include "minrep.h"
#include "stdio.h"


int main()
{
	
	int maxW0=66;//128;
	int maxH0=66;
	int maxW1=66;

	nm32s* src0=nmppsMalloc_32s(maxW0*maxH0);
	nm64s* src1=nmppsMalloc_64s(maxW0);
	nm64s* dst =nmppsMalloc_64s(maxH0+1);
	if ((src0==0)||(src1==0)||(dst==0)) return -1;


	unsigned int crc = 0;
	
	nmppsRandUniform_32u((nm32u*)src0,maxW0*maxH0);
	nmppsRandUniform_32u((nm32u*)src1,maxW0*2);
	nmppsSet_32s((nm32s*)dst,(int)0xCCCCCCCC,(maxH0+1)*2);
	
	int w1=0;
	for(int h0=1; h0<=maxH0; h0+=1){
		for(int w0=2; w0<=maxW0; w0+=2){
			//printf("h0=%d w0=%d w1=%d %x\n",h0,w0,w1,crc);
			nmppmMul_mv_32s64s  (src0,src1, dst, h0,w0);				
			nmppsCrcAcc_64s (dst,(h0+1),&crc);
		}
	}
	//! \fn void nmppmMul_mm_32s32s(nm32s*,int,int,nm32s*,nm32s*,int)

	nmppsFree(src0);
	nmppsFree(src1);
	nmppsFree(dst);
	

	return crc>>2;
}
