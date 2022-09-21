#include "nmpp.h"
#include "minrep.h"
#include <stdio.h>


int main()
{
	int maxW0=70;
	int maxH0=70;
	int maxW1=70;

	float* src0=nmppsMalloc_32f( maxW0*maxH0 );
	float* src1=nmppsMalloc_32f( maxW1*maxW0 );
	float* dst =nmppsMalloc_32f( maxW1*(maxH0+1) );
	
	if ((src0==0)||(src1==0)||(dst==0)) return -1;

	unsigned int crc = 0;
	
	nmppsRandUniform_32f_integer( src0, maxW0* maxH0,    9, 0);
	nmppsRandUniform_32f_integer( src1, maxW1* maxW0,    9, 0);
	nmppsRandUniform_32f_integer( dst,  maxW1*(maxH0+1), 9, 0);
	
	int w1=0;
	for(int h0=1; h0<=maxH0; h0+=1){
		for(int w0=2; w0<=maxW0; w0+=2){
			//printf("h0=%d w0=%d w1=%d %x\n",h0,w0,w1,crc);
			printf("h0=%d w0=%d w1=%d %x\n",h0,w0,w1,crc);
			for(int w1=2; w1<=maxW1; w1+=2){
                nmppmMul_mm_32f  (  src0,  h0,  w0,
                                    src1,  w0,  w1,
                                    dst,   w1,  w1,  true );
				nmppsCrcAcc_32f (dst, 1, w1*h0,&crc);
			}
		}
	}
	//! \fn void nmppmMul_mm_32f( float*, int, int, float*,  int,  int, float*, int,  int,  bool )

	nmppsFree(src0);
	nmppsFree(src1);
	nmppsFree(dst);
	

	return crc>>2;
}
