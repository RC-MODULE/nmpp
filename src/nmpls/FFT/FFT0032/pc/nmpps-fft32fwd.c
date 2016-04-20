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
	//------- stage 1 --------------
	//!for(int i=0; i<16; i++){
	//!	sum[i]=x[i]+x[i+16];
	//!	dif[i]=x[i]-x[i+16];
	//!}
	for(k=0; k<16; k++){
		ar1_lo[k].re=src[k].re+src[k+16].re;
		ar1_lo[k].im=src[k].im+src[k+16].im;
		ar2_lo[k].re=src[k].re-src[k+16].re;
		ar2_lo[k].im=src[k].im-src[k+16].im;
	}
	//------- stage 2 -------------
	//                     [ar1:lo]*[ar4:re]->[ar2:hi]
	//!for(int k=0; k<32; k+=2){
	//!	for(int p=0; p<16; p++){
	//!		y[k]+=toFix(W32(p*k),MAX)*sum[p];
	//!	}
	//!	y[k].re+=MAX/2;
	//!	y[k].im+=MAX/2;
	//!	y[k].re>>=7;
	//!	y[k].im>>=7;
	//!}
	// stage 2.1.1 sum(re|im)*w.re
	for(k=0; k<16; k++){ 	//rep 16 vsum ,data,0
		nm32sc afifo={0,0};
		for(p=0;p<8;p++,i++){
			afifo.re+=w[i] * ar1_lo[p].re;
			afifo.im+=w[i] * ar1_lo[p].im;
		}
		ar2_hi[k]=afifo;
	}
	// stage 2.1.2 sum(re|im)*w.re
	for(k=0; k<16; k++){	// rep 16 vsum ,data,afifo
		nm32sc afifo={0,0};
		for(p=8;p<16;p++,i++){
			afifo.re+=w[i] * ar1_lo[p].re;
			afifo.im+=w[i] * ar1_lo[p].im;
		}
		ar2_hi[k].re+=afifo.re;
		ar2_hi[k].im+=afifo.im;
	}
	//------------------------------
	//                     [ar1:lo]*[ar4:im]->[ar1:hi]
	// stage 2.1.3 sum(re|im)*w.im
	for(k=0; k<16; k++){	//rep 16 vsum ,data,0
		nm32sc afifo={0,0};
		for(p=0;p<8;p++,i++){
			afifo.re+=w[i] * ar1_lo[p].re;
			afifo.im+=w[i] * ar1_lo[p].im;
		}
		ar1_hi[k]=afifo;
	}
	// stage 2.1.4 sum(re|im)*w.im
	for(k=0; k<16; k++){	// rep 16 vsum ,data,afifo
		nm32sc afifo={0,0};
		for(p=8;p<16;p++,i++){
			afifo.re+=w[i] * ar1_lo[p].re;
			afifo.im+=w[i] * ar1_lo[p].im;
		}
		ar1_hi[k].re+=afifo.re;
		ar1_hi[k].im+=afifo.im;
	}
	//--------------------------------------------
	//                     [ar2:lo]*[ar4:re]->[ar1:lo]
	for(k=0; k<16; k++){
		nm32sc afifo={0,0};
		for( p=0;p<8;p++,i++){
			afifo.re+=w[i] * ar2_lo[p].re;
			afifo.im+=w[i] * ar2_lo[p].im;
		}
		ar1_lo[k]=afifo;
	}
	for(k=0; k<16; k++){
		nm32sc afifo={0,0};
		for( p=8;p<16;p++,i++){
			afifo.re+=w[i] * ar2_lo[p].re;
			afifo.im+=w[i] * ar2_lo[p].im;
		}
		ar1_lo[k].re+=afifo.re;
		ar1_lo[k].im+=afifo.im;
	}
	//----------------------------------------------
	//                     [ar2:lo]*[ar4:im]->[ar2:lo]					              
	for(k=0; k<16; k++){
		nm32sc afifo={0,0};
		for( p=0;p<8;p++,i++){
			afifo.re+=w[i] * ar2_lo[p].re;
			afifo.im+=w[i] * ar2_lo[p].im;
		}
		ar2_Lo[k]=afifo;
	}
	for(k=0; k<16; k++){
		nm32sc afifo={0,0};
		for( p=8;p<16;p++,i++){
			afifo.re+=w[i] * ar2_lo[p].re;
			afifo.im+=w[i] * ar2_lo[p].im;
		}
		ar2_Lo[k].re+=afifo.re;
		ar2_Lo[k].im+=afifo.im;
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


