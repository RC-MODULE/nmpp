#include "fft_32fc.h"
#include <malloc.h>

void nmppsFFT2048Inv_32fc(nm32fcr *ix2048, nm32fcr *iX2048, NmppsFFTSpec_32fc *ispec2048)
{
    nmppsFFT2048Fwd_32fc(ix2048, iX2048, ispec2048);
}
