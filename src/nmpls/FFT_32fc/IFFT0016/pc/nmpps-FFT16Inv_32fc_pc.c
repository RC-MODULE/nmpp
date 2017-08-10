#include "fft_32fc.h"

void nmppsFFT16Inv_32fc(nm32fcr *ix16, nm32fcr *iX16, NmppsFFTSpec_32fc *ispec16)
{
    nmppsFFT16Fwd_32fc(ix16, iX16, ispec16);
}