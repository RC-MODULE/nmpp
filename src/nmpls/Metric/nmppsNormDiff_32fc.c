#include "fft_32fc.h"

float nmppsNormDiff_32fc(nm32fc *src, nm32fc *outInv1, int num)
{
    int i;
    float SKO_dft32;
    SKO_dft32 = 0;
    for(i = 0; i < num; i++) {
       SKO_dft32 += (src[i].re - outInv1[i].re) * (src[i].re - outInv1[i].re);
       SKO_dft32 += (src[i].im - outInv1[i].im) * (src[i].im - outInv1[i].im);
    }
    SKO_dft32 = SKO_dft32 / 2*num;
    SKO_dft32 = sqrtf(SKO_dft32);
    return SKO_dft32;
}
