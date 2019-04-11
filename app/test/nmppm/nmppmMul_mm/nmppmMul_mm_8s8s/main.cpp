#include "nmpp.h"
#include "minrep.h"
#include "stdio.h"


int main()
{
	
	int maxW0=128;
	int maxH0=128;
	int maxW1=128;

	nm8s* src0=nmppsMalloc_8s(maxW0*maxH0);
	nm8s* src1=nmppsMalloc_8s(maxW1*maxW0);
	nm8s* dst =nmppsMalloc_8s(maxW1*(maxH0+1));
	if ((src0==0)||(src1==0)||(dst==0)) return -1;


	unsigned int crc = 0;
	
	nmppsRandUniform_32u((nm32u*)src0,maxW0*maxH0/4);
	nmppsRandUniform_32u((nm32u*)src1,maxW1*maxW0/4);
	nmppsSet_32s((nm32s*)dst,(int)0xCCCCCCCC,maxW1*(maxH0+1)/4);
	
	int w1=0;
	for(int h0=1; h0<=maxH0; h0+=1){
		for(int w0=8; w0<=maxW0; w0+=8){
				printf("h0=%d w0=%d w1=%d %x\n",h0,w0,w1,crc);
			for(int w1=8; w1<=maxW1; w1+=8){
				
				nmppmMul_mm_8s8s  (src0,h0,w0,src1, dst, w1);				
				nmppsCrcAcc_8s (dst, w1*(h0+1),&crc);

			}
		}
	}
	//! \fn void nmppmMul_mm_8s8s(nm8s*,int,int,nm8s*,nm8s*,int)

	nmppsFree(src0);
	nmppsFree(src1);
	nmppsFree(dst);
	

	return crc>>2;
}
