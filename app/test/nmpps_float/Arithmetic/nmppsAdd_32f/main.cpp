#include <nmtype.h>
#include <malloc32.h>
#include <nmpp.h>

#define PI 3.1415
int main()
{
	float* src0 = (float *) nmppsMalloc_32f(64);
	float* src1 = (float *) nmppsMalloc_32f(64);
	float* dst  = (float *) nmppsMalloc_32f(64);
	unsigned crc=0;
	for(int i = 0; i < 64; i++) {
		src0[i] = i*PI;
		src1[i] = i+PI;
	}
	
	for(int size=2; size<64; size+=2){
		nmppsAdd_32f(src0,src1,dst,size);
		nmppsCrcAcc_32f(dst,0,size,&crc);
	}
	free(src0);
	free(src1);
	free(dst);
	return crc>>2;
}