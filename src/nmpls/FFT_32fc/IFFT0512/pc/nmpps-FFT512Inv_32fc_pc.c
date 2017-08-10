#include "fft_32fc.h"
#include <malloc.h>

void nmppsFFT512Inv_32fc(nm32fcr *ix512, nm32fcr *iX512, NmppsFFTSpec_32fc *ispec512)
{
    nmppsFFT512Fwd_32fc(ix512, iX512, ispec512);
}
