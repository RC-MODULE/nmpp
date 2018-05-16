#include "fft_32fcr.h"

void nmppsFFT64Inv_32fcr(const nm32fcr *ix, nm32fcr *iX, NmppsFFTSpec_32fcr *ispec)
{
    nmppsFFT64Fwd_32fcr(ix, iX, ispec);
}
