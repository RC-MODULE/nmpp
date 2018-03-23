#include "fft_32fcr.h"

void nmppsFFT16Inv_32fcr(const nm32fcr *ix, nm32fcr *iX, NmppsFFTSpec_32fcr *ispec)
{
    nmppsFFT16Fwd_32fcr(ix, iX, ispec);
}