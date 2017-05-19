#include "fft_32fc.h"

void nmppsDFT8Fwd_32fc(nm32fcr *x8, nm32fcr *X8, NmppsFFTSpec_32fc *spec8)
{
   int i, j;
   nm32fcr columns[8][8];
   for(i = 0; i < 8; i++) {
       columns[0][i].im = spec8->Buffers[0][i].re * x8[0].im + spec8->Buffers[0][i].im * x8[0].re;
       columns[0][i].re = spec8->Buffers[0][i].re * x8[0].re - spec8->Buffers[0][i].im * x8[0].im;

       columns[1][i].im = spec8->Buffers[0][i + 8].re * x8[1].im + spec8->Buffers[0][i + 8].im * x8[1].re;
       columns[1][i].re = spec8->Buffers[0][i + 8].re * x8[1].re - spec8->Buffers[0][i + 8].im * x8[1].im;

       columns[2][i].im = spec8->Buffers[0][i + 16].re * x8[2].im + spec8->Buffers[0][i + 16].im * x8[2].re;
       columns[2][i].re = spec8->Buffers[0][i + 16].re * x8[2].re - spec8->Buffers[0][i + 16].im * x8[2].im;

       columns[3][i].im = spec8->Buffers[0][i + 24].re * x8[3].im + spec8->Buffers[0][i + 24].im * x8[3].re;
       columns[3][i].re = spec8->Buffers[0][i + 24].re * x8[3].re - spec8->Buffers[0][i + 24].im * x8[3].im;

       columns[4][i].im = spec8->Buffers[0][i + 32].re * x8[4].im + spec8->Buffers[0][i + 32].im * x8[4].re;
       columns[4][i].re = spec8->Buffers[0][i + 32].re * x8[4].re - spec8->Buffers[0][i + 32].im * x8[4].im;

       columns[5][i].im = spec8->Buffers[0][i + 40].re * x8[5].im + spec8->Buffers[0][i + 40].im * x8[5].re;
       columns[5][i].re = spec8->Buffers[0][i + 40].re * x8[5].re - spec8->Buffers[0][i + 40].im * x8[5].im;

       columns[6][i].im = spec8->Buffers[0][i + 48].re * x8[6].im + spec8->Buffers[0][i + 48].im * x8[6].re;
       columns[6][i].re = spec8->Buffers[0][i + 48].re * x8[6].re - spec8->Buffers[0][i + 48].im * x8[6].im;

       columns[7][i].im = spec8->Buffers[0][i + 56].re * x8[7].im + spec8->Buffers[0][i + 56].im * x8[7].re;
       columns[7][i].re = spec8->Buffers[0][i + 56].re * x8[7].re - spec8->Buffers[0][i + 56].im * x8[7].im;
   }
   for(i = 0; i < 8; i++) {
       X8[i].im = 0;
       X8[i].re = 0;
   }
   for(i = 0; i < 8; i++) {
       for(j = 0; j < 8; j++) {
            X8[j].im += columns[i][j].im;
            X8[j].re += columns[i][j].re;
       }
   }
}
