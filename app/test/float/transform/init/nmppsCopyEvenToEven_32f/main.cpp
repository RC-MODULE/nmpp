#include "nmpp.h"

#define MAX_SIZE 1000
int main(){
	nm32f* src = (nm32f*)nmppsMalloc_32f(MAX_SIZE + 1);
	nm32f* dst  = (nm32f*)nmppsMalloc_32f(MAX_SIZE + 1);
	if (src==0 || dst ==0) 
		return -1;
	/* nmppsRandUniform_32f( src1, MAX_SIZE,0,10000);
	nmppsRandUniform_32f( src2, MAX_SIZE,0,10000);
	nmppsRandUniform_32f( src3, MAX_SIZE,0,10000); */
	unsigned int crc = 0;
	for(int i = 0;i < MAX_SIZE + 1; i++){
		src[i] = i;
		dst[i] = 0xCDCDCD;
	}
	nmppsCrcAcc_32f((nm32f*)src, 0, MAX_SIZE, &crc);
	//nmppsSet_32s(0xCDCDCDCD,(nm32s*)dst,MAX_SIZE);

	//nmppsCopyEvenToEven_32f(src, dst, 1);
	
	if (1) 
	for (int size = 1; size < MAX_SIZE; size++) {
	//for (int size = 1; size < 10; size++) {
		nmppsCopyEvenToEven_32f(src, dst, size);
		nmppsCrcAcc_32f((nm32f*)dst, 0, size + 1 , &crc);
	}
	return crc >> 2;
}