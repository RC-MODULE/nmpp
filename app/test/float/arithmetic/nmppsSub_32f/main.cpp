#include <nmtype.h>
#include <malloc32.h>
#include <time.h>
#include <nmpp.h>

#define PI 3.1415
int main()
{
	float* src0 = (float *) nmppsMalloc_32f(1024);
	float* src1 = (float *) nmppsMalloc_32f(1024);
	float* dst  = (float *) nmppsMalloc_32f(1024 + 11);
	unsigned crc=0;
	for(int i = 0; i < 1024; i++) {
		src0[i] = i*PI;
		src1[i] = i+PI;
	}

	for(int i = 0; i < 1024 + 11; i++) {
		dst[i] = 77777;
	}


	for(int size=2; size<1024; size+=2){
		nmppsSub_32f(src0,src1,dst,size);
		nmppsCrcAcc_32f(dst,0,size + 11,&crc);
	}
	free(src0);
	free(src1);
	free(dst);
	return crc>>2;
}

// #include "nmtype.h"
// #include "time.h"
// #include "nmpp.h"
// #include <stdio.h>
//
// #define		N				1024
//
// #ifdef __GNUC__
// /**************************NMC-GCC************************/
// __attribute__((section(".data_imu1"))) 	nm32f in[N];
// __attribute__((section(".data_imu2"))) 	nm32f out[N + 10];
// #else
// /***************************NMCC*************************/
// #pragma data_section ".data_imu1"
// 	nm32f in1[N];
// #pragma data_section ".data_imu2"
// 	nm32f in2[N];
// #pragma data_section ".data_imu3"
// 	nm32f out[N + 10];
// #endif
//
// int main()
// {
// 	int tm;
// 	clock_t t1, t2;
// 	for(int i = 0; i < N; i++) {
// 		in1[i] = i;
// 		in2[i] = i;
// 	}
// 	for(int i = 0; i < N + 10; i++) {
// 		out[i] = 1;
// 	}
// 	t1 = clock();
// 	nmppsAdd_32f(in1, in2, out,  N);
// 	t2 = clock();
// 	for(int i = 0; i < N + 10; i++) {
// 	//	printf("Res[%d] = %f\n", i, out[i]);
// 	}
// 	return t2 - t1;
// }
