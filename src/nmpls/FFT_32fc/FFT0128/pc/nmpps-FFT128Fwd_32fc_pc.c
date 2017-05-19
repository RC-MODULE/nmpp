#include "fft_32fc.h"

void nmppsFFT128Fwd_32fc(nm32fcr *x128, nm32fcr *X128, NmppsFFTSpec_32fc *spec128)
{
    int i;
    nm32fcr buff128[64], buff128xW[64];
    for(i = 0; i < 64; i++) {
        buff128[i].im = x128[2 * i].im;
        buff128[i].re = x128[2 * i].re;
        buff128xW[i].im = x128[2 * i + 1].im;
        buff128xW[i].re = x128[2 * i + 1].re;
    }
    nmppsFFT64Fwd_32fc(buff128, buff128, spec128);
    nmppsFFT64Fwd_32fc(buff128xW, buff128xW, spec128);
    for(i = 0; i < 64; i++) {
        X128[i].im = buff128[i].im + (spec128->Buffers[4][i].re * buff128xW[i].im + spec128->Buffers[4][i].im * buff128xW[i].re);
        X128[i].re = buff128[i].re + (spec128->Buffers[4][i].re * buff128xW[i].re - spec128->Buffers[4][i].im * buff128xW[i].im);
        X128[i + 64].im = buff128[i].im - (spec128->Buffers[4][i].re * buff128xW[i].im + spec128->Buffers[4][i].im * buff128xW[i].re);
        X128[i + 64].re = buff128[i].re - (spec128->Buffers[4][i].re * buff128xW[i].re - spec128->Buffers[4][i].im * buff128xW[i].im);
    }
}
