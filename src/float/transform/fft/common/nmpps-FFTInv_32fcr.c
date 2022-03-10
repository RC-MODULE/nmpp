//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software                      */
//*                                                                         */
//*   Software design:  A.Brodyazhenko                                      */
//*                                                                         */
//*   File:             nmpps-FFTInv_32fcr.c                             */
//*   Contents:         Routine for inverse FFT (32, 64, ..., 2048)         */
//*                     of complex array with 32 bit elements               */                                                        */
//***************************************************************************/

#include "fft_32fcr.h"

int nmppsFFTInv_32fcr(const nm32fcr* pSrcVec, nm32fcr* pDstVec, NmppsFFTSpec_32fcr* spec)
{
	if(spec->order == 5) {
		nmppsFFT32Inv_32fcr(pSrcVec, pDstVec, spec);
	} else if(spec->order == 6) {
		nmppsFFT64Inv_32fcr(pSrcVec, pDstVec, spec);
	} else if(spec->order == 7) {
		nmppsFFT128Inv_32fcr(pSrcVec, pDstVec, spec);
	} else if(spec->order == 8) {
		nmppsFFT256Inv_32fcr(pSrcVec, pDstVec, spec);
	} else if(spec->order == 9) {
		nmppsFFT512Inv_32fcr(pSrcVec, pDstVec, spec);
	} else if(spec->order == 10) {
		nmppsFFT1024Inv_32fcr(pSrcVec, pDstVec, spec);
	} else if(spec->order == 11) {
		nmppsFFT2048Inv_32fcr(pSrcVec, pDstVec, spec);
	} else { 
		return -1;
	}
	return 0;
}
