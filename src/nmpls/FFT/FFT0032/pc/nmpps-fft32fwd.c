//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software                      */
//*                                                                         */
//*   Software design:  S.Mushkaev                                          */
//*                                                                         */
//*                                                                         */
//***************************************************************************/

#include "fft2.h"

// data-flow:
//[ar0:lo]+[ar0:hi] -> [ar1:lo]
//[ar0:lo]-[ar0:hi] -> [ar2:lo]
//                     [ar1:lo]*[ar4:re]->[ar2:hi]
//                     [ar1:lo]*[ar4:im]->[ar1:hi]
//                     [ar2:lo]*[ar4:re]->[ar1:lo]
//                     [ar2:lo]*[ar4:im]->[ar2:lo]					              
//                                        [ar1:lo]|[ar2:lo]->[ar6:odd ]
//                                        [ar1:hi]|[ar2:hi]->[ar6:even]

void nmppsFFT32FwdRaw(nm32sc*	src, nm32sc*	dst, NmppsFFTSpec*	spec)
{
	nm32sc* ar1_lo=(nm32sc*)spec->buffer[0];
	nm32sc* ar1_hi=ar1_lo+16;
	nm32sc* ar2_lo=(nm32sc*)spec->buffer[1];
	nm32sc* ar2_hi=ar2_lo+16;
	char* w       =(char*)spec->fftTable[0];
	int i=0;
	int k;
	int p;
	nm32sc ar2_Lo[16];
	//[ar0:lo]+[ar0:hi] -> [ar1:lo]
	//[ar0:lo]-[ar0:hi] -> [ar2:lo]
	for(k=0; k<16; k++){
		ar1_lo[k].re=src[k].re+src[k+16].re;
		ar1_lo[k].im=src[k].im+src[k+16].im;
		ar2_lo[k].re=src[k].re-src[k+16].re;
		ar2_lo[k].im=src[k].im-src[k+16].im;
	}
	//--------------------------------
	//                     [ar1:lo]*[ar4:re]->[ar2:hi]
	for(k=0; k<16; k++){
		ar2_hi[k].re=0;
		ar2_hi[k].im=0;
		for(p=0;p<8;p++,i++){
			ar2_hi[k].re+=ar1_lo[p].re*w[i];
			ar2_hi[k].im+=ar1_lo[p].im*w[i];
		}
	}
	for(k=0; k<16; k++){
		for(p=8;p<16;p++,i++){
			ar2_hi[k].re+=ar1_lo[p].re*w[i];
			ar2_hi[k].im+=ar1_lo[p].im*w[i];
		}
	}
	//------------------------------
	//                     [ar1:lo]*[ar4:im]->[ar1:hi]
	for(k=0; k<16; k++){
		ar1_hi[k].re=0;
		ar1_hi[k].im=0;
		for(p=0;p<8;p++,i++){
			ar1_hi[k].re+=ar1_lo[p].re*w[i];
			ar1_hi[k].im+=ar1_lo[p].im*w[i];
		}
	}
	for(k=0; k<16; k++){
		for(p=8;p<16;p++,i++){
			ar1_hi[k].re+=ar1_lo[p].re*w[i];
			ar1_hi[k].im+=ar1_lo[p].im*w[i];
		}
	}
	//--------------------------------------------
	//                     [ar2:lo]*[ar4:re]->[ar1:lo]
	for(k=0; k<16; k++){
		ar1_lo[k].re=0;
		ar1_lo[k].im=0;
		for( p=0;p<8;p++,i++){
			ar1_lo[k].re+=ar2_lo[p].re*w[i];
			ar1_lo[k].im+=ar2_lo[p].im*w[i];
		}
	}
	for(k=0; k<16; k++){
		for( p=8;p<16;p++,i++){
			ar1_lo[k].re+=ar2_lo[p].re*w[i];
			ar1_lo[k].im+=ar2_lo[p].im*w[i];
		}
	}
	//----------------------------------------------
	//                     [ar2:lo]*[ar4:im]->[ar2:lo]					              
	for(k=0; k<16; k++){
		ar2_Lo[k].re=0;
		ar2_Lo[k].im=0;
		for( p=0;p<8;p++,i++){
			ar2_Lo[k].re+=ar2_lo[p].re*w[i];
			ar2_Lo[k].im+=ar2_lo[p].im*w[i];
		}
	}
	for(k=0; k<16; k++){
		for( p=8;p<16;p++,i++){
			ar2_Lo[k].re+=ar2_lo[p].re*w[i];
			ar2_Lo[k].im+=ar2_lo[p].im*w[i];
		}
	}
	//------------------------------------
	//										[ar1:hi]|[ar2:hi]->[ar6:even]
	for(k=0; k<16; k++){
		dst[2*k].re=ar2_hi[k].re-ar1_hi[k].im;
		dst[2*k].im=ar2_hi[k].im+ar1_hi[k].re;
	}
	//------------------------------------
	//                                        [ar1:lo]|[ar2:lo]->[ar6:odd ]
	for(k=0; k<16; k++){
		dst[2*k+1].re=ar1_lo[k].re-ar2_Lo[k].im;
		dst[2*k+1].im=ar1_lo[k].im+ar2_Lo[k].re;
	}
}

void nmppsFFT32Fwd(nm32sc*	src, nm32sc*	dst, NmppsFFTSpec*	spec)
{
	int k;
	nmppsFFT32FwdRaw(src, dst, spec);
	
	for(k=0; k<32; k++){
		dst[k].re+=64;
		dst[k].im+=64;
		dst[k].re>>=7;
		dst[k].im>>=7;
	}
}


