#include <malloc.h>
#include "fft_32fc.h"

int nmppsFFTFree_32fc(NmppsFFTSpec_32fc *specN)
{
	int i;
	if(specN) {
		#ifndef __NM__
		for(i = 0; i < NUMBUFF1; i++) {
			if(specN->Buffers[i]) {
				free(specN->Buffers[i]);
			}
		}
		#else
		for(i = 0; i < NUMBUFF2; i++) {
			if(specN->Buffs[i]) {
				free(specN->Buffs[i]);
			}
		}
		#endif
	} else {
		return -1;
	}
	free(specN);
	return 0;
}