#include <stdio.h>
#include <time.h>
#include "nmpp.h"
#include <malloc32.h>

#define		N			1024

// #pragma data_section ".data_imu1"
// 	nm32fcr in1[N];
// #pragma data_section ".data_imu2"
// 	nm32fcr in2[N];
// #pragma data_section ".data_imu3"
// 	nm32fcr in3[N];
// #pragma data_section ".data_imu4"
// 	nm32fcr in4[N];
// #pragma data_section ".data_imu5"
// 	nm32fcr out[N + 10];

int main()
{
	int i;

	nm32f* in2  = (nm32f*) nmppsMalloc_32f(N * sizeof(nm32f));
	nm32f* in3  = (nm32f*) nmppsMalloc_32f(N * sizeof(nm32f));
	nm32f* in4  = (nm32f*) nmppsMalloc_32f(N * sizeof(nm32f));
	nm32f* in1  = (nm32f*) nmppsMalloc_32f(N * sizeof(nm32f));
	nm32f* out  = (nm32f*) nmppsMalloc_32f((N + 11) * sizeof(nm32f));

	for(i = 0; i < N; i++) {
	 	in1[i] = 2;
	 	in2[i] = 2;
	 	in3[i] = 2;
	 	in4[i] = 2;
	}

	for(i = 0; i < N + 11; i++) {
	 	out[i] = 0;
	}

	//clock_t t1, t2;
	// t1 = clock();
	// nmppsMul_Mul_Add_32fcr(in1, in2, in3, in4, out, N);
	// t2 = clock();
	// int tm = t2 - t1;
	// for(i = 0; i < N + 10; i++) {
	// 	printf("[%d] %f    %f \n", i, out[i].re, out[i].im);
	// }

	unsigned crc = 0;

	for(i = 2; i < N; i += 2) {
		nmppsMul_Mul_Sub_32f(in1, in2, in3, in4, out, i);
		nmppsCrcAcc_32f(out, 1, i + 11, &crc);
	}

	free(in1);
	free(in2);
	free(in3);
	free(in4);
	free(out);
	return crc >> 2;
}
