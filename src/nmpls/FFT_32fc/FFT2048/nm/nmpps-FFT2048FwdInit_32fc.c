#include <malloc.h>
//#include <math.h>
#include "fft_32fc.h"

float sinf(float);
float cosf(float);

int nmppsFFT2048FwdInitAlloc_32fc(NmppsFFTSpec_32fc **addr2048)
{
	int i, j, k;
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
	ratios->buff_fft = (nm32fc *) malloc2(1024 * sizeof(nm32fc));
	if (ratios->buff_fft == NULL)
		return -4;
	ratios->buff_fftxW = (nm32fc *) malloc3(1024 * sizeof(nm32fc));
	if (ratios->buff_fftxW == NULL)
		return -5;
    ratios->buff2048_0 = (nm32fc *) malloc1(512 * sizeof(nm32fc));
    if (ratios->buff2048_0 == NULL)
        return -6;
	ratios->buff2048_1 = (nm32fc *) malloc(512 * sizeof(nm32fc));
	if (ratios->buff2048_1 == NULL)
		return -7;
	ratios->w1024 = (nm32fc *) malloc(1024 * sizeof(nm32fc));
	if (ratios->w1024 == NULL)
		return -8;
	*addr2048 = ratios;
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
    for(i = 0; i < 1024; i++) {
        alpha = (2 * pi * (float)i) / 2048.0;
        ratios->w1024[i].im = -sinf(alpha);
        ratios->w1024[i].re = cosf(alpha);
    }
    free(SinCos);
    return 0;
}