//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software                      */
//*                                                                         */
//*   Software design:  S.Mushkaev                                          */
//*                                                                         */
//*                                                                         */
//***************************************************************************/

#include "fft.h"

#ifndef PI
#define PI 3.14159265359
#endif

nm32sc fixW64(int arg, int max);
	

void nmppsFFT64Fwd8x8Raw(const nm32sc*	src, nm32sc*	dst, const NmppsFFTSpec*	spec)
{
	int SHR1=16;
	int SHR2=7;
	int MAX1=1<<SHR1;
	int MAX2=1<<SHR2;
	
	
	nm32sc* green =(nm32sc*)spec->buffer[0]; 
	nm32sc* yellow=(nm32sc*)spec->buffer[1]; 
	nm32sc* red   =dst; 

	nm32sc* sLo=green;
	nm32sc* sHi=yellow;
	nm32sc* dRe=red;
	nm32sc* dIm=green;
	nm32sc* d=yellow;
	nm32sc* n=red;
	nm32sc* yRe=yellow;
	nm32sc* yIm=green;

	//nm32sc sLo[64]; 	// sLo and sHi should be palced in differnet banks
	//nm32sc sHi[64];
	//nm32sc dRe[64];
	//nm32sc dIm[64];
	//nm32sc d[64];
	//nm32sc n[64];
	//nm32sc yRe[64];
	//nm32sc yIm[64];
	//nm32sc y[64];
	
	nm32sc afifo;
	nm32sc w;
	
	char* w0    =(char*)spec->fftTable[0];
	char* w1    =(char*)spec->fftTable[1];
	int i=0;
	int m,p,k;

	//-------- stage0 ------------------------ 
	// [0]
	//for(int i=0; i<32; i++){
	//	s[i]   =x[i]+x[32+i];
	//	s[32+i]=x[i]-x[32+i];
	//}
	// [0.0] [rep32]
	for(k=0; k<32; k++){
		sLo[k].re=src[k].re+src[k+32].re;
		sLo[k].im=src[k].im+src[k+32].im;
	}
	// [0.1] [rep32]
	for(k=0; k<32; k++){
		sHi[k].re=src[k].re-src[k+32].re; 
		sHi[k].im=src[k].im-src[k+32].im;
	}	

	//-------- stage 1 ---------------------- 
	// stage [1.0.0] [4*rep8]
	
	for( m=0; m<8; m++){	// rep 8
		// [1.0.0.re]
		for( k=0; k<8; k+=2){	// rep 4
			nm32sc afifo={0,0};
			for(p=0; p<4; p++){	// vector-matrix mul dRe[4]=w[4].re*sLo[4x2]
				w=fixW64(8*p*k,MAX1);
				afifo.re+=w.re * sLo[8*p+m].re;
				afifo.im+=w.re * sLo[8*p+m].im;
			}
			dRe[8*k+m]=afifo;
		}
		
		// [1.0.0.im]
		for( k=0; k<8; k+=2){		// rep 4
			nm32sc afifo={0,0};
			for(p=0; p<4; p++){ // vector-matrix mul dIm[4]=w[4].im*sLo[4x2]
				w=fixW64(8*p*k,MAX1);
				afifo.re+=w.im * sLo[8*p+m].re;
				afifo.im+=w.im * sLo[8*p+m].im;
			}                
			dIm[8*k+m]=afifo;
		}		
	}
	// [1.0.1]
	for( m=0; m<8; m++){	// rep 8
		for( k=1; k<8; k+=2){		// rep 4
			nm32sc afifo={0,0};
			for(p=0; p<4; p++){
				w=fixW64(8*p*k,MAX1);
				afifo.re+=w.re * sHi[8*p+m].re;
				afifo.im+=w.re * sHi[8*p+m].im;
			}
			dRe[8*k+m]=afifo;
		}
		
		for( k=1; k<8; k+=2){		// rep 4
			nm32sc afifo={0,0};
			for(p=0; p<4; p++){
				w=fixW64(8*p*k,MAX1);
				afifo.re+=w.im * sHi[8*p+m].re;
				afifo.im+=w.im * sHi[8*p+m].im;
			}                
			dIm[8*k+m]=afifo;
		}
	}

	// stage 1.1 [2*rep32]
	for (i =0; i<64; i++){
		d[i].re = dRe[i].re - dIm[i].im + MAX1/2;
		d[i].im = dRe[i].im + dIm[i].re + MAX1/2;
	}
	// stage 1.2 [2*rep32]
	for (i =0; i<64; i++){
		n[i].re = d[i].re >> SHR1;
		n[i].im = d[i].im >> SHR1;
	}

	
	//---------- stage 2 -------------
	//!for(int p=0; p<8; p++){
	//!	for(int k=0; k<8; k++){
	//!		for(int m=0; m<8; m++){
	//!			y[k]+=W64(m*(8*p+k))*d[8*k+m];
	//!		}
	//!	}
	//!}
	// stage 2.0 [8*rep16]
	for( p=0; p<8; p++){
		for( k=0; k<8; k++){ 		// rep 8 data = [w] with vsum ,data,0
			nm32sc afifo={0,0};
			for( m=0; m<8; m++){	// rep 8 wfifo =[n]
				w=fixW64(m*(8*p+k),MAX2);
				afifo.re+=w.re * n[8*k+m].re; 
				afifo.im+=w.re * n[8*k+m].im; 
			}
			yRe[8*p+k]=afifo;
		}							// rep [yRe]=afifo;

		for( k=0; k<8; k++){ 		// rep 8 data = [w] with vsum ,data,0
			nm32sc afifo={0,0};
			for( m=0; m<8; m++){	// rep 8 wfifo =[n]
				w=fixW64(m*(8*p+k),MAX2);
				afifo.re+=w.im * n[8*k+m].re; 
				afifo.im+=w.im * n[8*k+m].im; 
			}
			yIm[8*p+k]=afifo;
		}							// rep [yIm]=afifo;
	}
	
	
	// stage 2.1 [2*rep32]
	for (i =0; i<64; i++){
		dst[i].re = yRe[i].re - yIm[i].im +MAX2/2;
		dst[i].im = yRe[i].im + yIm[i].re +MAX2/2;
	}
	//------------------------
	// stage 0.1   [rep32]
	// stage 0.2   [rep32]
	// stage 1.0.0 [4*rep8]
	// stage 1.1.0 [4*rep8]
	// stage 1.2   [2*rep32]
	// stage 1.3.0 [2*rep32]
	// stage 2.0   [8*rep8*2]
	// stage 2.1   [2*rep32]
	// TOTAL: 2*32+2*4*8+2*32*2+8*8*2+2*32=448
	// TICKS: 1043
	// КПД = 448/=42%
}

void nmppsFFT64Fwd(const nm32sc*	src, nm32sc*	dst, const NmppsFFTSpec*	spec)
{
	int k;
	nmppsFFT64Fwd8x8Raw(src, dst, spec);
	
	for(k=0; k<64; k++){
		//dst[k].re+=64;
		//dst[k].im+=64;
		dst[k].re>>=7;
		dst[k].im>>=7;
	}
}


