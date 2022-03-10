
#include "nmpp.h"
#include "fft_32fcr.h"
#include <malloc.h>

void nmppsFFT4096Fwd_32fcr(const nm32fcr* pSrcVec, nm32fcr* pDstVec, NmppsFFTSpec_32fcr* spec)
{
    int i;
    nm32fcr* buff2048 = (nm32fcr *)malloc(2048 * sizeof(nm32fcr));
    nm32fcr* buff2048xW = (nm32fcr *)malloc(2048 * sizeof(nm32fcr));
    nmppsSplit_32fcr(pSrcVec, buff2048, buff2048xW, 4096);
    nmppsFFT2048Fwd_32fcr(buff2048, buff2048, spec);
    nmppsFFT2048Fwd_32fcr(buff2048xW, buff2048xW, spec);
    for(i = 0; i < 2048; i++) {
        pDstVec[i].im = buff2048[i].im + (spec->Buffers[9][i].re * buff2048xW[i].im + spec->Buffers[9][i].im * buff2048xW[i].re);
        pDstVec[i].re = buff2048[i].re + (spec->Buffers[9][i].re * buff2048xW[i].re - spec->Buffers[9][i].im * buff2048xW[i].im);
        pDstVec[i + 2048].im = buff2048[i].im - (spec->Buffers[9][i].re * buff2048xW[i].im + spec->Buffers[9][i].im * buff2048xW[i].re);
        pDstVec[i + 2048].re = buff2048[i].re - (spec->Buffers[9][i].re * buff2048xW[i].re - spec->Buffers[9][i].im * buff2048xW[i].im);
    }
    free(buff2048);
    free(buff2048xW);
}
