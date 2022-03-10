#include <nmtype.h>
#include <nmpp.h>
#include <math.h>
#include <stdio.h>

#define    SIZE                         1024


#ifdef __GNUC__
__attribute__((section(".data_imu1"))) 	nm32f src[SIZE];
__attribute__((section(".data_imu2"))) 	nm32f dst[SIZE + 10];
__attribute__((section(".data_imu2"))) 	nm32f dst_ethalon[SIZE + 10];
__attribute__((section(".data_imu3"))) 	nm32f tmp[SIZE];
#else
nm32f src[SIZE];
nm32f dst[SIZE + 10];
nm32f dst_ethalon[SIZE + 10];
nm32f tmp[SIZE];
#endif

void SqrtEthalon(const nm32f* src, nm32f* dst, int size) {
	for(int i = 0; i < size; i++) {
		dst[i] = sqrtf(src[i]);
	}
}

int main()
{
	
	for(int i = 0; i < SIZE; i++) {
		src[i] = i;
	}

	for(int i = 0; i < SIZE + 10; i++) {
		dst[i] = 777;
		dst_ethalon[i] = 777;
	}

	nmppsSqrt_32f(src, dst, tmp, SIZE);
	SqrtEthalon(src, dst_ethalon, SIZE);

	float norm;
	nmppsNormDiff_L2_32f(dst_ethalon, dst, SIZE + 10, &norm);
	printf("norm = %f\n", norm);
	return 0;
}