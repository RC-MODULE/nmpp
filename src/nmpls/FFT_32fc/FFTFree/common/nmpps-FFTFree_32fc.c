#include <malloc.h>
#include "fft_32fc.h"

int nmppsFFTFree_32fc(NmppsFFTSpec_32fc *spec)
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
		return -1;
	}
	free(spec);
	return 0;
}