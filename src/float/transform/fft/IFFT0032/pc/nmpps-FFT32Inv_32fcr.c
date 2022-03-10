//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software                      */
//*                                                                         */
//*   Software design:  A.Brodyazhenko                                      */
//*                                                                         */
//*   File:             nmpps-FFT32Inv_32fcr.c                              */
//*   Contents:         Routine for inverse FFT 32                          */
//*                     of complex array with 32 bit elements				*/
//***************************************************************************/

#include "fft_32fcr.h"

void nmppsFFT32Inv_32fcr(const nm32fcr* pSrcVec, nm32fcr* pDstVec, NmppsFFTSpec_32fcr* spec)
{
    nmppsFFT32Fwd_32fcr(pSrcVec, pDstVec, spec);
}
