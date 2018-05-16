#include "nmpp.h"
#include "time.h"

#define MAX_SIZE 2000
int main(){
	nm64f* src1 = (nm64f*)nmppsMalloc_64f(MAX_SIZE+1);
	nm64f* src2 = (nm64f*)nmppsMalloc_64f(MAX_SIZE+1);
	nm64f* src3 = (nm64f*)nmppsMalloc_64f(MAX_SIZE+1);
	nm64f* dst  = (nm64f*)nmppsMalloc_64f(MAX_SIZE+1);
	unsigned int crc = 0;
	
	/* nmppsRandUniform_64f( src1, MAX_SIZE,0,10000);
	nmppsRandUniform_64f( src2, MAX_SIZE,0,10000);
	nmppsRandUniform_64f( src3, MAX_SIZE,0,10000); */
	for(int i =0;i<MAX_SIZE+1;i++){
		src1[i] = i;
		src2[i] = 2*i;
		src3[i] = 3*i;
		dst[i] = 0xCDCDCDCDCDCDCDCD;
	}
	nmppsCrcAcc_64f((nm64f*)src1, 0, MAX_SIZE, &crc);
	nmppsCrcAcc_64f((nm64f*)src2, 0, MAX_SIZE, &crc);
	nmppsCrcAcc_64f((nm64f*)src3, 0, MAX_SIZE, &crc);
	//nmppsSet_32s((nm32s*)dst,0xCDCDCDCD,MAX_SIZE);

	clock_t t1,t0;
	for (int size = 1; size < MAX_SIZE; size++) {
		t0 = clock();
		nmppsMul_Add_64f(src1, src2, src3, dst, size);
		t1 = clock();
		nmppsCrcAcc_64f((nm64f*)dst, 0, size+1 , &crc);
	}
	return t1-t0;
}