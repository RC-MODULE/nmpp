#include <nmtype.h>
#include <malloc32.h>
#include <stdio.h>
#include <nmpp.h>

int main()
{
	float* src0 = (float *) nmppsMalloc_32f(1024);
	float* dst  = (float *) nmppsMalloc_32f(1024 + 11);
	unsigned crc=0;
	clock_t t0,t1;
	for(int i = 0; i < 1024; i++) {
		src0[i] = i;
	}

	for(int i = 0; i < 1024 + 11; i++) {
		dst[i] = 77777;
	}


	for(int size=2; size<=1024; size+=2){
		t0 = clock();
		nmppsMulC_AddC_32f(src0,5,10,dst,size);
		t1 = clock();
		nmppsCrcAcc_32f(dst,0,size + 11,&crc);
	}

	free(src0);
	free(dst);
	return t1-t0;
}

