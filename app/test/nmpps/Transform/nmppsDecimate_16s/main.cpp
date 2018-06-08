#include "nmpp.h"
#include "time.h"

#define MAX_SIZE 1024
#define STEP 8
extern "C" void nmppsDecimate_16s(nm16s* pSrc, int startPos, int step, nm16s* pDst, int nSize);

int main (){
	nm32s* src = nmppsMalloc_32s(MAX_SIZE*STEP +2);
	nm32s* dst = nmppsMalloc_32s(MAX_SIZE+2);
	nmppsSet_32s(dst,0xCDCDCDCD,MAX_SIZE+2);
	
	nmppsRandUniform_32s(src,MAX_SIZE*STEP);

	clock_t t1,t0;
	unsigned crc = 0;
	nmppsCrcAcc_32s(src,MAX_SIZE*STEP,&crc);
	for (int startPos=0;startPos<4;startPos++){
		for (int size =0;size<=MAX_SIZE;size+=4){
			t0 = clock();
			nmppsDecimate_16s((nm16s*)src, startPos, STEP, (nm16s*)dst, size);
			t1 = clock();
			nmppsCrcAcc_32s(dst,size+2,&crc);
		}	
	}
	
	return crc>>2;
	//return t1-t0;
	
}