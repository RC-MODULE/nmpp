#include <nmtype.h>
#include <malloc32.h>
#include <nmpp.h>


#define PI 3.1415
int main()
{
	float* src0 = (float *) nmppsMalloc_32f(64);
	float* src1 = (float *) nmppsMalloc_32f(64);
	unsigned crc=0;
	for(int i = 0; i < 64; i++) {
		src0[i] = i*PI;
		src1[i] = i*PI+0.1;
	}
	float norm;
	for(int size=0; size<64; size+=2){
		nmppsNormDiff_Inf_32f(src0,src1,size,&norm);
		nmppsCrcAcc_32f(&norm,0,1,&crc);
	}
	free(src0);
	free(src1);
	return crc>>2;
}