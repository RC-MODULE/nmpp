#include "fft_32fcr.h"
#include <malloc.h>
#include <math.h>

int nmppsFFT16FwdInitAlloc_32fcr(NmppsFFTSpec_32fcr **addr16)
{
    int i, j, k;
    float alpha;
    const float pi = 3.141592653;
    NmppsFFTSpec_32fcr *spec_32fcr = (NmppsFFTSpec_32fcr *) malloc(sizeof(NmppsFFTSpec_32fcr));
    if(spec_32fcr == 0) {
        return 0xF16;
    }
    for(i = 0; i < NUMBUFF1; i++) {
        spec_32fcr->Buffers[i] = 0;
    }
    spec_32fcr->Buffers[0] = (nm32fcr *) malloc(64 * sizeof(nm32fcr)); // SinCos0
    if(!spec_32fcr->Buffers[0]) {
        return 0xF17;
    }
    spec_32fcr->Buffers[1] = (nm32fcr *) malloc(8 * sizeof(nm32fcr)); // W8_0
    if(!spec_32fcr->Buffers[1]) {
        return 0xF18;
    }
    *addr16 = spec_32fcr;
    k = 0;
    for(i = 0; i <  8; i++) {
        for(j = 0; j < 64; j = j + 8) {
            alpha = (2 * pi * (float)i * (float)k) / 8.0;
            spec_32fcr->Buffers[0][i + j].im = -sinf(alpha);
            spec_32fcr->Buffers[0][i + j].re = cosf(alpha);
            k++;
        }
        k = 0;
    }
    for(i = 0; i < 8; i++) {
        alpha = 2 * pi * (float)i / 16;
        spec_32fcr->Buffers[1][i].im = -sinf(alpha);
        spec_32fcr->Buffers[1][i].re = cosf(alpha);
    }
    return 0;
}
