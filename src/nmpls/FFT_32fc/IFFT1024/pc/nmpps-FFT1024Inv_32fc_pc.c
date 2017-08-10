#include "fft_32fc.h"
#include <malloc.h>

void nmppsFFT1024Inv_32fc(nm32fcr *ix1024, nm32fcr *iX1024, NmppsFFTSpec_32fc *ispec1024)
{
	nmppsFFT1024Fwd_32fc(ix1024, iX1024, ispec1024);
}
