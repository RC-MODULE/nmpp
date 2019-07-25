#include "fft_32fcr.h"
#include <malloc.h>

void nmppsFFT2048Fwd_32fcr(const nm32fcr* pSrcVec, nm32fcr* pDstVec, NmppsFFTSpec_32fcr* spec)
{
    int i;
    nm32fcr* buff2048 = (nm32fcr*)malloc(1024 * sizeof(nm32fcr));
    nm32fcr* buff2048xW = (nm32fcr*)malloc(1024 * sizeof(nm32fcr));
    for(i = 0; i < 1024; i++) {
        buff2048[i].im = pSrcVec[2 * i].im;
        buff2048[i].re = pSrcVec[2 * i].re;
        buff2048xW[i].im = pSrcVec[2 * i + 1].im;
        buff2048xW[i].re = pSrcVec[2 * i + 1].re;
    }
    nmppsFFT1024Fwd_32fcr(buff2048, buff2048, spec);
    nmppsFFT1024Fwd_32fcr(buff2048xW, buff2048xW, spec);
    for(i = 0; i < 1024; i++) {
        pDstVec[i].im = buff2048[i].im + (spec->Buffers[8][i].re * buff2048xW[i].im + spec->Buffers[8][i].im * buff2048xW[i].re);
        pDstVec[i].re = buff2048[i].re + (spec->Buffers[8][i].re * buff2048xW[i].re - spec->Buffers[8][i].im * buff2048xW[i].im);
        pDstVec[i + 1024].im = buff2048[i].im - (spec->Buffers[8][i].re * buff2048xW[i].im + spec->Buffers[8][i].im * buff2048xW[i].re);
        pDstVec[i + 1024].re = buff2048[i].re - (spec->Buffers[8][i].re * buff2048xW[i].re - spec->Buffers[8][i].im * buff2048xW[i].im);
    }
    free(buff2048);
    free(buff2048xW);
}
