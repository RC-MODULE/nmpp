#include <math.h>
#include "nmpp.h"
#include "time.h"
#include <stdio.h>

#define		N_ST	400 // число байт

#pragma data_section ".data_imu1"
	nm32u in[N_ST/4];
#pragma data_section ".data_imu2"
	nm32u out[N_ST];

extern "C" {
	void nmppsConvertRisc_8u32u(nm32u *x, nm32u *X, int size);
}

int main()
{
	int tm;
	clock_t t1, t2;
	unsigned int crc = 0;
	in[0] = 66051;
	for(int i = 1; i < N_ST/4; i++) {
	 	in[i] = in[i - 1] + 16843009;
	}
	t1 = clock();
	nmppsConvertRisc_8u32u(in, out, N_ST);
	t2 = clock();
	tm = t2 - t1;
	// int count = 0;
	// for(int i = 0; i < N_ST; i++) {
	// 	printf("%d\n", out[i]);
	// 	count++;
	// 	if(count == 4) {
	// 		printf("\n");
	// 		count = 0;
	// 	}
	// }

	nmppsCrcAcc_32u(out, N_ST, &crc);
	printf("%d\n", tm);
	// printf("%d\n", crc2>>2);
	return crc>>2;
}