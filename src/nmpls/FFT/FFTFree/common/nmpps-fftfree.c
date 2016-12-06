//#include "fft.h"


#include "time.h"
#include "malloc32.h"
#include "fft2.h"

	
void nmppsFFTFree(NmppsFFTSpec* spec )
{
	int i;
	if (spec){
		for(i=0; i<FFT_SPEC_NUM_BUFFERS; i++)
			//nmppsFree(spec->buffer[i]);
			spec->free(spec->buffer[i]);
		for(i=0; i<FFT_SPEC_NUM_TABLES; i++)
			//nmppsFree(spec->fftTable[i]);
			spec->free(spec->fftTable[i]);
		spec->free(spec);
	}
}	

void nmppsFFTResetSpec(NmppsFFTSpec* spec)
{
	int i;
	for(i=0; i<FFT_SPEC_NUM_BUFFERS; i++)
		spec->buffer[i]=0;
	for(i=0; i<FFT_SPEC_NUM_TABLES; i++)
		spec->fftTable[i]=0;
	for(i=0; i<FFT_SPEC_NUM_SHIFTS; i++)
		spec->shift[i]=0;
	for(i=0; i<FFT_SPEC_NUM_AMPLITUDES; i++)
		spec->amp[i]=0;
	spec->free=nmppsFree;
	
}

//};