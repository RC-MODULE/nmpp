#ifndef _FFT_32FC_H_INCLUDED_
#define _FFT_32FC_H_INCLUDED_

#ifdef __cplusplus
		extern "C" {
#endif

#include "nmtype.h"

typedef struct
{
    nm32fc *SinCos0;
    nm32fc *SinCos1;
    nm32fc *buff_fft;
    nm32fc *buff_fftxW;
    nm32fc *tmp_128;
    nm32fc *tmp_128xW;
    nm32fc *buff1024;
    nm32fc *buff2048_0;
    nm32fc *buff2048_1;
    nm32fc *w8_0;
    nm32fc *w8_1;
    nm32fc *w16_0;
    nm32fc *w16_1;
    nm32fc *w32_0;
    nm32fc *w32_1;
    nm32fc *w64_0;
    nm32fc *w64_1;
    nm32fc *w128;
    nm32fc *w256;
    nm32fc *w512;
    nm32fc *w1024;
} NmppsFFTSpec_32fc;

void nmppsDFT8Fwd_32fc(nm32fc *x8, nm32fc *X8, NmppsFFTSpec_32fc *spec8);
void nmppsFFT16Fwd_32fc(nm32fc *x16, nm32fc *X16, NmppsFFTSpec_32fc *spec16);
void nmppsFFT32Fwd_32fc(nm32fc *x32, nm32fc *X32, NmppsFFTSpec_32fc *spec32);
void nmppsFFT64Fwd_32fc(nm32fc *x64, nm32fc *X64, NmppsFFTSpec_32fc *spec64);
void nmppsFFT128Fwd_32fc(nm32fc *x128, nm32fc *X128, NmppsFFTSpec_32fc *spec128);
void nmppsFFT256Fwd_32fc(nm32fc *x256, nm32fc *X256, NmppsFFTSpec_32fc *spec256);
void nmppsFFT512Fwd_32fc(nm32fc *x512, nm32fc *X512, NmppsFFTSpec_32fc *spec512);
void nmppsFFT1024Fwd_32fc(nm32fc *x1024, nm32fc *X1024, NmppsFFTSpec_32fc *spec1024);
void nmppsFFT2048Fwd_32fc(nm32fc *x2048, nm32fc *X2048, NmppsFFTSpec_32fc *spec2048);

int nmppsFFT16FwdInitAlloc_32fc(NmppsFFTSpec_32fc **addr16);
int nmppsFFT32FwdInitAlloc_32fc(NmppsFFTSpec_32fc **addr32);
int nmppsFFT64FwdInitAlloc_32fc(NmppsFFTSpec_32fc **addr64);
int nmppsFFT128FwdInitAlloc_32fc(NmppsFFTSpec_32fc **addr128);
int nmppsFFT256FwdInitAlloc_32fc(NmppsFFTSpec_32fc **addr256);
int nmppsFFT512FwdInitAlloc_32fc(NmppsFFTSpec_32fc **addr512);
int nmppsFFT1024FwdInitAlloc_32fc(NmppsFFTSpec_32fc **addr1024);
int nmppsFFT2048FwdInitAlloc_32fc(NmppsFFTSpec_32fc **addr2048);

float nmppNormDiff_32fc(nm32fc *src, nm32fc *outInv1, int num);


#ifdef __cplusplus
		};
#endif

#endif // _FFT_32FC_H_INCLUDED_