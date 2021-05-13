#include "stdio.h"
#include "nmpp.h"


#define MAX_SIZE 1000

int main(){
	nm32f* src = (nm32f*)nmppsMalloc_32f(MAX_SIZE);
	nm32f* dst = (nm32f*)nmppsMalloc_32f(MAX_SIZE);
	if (src==0 || dst ==0) 
		return -1;
	unsigned int crc = 0;
	
	for(int i = 0; i < MAX_SIZE; i++){
		src[i] = i;
		dst[i] = 777;
	}
	nmppsCrcAcc_32f((nm32f*)src, 0, MAX_SIZE, &crc);
	//nmppsSet_32s((nm32s*)dst,0xCDCDCDCD,MAX_SIZE);

	for (int size = 1; size < MAX_SIZE-2; size++) {
		nmppsCopyEvenToOdd_32f(src, dst + 1, size);
		nmppsCrcAcc_32f((nm32f*)dst, 0, size + 2 , &crc);
	}
	
	//nmppsCopy_32f_even_odd_address(src, dst + 1, 1987);
	//nmppsCopy_32f_even_odd_address(src, dst + 1, 1998);
	//nmppsCopy_32f_even_odd_address(src, dst + 1, 1999);
	//nmppsCopy_32f_even_odd_address(src, dst + 1, 2000);
	//for(int i = 0; i < MAX_SIZE + 2; i++)
    //   printf("dst %f\n", dst[i]);
	return crc >> 2;
}