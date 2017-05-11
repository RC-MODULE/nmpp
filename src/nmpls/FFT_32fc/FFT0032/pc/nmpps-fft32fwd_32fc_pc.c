#include "fft_32fc.h"
#include <malloc.h>

void nmppsFFT32Fwd_32fc(nm32fc *x32, nm32fc *X32, NmppsFFTSpec_32fc *spec32)
{
    int i;
    nm32fc *buff32 = (nm32fc *)malloc(16 * sizeof(nm32fc));
    nm32fc *buff32xW = (nm32fc *)malloc(16 * sizeof(nm32fc));
    for(i = 0; i < 16; i++) {
        buff32[i].im = x32[2 * i].im;
        buff32[i].re = x32[2 * i].re;
        buff32xW[i].im = x32[2 * i + 1].im;
        buff32xW[i].re = x32[2 * i + 1].re;
    }
    nmppsFFT16Fwd_32fc(buff32, buff32, spec32);
    nmppsFFT16Fwd_32fc(buff32xW, buff32xW, spec32);
    for(i = 0; i < 16; i++) {
        X32[i].im = buff32[i].im + (spec32->Buffers[2][i].re * buff32xW[i].im + spec32->Buffers[2][i].im * buff32xW[i].re);
        X32[i].re = buff32[i].re + (spec32->Buffers[2][i].re * buff32xW[i].re - spec32->Buffers[2][i].im * buff32xW[i].im);
        X32[i + 16].im = buff32[i].im - (spec32->Buffers[2][i].re * buff32xW[i].im + spec32->Buffers[2][i].im * buff32xW[i].re);
        X32[i + 16].re = buff32[i].re - (spec32->Buffers[2][i].re * buff32xW[i].re - spec32->Buffers[2][i].im * buff32xW[i].im);
    }
    free(buff32);
    free(buff32xW);
}
