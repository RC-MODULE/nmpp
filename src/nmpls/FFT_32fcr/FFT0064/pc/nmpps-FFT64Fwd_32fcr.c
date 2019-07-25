#include "fft_32fcr.h"
#include <malloc.h>

void nmppsFFT64Fwd_32fcr(const nm32fcr* pSrcVec, nm32fcr* pDstVec, NmppsFFTSpec_32fcr* spec)
{
    int i;
    nm32fcr* buff64 = (nm32fcr*)malloc(32 * sizeof(nm32fcr));
    nm32fcr* buff64xW = (nm32fcr*)malloc(32 * sizeof(nm32fcr));
    for(i = 0; i < 32; i++) {
        buff64[i].im = pSrcVec[2 * i].im;
        buff64[i].re = pSrcVec[2 * i].re;
        buff64xW[i].im = pSrcVec[2 * i + 1].im;
        buff64xW[i].re = pSrcVec[2 * i + 1].re;
    }
    nmppsFFT32Fwd_32fcr(buff64, buff64, spec);
    nmppsFFT32Fwd_32fcr(buff64xW, buff64xW, spec);
    for(i = 0; i < 32; i++) {
        pDstVec[i].im = buff64[i].im + (spec->Buffers[3][i].re * buff64xW[i].im + spec->Buffers[3][i].im * buff64xW[i].re);
        pDstVec[i].re = buff64[i].re + (spec->Buffers[3][i].re * buff64xW[i].re - spec->Buffers[3][i].im * buff64xW[i].im);
        pDstVec[i + 32].im = buff64[i].im - (spec->Buffers[3][i].re * buff64xW[i].im + spec->Buffers[3][i].im * buff64xW[i].re);
        pDstVec[i + 32].re = buff64[i].re - (spec->Buffers[3][i].re * buff64xW[i].re - spec->Buffers[3][i].im * buff64xW[i].im);
    }
	free(buff64);
	free(buff64xW);
}
