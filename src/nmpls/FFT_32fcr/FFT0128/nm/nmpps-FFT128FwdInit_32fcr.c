#include <malloc32.h>
#include <math.h>
#include "fft_32fcr.h"

int nmppsFFT128FwdInitAlloc_32fcr(NmppsFFTSpec_32fcr **addr)
{
	int i, j, k;
	int gr1;
	const float pi = 3.141592653;
    float alpha;
    nm32fcr *SinCos = (nm32fcr *) malloc0(64 * sizeof(nm32fcr));
	NmppsFFTSpec_32fcr *spec_32fcr = (NmppsFFTSpec_32fcr *) malloc(sizeof(NmppsFFTSpec_32fcr));
	if(!spec_32fcr) {
		return 0x128F;
	}
    for(i = 0; i < NUMBUFF2; i++) {
        spec_32fcr->Buffs[i] = 0;
    }
    spec_32fcr->Buffs[0] = (nm32fcr *) malloc0((8 + 16 + 32 + 64) * sizeof(nm32fcr));
    if(!spec_32fcr->Buffs[0])
        return 0x128F0;

    spec_32fcr->Buffers[4] = spec_32fcr->Buffs[0];	   // W8_0
    spec_32fcr->Buffers[6] = spec_32fcr->Buffs[0] + 8;   // W16_0
    spec_32fcr->Buffers[10] = spec_32fcr->Buffs[0] + 24; // W32_0
    spec_32fcr->Buffers[12] = spec_32fcr->Buffs[0] + 56; // W64_0

    spec_32fcr->Buffs[1] = (nm32fcr *) malloc1((32 + 8 + 16 + 32) * sizeof(nm32fcr));
    if(!spec_32fcr->Buffs[0])
        return 0x128F1;

    spec_32fcr->Buffers[1] = spec_32fcr->Buffs[1];	   // SinCos1
    spec_32fcr->Buffers[5] = spec_32fcr->Buffs[1] + 32;   // W8_1
    spec_32fcr->Buffers[7] = spec_32fcr->Buffs[1] + 40; // W16_1
    spec_32fcr->Buffers[11] = spec_32fcr->Buffs[1] + 56; // W32_1

    spec_32fcr->Buffs[2] = (nm32fcr *) malloc2((32 + 64 + 32) * sizeof(nm32fcr));
    if(!spec_32fcr->Buffs[0])
        return 0x128F2;

    spec_32fcr->Buffers[0] = spec_32fcr->Buffs[2];	   // SinCos0
    spec_32fcr->Buffers[2] = spec_32fcr->Buffs[2] + 32;   // buff_fft
    spec_32fcr->Buffers[9] = spec_32fcr->Buffs[2] + 96; // tmp_128xW

    spec_32fcr->Buffs[3] = (nm32fcr *) malloc3((64 + 32) * sizeof(nm32fcr));
    if(!spec_32fcr->Buffs[3])
        return 0x128F3;

    spec_32fcr->Buffers[3] = spec_32fcr->Buffs[3];	   // buff_fftxW
    spec_32fcr->Buffers[8] = spec_32fcr->Buffs[3] + 64;   // tmp_128
    
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
    for(i = 0; i < 64; i++) {
        alpha = (0.04908738521 * (float)i);
        spec_32fcr->Buffers[12][i].im = -sinf(alpha);
        spec_32fcr->Buffers[12][i].re = cosf(alpha);
    }
    gr1 = 0;
    for(i = 0; i < 8; i++) {
        spec_32fcr->Buffers[4][i].im = spec_32fcr->Buffers[12][gr1].im;
        spec_32fcr->Buffers[4][i].re = spec_32fcr->Buffers[12][gr1].re;
        spec_32fcr->Buffers[5][i].im = spec_32fcr->Buffers[12][gr1].im;
        spec_32fcr->Buffers[5][i].re = spec_32fcr->Buffers[12][gr1].re;
        gr1 += 8;
    }
    gr1 = 0;
    for(i = 0; i < 16; i++) {
        spec_32fcr->Buffers[6][i].im = spec_32fcr->Buffers[12][gr1].im;
        spec_32fcr->Buffers[6][i].re = spec_32fcr->Buffers[12][gr1].re;
        spec_32fcr->Buffers[7][i].im = spec_32fcr->Buffers[12][gr1].im;
        spec_32fcr->Buffers[7][i].re = spec_32fcr->Buffers[12][gr1].re;
        gr1 += 4;
    }
    gr1 = 0;
    for(i = 0; i < 32; i++) {
        spec_32fcr->Buffers[10][i].im = spec_32fcr->Buffers[12][gr1].im;
        spec_32fcr->Buffers[10][i].re = spec_32fcr->Buffers[12][gr1].re;
        spec_32fcr->Buffers[11][i].im = spec_32fcr->Buffers[12][gr1].im;
        spec_32fcr->Buffers[11][i].re = spec_32fcr->Buffers[12][gr1].re;
        gr1 += 2;
    }
    free(SinCos);
    return 0;
}