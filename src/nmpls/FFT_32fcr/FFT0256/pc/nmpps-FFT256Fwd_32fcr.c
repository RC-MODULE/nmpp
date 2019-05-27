//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software                      */
//*                                                                         */
//*   Fast Fourie Transform Library                                         */
//*                                                                         */
//*   File:             nmpps-FFT256Fwd_32fcr.c                             */
//*   Contents:         C Equivalent function of the FFTFwd256              */
//*                                                                         */
//*   Software design:  A.Brodyazhenko                                      */
//*                                                                         */
//*                                                                         */
//***************************************************************************/

#include "fft_32fcr.h"
#include <malloc.h>

void nmppsFFT256Fwd_32fcr(const nm32fcr* pSrcVec, nm32fcr* pDstVec, NmppsFFTSpec_32fcr* spec)
{
    int i;
    nm32fcr* buff256 = (nm32fcr*)malloc(128 * sizeof(nm32fcr));
    nm32fcr* buff256xW = (nm32fcr*)malloc(128 * sizeof(nm32fcr));
    for(i = 0; i < 128; i++) {
        buff256[i].im = pSrcVec[2 * i].im;
        buff256[i].re = pSrcVec[2 * i].re;
        buff256xW[i].im = pSrcVec[2 * i + 1].im;
        buff256xW[i].re = pSrcVec[2 * i + 1].re;
        //X256[i].im = 0;
       // X256[i].re = 0;
        //X256[i + 128].im = 0;
       // X256[i + 128].re = 0;
    }
    nmppsFFT128Fwd_32fcr(pSrcVec, pDstVec, spec);
    nmppsFFT128Fwd_32fcr(pSrcVec, pDstVec, spec);
    for(i = 0; i < 128; i++) {
        pDstVec[i].im = buff256[i].im + (spec->Buffers[5][i].re * buff256xW[i].im + spec->Buffers[5][i].im * buff256xW[i].re);
        pDstVec[i].re = buff256[i].re + (spec->Buffers[5][i].re * buff256xW[i].re - spec->Buffers[5][i].im * buff256xW[i].im);
        pDstVec[i + 128].im = buff256[i].im - (spec->Buffers[5][i].re * buff256xW[i].im + spec->Buffers[5][i].im * buff256xW[i].re);
        pDstVec[i + 128].re = buff256[i].re - (spec->Buffers[5][i].re * buff256xW[i].re - spec->Buffers[5][i].im * buff256xW[i].im);
    }
    free(buff256);
    free(buff256xW);
}
