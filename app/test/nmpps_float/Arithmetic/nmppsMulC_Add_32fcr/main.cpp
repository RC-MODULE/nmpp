#include "nmpp.h"

#define MAX_SIZE 2000
int main(){
	nm32fcr* src1 = (nm32fcr*)nmppsMalloc_32s(2*MAX_SIZE+2);
	nm32fcr* src2 = (nm32fcr*)nmppsMalloc_32s(2*MAX_SIZE+2);
	nm32fcr* dst  = (nm32fcr*)nmppsMalloc_32s(2*MAX_SIZE+2);
	unsigned int crc = 0;
	
	/*nmppsRand_32f((nm32f*) src1, 2*MAX_SIZE,0,10000);
	nmppsRand_32f((nm32f*) src2, 2*MAX_SIZE,0,10000);*/
	for (int i = 0; i < MAX_SIZE+1; i++) {
		src1[i].im = i;
		src1[i].re = MAX_SIZE - i;
		src2[i].im = MAX_SIZE - i;
		src2[i].re = i;
		dst[i].re = 13;
		dst[i].im = 13;
	}
	nmppsCrcAcc_32f((nm32f*)src1, 0, 2 * MAX_SIZE+2, &crc);
	nmppsCrcAcc_32f((nm32f*)src2, 0, 2 * MAX_SIZE+2, &crc);
	//nmppsSet_32s((nm32s*)dst,0xCDCDCDCD,MAX_SIZE);

	
	for (int size = 1; size < 33; size++) {
		nmppsMulC_Add_32fcr(src1, src2, dst, 15, size);
		nmppsCrcAcc_32f((nm32f*)dst, 0, 2 * size + 2, &crc);
	}
	return crc;
}