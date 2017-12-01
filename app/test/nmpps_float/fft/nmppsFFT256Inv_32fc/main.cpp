#include "math.h"
#include "time.h"
#include "fft_32fc.h"
#include "malloc.h"
#include <stdio.h>
#include "nmpp.h"

#pragma data_section ".data_imu1"
	nm32fcr out[256];
#pragma data_section ".data_imu5"
	nm32fcr outInv[256];

int main()
{
	int i, tm, time;
	float norm;
	clock_t t1, t2;
	nm32fcr *in; //, *out, *outInv;
	NmppsFFTSpec_32fc *spec, *ispec;
	tm = nmppsFFT256FwdInitAlloc_32fc(&spec);
	if(tm) {
		return 777;
	}
	tm = nmppsFFT256InvInitAlloc_32fc(&ispec);
	if(tm) {
		return 111;
	}
	in = (nm32fcr *) malloc (256 * sizeof(nm32fcr));
	//out = (nm32fcr *) malloc (256 * sizeof(nm32fcr));
	//outInv = (nm32fcr *) malloc (256 * sizeof(nm32fcr));
	for(i = 0; i < 256; i++) {
		in[i].re = i + 1;
		in[i].im = i + 1;
		outInv[i].re = 0;
		outInv[i].im = 0;
		out[i].re = 0;
		out[i].im = 0;
	}
	nmppsFFT256Fwd_32fc(in, out, spec);
	t1 = clock();
	nmppsFFT256Inv_32fc(out, outInv, ispec);
	t2 = clock();
	time = t2 - t1;
	nmppsNormDiff_L2_32fc(in, outInv, 256, &norm);
	tm = nmppsFFTFree_32fc(spec);
	tm = nmppsFFTFree_32fc(ispec);
	unsigned int crc = 0;
	nmppsCrcAcc_32f((nm32f *)outInv, 14, 256*2, &crc);
	printf("%.7f\n", norm);
	//printf("\n");
	//printf("%d\n", time);
	for(i = 0; i < 256; i++)
		//printf("%.5f %.5f\n", outInv[i].re, outInv[i].im);
	return crc>>2;
}