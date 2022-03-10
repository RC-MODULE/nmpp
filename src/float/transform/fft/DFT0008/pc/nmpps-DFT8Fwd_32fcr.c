#include "fft_32fcr.h"

void nmppsDFT8Fwd_32fcr(const nm32fcr* pSrcVec, nm32fcr* pDstVec, NmppsFFTSpec_32fcr* spec)
{
   int i, j;
   nm32fcr columns[8][8];
   for(i = 0; i < 8; i++) {
       columns[0][i].im = spec->Buffers[0][i].re * pSrcVec[0].im + spec->Buffers[0][i].im * pSrcVec[0].re;
       columns[0][i].re = spec->Buffers[0][i].re * pSrcVec[0].re - spec->Buffers[0][i].im * pSrcVec[0].im;

       columns[1][i].im = spec->Buffers[0][i + 8].re * pSrcVec[1].im + spec->Buffers[0][i + 8].im * pSrcVec[1].re;
       columns[1][i].re = spec->Buffers[0][i + 8].re * pSrcVec[1].re - spec->Buffers[0][i + 8].im * pSrcVec[1].im;

       columns[2][i].im = spec->Buffers[0][i + 16].re * pSrcVec[2].im + spec->Buffers[0][i + 16].im * pSrcVec[2].re;
       columns[2][i].re = spec->Buffers[0][i + 16].re * pSrcVec[2].re - spec->Buffers[0][i + 16].im * pSrcVec[2].im;

       columns[3][i].im = spec->Buffers[0][i + 24].re * pSrcVec[3].im + spec->Buffers[0][i + 24].im * pSrcVec[3].re;
       columns[3][i].re = spec->Buffers[0][i + 24].re * pSrcVec[3].re - spec->Buffers[0][i + 24].im * pSrcVec[3].im;

       columns[4][i].im = spec->Buffers[0][i + 32].re * pSrcVec[4].im + spec->Buffers[0][i + 32].im * pSrcVec[4].re;
       columns[4][i].re = spec->Buffers[0][i + 32].re * pSrcVec[4].re - spec->Buffers[0][i + 32].im * pSrcVec[4].im;

       columns[5][i].im = spec->Buffers[0][i + 40].re * pSrcVec[5].im + spec->Buffers[0][i + 40].im * pSrcVec[5].re;
       columns[5][i].re = spec->Buffers[0][i + 40].re * pSrcVec[5].re - spec->Buffers[0][i + 40].im * pSrcVec[5].im;

       columns[6][i].im = spec->Buffers[0][i + 48].re * pSrcVec[6].im + spec->Buffers[0][i + 48].im * pSrcVec[6].re;
       columns[6][i].re = spec->Buffers[0][i + 48].re * pSrcVec[6].re - spec->Buffers[0][i + 48].im * pSrcVec[6].im;

       columns[7][i].im = spec->Buffers[0][i + 56].re * pSrcVec[7].im + spec->Buffers[0][i + 56].im * pSrcVec[7].re;
       columns[7][i].re = spec->Buffers[0][i + 56].re * pSrcVec[7].re - spec->Buffers[0][i + 56].im * pSrcVec[7].im;
   }
   for(i = 0; i < 8; i++) {
       pDstVec[i].im = 0;
       pDstVec[i].re = 0;
   }
   for(i = 0; i < 8; i++) {
       for(j = 0; j < 8; j++) {
            pDstVec[j].im += columns[i][j].im;
            pDstVec[j].re += columns[i][j].re;
       }
   }
}
