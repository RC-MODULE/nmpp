#include "math.h"
#include "fft_32fc.h"
#include "malloc.h"
//#include <stdio.h>
#include "nmpp.h"

union abc {
	float FL;
	int IN;
};

int main()
{
	int i, tm;
	union abc ab;
	nm32fcr *in, *out, *outInv;
	NmppsFFTSpec_32fc *spec, *ispec;
	tm = nmppsFFT16FwdInitAlloc_32fc(&spec);
	if(tm) {
		return 777;
	}
	tm = nmppsFFT16InvInitAlloc_32fc(&ispec);
	if(tm) {
		return 111;
	}
	in = (nm32fcr *) malloc (16 * sizeof(nm32fcr));
	out = (nm32fcr *) malloc (16 * sizeof(nm32fcr));
	outInv = (nm32fcr *) malloc (16 * sizeof(nm32fcr));
	for(i = 0; i < 16; i++) {
		in[i].re = i;
		in[i].im = 0;
		outInv[i].re = 0;
		outInv[i].im = 0;
		out[i].re = 0;
		out[i].im = 0;
	}
	float SKO_dft16;
	SKO_dft16 = 0;
	nmppsFFT16Fwd_32fc(in, out, spec);
	nmppsFFT16Inv_32fc(out, outInv, ispec);
	tm = nmppsFFTFree_32fc(spec);
	tm = nmppsFFTFree_32fc(ispec);
	unsigned int crc = 0;
	nmppsCrcAcc_32f((nm32f *)outInv, 9, 16*2, &crc);
	//for(i = 0; i < 16; i++)
	//	printf("%.5f %.5f\n", outInv[i].re, outInv[i].im);
	for(i = 0; i < 16; i++) {
        SKO_dft16 += (in[i].re - outInv[i].re) * (in[i].re - outInv[i].re);
        SKO_dft16 += (in[i].im - outInv[i].im) * (in[i].im - outInv[i].im);
    }
    SKO_dft16 = SKO_dft16 / 32.0;
    SKO_dft16 = sqrtf(SKO_dft16);
    ab.FL = SKO_dft16;
    //printf("0x%08x\n", ab.IN);
	return crc>>2;
}
