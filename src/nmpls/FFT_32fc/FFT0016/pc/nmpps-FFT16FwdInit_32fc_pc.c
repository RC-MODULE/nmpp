#include "fft_32fc.h"
#include <malloc.h>
#include <math.h>

int nmppsFFT16FwdInitAlloc_32fc(NmppsFFTSpec_32fc **addr16)
{
    int i, j, k;
    float alpha;
    const float pi = 3.141592653;
    NmppsFFTSpec_32fc *spec_32fc = (NmppsFFTSpec_32fc *) malloc(sizeof(NmppsFFTSpec_32fc));
    if(spec_32fc == 0) {
        return -1;
    }
    spec_32fc->Buffers[0] = (nm32fcr *) malloc(64 * sizeof(nm32fcr)); // SinCos0
    if(!spec_32fc->Buffers[0]) {
        return -2;
    }
    spec_32fc->Buffers[1] = (nm32fcr *) malloc(8 * sizeof(nm32fcr)); // W8_0
    if(!spec_32fc->Buffers[1]) {
        return -3;
    }
    *addr16 = spec_32fc;
    for(i = 0; i <  8; i++) {
        for(j = 0; j < 64; j = j + 8) {
            alpha = (2 * pi * (float)i * (float)k) / 8.0;
            spec_32fc->Buffers[0][i + j].im = -sinf(alpha);
            spec_32fc->Buffers[0][i + j].re = cosf(alpha);
            k++;
        }
        k = 0;
    }
    for(i = 0; i < 8; i++) {
        alpha = 2 * pi * (float)i / 16;
        spec_32fc->Buffers[1][i].im = -sinf(alpha);
        spec_32fc->Buffers[1][i].re = cosf(alpha);
    }
    return 0;
}
