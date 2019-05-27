//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software                      */
//*                                                                         */
//*   Software design:  A.Brodyazhenko                                      */
//*                                                                         */
//*   File:             nmpps-FFT64Inv_32fcr.c                              */
//*   Contents:         Routine for inverse FFT 64                          */
//*                     of complex array with 32 bit elements				*/
//***************************************************************************/

#include "fft_32fcr.h"

void nmppsFFT64Inv_32fcr(const nm32fcr* pSrcVec, nm32fcr* pDstVec, NmppsFFTSpec_32fcr* spec)
{
    nmppsFFT64Fwd_32fcr(pSrcVec, pDstVec, spec);
}
