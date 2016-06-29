//#include "fft.h"


#include "time.h"
#include "malloc32.h"
#include "fft2.h"

	
void nmppsFFTFree(NmppsFFTSpec* spec )
{
	if (spec){
		spec->free(spec->buffer[0]);
		spec->free(spec->buffer[1]);
		spec->free(spec->buffer[2]);
		spec->free(spec->buffer[3]);
		free(spec);
	}
}	


//};