#include <malloc.h>
#include <math.h>
#include "fft_32fc.h"

int nmppsFFT512InvInitAlloc_32fc(NmppsFFTSpec_32fc **iaddr512)
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

    spec_32fc->Buffs[0] = (nm32fcr *) malloc((8 + 16) * sizeof(nm32fcr));
    if(!spec_32fc->Buffs[0])
        return -2;

    spec_32fc->Buffers[4] = spec_32fc->Buffs[0];     // W8_0
    spec_32fc->Buffers[6] = spec_32fc->Buffs[0] + 8; // W16_0

    spec_32fc->Buffs[1] = (nm32fcr *) malloc1((32 + 8 + 16 + 256) * sizeof(nm32fcr));
    if(!spec_32fc->Buffs[1])
        return -2;

    spec_32fc->Buffers[1] = spec_32fc->Buffs[1];            // SinCos1
    spec_32fc->Buffers[5] = spec_32fc->Buffs[1] + 32; // W8_1
    spec_32fc->Buffers[7] = spec_32fc->Buffs[1] + 40; // W16_1
    spec_32fc->Buffers[8] = spec_32fc->Buffs[1] + 56; // W256

    spec_32fc->Buffs[2] = (nm32fcr *) malloc2((32 + 256) * sizeof(nm32fcr));
    if(!spec_32fc->Buffs[2])
        return -2;

    spec_32fc->Buffers[0] = spec_32fc->Buffs[2];      // SinCos0
    spec_32fc->Buffers[2] = spec_32fc->Buffs[2] + 32; // buff_fft

    spec_32fc->Buffs[3] = (nm32fcr *) malloc3(256 * sizeof(nm32fcr));
    if(!spec_32fc->Buffs[3])
        return -2;

    spec_32fc->Buffers[3] = spec_32fc->Buffs[3]; // buff_fftxW

    *iaddr512 = spec_32fc;
    k = 0;
    for(i = 0; i <  8; i++) {
        for(j = 0; j < 64; j = j + 8) {
            alpha = (2 * pi * (float)i * (float)k) / 8.0;
            SinCos[i + j].im = sinf(alpha) * 0.001953125; // 1/512 = 0.001953125
            SinCos[i + j].re = cosf(alpha) * 0.001953125;
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
    for(i = 0; i < 256; i++) {
        alpha = (0.0122718463 * (float)i);
        spec_32fc->Buffers[8][i].im = sinf(alpha);
        spec_32fc->Buffers[8][i].re = cosf(alpha);
    }
    gr1 = 0;
    for(i = 0; i < 8; i++) {
        spec_32fc->Buffers[4][i].im = spec_32fc->Buffers[8][gr1].im;
        spec_32fc->Buffers[4][i].re = spec_32fc->Buffers[8][gr1].re;
        spec_32fc->Buffers[5][i].im = spec_32fc->Buffers[8][gr1].im;
        spec_32fc->Buffers[5][i].re = spec_32fc->Buffers[8][gr1].re;
        gr1 += 32;
    }
    gr1 = 0;
    for(i = 0; i < 16; i++) {
        spec_32fc->Buffers[6][i].im = spec_32fc->Buffers[8][gr1].im;
        spec_32fc->Buffers[6][i].re = spec_32fc->Buffers[8][gr1].re;
        spec_32fc->Buffers[7][i].im = spec_32fc->Buffers[8][gr1].im;
        spec_32fc->Buffers[7][i].re = spec_32fc->Buffers[8][gr1].re;
        gr1 += 16;
    }
    free(SinCos);
    return 0;
}