//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software                      */
//*                                                                         */
//*   Software design:  S.Mushkaev                                          */
//*                                                                         */
//*                                                                         */
//***************************************************************************/

#include "fft.h"


// data-flow:
//[ar0:lo]+[ar0:hi] -> [ar1:lo]
//[ar0:lo]-[ar0:hi] -> [ar2:lo]
//                     [ar1:lo]*[ar4:re]->[ar2:hi]
//                     [ar1:lo]*[ar4:im]->[ar1:hi]
//                     [ar2:lo]*[ar4:re]->[ar1:lo]
//                     [ar2:lo]*[ar4:im]->[ar2:lo]					              
//                                        [ar1:lo]|[ar2:lo]->[ar6:odd ]
//                                        [ar1:hi]|[ar2:hi]->[ar6:even]

void nmppsFFT128FwdRaw(nm32sc*	src, nm32sc*	dst, NmppsFFTSpec*	spec)
{
	
}

void nmppsFFT128Fwd(nm32sc*	src, nm32sc*	dst, NmppsFFTSpec*	spec)
{
	int k;
	nmppsFFT128FwdRaw(src, dst, spec);
	
	for(k=0; k<128; k++){
		dst[k].re+=128;
		dst[k].im+=128;
		dst[k].re>>=7;
		dst[k].im>>=7;
	}
}


