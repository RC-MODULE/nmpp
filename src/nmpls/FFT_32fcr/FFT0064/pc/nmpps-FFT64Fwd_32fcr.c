#include "fft_32fcr.h"
#include <malloc.h>

void nmppsFFT64Fwd_32fcr(const nm32fcr *x, nm32fcr *X, NmppsFFTSpec_32fcr *spec)
{
    int i;
    nm32fcr *buff64 = (nm32fcr *)malloc(32 * sizeof(nm32fcr));
    nm32fcr *buff64xW = (nm32fcr *)malloc(32 * sizeof(nm32fcr));
    for(i = 0; i < 32; i++) {
        buff64[i].im = x[2 * i].im;
        buff64[i].re = x[2 * i].re;
        buff64xW[i].im = x[2 * i + 1].im;
        buff64xW[i].re = x[2 * i + 1].re;
    }
    nmppsFFT32Fwd_32fcr(buff64, buff64, spec);
    nmppsFFT32Fwd_32fcr(buff64xW, buff64xW, spec);
    for(i = 0; i < 32; i++) {
        X[i].im = buff64[i].im + (spec->Buffers[3][i].re * buff64xW[i].im + spec->Buffers[3][i].im * buff64xW[i].re);
        X[i].re = buff64[i].re + (spec->Buffers[3][i].re * buff64xW[i].re - spec->Buffers[3][i].im * buff64xW[i].im);
        X[i + 32].im = buff64[i].im - (spec->Buffers[3][i].re * buff64xW[i].im + spec->Buffers[3][i].im * buff64xW[i].re);
        X[i + 32].re = buff64[i].re - (spec->Buffers[3][i].re * buff64xW[i].re - spec->Buffers[3][i].im * buff64xW[i].im);
    }
	free(buff64);
	free(buff64xW);
}
