//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software                      */
//*                                                                         */
//*   Software design:  A.Brodyazhenko                                      */
//*                                                                         */
//*   File:             nmpps-FFT4096FwdInit_32fcr.c                        */
//*   Contents:         Routine for the struct initialization               */
//*                     of the W-coefficients for FFT2048Fwd                */
//***************************************************************************/

#include "math.h"
#include "nmpp.h"
#include "malloc32.h"
#include "fft_32fcr.h"

int nmppsFFT4096FwdInitAlloc_32fcr(NmppsFFTSpec_32fcr** addr)
{
    int i;
    const float pi = 3.141592653;
    float alpha;
    NmppsFFTSpec_32fcr *spec_32fcr;

    int status = nmppsFFT2048FwdInitAlloc_32fcr(&spec_32fcr);
    if(status) return 0x4096F0;

    spec_32fcr->Buffers[12] = (nm32fcr *) malloc0((2048) * sizeof(nm32fcr)); // buff_fft4096
    if(!spec_32fcr->Buffers[12])
        return 0x4096F1;

	spec_32fcr->Buffers[13] = (nm32fcr *) malloc1((2048) * sizeof(nm32fcr)); // buff_fft4096xW
    if(!spec_32fcr->Buffers[13])
        return 0x4096F2;

    spec_32fcr->Buffers[14] = (nm32fcr *) malloc2((2048) * sizeof(nm32fcr)); // buff_fft4096_addi
    if(!spec_32fcr->Buffers[14])
        return 0x4096F3;

	spec_32fcr->Buffers[15] = (nm32fcr *) malloc3((2048) * sizeof(nm32fcr)); // W4096
    if(!spec_32fcr->Buffers[15])
        return 0x4096F4;

    *addr = spec_32fcr;

    for(i = 0; i < 2048; i++) {
        alpha = (2.0 * pi * (float)i) / 4096.0;
        spec_32fcr->Buffers[15][i].im = -sinf(alpha);
        spec_32fcr->Buffers[15][i].re = cosf(alpha);
    }

    return 0;
}