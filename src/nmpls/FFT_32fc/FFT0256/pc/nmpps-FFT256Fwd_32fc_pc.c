//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software                      */
//*                                                                         */
//*   Fast Fourie Transform Library                                         */
//*                                                                         */
//*   File:             nmpps-FFT256Fwd_32fc_pc.c                           */
//*   Contents:         C Equivalent function of the FFTFwd256              */
//*                                                                         */
//*   Software design:  A.Brodyazhenko                                      */
//*                                                                         */
//*                                                                         */
//***************************************************************************/

#include "fft_32fc.h"
#include <malloc.h>

void nmppsFFT256Fwd_32fc(nm32fcr *x256, nm32fcr *X256, NmppsFFTSpec_32fc *spec256)
{
    int i;
    nm32fcr *buff256 = (nm32fcr *)malloc(128 * sizeof(nm32fcr));
    nm32fcr *buff256xW = (nm32fcr *)malloc(128 * sizeof(nm32fcr));
    for(i = 0; i < 128; i++) {
        buff256[i].im = x256[2 * i].im;
        buff256[i].re = x256[2 * i].re;
        buff256xW[i].im = x256[2 * i + 1].im;
        buff256xW[i].re = x256[2 * i + 1].re;
    }
    nmppsFFT128Fwd_32fc(buff256, buff256, spec256);
    nmppsFFT128Fwd_32fc(buff256xW, buff256xW, spec256);
    for(i = 0; i < 128; i++) {
        X256[i].im = buff256[i].im + (spec256->Buffers[5][i].re * buff256xW[i].im + spec256->Buffers[5][i].im * buff256xW[i].re);
        X256[i].re = buff256[i].re + (spec256->Buffers[5][i].re * buff256xW[i].re - spec256->Buffers[5][i].im * buff256xW[i].im);
        X256[i + 128].im = buff256[i].im - (spec256->Buffers[5][i].re * buff256xW[i].im + spec256->Buffers[5][i].im * buff256xW[i].re);
        X256[i + 128].re = buff256[i].re - (spec256->Buffers[5][i].re * buff256xW[i].re - spec256->Buffers[5][i].im * buff256xW[i].im);
    }
    free(buff256);
    free(buff256xW);
}
