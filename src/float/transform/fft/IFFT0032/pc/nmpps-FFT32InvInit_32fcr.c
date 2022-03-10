//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software                      */
//*                                                                         */
//*   Software design:  A.Brodyazhenko                                      */
//*                                                                         */
//*   File:             nmpps-FFT32InvInit_32fcr.c                          */
//*   Contents:         Routine for the struct initialization               */
//*                     of the W-coefficients for FFT32Inv                  */
//***************************************************************************/

#include "fft_32fcr.h"
#include <malloc.h>
#include <math.h>

int nmppsFFT32InvInitAlloc_32fcr(NmppsFFTSpec_32fcr** addr)
{
    int i, j, k;
    int gr1;
    const float pi = 3.141592653;
    float alpha;
    NmppsFFTSpec_32fcr *spec_32fcr = (NmppsFFTSpec_32fcr *) malloc(sizeof(NmppsFFTSpec_32fcr));
    if(!spec_32fcr) {
        return 0x32B;
    }
    for(i = 0; i < NUMBUFF1; i++) {
    	spec_32fcr->Buffers[i] = 0;
    }
    spec_32fcr->Buffers[0] = (nm32fcr *) malloc(64 * sizeof(nm32fcr)); // SinCos0
    if (!spec_32fcr->Buffers[0])
        return 0x32B0;
    spec_32fcr->Buffers[1] = (nm32fcr *) malloc(8 * sizeof(nm32fcr)); // W8_0
    if (!spec_32fcr->Buffers[1])
        return 0x32B1;
    spec_32fcr->Buffers[2] = (nm32fcr *) malloc(16 * sizeof(nm32fcr)); // W16_0
    if (!spec_32fcr->Buffers[2])
        return 0x32B2;
	k = 0;
    *addr = spec_32fcr;
    for(i = 0; i <  8; i++) {
        for(j = 0; j < 64; j = j + 8) {
            alpha = (2 * pi * (float)i * (float)k) / 8.0;
            spec_32fcr->Buffers[0][i + j].im = sinf(alpha) / 32.0;
            spec_32fcr->Buffers[0][i + j].re = cosf(alpha) / 32.0;
            k++;
        }
        k = 0;
    }
    for(i = 0; i < 16; i++) {
        alpha = (2 * pi * (float)i) / 32.0;
        spec_32fcr->Buffers[2][i].im = sinf(alpha);
        spec_32fcr->Buffers[2][i].re = cosf(alpha);
    }
    gr1 = 0;
    for(i = 0; i < 8; i++) {
        spec_32fcr->Buffers[1][i].im = spec_32fcr->Buffers[2][gr1].im;
        spec_32fcr->Buffers[1][i].re = spec_32fcr->Buffers[2][gr1].re;
        gr1 += 2;
    }
    return 0;
}