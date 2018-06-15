
#include "nmpp.h"
#include "fft_32fcr.h"

void LastLayerFFT_32fcr(const nm32fcr* src1, const nm32fcr* src2, nm32fcr* dst, const nm32fcr *W4096, int N);

void nmppsFFT4096Fwd_32fcr(const nm32fcr* x, nm32fcr* X, NmppsFFTSpec_32fcr* spec)
{
	nmppsSplit_32fcr(x, spec->Buffers[12], spec->Buffers[13], 4096);
	nmppsFFT2048Fwd_32fcr(spec->Buffers[12], spec->Buffers[14], spec);
	nmppsFFT2048Fwd_32fcr(spec->Buffers[13], spec->Buffers[12], spec);
	LastLayerFFT_32fcr(spec->Buffers[14], spec->Buffers[12], X, spec->Buffers[15], 16);
}