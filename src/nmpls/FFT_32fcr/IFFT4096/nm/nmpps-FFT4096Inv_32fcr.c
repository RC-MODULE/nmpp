
#include "nmpp.h"
#include "fft_32fcr.h"

void LastLayerFFT_32fcr(const nm32fcr* src1, const nm32fcr* src2, nm32fcr* dst, const nm32fcr *W4096, int N);

void nmppsFFT4096Inv_32fcr(const nm32fcr* ix, nm32fcr* iX, NmppsFFTSpec_32fcr* ispec)
{
	nmppsSplit_32fcr(ix, ispec->Buffers[12], ispec->Buffers[13], 4096);
	nmppsFFT2048Inv_32fcr(ispec->Buffers[12], ispec->Buffers[14], ispec);
	nmppsFFT2048Inv_32fcr(ispec->Buffers[13], ispec->Buffers[12], ispec);
	LastLayerFFT_32fcr(ispec->Buffers[14], ispec->Buffers[12], iX, ispec->Buffers[15], 32);
}