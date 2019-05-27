#include "fft_32fcr.h"

void nmppsFFT128Fwd_32fcr(const nm32fcr* pSrcVec, nm32fcr* pDstVec, NmppsFFTSpec_32fcr* spec)
{
    int i;
    nm32fcr buff128[64], buff128xW[64];
    for(i = 0; i < 64; i++) {
        buff128[i].im = pSrcVec[2 * i].im;
        buff128[i].re = pSrcVec[2 * i].re;
        buff128xW[i].im = pSrcVec[2 * i + 1].im;
        buff128xW[i].re = pSrcVec[2 * i + 1].re;
    }
    nmppsFFT64Fwd_32fcr(pSrcVec, pDstVec, spec);
    nmppsFFT64Fwd_32fcr(pSrcVec, pDstVec, spec);
    for(i = 0; i < 64; i++) {
        pDstVec[i].im = buff128[i].im + (spec->Buffers[4][i].re * buff128xW[i].im + spec->Buffers[4][i].im * buff128xW[i].re);
        pDstVec[i].re = buff128[i].re + (spec->Buffers[4][i].re * buff128xW[i].re - spec->Buffers[4][i].im * buff128xW[i].im);
        pDstVec[i + 64].im = buff128[i].im - (spec->Buffers[4][i].re * buff128xW[i].im + spec->Buffers[4][i].im * buff128xW[i].re);
        pDstVec[i + 64].re = buff128[i].re - (spec->Buffers[4][i].re * buff128xW[i].re - spec->Buffers[4][i].im * buff128xW[i].im);
    }
}
