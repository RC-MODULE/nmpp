#include "fft_32fc.h"

void nmppsFFT64Inv_32fc(nm32fcr *ix64, nm32fcr *iX64, NmppsFFTSpec_32fc *ispec64)
{
    nmppsFFT64Fwd_32fc(ix64, iX64, ispec64);
}
