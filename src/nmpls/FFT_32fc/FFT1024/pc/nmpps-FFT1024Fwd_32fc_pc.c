#include "fft_32fc.h"
#include <malloc.h>

void nmppsFFT1024Fwd_32fc(nm32fcr *x1024, nm32fcr *X1024, NmppsFFTSpec_32fc *spec1024)
{
    int i;
    nm32fcr *buff1024 = (nm32fcr *)malloc(512 * sizeof(nm32fcr));
    nm32fcr *buff1024xW = (nm32fcr *)malloc(512 * sizeof(nm32fcr));
    for(i = 0; i < 512; i++) {
        buff1024[i].im = x1024[2 * i].im;
        buff1024[i].re = x1024[2 * i].re;
        buff1024xW[i].im = x1024[2 * i + 1].im;
        buff1024xW[i].re = x1024[2 * i + 1].re;
    }
    nmppsFFT512Fwd_32fc(buff1024, buff1024, spec1024);
    nmppsFFT512Fwd_32fc(buff1024xW, buff1024xW, spec1024);
    for(i = 0; i < 512; i++) {
        X1024[i].im = buff1024[i].im + (spec1024->Buffers[7][i].re * buff1024xW[i].im + spec1024->Buffers[7][i].im * buff1024xW[i].re);
        X1024[i].re = buff1024[i].re + (spec1024->Buffers[7][i].re * buff1024xW[i].re - spec1024->Buffers[7][i].im * buff1024xW[i].im);
        X1024[i + 512].im = buff1024[i].im - (spec1024->Buffers[7][i].re * buff1024xW[i].im + spec1024->Buffers[7][i].im * buff1024xW[i].re);
        X1024[i + 512].re = buff1024[i].re - (spec1024->Buffers[7][i].re * buff1024xW[i].re - spec1024->Buffers[7][i].im * buff1024xW[i].im);
    }
    free(buff1024);
    free(buff1024xW);
}
