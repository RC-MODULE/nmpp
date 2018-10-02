#include "nmtype.h"
#include "time.h"
#include <stdio.h>

#define		N				1024

#ifdef __GNUC__
/**************************NMC-GCC************************/
__attribute__((section(".data_imu1"))) 	nm32f in[N];
__attribute__((section(".data_imu2"))) 	nm32f out[N + 10];
#else
/***************************NMCC*************************/
#pragma data_section ".data_imu1"
	nm32f in[N];
#pragma data_section ".data_imu2"
	nm32f out[N + 10];
#endif

int main()
{
	int tm;
	clock_t t1, t2;
	for(int i = 0; i < N; i++) {
		in[i] = i;
	}
	for(int i = 0; i < N + 10; i++) {
		out[i] = 1;
	}
	t1 = clock();
	nmppsMulC_32f(in, out, 2.0, N);
	t2 = clock();
	for(int i = 0; i < N + 10; i++) {
		printf("Res[%d] = %f\n", i, out[i]);
	}
	return t2 - t1;
}
