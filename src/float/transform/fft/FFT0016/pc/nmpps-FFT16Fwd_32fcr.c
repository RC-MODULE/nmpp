#include "fft_32fcr.h"
#include <malloc.h>

void nmppsFFT16Fwd_32fcr(const nm32fcr* pSrcVec, nm32fcr* pDstVec, NmppsFFTSpec_32fcr* spec)
{
    int i = 0;
    nm32fcr* buff8 = (nm32fcr*)malloc(8 * sizeof(nm32fcr));
    nm32fcr* buff8xW = (nm32fcr*)malloc(8 * sizeof(nm32fcr));
    for(i = 0; i < 8; i++) {
        buff8[i].im = pSrcVec[2 * i].im;
        buff8[i].re = pSrcVec[2 * i].re;
        buff8xW[i].im = pSrcVec[2 * i + 1].im;
        buff8xW[i].re = pSrcVec[2 * i + 1].re;
    }
    nmppsDFT8Fwd_32fcr(buff8, buff8, spec);
    nmppsDFT8Fwd_32fcr(buff8xW, buff8xW, spec);
    for(i = 0; i < 8; i++) {
        pDstVec[i].im = buff8[i].im + (spec->Buffers[1][i].re * buff8xW[i].im + spec->Buffers[1][i].im * buff8xW[i].re);
        pDstVec[i].re = buff8[i].re + (spec->Buffers[1][i].re * buff8xW[i].re - spec->Buffers[1][i].im * buff8xW[i].im);
        pDstVec[i + 8].im = buff8[i].im - (spec->Buffers[1][i].re * buff8xW[i].im + spec->Buffers[1][i].im * buff8xW[i].re);
        pDstVec[i + 8].re = buff8[i].re - (spec->Buffers[1][i].re * buff8xW[i].re - spec->Buffers[1][i].im * buff8xW[i].im);
    }
    free(buff8);
    free(buff8xW);
}
