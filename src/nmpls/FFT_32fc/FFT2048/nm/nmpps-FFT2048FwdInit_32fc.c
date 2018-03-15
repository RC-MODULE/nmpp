#include <malloc32.h>
#include <math.h>
#include "fft_32fc.h"

int nmppsFFT2048FwdInitAlloc_32fc(NmppsFFTSpec_32fc **addr2048)
{
    int i, j, k;
    const float pi = 3.141592653;
    float alpha;
    nm32fcr *SinCos = (nm32fcr *) malloc0(64 * sizeof(nm32fcr));
    NmppsFFTSpec_32fc *spec_32fc = (NmppsFFTSpec_32fc *) malloc(sizeof(NmppsFFTSpec_32fc));
    if(!spec_32fc) {
        return -1;
    }
    for(i = 0; i < NUMBUFF2; i++) {
        spec_32fc->Buffs[i] = 0;
    }
    spec_32fc->Buffs[0] = (nm32fcr *) malloc0((32 + 512 + 1024) * sizeof(nm32fcr));
    if(!spec_32fc->Buffs[0])
        return -2;

    spec_32fc->Buffers[0] = spec_32fc->Buffs[0];       // SinCos0
    spec_32fc->Buffers[6] = spec_32fc->Buffs[0] + 32;  // buff2048_1
    spec_32fc->Buffers[4] = spec_32fc->Buffs[0] + 544; // W1024

    spec_32fc->Buffs[1] = (nm32fcr *) malloc1((32 + 512) * sizeof(nm32fcr));
    if(!spec_32fc->Buffs[1])
        return -3;

    spec_32fc->Buffers[1] = spec_32fc->Buffs[1];       // SinCos1
    spec_32fc->Buffers[5] = spec_32fc->Buffs[1] + 32;  // buff2048_0

    spec_32fc->Buffs[2] = (nm32fcr *) malloc2(1024 * sizeof(nm32fcr));
    if(!spec_32fc->Buffs[2])
        return -4;

    spec_32fc->Buffers[2] = spec_32fc->Buffs[2]; // buff_fft

    spec_32fc->Buffs[3] = (nm32fcr *) malloc3(1024 * sizeof(nm32fcr));
    if(!spec_32fc->Buffs[3])
        return -5;

    spec_32fc->Buffers[3] = spec_32fc->Buffs[3]; // buff_fftxW

    *addr2048 = spec_32fc;
    k = 0;
    for(i = 0; i <  8; i++) {
        for(j = 0; j < 64; j = j + 8) {
            alpha = (2 * pi * (float)i * (float)k) / 8.0;
            SinCos[i + j].im = -sinf(alpha);
            SinCos[i + j].re = cosf(alpha);
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
    for(i = 0; i < 1024; i++) {
        alpha = (2 * pi * (float)i) / 2048.0;
        spec_32fc->Buffers[4][i].im = -sinf(alpha);
        spec_32fc->Buffers[4][i].re = cosf(alpha);
    }
    free(SinCos);
    return 0;
}