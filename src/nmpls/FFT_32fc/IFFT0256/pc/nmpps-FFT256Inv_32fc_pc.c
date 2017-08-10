#include "fft_32fc.h"

void nmppsFFT256Inv_32fc(nm32fcr *ix256, nm32fcr *iX256, NmppsFFTSpec_32fc *ispec256)
{
	nmppsFFT256Fwd_32fc(ix256, iX256, ispec256);
}
