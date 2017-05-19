#include "fft_32fc.h"
#include <malloc.h>

void nmppsFFT2048Fwd_32fc(nm32fcr *x2048, nm32fcr *X2048, NmppsFFTSpec_32fc *spec2048)
{
    int i;
    nm32fcr *buff2048 = (nm32fcr *)malloc(1024 * sizeof(nm32fc));
    nm32fcr *buff2048xW = (nm32fcr *)malloc(1024 * sizeof(nm32fc));
    for(i = 0; i < 1024; i++) {
        buff2048[i].im = x2048[2 * i].im;
        buff2048[i].re = x2048[2 * i].re;
        buff2048xW[i].im = x2048[2 * i + 1].im;
        buff2048xW[i].re = x2048[2 * i + 1].re;
    }
    nmppsFFT1024Fwd_32fc(buff2048, buff2048, spec2048);
    nmppsFFT1024Fwd_32fc(buff2048xW, buff2048xW, spec2048);
    for(i = 0; i < 1024; i++) {
        X2048[i].im = buff2048[i].im + (spec2048->Buffers[8][i].re * buff2048xW[i].im + spec2048->Buffers[8][i].im * buff2048xW[i].re);
        X2048[i].re = buff2048[i].re + (spec2048->Buffers[8][i].re * buff2048xW[i].re - spec2048->Buffers[8][i].im * buff2048xW[i].im);
        X2048[i + 1024].im = buff2048[i].im - (spec2048->Buffers[8][i].re * buff2048xW[i].im + spec2048->Buffers[8][i].im * buff2048xW[i].re);
        X2048[i + 1024].re = buff2048[i].re - (spec2048->Buffers[8][i].re * buff2048xW[i].re - spec2048->Buffers[8][i].im * buff2048xW[i].im);
    }
    free(buff2048);
    free(buff2048xW);
}
