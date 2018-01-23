#include "nmtype.h"
#include "time.h"
#include <stdio.h>
#include "nmpp.h"

#define		N_ST	256
#define		MASK	1

#pragma data_section ".data_imu1"
	nm32sc in[N_ST];
	//nm32fcr out[N_ST];
#pragma data_section ".data_imu2"
	nm32fcr out[N_ST];

// extern "C" {
// 	void nmppsConvert_32sc32fcr(nm32sc *x, nm32fcr *X, int N);
// }

int main()
{
	int tm;
	unsigned int crc1 = 0;
	unsigned int crc2 = 0;
	unsigned int crc3 = 0;
	unsigned int crc4 = 0;

	//clock_t t1, t2;
	for(int i = 0; i < N_ST; i++) {
		in[i].re = i;
		in[i].im = i + 1;
		out[i].re = 0;
		out[i].im = 0;
	}
//////////////reminder = 0//////////////
	//t1 = clock();
	nmppsConvert_32sc32fcr(in, out, N_ST);
	//t2 = clock();
	//tm = t2 - t1;
	nmppsCrcAcc_32f((nm32f *)out, MASK, N_ST*2, &crc1);

//////////////reminder/////////////////
	nmppsConvert_32sc32fcr(in, out, N_ST - 11);
	nmppsCrcAcc_32f((nm32f *)out, MASK, (N_ST - 11)*2, &crc2);

//////////////reminder = 0, vlen = 32/////////////////
	nmppsConvert_32sc32fcr(in, out, 32);
	nmppsCrcAcc_32f((nm32f *)out, MASK, 32*2, &crc3);

//////////////reminder = 0, vlen = 17 < 32/////////////////
	nmppsConvert_32sc32fcr(in, out, 17);
	nmppsCrcAcc_32f((nm32f *)out, MASK, 17*2, &crc4);
	for(int i = 0; i < 17; i++) {
		printf("%.3f  %.3f\n", out[i].re, out[i].im);
		//printf("%d  %d\n", in[i].re, in[i].im);
	}

	printf("%d\n crc1 = ", crc1 >> 2);
	printf("%d\n crc2 = ", crc2 >> 2);
	printf("%d\n crc3 = ", crc3 >> 2);
	printf("%d\n crc4 = ", crc4 >> 2);
	printf("\n");
	return tm;
}