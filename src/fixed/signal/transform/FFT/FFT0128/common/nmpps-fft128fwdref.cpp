//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM6403 Software                      */
//*                                                                         */
//*   Fast Fourie Transform Library                                         */
//*                                                                         */
//*   File:             pcFFT256.cpp                                        */
//*   Contents:         C++ Equivalent function of the FFT_Fwd256.          */
//*                     Additional FFT256 functions using                   */
//*                         fixed and floating-point arithmetic             */ 
//*                                                                         */
//*   Software design:  S.Mushkaev                                          */
//*                                                                         */
//*   Start date:       15.01.2001                                          */
//*   Last update :     -                                                   */
//*                                                                         */
//*                                                                         */
//***************************************************************************/

//#include "internal.h"
#include "fft.h"
//#include "fftext.h"
#include "nmtl/tcmplx_spec.h"
#include <math.h>

#ifndef PI
#define PI 3.14159265359
#endif


cmplx<double> W128(int power)
{
	cmplx<double> z(0,-2.0*PI*power/128.0);
	return exp(z);
}

cmplx<int > toFix(cmplx<double> X,double Ampl);





void nmppsFFT128FwdRef_f( nm32sc* src, nm32sc* dst)
{
	vec<cmplx<double> > x(128);
	vec<cmplx<double> > y(128);
	
	for(int i=0; i<128; i++){
		x[i].re=src[i].re;
		x[i].im=src[i].im;
	}
	for(int k=0; k<128; k++){
		y[k]=W128(0)*x[0];
		for(int n=1; n<128; n++){
			y[k]+=W128(n*k)*x[n];
		}
	}
	for(int i=0; i<128; i++){
		dst[i].re=floor(y[i].re+0.5);
		dst[i].im=floor(y[i].im+0.5);
	}
}




void nmppsFFT128FwdRef288_f( nm32sc* src, nm32sc* dst)
{
	vec<cmplx<double> > x(128);
	vec<cmplx<double> > y(128);
	vec<cmplx<double> > s(128);
	vec<cmplx<double> > d(128);
	

	for(int i=0; i<128; i++){
		x[i].re=src[i].re;
		x[i].im=src[i].im;
		y[i].re=0;
		y[i].im=0;
		s[i].re=0;
		s[i].im=0;
		d[i].re=0;
		d[i].im=0;
	}

//------ initial scheme -------------------------
// 	for(int k=0; k<128; k++){
// 		for(int m=0; m<8; m++){
// 			for(int p=0; p<8; p++){
// 				for(int n=0; n<2; n++){
// 					y[k]+=W128(m*k)*W128(8*p*k)*W128(64*n*k)*x[64*n+8*p+m];
// 				}
// 			}
// 		}
// 	}
//------ intermediate scheme 1 -------------------------
// 	for(int k=0; k<2; k++){
// 		for(int m=0; m<8; m++){
// 			for(int p=0; p<8; p++){
// 				for(int n=0; n<2; n++){
// 					s[64*k+8*p+m]+=W128(64*n*k)*x[64*n+8*p+m];
// 				}
// 			}
// 		}
// 	}	
// 	for(int k=0; k<128; k++){
// 		for(int m=0; m<8; m++){
// 			for(int p=0; p<8; p++){
// 				y[k]+=W128(m*k)*W128(8*p*k)*s[64*(k%2)+8*p+m];
// 			}
// 		}
// 	}
	//------- final scheme  ------------------------	
	for(int k=0; k<2; k++){
		for(int m=0; m<8; m++){
			for(int p=0; p<8; p++){
				for(int n=0; n<2; n++){
					s[64*k+8*p+m]+=W128(64*n*k)*x[64*n+8*p+m];
				}
			}
		}
	}	
	for(int k=0; k<16; k++){
		for(int m=0; m<8; m++){
			for(int p=0; p<8; p++){
				d[k*8+m]+=W128(8*p*k)*s[64*(k%2)+8*p+m];
			}
		}
	}
	for(int k=0; k<128; k++){
		for(int m=0; m<8; m++){
			y[k]+=W128(m*k)*d[8*(k%16)+m];
		}
	}
	//-------- rounding -----------------------
	for(int i=0; i<128; i++){
		dst[i].re=floor(y[i].re+0.5);
		dst[i].im=floor(y[i].im+0.5);
	}
}

void nmppsFFT128FwdRef288(nm32sc*	src, nm32sc*	dst)
{
	//---------------------
	int SHR1=7;
	int SHR2=7;
	int MAX1=1<<SHR1;
	int MAX2=1<<SHR2;

	//---------------------
	vec<cmplx<int> > x((cmplx<int>*)src,128);
	vec<cmplx<int> > y((cmplx<int>*)dst,128);
	vec<cmplx<int> > s(128);
	vec<cmplx<int> > d(128);

	for(int i=0; i<128; i++){
		y[i].re=0;
		y[i].im=0;
		d[i].re=0;
		d[i].im=0;
	}
	//-------- stage0 ------------------------ 2*rep64= 128 ticks
	for(int i=0; i<64; i++){
		s[i]   =x[i]+x[64+i];
		s[64+i]=x[i]-x[64+i];
	}

	//-------- stage 1 ---------------------- 16*rep8*2  =256 ticks + 128 Tics(conjg)
// 	for(int k=0; k<16; k++){
// 		for(int m=0; m<8; m++){
// 			for(int p=0; p<8; p++){
// 				d[k*8+m]+=toFix(W128(8*p*k),MAX1)*s[64*(k%2)+8*p+m];
// 			}
// 		}
// 	}
	for(int m=0; m<8; m++){
		for(int p=0; p<8; p++){
			d[0 *8+m]+=toFix(W128(8*p*(0 )),MAX1)*s[8*p+m];
			d[2 *8+m]+=toFix(W128(8*p*(2 )),MAX1)*s[8*p+m];
			d[4 *8+m]+=toFix(W128(8*p*(4 )),MAX1)*s[8*p+m];
			d[6 *8+m]+=toFix(W128(8*p*(6 )),MAX1)*s[8*p+m];
			d[8 *8+m]+=toFix(W128(8*p*(8 )),MAX1)*s[8*p+m];
			d[10*8+m]+=toFix(W128(8*p*(10)),MAX1)*s[8*p+m];
			d[12*8+m]+=toFix(W128(8*p*(12)),MAX1)*s[8*p+m];
			d[14*8+m]+=toFix(W128(8*p*(14)),MAX1)*s[8*p+m];
			
			d[1 *8+m]+=toFix(W128(8*p*(1 )),MAX1)*s[64+8*p+m];
			d[3 *8+m]+=toFix(W128(8*p*(3 )),MAX1)*s[64+8*p+m];
			d[5 *8+m]+=toFix(W128(8*p*(5 )),MAX1)*s[64+8*p+m];
			d[7 *8+m]+=toFix(W128(8*p*(7 )),MAX1)*s[64+8*p+m];
			d[9 *8+m]+=toFix(W128(8*p*(9 )),MAX1)*s[64+8*p+m];
			d[11*8+m]+=toFix(W128(8*p*(11)),MAX1)*s[64+8*p+m];
			d[13*8+m]+=toFix(W128(8*p*(13)),MAX1)*s[64+8*p+m];
			d[15*8+m]+=toFix(W128(8*p*(15)),MAX1)*s[64+8*p+m];
		}
	}
	//-------- stage 1 (norm) -------------- 4*rep32 = 128 Ticks
	for(int i=0; i<128; i++){
		d[i].re  =(d[i].re + MAX1/2)>>SHR1;
		d[i].im  =(d[i].im + MAX1/2)>>SHR1;
	}
	
	//-------- stage 2 --------------------- 16*rep8*2 = 256 Ticks + 128 Ticks(conjg)
// 	for(int k=0; k<128; k++){
// 		for(int m=0; m<8; m++){
// 			y[k]+=toFix(W128(m*k),MAX2)*d[8*(k%16)+m];
// 		}
// 	}
//                     equal to:
// 	for(int n=0; n<8; n++){
// 		for(int k=0; k<16; k++){
// 			for(int m=0; m<8; m++){
// 				y[16*n+k]+=toFix(W128(m*(16*n+k)),MAX2)*d[8*((16*n+k)%16)+m];
// 			}
// 		}
// 	}
	for(int k=0; k<16; k++){
		for(int m=0; m<8; m++){
			y[16*0+k]+=toFix(W128(m*(16*0+k)),MAX2)*d[8*k+m];
			y[16*1+k]+=toFix(W128(m*(16*1+k)),MAX2)*d[8*k+m];
			y[16*2+k]+=toFix(W128(m*(16*2+k)),MAX2)*d[8*k+m];
			y[16*3+k]+=toFix(W128(m*(16*3+k)),MAX2)*d[8*k+m];
			y[16*4+k]+=toFix(W128(m*(16*4+k)),MAX2)*d[8*k+m];
			y[16*5+k]+=toFix(W128(m*(16*5+k)),MAX2)*d[8*k+m];
			y[16*6+k]+=toFix(W128(m*(16*6+k)),MAX2)*d[8*k+m];
			y[16*7+k]+=toFix(W128(m*(16*7+k)),MAX2)*d[8*k+m];
		}
	}

	//-------- stage 2 (norm) -------------- 2*rep64 = 128Ticks
	for(int i=0; i<128; i++){
		y[i].re  =(y[i].re + MAX2/2)>>SHR2;
		y[i].im  =(y[i].im + MAX2/2)>>SHR2;
	}
	// TOTAL = 128+(256+128+128)+(256+128+128)= 1152 Ticks
	// TABLE = 16*8*2+128*8*2 = 2304 Coeffs
}




