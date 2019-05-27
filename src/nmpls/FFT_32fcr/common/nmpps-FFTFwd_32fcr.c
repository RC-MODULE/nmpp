//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software                      */
//*                                                                         */
//*   Software design:  A.Brodyazhenko                                      */
//*                                                                         */
//*   File:             nmpps-FFTFwd_32fcr.c                             	*/
//*   Contents:         Routine for forward FFT (32, 64, ..., 2048)         */
//*                     of complex array with 32 bit elements               */
//***************************************************************************/

#include "fft_32fcr.h"

//int nmppsFFTFwd_32fcr(const nm32fcr* pSrcVec, nm32fcr* pDstVec, NmppsFFTSpec_32fcr* spec)
//{
//	if(spec->order == 5) {
//		nmppsFFT32Fwd_32fcr(pSrcVec, pDstVec, spec);
//	} else if(spec->order == 6) {
//		nmppsFFT64Fwd_32fcr(pSrcVec, pDstVec, spec);
//	} else if(spec->order == 7) {
//		nmppsFFT128Fwd_32fcr(pSrcVec, pDstVec, spec);
//	} else if(spec->order == 8) {
//		nmppsFFT256Fwd_32fcr(pSrcVec, pDstVec, spec);
//	} else if(spec->order == 9) {
//		nmppsFFT512Fwd_32fcr(pSrcVec, pDstVec, spec);
//	} else if(spec->order == 10) {
//		nmppsFFT1024Fwd_32fcr(pSrcVec, pDstVec, spec);
//	} else if(spec->order == 11) {
//		nmppsFFT2048Fwd_32fcr(pSrcVec, pDstVec, spec);
//	} else { 
//		return -1;
//	}
//	return 0;
//}