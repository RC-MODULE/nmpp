//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software                      */
//*                                                                         */
//*   Software design:  A.Brodyazhenko                                      */
//*                                                                         */
//*   File:             nmpps-FFT2048FwdInit_32fcr.c                        */
//*   Contents:         Routine for the struct initialization               */
//*                     of the W-coefficients for FFT2048Fwd                */
//***************************************************************************/

#include <malloc32.h>
#include <math.h>
#include "fft_32fcr.h"

int nmppsFFT2048FwdInitAlloc_32fcr(NmppsFFTSpec_32fcr **addr)
{
    int i;
    const float pi = 3.141592653;
    float alpha;
    NmppsFFTSpec_32fcr *spec_32fcr = (NmppsFFTSpec_32fcr *) malloc0(sizeof(NmppsFFTSpec_32fcr));
    if(!spec_32fcr) {
        return 0x2048F;
    }

/*************************************Bank1*************************************/
    spec_32fcr->Buffs[0] = (nm32fcr *) malloc1((1 + 1024) * sizeof(nm32fcr));
    if(!spec_32fcr->Buffs[0])
        return 0x2048F0;

    spec_32fcr->Buffers[0] = spec_32fcr->Buffs[0];      // 1.0 or 1/2048
    spec_32fcr->Buffers[1] = spec_32fcr->Buffs[0] + 1;  // buff_fft2048

/*************************************Bank2*************************************/
    spec_32fcr->Buffs[1] = (nm32fcr *) malloc2((1024) * sizeof(nm32fcr));
    if(!spec_32fcr->Buffs[1])
        return 0x2048F1;

    spec_32fcr->Buffers[2] = spec_32fcr->Buffs[1];      // buff_fft2048xW

/*************************************Bank3*************************************/
    spec_32fcr->Buffs[2] = (nm32fcr *) malloc3((1024) * sizeof(nm32fcr));
    if(!spec_32fcr->Buffs[2])
        return 0x2048F2;

    spec_32fcr->Buffers[11] = spec_32fcr->Buffs[2];     // buff_fft2048mulW

/*************************************Bank4*************************************/
    spec_32fcr->Buffs[3] = (nm32fcr *) malloc0((7 + 1024) * sizeof(nm32fcr));
    if(!spec_32fcr->Buffs[3])
        return 0x2048F3;

    spec_32fcr->Buffers[3] = spec_32fcr->Buffs[3];          // W4_16
    spec_32fcr->Buffers[4] = spec_32fcr->Buffs[3] + 1;      // W2_16
    spec_32fcr->Buffers[5] = spec_32fcr->Buffs[3] + 2;      // W6_16
    spec_32fcr->Buffers[6] = spec_32fcr->Buffs[3] + 3;      // W1_16
    spec_32fcr->Buffers[7] = spec_32fcr->Buffs[3] + 4;      // W3_16
    spec_32fcr->Buffers[8] = spec_32fcr->Buffs[3] + 5;      // W5_16
    spec_32fcr->Buffers[9] = spec_32fcr->Buffs[3] + 6;      // W7_16
    spec_32fcr->Buffers[10] = spec_32fcr->Buffs[3] + 7;     // W2048

    *addr = spec_32fcr;

/********************************Fields Fulliling********************************/
    spec_32fcr->Buffers[0]->im = 0;
    spec_32fcr->Buffers[0]->re = 1.0;                    // 1.0

    spec_32fcr->Buffers[3]->im = -1.0;                   // W4_16
    spec_32fcr->Buffers[3]->re = -4.3711388286738e-08;

    spec_32fcr->Buffers[4]->im = -0.70710676908493;      // W2_16  
    spec_32fcr->Buffers[4]->re = 0.70710676908493;

    spec_32fcr->Buffers[5]->im = -0.70710676908493;      // W6_16
    spec_32fcr->Buffers[5]->re = -0.70710676908493;

    spec_32fcr->Buffers[6]->im = -0.38268345594406;      // W1_16
    spec_32fcr->Buffers[6]->re = 0.9238795042038;

    spec_32fcr->Buffers[7]->im = -0.9238795042038;       // W3_16
    spec_32fcr->Buffers[7]->re = 0.38268342614174;

    spec_32fcr->Buffers[8]->im = -0.9238795042038;       // W5_16
    spec_32fcr->Buffers[8]->re = -0.38268342614174;

    spec_32fcr->Buffers[9]->im = -0.38268327713013;      // W7_16
    spec_32fcr->Buffers[9]->re = -0.92387962341309;

/************************************W2048*************************************/
    for(i = 0; i < 1024; i++) {
        alpha = (2 * pi * (float)i) / 2048.0;
        spec_32fcr->Buffers[10][i].im = -sinf(alpha);
        spec_32fcr->Buffers[10][i].re = cosf(alpha);
    }
    return 0;
}