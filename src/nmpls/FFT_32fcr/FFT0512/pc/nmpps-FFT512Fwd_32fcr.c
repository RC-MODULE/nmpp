#include "fft_32fcr.h"
#include <malloc.h>

void nmppsFFT512Fwd_32fcr(const nm32fcr *x, nm32fcr *X, NmppsFFTSpec_32fcr *spec)
{
    int i;
    nm32fcr *buff512 = (nm32fcr *)malloc(256 * sizeof(nm32fcr));
    nm32fcr *buff512xW = (nm32fcr *)malloc(256 * sizeof(nm32fcr));
    for(i = 0; i < 256; i++) {
        buff512[i].im = x[2 * i].im;
        buff512[i].re = x[2 * i].re;
        buff512xW[i].im = x[2 * i + 1].im;
        buff512xW[i].re = x[2 * i + 1].re;
    }
    nmppsFFT256Fwd_32fcr(buff512, buff512, spec);
    nmppsFFT256Fwd_32fcr(buff512xW, buff512xW, spec);
    for(i = 0; i < 256; i++) {
        X[i].im = buff512[i].im + (spec->Buffers[6][i].re * buff512xW[i].im + spec->Buffers[6][i].im * buff512xW[i].re);
        X[i].re = buff512[i].re + (spec->Buffers[6][i].re * buff512xW[i].re - spec->Buffers[6][i].im * buff512xW[i].im);
        X[i + 256].im = buff512[i].im - (spec->Buffers[6][i].re * buff512xW[i].im + spec->Buffers[6][i].im * buff512xW[i].re);
        X[i + 256].re = buff512[i].re - (spec->Buffers[6][i].re * buff512xW[i].re - spec->Buffers[6][i].im * buff512xW[i].im);
    }
    free(buff512);
    free(buff512xW);
}