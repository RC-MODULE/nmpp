//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software                      */
//*                                                                         */
//*   Software design:  A.Brodyazhenko                                      */
//*                                                                         */
//*   File:             nmpps-FFT128Inv_32fcr.c                             */
//*   Contents:         Routine for inverse FFT 128                         */
//*                     of complex array with 32 bit elements				*/
//***************************************************************************/

#include "fft_32fcr.h"

void nmppsFFT128Inv_32fcr(const nm32fcr* pSrcVec, nm32fcr* pDstVec, NmppsFFTSpec_32fcr* spec)
{
	nmppsFFT128Fwd_32fcr(pSrcVec, pDstVec, spec);
}
