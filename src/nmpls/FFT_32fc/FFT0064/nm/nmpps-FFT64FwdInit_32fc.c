#include <malloc.h>
#include <math.h>
//float sinf(float);
//float cosf(float);

#include "fft_32fc.h"

int nmppsFFT64FwdInitAlloc_32fc(NmppsFFTSpec_32fc **addr64)
{
	int i, j, k;
	int gr1;
	const float pi = 3.141592653;
    float alpha;
    nm32fcr *SinCos = (nm32fcr *) malloc(64 * sizeof(nm32fcr));
	NmppsFFTSpec_32fc *ratios = (NmppsFFTSpec_32fc *) malloc(sizeof(NmppsFFTSpec_32fc));
	if(ratios == NULL) {
		return -1;
	}
	ratios->SinCos0 = (nm32fcr *) malloc(32 * sizeof(nm32fcr));
	if (ratios->SinCos0 == NULL)
		return -2;
	ratios->SinCos1 = (nm32fcr *) malloc1(32 * sizeof(nm32fcr));
	if (ratios->SinCos1 == NULL)
		return -3;
	ratios->buff_fft = (nm32fcr *) malloc2(32 * sizeof(nm32fcr));
	if (ratios->buff_fft == NULL)
		return -4;
	ratios->buff_fftxW = (nm32fcr *) malloc3(32 * sizeof(nm32fcr));
	if (ratios->buff_fftxW == NULL)
		return -5;
	ratios->w8_0 = (nm32fcr *) malloc1(8 * sizeof(nm32fcr));
	if (ratios->w8_0 == NULL)
		return -6;
	ratios->w16_0 = (nm32fcr *) malloc1(16 * sizeof(nm32fcr));
	if (ratios->w16_0 == NULL)
		return -7;
	ratios->w32_0 = (nm32fcr *) malloc1(32 * sizeof(nm32fcr));
	if (ratios->w32_0 == NULL)
		return -8;
	*addr64 = ratios;
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
        ratios->SinCos0[i].im = SinCos[i].im;
        ratios->SinCos0[i].re = SinCos[i].re;
        ratios->SinCos1[i].im = SinCos[i + 32].im;
        ratios->SinCos1[i].re = SinCos[i + 32].re;
    }
    for(i = 0; i < 32; i++) {
        alpha = (0.09817477042 * (float)i);
        ratios->w32_0[i].im = -sinf(alpha);
        ratios->w32_0[i].re = cosf(alpha);
    }
    gr1 = 0;
    for(i = 0; i < 8; i++) {
    	ratios->w8_0[i].im = ratios->w32_0[gr1].im;
    	ratios->w8_0[i].re = ratios->w32_0[gr1].re;
    	gr1 += 4;
    }
    gr1 = 0;
    for(i = 0; i < 16; i++) {
    	ratios->w16_0[i].im = ratios->w32_0[gr1].im;
    	ratios->w16_0[i].re = ratios->w32_0[gr1].re;
    	gr1 += 2;
    }
    free(SinCos);
    return 0;
}