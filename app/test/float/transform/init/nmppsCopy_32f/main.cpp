#include "nmpp.h"
#include "stdio.h"

#define MAX_SIZE 1000

void FullArray_32f(nm32f* array, int size)
{
	for(int i = 0;i < size; i++){
		array[i] = 0xCDCDCD;
	}
}

void TestCopy_32f(nm32f* src, nm32f* dst, int max_size, unsigned int* crc)
{
	for (int size = 2; size < MAX_SIZE; size++) {
		nmppsCopy_32f(src, dst, size);
		nmppsCrcAcc_32f((nm32f*)dst, 0, size + 2, crc);
	}
}

int main(){
	nm32f* src = (nm32f*)nmppsMalloc_32f(MAX_SIZE + 2);
	nm32f* dst  = (nm32f*)nmppsMalloc_32f(MAX_SIZE + 2);
	
	printf("parity src address: %d\n", (int)src & 1);
	printf("parity src address: %d\n", (int)dst & 1);
	
	/* nmppsRandUniform_32f( src1, MAX_SIZE,0,10000);
	nmppsRandUniform_32f( src2, MAX_SIZE,0,10000);
	nmppsRandUniform_32f( src3, MAX_SIZE,0,10000); */
	for(int i = 0;i < MAX_SIZE + 2; i++){
		src[i] = i;
	}
	
	FullArray_32f(dst, MAX_SIZE + 2);

	unsigned int crc = 0;
	nmppsCrcAcc_32f((nm32f*)src, 0, MAX_SIZE, &crc);
	//nmppsSet_32s(0xCDCDCDCD,(nm32s*)dst,MAX_SIZE);

	printf("origin crc = %d\n", crc >> 2);
// Test copy from even address to even address
    TestCopy_32f(src, dst, MAX_SIZE, &crc);
    printf("even to even crc = %d\n", crc >> 2);
    FullArray_32f(dst, MAX_SIZE + 2);

// Test copy from odd address to odd address
    TestCopy_32f(src + 1, dst + 1, MAX_SIZE, &crc);
    printf("odd to odd crc = %d\n", crc >> 2);
	FullArray_32f(dst, MAX_SIZE + 2);

// Test copy from even address to odd address
    TestCopy_32f(src, dst + 1, MAX_SIZE, &crc);
    printf("even to odd crc = %d\n", crc >> 2);
    FullArray_32f(dst, MAX_SIZE + 2);

// Test copy from odd address to even address
    TestCopy_32f(src + 1, dst, MAX_SIZE, &crc);
    printf("odd to even crc = %d\n", crc >> 2);
    FullArray_32f(dst, MAX_SIZE + 2);

	return crc >> 2;
}