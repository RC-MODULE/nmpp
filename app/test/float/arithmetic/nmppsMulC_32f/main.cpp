#include <nmtype.h>
#include <malloc32.h>
#include <nmpp.h>

#define PI 3.1415
int main()
{
	float* src0 = (float *) nmppsMalloc_32f(1024);
	float* dst  = (float *) nmppsMalloc_32f(1024 + 11);
	unsigned crc=0;
	for(int i = 0; i < 1024; i++) {
		src0[i] = i*PI;
	}

	for(int i = 0; i < 1024 + 11; i++) {
		dst[i] = 77777;
	}

	for(int size=2; size<1024; size+=2){
		nmppsMulC_32f(src0, dst, 2.0, size);
		nmppsCrcAcc_32f(dst,0,size + 11,&crc);
	}
	free(src0);
	free(dst);
	return crc>>2;
}

