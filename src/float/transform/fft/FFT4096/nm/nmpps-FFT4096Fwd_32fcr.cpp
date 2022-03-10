//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software                      */
//*                                                                         */
//*   Software design:  A.Brodyazhenko                                      */
//*                                                                         */
//*   File:             nmpps-FFT4096Fwd_32fcr.c                            */
//*   Contents:         Routine for forward and inverse FFT 4096            */
//*                     of complex array with 32 bit elements               */
//***************************************************************************/

#include "nmpp.h"
#include "fft_32fcr.h"

extern "C"{

void LastLayerFFT_32fcr(const nm32fcr* src1, const nm32fcr* src2, nm32fcr* dst, const nm32fcr *W4096, int N);


void nmppsFFT4096Fwd_32fcr(const nm32fcr* pSrcVec, nm32fcr* pDstVec, NmppsFFTSpec_32fcr* spec)
{
	nmppsSplit_32fcr(pSrcVec, spec->Buffers[12], spec->Buffers[13], 4096);
	nmppsFFT2048Fwd_32fcr(spec->Buffers[12], spec->Buffers[14], spec);
	nmppsFFT2048Fwd_32fcr(spec->Buffers[13], spec->Buffers[12], spec);
    LastLayerFFT_32fcr(spec->Buffers[14], spec->Buffers[12], pDstVec, spec->Buffers[15], 32);
}

};