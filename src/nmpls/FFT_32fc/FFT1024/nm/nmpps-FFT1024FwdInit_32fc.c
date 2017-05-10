#include <malloc.h>
//#include <math.h>
#include "fft_32fc.h"

float sinf(float);
float cosf(float);

int nmppsFFT1024FwdInitAlloc_32fc(NmppsFFTSpec_32fc **addr1024)
{
	int i, j, k;
	int gr1;
	const float pi = 3.141592653;
    float alpha;
    nm32fc *SinCos = (nm32fc *) malloc(64 * sizeof(nm32fc));
	NmppsFFTSpec_32fc *ratios = (NmppsFFTSpec_32fc *) malloc(sizeof(NmppsFFTSpec_32fc));
	if(ratios == NULL) {
		return -1;
	}
	ratios->SinCos0 = (nm32fc *) malloc(32 * sizeof(nm32fc));
	if (ratios->SinCos0 == NULL)
		return -2;
	ratios->SinCos1 = (nm32fc *) malloc1(32 * sizeof(nm32fc));
	if (ratios->SinCos1 == NULL)
		return -3;
	ratios->buff_fft = (nm32fc *) malloc2(512 * sizeof(nm32fc));
	if (ratios->buff_fft == NULL)
		return -2;
	ratios->buff_fftxW = (nm32fc *) malloc3(512 * sizeof(nm32fc));
	if (ratios->buff_fftxW == NULL)
		return -3;
    ratios->buff1024 = (nm32fc *) malloc1(512 * sizeof(nm32fc));
    if (ratios->buff1024 == NULL)
        return -3;
	ratios->w8_0 = (nm32fc *) malloc(8 * sizeof(nm32fc));
	if (ratios->w8_0 == NULL)
		return -4;
	ratios->w8_1 = (nm32fc *) malloc1(8 * sizeof(nm32fc));
	if (ratios->w8_1 == NULL)
		return -5;
	ratios->w512 = (nm32fc *) malloc(512 * sizeof(nm32fc));
	if (ratios->w512 == NULL)
		return -6;
	*addr1024 = ratios;
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
    for(i = 0; i < 512; i++) {
        alpha = (2 * pi * (float)i) / 1024.0;
        ratios->w512[i].im = -sinf(alpha);
        ratios->w512[i].re = cosf(alpha);
    }
    gr1 = 0;
    for(i = 0; i < 8; i++) {
        ratios->w8_0[i].im = ratios->w512[gr1].im;
        ratios->w8_0[i].re = ratios->w512[gr1].re;
        ratios->w8_1[i].im = ratios->w512[gr1].im;
        ratios->w8_1[i].re = ratios->w512[gr1].re;
        gr1 += 64;
    }
    free(SinCos);
    return 0;
}