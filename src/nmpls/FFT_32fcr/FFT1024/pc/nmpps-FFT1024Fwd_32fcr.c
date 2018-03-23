#include "fft_32fcr.h"
#include <malloc.h>

void nmppsFFT1024Fwd_32fcr(const nm32fcr *x, nm32fcr *X, NmppsFFTSpec_32fcr *spec)
{
    int i;
    nm32fcr *buff1024 = (nm32fcr *)malloc(512 * sizeof(nm32fcr));
    nm32fcr *buff1024xW = (nm32fcr *)malloc(512 * sizeof(nm32fcr));
    for(i = 0; i < 512; i++) {
        buff1024[i].im = x[2 * i].im;
        buff1024[i].re = x[2 * i].re;
        buff1024xW[i].im = x[2 * i + 1].im;
        buff1024xW[i].re = x[2 * i + 1].re;
    }
    nmppsFFT512Fwd_32fcr(buff1024, buff1024, spec);
    nmppsFFT512Fwd_32fcr(buff1024xW, buff1024xW, spec);
    for(i = 0; i < 512; i++) {
        X[i].im = buff1024[i].im + (spec->Buffers[7][i].re * buff1024xW[i].im + spec->Buffers[7][i].im * buff1024xW[i].re);
        X[i].re = buff1024[i].re + (spec->Buffers[7][i].re * buff1024xW[i].re - spec->Buffers[7][i].im * buff1024xW[i].im);
        X[i + 512].im = buff1024[i].im - (spec->Buffers[7][i].re * buff1024xW[i].im + spec->Buffers[7][i].im * buff1024xW[i].re);
        X[i + 512].re = buff1024[i].re - (spec->Buffers[7][i].re * buff1024xW[i].re - spec->Buffers[7][i].im * buff1024xW[i].im);
    }
    free(buff1024);
    free(buff1024xW);
}
