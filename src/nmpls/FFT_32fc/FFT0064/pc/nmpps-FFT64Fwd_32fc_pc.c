#include "fft_32fc.h"
#include <malloc.h>

void nmppsFFT64Fwd_32fc(nm32fcr *x64, nm32fcr *X64, NmppsFFTSpec_32fc *spec64)
{
    int i;
    nm32fcr *buff64 = (nm32fcr *)malloc(32 * sizeof(nm32fcr));
    nm32fcr *buff64xW = (nm32fcr *)malloc(32 * sizeof(nm32fcr));
    for(i = 0; i < 32; i++) {
        buff64[i].im = x64[2 * i].im;
        buff64[i].re = x64[2 * i].re;
        buff64xW[i].im = x64[2 * i + 1].im;
        buff64xW[i].re = x64[2 * i + 1].re;
    }
    nmppsFFT32Fwd_32fc(buff64, buff64, spec64);
    nmppsFFT32Fwd_32fc(buff64xW, buff64xW, spec64);
    for(i = 0; i < 32; i++) {
        X64[i].im = buff64[i].im + (spec64->Buffers[3][i].re * buff64xW[i].im + spec64->Buffers[3][i].im * buff64xW[i].re);
        X64[i].re = buff64[i].re + (spec64->Buffers[3][i].re * buff64xW[i].re - spec64->Buffers[3][i].im * buff64xW[i].im);
        X64[i + 32].im = buff64[i].im - (spec64->Buffers[3][i].re * buff64xW[i].im + spec64->Buffers[3][i].im * buff64xW[i].re);
        X64[i + 32].re = buff64[i].re - (spec64->Buffers[3][i].re * buff64xW[i].re - spec64->Buffers[3][i].im * buff64xW[i].im);
    }
	free(buff64);
	free(buff64xW);
}
