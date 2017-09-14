#include "fft_32fc.h"

void nmppsFFT128Inv_32fc(nm32fcr *ix128, nm32fcr *iX128, NmppsFFTSpec_32fc *ispec128)
{
	nmppsFFT128Fwd_32fc(ix128, iX128, ispec128);
}
