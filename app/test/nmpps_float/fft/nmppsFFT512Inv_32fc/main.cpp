#include "math.h"
#include "fft_32fc.h"
#include "time.h"
#include "malloc.h"
#include <stdio.h>
#include "nmpp.h"

#pragma data_section ".data_imu2"
	nm32fcr out[32*16];
#pragma data_section ".data_imu1"
	nm32fcr outInv[32*16];

int main()
{
	int i, tm, time;
	nm32fcr *in;
	clock_t t1, t2;
	float norm;
	NmppsFFTSpec_32fc *spec, *ispec;
	tm = nmppsFFT512FwdInitAlloc_32fc(&spec);
	if(tm) {
		return 777;
	}
	tm = nmppsFFT512InvInitAlloc_32fc(&ispec);
	if(tm) {
		return 111;
	}

	in = (nm32fcr *) malloc (512 * sizeof(nm32fcr));

	for(i = 0; i < 512; i++) {
		in[i].re = i + 1;
		in[i].im = i + 1;
		outInv[i].re = 0;
		outInv[i].im = 0;
		out[i].re = 0;
		out[i].im = 0;
	}
	nmppsFFT512Fwd_32fc(in, out, spec);
	t1 = clock();
	nmppsFFT512Inv_32fc(out, outInv, ispec);
	t2 = clock();
	time = t2 - t1;
	nmppsNormDiff_L2_32fc(in, outInv, 512, &norm);
	tm = nmppsFFTFree_32fc(spec);
		
	//tm = nmppsFFTFree_32fc(ispec);
	unsigned int crc = 0;
	nmppsCrcAcc_32f((nm32f *)outInv, 25, 512*2, &crc);
	printf("%.7f", norm);
	printf("\n");
	printf("%d", time );
	printf("\n");
	//for(i = 0; i < 512; i++)
		//printf("%.5f %.5f\n", outInv[i].re, outInv[i].im);
	return crc>>2;
}
