#include <malloc32.h>
#include <math.h>
#include "fft_32fcr.h"

int nmppsFFT64InvInitAlloc_32fcr(NmppsFFTSpec_32fcr **iaddr)
{
	int i, j, k;
	int gr1;
	const float pi = 3.141592653;
    float alpha;
    nm32fcr *SinCos = (nm32fcr *) malloc0(64 * sizeof(nm32fcr));
	NmppsFFTSpec_32fcr *spec_32fcr = (NmppsFFTSpec_32fcr *) malloc(sizeof(NmppsFFTSpec_32fcr));
	if(!spec_32fcr) {
		return 0x64B;
	}
    for(i = 0; i <  NUMBUFF1; i++) {
        spec_32fcr->Buffers[i] = 0;
    }
    for(i = 0; i < NUMBUFF2; i++) {
        spec_32fcr->Buffs[i] = 0;

    }
    spec_32fcr->Buffs[0] = (nm32fcr *) malloc0(32 * sizeof(nm32fcr)); // SinCos0
    if(!spec_32fcr->Buffs[0])
        return 0x64B0;

    spec_32fcr->Buffers[0] = spec_32fcr->Buffs[0];

    spec_32fcr->Buffs[1] = (nm32fcr *) malloc1((32 + 8 + 16 + 32) * sizeof(nm32fcr)); // SinCos1, buff_fft
    if(!spec_32fcr->Buffs[1])
        return 0x64B1;
    
    spec_32fcr->Buffers[1] = spec_32fcr->Buffs[1];      // SinCos1
    spec_32fcr->Buffers[4] = spec_32fcr->Buffs[1] + 32; // W8_0
    spec_32fcr->Buffers[5] = spec_32fcr->Buffs[1] + 40; // W16_0
    spec_32fcr->Buffers[6] = spec_32fcr->Buffs[1] + 56; // W32_0

    spec_32fcr->Buffs[2] = (nm32fcr *) malloc2(32 * sizeof(nm32fcr));
    if(!spec_32fcr->Buffs[2])
        return 0x64B2;

    spec_32fcr->Buffers[2] = spec_32fcr->Buffs[2]; // buff_fft

    spec_32fcr->Buffs[3] = (nm32fcr *) malloc3(32 * sizeof(nm32fcr));
    if(!spec_32fcr->Buffs[3])
        return 0x64B3;

    spec_32fcr->Buffers[3] = spec_32fcr->Buffs[3]; // buff_fftxW

	*iaddr = spec_32fcr;
	k = 0;
    for(i = 0; i <  8; i++) {
        for(j = 0; j < 64; j = j + 8) {
            alpha = (2 * pi * (float)i * (float)k) / 8.0;
            SinCos[i + j].im = sinf(alpha) * 0.015625; // 1/64 = 0.015625
            SinCos[i + j].re = cosf(alpha) * 0.015625;
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
    for(i = 0; i < 32; i++) {
        alpha = (0.09817477042 * (float)i);
        spec_32fcr->Buffers[6][i].im = sinf(alpha);
        spec_32fcr->Buffers[6][i].re = cosf(alpha);
    }
    gr1 = 0;
    for(i = 0; i < 8; i++) {
    	spec_32fcr->Buffers[4][i].im = spec_32fcr->Buffers[6][gr1].im;
    	spec_32fcr->Buffers[4][i].re = spec_32fcr->Buffers[6][gr1].re;
    	gr1 += 4;
    }
    gr1 = 0;
    for(i = 0; i < 16; i++) {
    	spec_32fcr->Buffers[5][i].im = spec_32fcr->Buffers[6][gr1].im;
    	spec_32fcr->Buffers[5][i].re = spec_32fcr->Buffers[6][gr1].re;
    	gr1 += 2;
    }
    free(SinCos);
    return 0;
}