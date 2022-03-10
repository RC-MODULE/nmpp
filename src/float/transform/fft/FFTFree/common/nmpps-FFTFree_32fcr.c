//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software                      */
//*                                                                         */
//*   Software design:  A.Brodyazhenko                                      */
//*                                                                         */
//*   File:             nmpps-FFTFree_32fcr.c                               */
//***************************************************************************/

#include <malloc.h>
#include "fft_32fcr.h"

int nmppsFFTFree_32fcr(NmppsFFTSpec_32fcr* spec)
{
	int i;
	if(spec) {
		#ifndef __NM__
		for(i = 0; i < NUMBUFF1; i++) {
			if(spec->Buffers[i]) {
				free(spec->Buffers[i]);
			}
		}
		#else
		for(i = 0; i < NUMBUFF2; i++) {
			if(spec->Buffs[i]) {
				free(spec->Buffs[i]);
			}
		}
		#endif
	} else {
		return 0xF6EE;
	}
	free(spec);
	return 0;
}