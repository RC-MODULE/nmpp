#include "fft_32fcr.h"
#include <malloc.h>

void nmppsFFT2048Inv_32fcr(const nm32fcr *ix, nm32fcr *iX, NmppsFFTSpec_32fcr *ispec)
{
    nmppsFFT2048Fwd_32fcr(ix, iX, ispec);
}
