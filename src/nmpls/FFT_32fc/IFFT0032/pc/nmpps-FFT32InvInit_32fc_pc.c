#include "fft_32fc.h"
#include <malloc.h>
#include <math.h>

int nmppsFFT32InvInitAlloc_32fc(NmppsFFTSpec_32fc **iaddr32)
{
    int i, j, k;
    int gr1;
    const float pi = 3.141592653;
    float alpha;
    NmppsFFTSpec_32fc *spec_32fc = (NmppsFFTSpec_32fc *) malloc(sizeof(NmppsFFTSpec_32fc));
    if(!spec_32fc) {
        return -1;
    }
    for(i = 0; i < NUMBUFF1; i++) {
    	spec_32fc->Buffers[i] = 0;
    }
    spec_32fc->Buffers[0] = (nm32fcr *) malloc(64 * sizeof(nm32fcr)); // SinCos0
    if (!spec_32fc->Buffers[0])
        return -2;
    spec_32fc->Buffers[1] = (nm32fcr *) malloc(8 * sizeof(nm32fcr)); // W8_0
    if (!spec_32fc->Buffers[1])
        return -3;
    spec_32fc->Buffers[2] = (nm32fcr *) malloc(16 * sizeof(nm32fcr)); // W16_0
    if (!spec_32fc->Buffers[2])
        return -4;
	k = 0;
    *iaddr32 = spec_32fc;
    for(i = 0; i <  8; i++) {
        for(j = 0; j < 64; j = j + 8) {
            alpha = (2 * pi * (float)i * (float)k) / 8.0;
            spec_32fc->Buffers[0][i + j].im = sinf(alpha) / 32.0;
            spec_32fc->Buffers[0][i + j].re = cosf(alpha) / 32.0;
            k++;
        }
        k = 0;
    }
    for(i = 0; i < 16; i++) {
        alpha = (2 * pi * (float)i) / 32.0;
        spec_32fc->Buffers[2][i].im = sinf(alpha);
        spec_32fc->Buffers[2][i].re = cosf(alpha);
    }
    gr1 = 0;
    for(i = 0; i < 8; i++) {
        spec_32fc->Buffers[1][i].im = spec_32fc->Buffers[2][gr1].im;
        spec_32fc->Buffers[1][i].re = spec_32fc->Buffers[2][gr1].re;
        gr1 += 2;
    }
    return 0;
}
