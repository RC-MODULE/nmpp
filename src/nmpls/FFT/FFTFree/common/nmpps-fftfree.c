//#include "fft.h"


#include "time.h"
#include "malloc32.h"
#include "fft2.h"

	
void nmppsFFTFree(NmppsFFTSpec* spec )
{
	if (spec){
		nmppsFree(spec->buffer[0]);
		nmppsFree(spec->buffer[1]);
		nmppsFree(spec->fftTable[0]);
		nmppsFree(spec->fftTable[1]);
		nmppsFree(spec->fftTable[2]);
		nmppsFree(spec->fftTable[3]);

		nmppsFree(spec);
	}
}	


//};