#include "math.h"
#include "fft_32fc.h"
#include "malloc.h"
//#include <stdio.h>
#include "nmpp.h"

int main()
{
	int i, tm;
	nm32fcr *in, *out, *outInv;
	NmppsFFTSpec_32fc *spec, *ispec;
	tm = nmppsFFT64FwdInitAlloc_32fc(&spec);
	if(tm) {
		return 777;
	}
	tm = nmppsFFT64InvInitAlloc_32fc(&ispec);
	if(tm) {
		return 111;
	}
	in = (nm32fcr *) malloc (64 * sizeof(nm32fcr));
	out = (nm32fcr *) malloc (64 * sizeof(nm32fcr));
	outInv = (nm32fcr *) malloc (64 * sizeof(nm32fcr));
	for(i = 0; i < 64; i++) {
		in[i].re = i;
		in[i].im = 1;
		outInv[i].re = 0;
		outInv[i].im = 0;
		out[i].re = 0;
		out[i].im = 0;
	}
	nmppsFFT64Fwd_32fc(in, out, spec);
	nmppsFFT64Inv_32fc(out, outInv, ispec);
	tm = nmppsFFTFree_32fc(spec);
	tm = nmppsFFTFree_32fc(ispec);
	unsigned int crc = 0;
	nmppsCrcAcc_32f((nm32f *)outInv, 23, 64*2, &crc);
	//for(i = 0; i < 64; i++)
	//	printf("%.5f %.5f\n", outInv[i].re, outInv[i].im);
	return crc>>2;
}
