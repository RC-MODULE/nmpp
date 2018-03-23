#include <malloc32.h>
#include <math.h>
#include "fft_32fcr.h"

int nmppsFFT256FwdInitAlloc_32fcr(NmppsFFTSpec_32fcr **addr)
{
    int i;
    int offset = 0;
    float alpha;
    NmppsFFTSpec_32fcr *spec_32fcr = (NmppsFFTSpec_32fcr *) malloc(sizeof(NmppsFFTSpec_32fcr));
    if(!spec_32fcr) {
        return -1;
    }

/**********************************Bank1**********************************/
    spec_32fcr->Buffs[0] = (nm32fcr *) malloc0((64 + 128) * sizeof(nm32fcr));
    if(!spec_32fcr->Buffs[0])
        return -2;

    spec_32fcr->Buffers[11] = spec_32fcr->Buffs[0];         // W64_0
    spec_32fcr->Buffers[10] = spec_32fcr->Buffs[0] + 64;    // W128

    spec_32fcr->Buffs[1] = (nm32fcr *) malloc1((7 + 64) * sizeof(nm32fcr));
    if(!spec_32fcr->Buffs[1])
        return -3;
    
    spec_32fcr->Buffers[3] = spec_32fcr->Buffs[1];          // W4_16
    spec_32fcr->Buffers[4] = spec_32fcr->Buffs[1] + 1;      // W2_16
    spec_32fcr->Buffers[5] = spec_32fcr->Buffs[1] + 2;      // W6_16
    spec_32fcr->Buffers[6] = spec_32fcr->Buffs[1] + 3;      // W1_16
    spec_32fcr->Buffers[7] = spec_32fcr->Buffs[1] + 4;      // W3_16
    spec_32fcr->Buffers[8] = spec_32fcr->Buffs[1] + 5;      // W5_16
    spec_32fcr->Buffers[9] = spec_32fcr->Buffs[1] + 6;      // W7_16
    spec_32fcr->Buffers[12] = spec_32fcr->Buffs[1] + 7;     // W64_1

/**********************************Bank2**********************************/
    spec_32fcr->Buffs[2] = (nm32fcr *) malloc2((128) * sizeof(nm32fcr));
    if(!spec_32fcr->Buffs[2])
        return -4;

    spec_32fcr->Buffers[1] = spec_32fcr->Buffs[2];          // buff_fft

/**********************************Bank3**********************************/
    spec_32fcr->Buffs[3] = (nm32fcr *) malloc3((128 + 1) * sizeof(nm32fcr));
    if(!spec_32fcr->Buffs[3])
        return -5;

    spec_32fcr->Buffers[2] = spec_32fcr->Buffs[3];        // buff_fftxW
    spec_32fcr->Buffers[0] = spec_32fcr->Buffs[3] + 128;  // 1.0

    *addr = spec_32fcr;

/**********************************Fields Fuliling**********************************/
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

    spec_32fcr->Buffers[0]->im = 0;
    spec_32fcr->Buffers[0]->re = 1.0; // 1.0 for any FFTFwd (1/N for FFTInv on the N-samples)

/**********************************W128**********************************/
    for(i = 0; i < 128; i++) {
        alpha = (0.02454369 * (float)i);
        spec_32fcr->Buffers[10][i].im = -sinf(alpha);
        spec_32fcr->Buffers[10][i].re = cosf(alpha);
    }

/*******************************W64_0, W64_1**********************************/
    for(i = 0; i < 64; i++) {
        spec_32fcr->Buffers[11][i].im = spec_32fcr->Buffers[10][offset].im;
        spec_32fcr->Buffers[11][i].re = spec_32fcr->Buffers[10][offset].re;
        spec_32fcr->Buffers[12][i].im = spec_32fcr->Buffers[10][offset].im;
        spec_32fcr->Buffers[12][i].re = spec_32fcr->Buffers[10][offset].re;
        offset += 2;
    }
    return 0;
}