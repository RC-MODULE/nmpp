#include <malloc.h>
#include <math.h>
#include "fft_32fc.h"

int nmppsFFT256InvInitAlloc_32fc(NmppsFFTSpec_32fc **iaddr256)
{
    int i, j, k;
    int gr1;
    const float pi = 3.141592653;
    float alpha;
    nm32fcr *SinCos = (nm32fcr *) malloc(64 * sizeof(nm32fcr));
    NmppsFFTSpec_32fc *spec_32fc = (NmppsFFTSpec_32fc *) malloc(sizeof(NmppsFFTSpec_32fc));
    if(!spec_32fc) {
        return -1;
    }
    spec_32fc->Buffs[0] = (nm32fcr *) malloc((32+8+16+32+64) * sizeof(nm32fcr));
    if(!spec_32fc->Buffs[0])
        return -2;

    spec_32fc->Buffers[0] = spec_32fc->Buffs[0];       // SinCos0
    spec_32fc->Buffers[4] = spec_32fc->Buffs[0] + 32;  // W8_0
    spec_32fc->Buffers[6] = spec_32fc->Buffs[0] + 40;  // W16_0
    spec_32fc->Buffers[8] = spec_32fc->Buffs[0] + 56;  // W32_0
    spec_32fc->Buffers[10] = spec_32fc->Buffs[0] + 88; // W64_0

    spec_32fc->Buffs[1] = (nm32fcr *) malloc1((32 + 128) * sizeof(nm32fcr));
    if(!spec_32fc->Buffs[1])
        return -3;
    
    spec_32fc->Buffers[1] = spec_32fc->Buffs[1];      // SinCos1
    spec_32fc->Buffers[2] = spec_32fc->Buffs[1] + 32; // buff_fft

    spec_32fc->Buffs[2] = (nm32fcr *) malloc2((128) * sizeof(nm32fcr));
    if(!spec_32fc->Buffs[2])
        return -4;

    spec_32fc->Buffers[3] = spec_32fc->Buffs[2]; // buff_fftxW

    spec_32fc->Buffs[3] = (nm32fcr *) malloc3((8 + 16 + 32 + 64 + 128) * sizeof(nm32fcr));
    if(!spec_32fc->Buffs[3])
        return -5;

    spec_32fc->Buffers[5] = spec_32fc->Buffs[3];        // W8_1
    spec_32fc->Buffers[7] = spec_32fc->Buffs[3] + 8;    // W16_1
    spec_32fc->Buffers[9] = spec_32fc->Buffs[3] + 24;   // W32_1
    spec_32fc->Buffers[11] = spec_32fc->Buffs[3] + 56;  // W64_1
    spec_32fc->Buffers[12] = spec_32fc->Buffs[3] + 120; // W128
    *iaddr256 = spec_32fc;
    k = 0;
    for(i = 0; i <  8; i++) {
        for(j = 0; j < 64; j = j + 8) {
            alpha = (2 * pi * (float)i * (float)k) / 8.0;
            SinCos[i + j].im = sinf(alpha) * 0.00390625; // 1/256 = 0.00390625
            SinCos[i + j].re = cosf(alpha) * 0.00390625;
            k++;
        }
        k = 0;
    }
    for(i = 0; i < 32; i++) {
        spec_32fc->Buffers[0][i].im = SinCos[i].im;
        spec_32fc->Buffers[0][i].re = SinCos[i].re;
        spec_32fc->Buffers[1][i].im = SinCos[i + 32].im;
        spec_32fc->Buffers[1][i].re = SinCos[i + 32].re;
    }

    for(i = 0; i < 128; i++) {
        alpha = (0.024543692606 * (float)i);
        spec_32fc->Buffers[12][i].im = sinf(alpha);
        spec_32fc->Buffers[12][i].re = cosf(alpha);
    }
    gr1 = 0;
    for(i = 0; i < 8; i++) {
        spec_32fc->Buffers[4][i].im = spec_32fc->Buffers[12][gr1].im;
        spec_32fc->Buffers[4][i].re = spec_32fc->Buffers[12][gr1].re;
        spec_32fc->Buffers[5][i].im = spec_32fc->Buffers[12][gr1].im;
        spec_32fc->Buffers[5][i].re = spec_32fc->Buffers[12][gr1].re;

        gr1 += 16;
    }
    gr1 = 0;
    for(i = 0; i < 16; i++) {
        spec_32fc->Buffers[6][i].im = spec_32fc->Buffers[12][gr1].im;
        spec_32fc->Buffers[6][i].re = spec_32fc->Buffers[12][gr1].re;
        spec_32fc->Buffers[7][i].im = spec_32fc->Buffers[12][gr1].im;
        spec_32fc->Buffers[7][i].re = spec_32fc->Buffers[12][gr1].re;
        gr1 += 8;
    }
    gr1 = 0;
    for(i = 0; i < 32; i++) {
        spec_32fc->Buffers[8][i].im = spec_32fc->Buffers[12][gr1].im;
        spec_32fc->Buffers[8][i].re = spec_32fc->Buffers[12][gr1].re;
        spec_32fc->Buffers[9][i].im = spec_32fc->Buffers[12][gr1].im;
        spec_32fc->Buffers[9][i].re = spec_32fc->Buffers[12][gr1].re;
        gr1 += 4;
    }
    gr1 = 0;
    for(i = 0; i < 64; i++) {
        spec_32fc->Buffers[10][i].im = spec_32fc->Buffers[12][gr1].im;
        spec_32fc->Buffers[10][i].re = spec_32fc->Buffers[12][gr1].re;
        spec_32fc->Buffers[11][i].im = spec_32fc->Buffers[12][gr1].im;
        spec_32fc->Buffers[11][i].re = spec_32fc->Buffers[12][gr1].re;
        gr1 += 2;
    }
    free(SinCos);
    return 0;
}