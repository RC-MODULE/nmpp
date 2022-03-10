#include <stdio.h>
#include <time.h>
#include "nmpp.h"
#include <malloc32.h>

#define		N			256

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

	nm64f* in1 = (nm64f *) nmppsMalloc_64f(N * sizeof(nm64f));
	nm64f* in2 = (nm64f *) nmppsMalloc_64f(N * sizeof(nm64f));
	nm64f* in3  = (nm64f *) nmppsMalloc_64f(N * sizeof(nm64f));
	nm64f* in4  = (nm64f *) nmppsMalloc_64f(N * sizeof(nm64f));
	nm64f* out  = (nm64f *) nmppsMalloc_64f((N + 10) * sizeof(nm64f));

	for(i = 0; i < N; i++) {
	 	in1[i] = 2;
	 	in2[i] = 2;
	 	in3[i] = 2;
	 	in4[i] = 2;
               
	 	in1[i] = 1;
	 	in2[i] = 1;
	 	in3[i] = 1;
	 	in4[i] = 1;
	}

	for(i = 0; i < N + 10; i++) {
	 	out[i] = 0;
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

	for(i = 0; i < N; i++) {
		nmppsMul_Mul_Add_64f(in1, in2, in3, in4, out, i + 1);
		nmppsCrcAcc_64f(out, 1, (i + 11), &crc);
	}

	free(in1);
	free(in2);
	free(in3);
	free(in4);
	free(out);
	return crc >> 2;
}
