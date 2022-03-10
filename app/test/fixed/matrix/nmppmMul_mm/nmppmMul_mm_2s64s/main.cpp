#include "nmpp.h"
#include "minrep.h"
#include "stdio.h"


int main()
{
	
	int maxW0=70;
	int maxH0=70;
	int maxW1=70;

	nm2s*  src0=nmppsMalloc_2s (maxW0*maxH0);
	nm64s* src1=nmppsMalloc_64s(maxW1*maxW0);
	nm64s* dst =nmppsMalloc_64s(maxW1*(maxH0+1));
	if ((src0==0)||(src1==0)||(dst==0)) return -1;

	unsigned int crc = 0;
	nmppsRandUniform_32u((nm32u*)src0,maxW0*maxH0/16);
	nmppsRandUniform_32u((nm32u*)src1,maxW1*maxW0*2);
	nmppsSet_32s((int)0xCCCCCCCC,(nm32s*)dst,maxW1*(maxH0+1)*2);
	
	int w1=0;
	for(int h0=1; h0<=maxH0; h0+=1){
		for(int w0=32; w0<=maxW0; w0+=32){
			printf("h0=%d w0=%d w1=%d %x\n",h0,w0,w1,crc);
			for(int w1=1; w1<=maxW1; w1+=1){
				nmppmMul_mm_2s64s(src0,h0,w0,src1, dst, w1);				
				nmppsCrcAcc_64s (dst, w1*(h0+1),&crc);
			}
		}
	}

	nmppsFree(src0);
	nmppsFree(src1);
	nmppsFree(dst);
	

	return crc>>2;
}
