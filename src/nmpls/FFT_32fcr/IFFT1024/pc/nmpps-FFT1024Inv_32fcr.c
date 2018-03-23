#include "fft_32fcr.h"
#include <malloc.h>

void nmppsFFT1024Inv_32fcr(const nm32fcr *ix, nm32fcr *iX, NmppsFFTSpec_32fcr *ispec)
{
	nmppsFFT1024Fwd_32fcr(ix, iX, ispec);
}
