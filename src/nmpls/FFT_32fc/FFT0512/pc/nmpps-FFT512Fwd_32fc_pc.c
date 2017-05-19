#include "FFT_32fc.h"
#include <malloc.h>

void nmppsFFT512Fwd_32fc(nm32fcr *x512, nm32fcr *X512, NmppsFFTSpec_32fc *spec512)
{
    int i;
    nm32fcr *buff512 = (nm32fcr *)malloc(256 * sizeof(nm32fcr));
    nm32fcr *buff512xW = (nm32fcr *)malloc(256 * sizeof(nm32fcr));
    for(i = 0; i < 256; i++) {
        buff512[i].im = x512[2 * i].im;
        buff512[i].re = x512[2 * i].re;
        buff512xW[i].im = x512[2 * i + 1].im;
        buff512xW[i].re = x512[2 * i + 1].re;
    }
    nmppsFFT256Fwd_32fc(buff512, buff512, spec512);
    nmppsFFT256Fwd_32fc(buff512xW, buff512xW, spec512);
    for(i = 0; i < 256; i++) {
        X512[i].im = buff512[i].im + (spec512->Buffers[6][i].re * buff512xW[i].im + spec512->Buffers[6][i].im * buff512xW[i].re);
        X512[i].re = buff512[i].re + (spec512->Buffers[6][i].re * buff512xW[i].re - spec512->Buffers[6][i].im * buff512xW[i].im);
        X512[i + 256].im = buff512[i].im - (spec512->Buffers[6][i].re * buff512xW[i].im + spec512->Buffers[6][i].im * buff512xW[i].re);
        X512[i + 256].re = buff512[i].re - (spec512->Buffers[6][i].re * buff512xW[i].re - spec512->Buffers[6][i].im * buff512xW[i].im);
    }
    free(buff512);
    free(buff512xW);
}
