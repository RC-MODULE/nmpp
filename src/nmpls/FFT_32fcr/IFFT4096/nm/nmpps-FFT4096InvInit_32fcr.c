//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software                      */
//*                                                                         */
//*   Software design:  A.Brodyazhenko                                      */
//*                                                                         */
//*   File:             nmpps-FFT4096InvInit_32fcr.c                        */
//*   Contents:         Routine for the struct initializing                 */
//*                     of the W-coefficient for FFT4096Inv                 */
//***************************************************************************/


#include <malloc32.h>
#include <math.h>
#include "fft_32fcr.h"

int nmppsFFT4096InvInitAlloc_32fcr(NmppsFFTSpec_32fcr** addr)
{
    int i;
    const float pi = 3.141592653;
    float alpha;
    NmppsFFTSpec_32fcr *spec_32fcr;

    int status = nmppsFFT2048InvInitAlloc_32fcr(&spec_32fcr);
    if(status) return 0x4096B0;

    spec_32fcr->Buffers[12] = (nm32fcr *) malloc0((2048) * sizeof(nm32fcr)); // buff_fft4096
    if(!spec_32fcr->Buffers[12])
        return 0x4096B1;

    spec_32fcr->Buffers[13] = (nm32fcr *) malloc1((2048) * sizeof(nm32fcr)); // buff_fft4096xW
    if(!spec_32fcr->Buffers[13])
        return 0x4096B2;

    spec_32fcr->Buffers[14] = (nm32fcr *) malloc2((2048) * sizeof(nm32fcr)); // buff_fft4096_addi
    if(!spec_32fcr->Buffers[14])
        return 0x4096B3;

    spec_32fcr->Buffers[15] = (nm32fcr *) malloc3((2048) * sizeof(nm32fcr)); // W4096
    if(!spec_32fcr->Buffers[15])
        return 0x4096B4;

    *addr = spec_32fcr;

    spec_32fcr->Buffers[0]->re = 0.000244140625;

    for(i = 0; i < 2048; i++) {
        alpha = (2.0 * pi * (float)i) / 4096.0;
        spec_32fcr->Buffers[15][i].im = sinf(alpha);
        spec_32fcr->Buffers[15][i].re = cosf(alpha);
    }
    return 0;
}