#include "fft_32fcr.h"

void nmppsFFT256Inv_32fcr(const nm32fcr *ix, nm32fcr *iX, NmppsFFTSpec_32fcr *ispec)
{
	nmppsFFT256Fwd_32fcr(ix, iX, ispec);
}
