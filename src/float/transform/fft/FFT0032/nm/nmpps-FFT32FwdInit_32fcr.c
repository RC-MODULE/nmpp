#include <malloc32.h>
#include <math.h>
#include "fft_32fcr.h"

int nmppsFFT32FwdInitAlloc_32fcr(NmppsFFTSpec_32fcr **addr)
{
    int i, j, k;
    int gr1;
    const float pi = 3.1415926535;
    float alpha;
    nm32fcr *SinCos = (nm32fcr *) malloc0(64 * sizeof(nm32fcr));
    NmppsFFTSpec_32fcr *spec_32fcr = (NmppsFFTSpec_32fcr *) malloc(sizeof(NmppsFFTSpec_32fcr));
    if(!spec_32fcr) {
        return 0x32F;
    }
    spec_32fcr->Buffs[0] = (nm32fcr *) malloc0((32 + 8 + 16) * sizeof(nm32fcr)); // SinCos0, W8_0, W16_0
    if(!spec_32fcr->Buffs[0])
        return 0x32F0;

    spec_32fcr->Buffers[0] = spec_32fcr->Buffs[0];
    spec_32fcr->Buffers[4] = spec_32fcr->Buffs[0] + 32;
    spec_32fcr->Buffers[5] = spec_32fcr->Buffs[0] + 40;

    spec_32fcr->Buffs[1] = (nm32fcr *) malloc1(32 * sizeof(nm32fcr)); // SinCos1
    if(!spec_32fcr->Buffs[1])
        return 0x32F1;

    spec_32fcr->Buffers[1] = spec_32fcr->Buffs[1];

    spec_32fcr->Buffs[2] = (nm32fcr *) malloc2(16 * sizeof(nm32fcr)); // buff_fft
    if(!spec_32fcr->Buffs[2])
        return 0x32F2;

    spec_32fcr->Buffers[2] = spec_32fcr->Buffs[2];

    spec_32fcr->Buffs[3] = (nm32fcr *) malloc3(16 * sizeof(nm32fcr)); // buff_fftxW
    if(!spec_32fcr->Buffs[3])
        return 0x32F3;

    spec_32fcr->Buffers[3] = spec_32fcr->Buffs[3];
    *addr = spec_32fcr;
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
        spec_32fcr->Buffers[0][i].im = SinCos[i].im;
        spec_32fcr->Buffers[0][i].re = SinCos[i].re;
        spec_32fcr->Buffers[1][i].im = SinCos[i + 32].im;
        spec_32fcr->Buffers[1][i].re = SinCos[i + 32].re;
    }
    for(i = 0; i < 16; i++) {
        alpha = (0.196349540849 * (float)i);
        spec_32fcr->Buffers[5][i].im = -sinf(alpha);
        spec_32fcr->Buffers[5][i].re = cosf(alpha);
    }
    gr1 = 0;
    for(i = 0; i < 8; i++) {
        spec_32fcr->Buffers[4][i].im = spec_32fcr->Buffers[5][gr1].im;
        spec_32fcr->Buffers[4][i].re = spec_32fcr->Buffers[5][gr1].re;
        gr1 += 2;
    }
    free(SinCos);
    return 0;
}