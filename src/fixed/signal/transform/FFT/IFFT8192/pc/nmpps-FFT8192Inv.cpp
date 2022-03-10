//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software                      */
//*                                                                         */
//*   Software design:  S.Mushkaev                                          */
//*                                                                         */
//*                                                                         */
//***************************************************************************/

#include "fft.h"
#include "nmpp.h"
#include "nmtl.h"
#include "fftexp.h"
extern "C"{

int nmppsFFT8192Inv28888Raw(const nm32sc* src, nm32sc* dst, const NmppsFFTSpec* spec)
{
	return nmppsFFT8192Fwd28888Raw(src, dst, spec);
}

int nmppsFFT8192Inv28888(const nm32sc* src, nm32sc* dst, const NmppsFFTSpec* spec)
{
	nmppsFFT8192Fwd28888Raw(src, dst, spec);

	//---------------------------------- 3.2 -----------------------------------------
	for(int i=0; i<8192; i++){
		dst[i].re=dst[i].re>>spec->shift[4];
		dst[i].im=dst[i].im>>spec->shift[4];
	}
	return 0;
}

};