#include "FFT_32fc.h"
#include <malloc.h>

void nmppsFFT16Fwd_32fc(nm32fcr *x16, nm32fcr *X16, NmppsFFTSpec_32fc *spec16)
{
    int i = 0;
    nm32fcr *buff8 = (nm32fcr *)malloc(8 * sizeof(nm32fcr));
    nm32fcr *buff8xW = (nm32fcr *)malloc(8 * sizeof(nm32fcr));
    for(i = 0; i < 8; i++) {
        buff8[i].im = x16[2 * i].im;
        buff8[i].re = x16[2 * i].re;
        buff8xW[i].im = x16[2 * i + 1].im;
        buff8xW[i].re = x16[2 * i + 1].re;
    }
    nmppsDFT8Fwd_32fc(buff8, buff8, spec16);
    nmppsDFT8Fwd_32fc(buff8xW, buff8xW, spec16);
    for(i = 0; i < 8; i++) {
        X16[i].im = buff8[i].im + (spec16->Buffers[1][i].re * buff8xW[i].im + spec16->Buffers[1][i].im * buff8xW[i].re);
        X16[i].re = buff8[i].re + (spec16->Buffers[1][i].re * buff8xW[i].re - spec16->Buffers[1][i].im * buff8xW[i].im);
        X16[i + 8].im = buff8[i].im - (spec16->Buffers[1][i].re * buff8xW[i].im + spec16->Buffers[1][i].im * buff8xW[i].re);
        X16[i + 8].re = buff8[i].re - (spec16->Buffers[1][i].re * buff8xW[i].re - spec16->Buffers[1][i].im * buff8xW[i].im);
    }
    free(buff8);
    free(buff8xW);
}
