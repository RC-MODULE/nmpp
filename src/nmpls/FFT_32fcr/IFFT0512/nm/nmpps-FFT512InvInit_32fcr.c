//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software                      */
//*                                                                         */
//*   Software design:  A.Brodyazhenko                                      */
//*                                                                         */
//*   File:             nmpps-FFT512InvInit_32fcr.c                         */
//*   Contents:         Routine for the struct initialization               */
//*                     of the W-coefficients for FFT512Inv                 */
//***************************************************************************/

#include <malloc32.h>
#include <math.h>
#include "fft_32fcr.h"

int nmppsFFT512InvInitAlloc_32fcr(NmppsFFTSpec_32fcr** addr)
{
    int i;
    float alpha;
    NmppsFFTSpec_32fcr *spec_32fcr = (NmppsFFTSpec_32fcr *) malloc(sizeof(NmppsFFTSpec_32fcr));
    if(!spec_32fcr) {
        return 0x512B;
    }
    spec_32fcr->Buffs[0] = 0;

    spec_32fcr->Buffs[1] = (nm32fcr *) malloc1((1 + 7 + 256) * sizeof(nm32fcr));
    if(!spec_32fcr->Buffs[1])
        return 0x512B1;

    spec_32fcr->Buffers[0] = spec_32fcr->Buffs[1]; // 1.0

    spec_32fcr->Buffers[3] = spec_32fcr->Buffs[1] + 1;      // W4_16
    spec_32fcr->Buffers[4] = spec_32fcr->Buffs[1] + 2;      // W2_16
    spec_32fcr->Buffers[5] = spec_32fcr->Buffs[1] + 3;      // W6_16
    spec_32fcr->Buffers[6] = spec_32fcr->Buffs[1] + 4;      // W1_16
    spec_32fcr->Buffers[7] = spec_32fcr->Buffs[1] + 5;      // W3_16
    spec_32fcr->Buffers[8] = spec_32fcr->Buffs[1] + 6;      // W5_16
    spec_32fcr->Buffers[9] = spec_32fcr->Buffs[1] + 7;      // W7_16
    spec_32fcr->Buffers[10] = spec_32fcr->Buffs[1] + 8;     // W256

    spec_32fcr->Buffs[2] = (nm32fcr *) malloc2(256 * sizeof(nm32fcr));
    if(!spec_32fcr->Buffs[2])
        return 0x512B2;

    spec_32fcr->Buffers[1] = spec_32fcr->Buffs[2]; // buff_fft

    spec_32fcr->Buffs[3] = (nm32fcr *) malloc3(256 * sizeof(nm32fcr));
    if(!spec_32fcr->Buffs[3])
        return 0x512B3;

    spec_32fcr->Buffers[2] = spec_32fcr->Buffs[3]; // buff_fftxW

    *addr = spec_32fcr;

    spec_32fcr->Buffers[0]->im = 0;
    spec_32fcr->Buffers[0]->re = 0.001953125; // 1/512 for FFT512Inv (1.0 for any FFTFwd)

    spec_32fcr->Buffers[3]->im = 1.0;                   // W4_16
    spec_32fcr->Buffers[3]->re = -4.3711388286738e-08;

    spec_32fcr->Buffers[4]->im = 0.70710676908493;      // W2_16  
    spec_32fcr->Buffers[4]->re = 0.70710676908493;

    spec_32fcr->Buffers[5]->im = 0.70710676908493;      // W6_16
    spec_32fcr->Buffers[5]->re = -0.70710676908493;

    spec_32fcr->Buffers[6]->im = 0.38268345594406;      // W1_16
    spec_32fcr->Buffers[6]->re = 0.9238795042038;

    spec_32fcr->Buffers[7]->im = 0.9238795042038;       // W3_16
    spec_32fcr->Buffers[7]->re = 0.38268342614174;

    spec_32fcr->Buffers[8]->im = 0.9238795042038;       // W5_16
    spec_32fcr->Buffers[8]->re = -0.38268342614174;

    spec_32fcr->Buffers[9]->im = 0.38268327713013;      // W7_16
    spec_32fcr->Buffers[9]->re = -0.92387962341309;

    for(i = 0; i < 256; i++) {
        alpha = (0.0122718463 * (float)i);
        spec_32fcr->Buffers[10][i].im = sinf(alpha);
        spec_32fcr->Buffers[10][i].re = cosf(alpha);
    }
    return 0;
}