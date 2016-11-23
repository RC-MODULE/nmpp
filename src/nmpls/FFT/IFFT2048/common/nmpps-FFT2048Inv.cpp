//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software                      */
//*                                                                         */
//*   Software design:  S.Mushkaev                                          */
//*                                                                         */
//*                                                                         */
//***************************************************************************/

#include "fft2.h"
#include "fftexp.h"
#include "nmpp.h"

extern "C"{

	void nmppsFFT2048Inv(const nm32sc* src, nm32sc* dst, const NmppsFFTSpec* spec)
	{
		nmppsFFT2048Fwd(src, dst, spec);
	}

	void nmppsFFT2048InvRaw(const nm32sc* src, nm32sc* dst, const NmppsFFTSpec* spec)
	{
		nmppsFFT2048FwdRaw(src, dst, spec);
	}


};