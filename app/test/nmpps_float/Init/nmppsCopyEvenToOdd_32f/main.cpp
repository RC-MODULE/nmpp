#include "stdio.h"
#include "nmpp.h"


#define MAX_SIZE 10000

#pragma data_section ".data_imu0"
	nm32f src[MAX_SIZE + 2];
#pragma data_section ".data_imu1"
	nm32f dst[MAX_SIZE + 2]; 

int main(){
	//nm32f* src = (nm32f*)malloc(MAX_SIZE + 2);
	//nm32f* dst  = (nm32f*)malloc(MAX_SIZE + 2);
	unsigned int crc = 0;
	
	/* nmppsRandUniform_32f( src1, MAX_SIZE,0,10000);
	nmppsRandUniform_32f( src2, MAX_SIZE,0,10000);
	nmppsRandUniform_32f( src3, MAX_SIZE,0,10000); */
	for(int i = 0; i < MAX_SIZE + 2; i++){
		src[i] = i;
		dst[i] = 777;
	}
	nmppsCrcAcc_32f((nm32f*)src, 0, MAX_SIZE, &crc);
	//nmppsSet_32s((nm32s*)dst,0xCDCDCDCD,MAX_SIZE);

	for (int size = 1; size < MAX_SIZE; size++) {
		//if(size == 1985) continue;
		nmppsCopyEvenToOdd_32f(src, dst + 1, MAX_SIZE);
		nmppsCrcAcc_32f((nm32f*)dst, 0, size + 2 , &crc);
		//if(dst[3002] == 3001.0f) {
		//	printf("s = %d\n", size);
		//}
	}
	
	//nmppsCopy_32f_even_odd_address(src, dst + 1, 1987);
	//nmppsCopy_32f_even_odd_address(src, dst + 1, 1998);
	//nmppsCopy_32f_even_odd_address(src, dst + 1, 1999);
	//nmppsCopy_32f_even_odd_address(src, dst + 1, 2000);
	//for(int i = 0; i < MAX_SIZE + 2; i++)
    //   printf("dst %f\n", dst[i]);
	return crc >> 2;
}