#include <malloc.h>
//#include <math.h>
#include "fft_32fc.h"
float sinf(float);
float cosf(float);

int nmppsFFT32FwdInitAlloc_32fc(NmppsFFTSpec_32fc **addr32)
{
	int i, j, k;
	int gr1;
	const float pi = 3.1415926535;
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
	ratios->buff_fft = (nm32fc *) malloc2(16 * sizeof(nm32fc));
	if (ratios->buff_fft == NULL)
		return -4;
	ratios->buff_fftxW = (nm32fc *) malloc3(16 * sizeof(nm32fc));
	if (ratios->buff_fftxW == NULL)
		return -5;
	ratios->w8_0 = (nm32fc *) malloc(8 * sizeof(nm32fc));
	if ( ratios->w8_0 == NULL)
		return -6;
	ratios->w16_0 = (nm32fc *) malloc(16 * sizeof(nm32fc));
	if (ratios->w16_0 == NULL)
		return -7;
	*addr32 = ratios;
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
    for(i = 0; i < 16; i++) {
        alpha = (0.196349540849 * (float)i);
        ratios->w16_0[i].im = -sinf(alpha);
        ratios->w16_0[i].re = cosf(alpha);
    }
    gr1 = 0;
    for(i = 0; i < 8; i++) {
    	ratios->w8_0[i].im = ratios->w16_0[gr1].im;
    	ratios->w8_0[i].re = ratios->w16_0[gr1].re;
    	gr1 += 2;
    }
    free(SinCos);
    return 0;
}