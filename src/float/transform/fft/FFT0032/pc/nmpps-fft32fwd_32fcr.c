#include "fft_32fcr.h"
#include <malloc.h>

void nmppsFFT32Fwd_32fcr(const nm32fcr* pSrcVec, nm32fcr* pDstVec, NmppsFFTSpec_32fcr* spec)
{
    int i;
    nm32fcr *buff32 = (nm32fcr *)malloc(16 * sizeof(nm32fcr));
    nm32fcr *buff32xW = (nm32fcr *)malloc(16 * sizeof(nm32fcr));
    for(i = 0; i < 16; i++) {
        buff32[i].im = pSrcVec[2 * i].im;
        buff32[i].re = pSrcVec[2 * i].re;
        buff32xW[i].im = pSrcVec[2 * i + 1].im;
        buff32xW[i].re = pSrcVec[2 * i + 1].re;
    }
    nmppsFFT16Fwd_32fcr(buff32, buff32, spec);
    nmppsFFT16Fwd_32fcr(buff32xW, buff32xW, spec);
    for(i = 0; i < 16; i++) {
        pDstVec[i].im = buff32[i].im + (spec->Buffers[2][i].re * buff32xW[i].im + spec->Buffers[2][i].im * buff32xW[i].re);
        pDstVec[i].re = buff32[i].re + (spec->Buffers[2][i].re * buff32xW[i].re - spec->Buffers[2][i].im * buff32xW[i].im);
        pDstVec[i + 16].im = buff32[i].im - (spec->Buffers[2][i].re * buff32xW[i].im + spec->Buffers[2][i].im * buff32xW[i].re);
        pDstVec[i + 16].re = buff32[i].re - (spec->Buffers[2][i].re * buff32xW[i].re - spec->Buffers[2][i].im * buff32xW[i].im);
    }
    free(buff32);
    free(buff32xW);
}
