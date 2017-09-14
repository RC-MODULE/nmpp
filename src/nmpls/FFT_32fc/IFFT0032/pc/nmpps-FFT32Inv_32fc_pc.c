#include "fft_32fc.h"

void nmppsFFT32Inv_32fc(nm32fcr *ix32, nm32fcr *iX32, NmppsFFTSpec_32fc *ispec32)
{
    nmppsFFT32Fwd_32fc(ix32, iX32, ispec32);
}
