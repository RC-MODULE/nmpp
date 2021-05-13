#include "nmpp.h"

#define MAX_SIZE 1000
int main(){
	nm32f* src = (nm32f*)nmppsMalloc_32f(MAX_SIZE);
	nm32f* dst = (nm32f*)nmppsMalloc_32f(MAX_SIZE);
	if (src==0 || dst ==0) 
		return -1;

	unsigned int crc = 0;
	
	for(int i = 0;i < MAX_SIZE ; i++){
		src[i] = i;
		dst[i] = 0xCDCDCD;
	}
	nmppsCrcAcc_32f((nm32f*)src, 0, MAX_SIZE, &crc);
	
	for (int size = 1; size < MAX_SIZE-2; size++) {
		nmppsCopyOddToOdd_32f(src + 1, dst + 1, size);
		nmppsCrcAcc_32f((nm32f*)dst, 0, size + 2 , &crc);
	}
	return crc >> 2;
}