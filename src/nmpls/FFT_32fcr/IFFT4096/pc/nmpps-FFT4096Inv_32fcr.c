//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software                      */
//*                                                                         */
//*   Software design:  A.Brodyazhenko                                      */
//*                                                                         */
//*   File:             nmpps-FFT4096Inv_32fcr.c                            */
//*   Contents:         Routine for inverse FFT 4096                        */
//*                     of complex array with 32 bit elements				*/
//***************************************************************************/

#include "fft_32fcr.h"
#include <malloc.h>

void nmppsFFT4096Inv_32fcr(const nm32fcr* pSrcVec, nm32fcr* pDstVec, NmppsFFTSpec_32fcr* spec)
{
    nmppsFFT4096Fwd_32fcr(pSrcVec, pDstVec, spec);
}
