//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM6403 Software                      */
//*                                                                         */
//*   Fast Fourie Transform Library                                         */
//*                                                                         */
//*   File:             pcFFT256.cpp                                        */
//*   Contents:         C++ Equivalent function of the FFT_Fwd256.            */
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


cmplx<double> W64(int power)
{
	cmplx<double> z(0,-2.0*PI*power/64.0);
	return exp(z);
}



cmplx<int > toFix(cmplx<double> X,double Ampl);



void nmppsFFT64FwdRef64( nm32sc* src, nm32sc* dst)
{
	int MAX=128;
	vec<cmplx<int> > x((cmplx<int>*)src,64);
	vec<cmplx<int> > y((cmplx<int>*)dst,64);

	for(int k=0; k<64; k++){
		y[k]=toFix(W64(0),MAX)*x[0];
		for(int n=1; n<64; n++){
			y[k]+=toFix(W64(n*k),MAX)*x[n];
		}
		y[k].re+=MAX/2;
		y[k].im+=MAX/2;
		y[k].re>>=7;
		y[k].im>>=7;
	}
}

void nmppsFFT64FwdRef_f( nm32sc* src, nm32sc* dst)
{
	vec<cmplx<double> > x(64);
	vec<cmplx<double> > y(64);
	
	for(int i=0; i<64; i++){
		x[i].re=src[i].re;
		x[i].im=src[i].im;
	}
	for(int k=0; k<64; k++){
		y[k]=W64(0)*x[0];
		for(int n=1; n<64; n++){
			y[k]+=W64(n*k)*x[n];
		}
	}
	for(int i=0; i<64; i++){
		dst[i].re=floor(y[i].re+0.5);
		dst[i].im=floor(y[i].im+0.5);
	}
}

void nmppsFFT64FwdRef2x32_f( nm32sc* src, nm32sc* dst)
{
	vec<cmplx<double> > x(64);
	vec<cmplx<double> > y(64);
	vec<cmplx<double> > s(64);
	
	for(int i=0; i<64; i++){
		x[i].re=src[i].re;
		x[i].im=src[i].im;
		y[i].re=0;
		y[i].im=0;
		s[i].re=0;
		s[i].im=0;
	}
	

	for(int k=0; k<2; k++){
		for(int p=0; p<32; p++){
			for(int n=0; n<2; n++){
				s[32*k+p]+=W64(n*k*32)*x[32*n+p];
			}
		}
	}

	for(int k=0; k<64; k++){
		for(int p=0; p<32; p++){	
			y[k]+=W64(k*p)*s[32*(k%2)+p];
		}
	}

	for(int i=0; i<64; i++){
		dst[i].re=floor(y[i].re+0.5);
		dst[i].im=floor(y[i].im+0.5);
	}
}

/*
void nmppsFFT64FwdRef2x4õ8_f( nm32sc* src, nm32sc* dst)
{
	vec<cmplx<double> > x(64);
	vec<cmplx<double> > y(64);
	vec<cmplx<double> > s(64);
	vec<cmplx<double> > d(64);
	

	for(int i=0; i<64; i++){
		x[i].re=src[i].re;
		x[i].im=src[i].im;
		y[i].re=0;
		y[i].im=0;
		d[i].re=0;
		d[i].im=0;
	}

//------ initial scheme -------------------------
// 		for(int k=0; k<64; k++){
// 			for(int m=0; m<8; m++){
// 				for(int p=0; p<4; p++){
// 					for(int n=0; n<2; n++){
// 						y[k]+=W64(m*k)*W64(8*p*k)*W64(n*k*32)*x[32*n+8*p+m];
// 					}
// 				}
// 			}
// 		}
//------ intermediate scheme 1 -------------------------
// 		for(int k=0; k<2; k++){
// 			for(int m=0; m<8; m++){
// 				for(int p=0; p<4; p++){
// 					//y[k]+=W64(m*k)*W64(8*p*k)*(x[8*p+m]+W64(k*32)*x[32+8*p+m]);
// 					s[k*32+8*p+m]=x[8*p+m]+W64(32*k)*x[32+8*p+m];
// 				}
// 			}
// 		}
// 		
// 		for(int k=0; k<64; k++){
// 			for(int m=0; m<8; m++){
// 				for(int p=0; p<4; p++){
// 					y[k]+=W64(m*k)*W64(8*p*k)*W64(0*k*32)*s[32*(k%2)+8*p+m];
// 				}
// 			}
// 		}
//------- final scheme  ------------------------	
	for(int k=0; k<2; k++){
		for(int m=0; m<8; m++){
			for(int p=0; p<4; p++){
				s[32*k+8*p+m]=x[8*p+m]+W64(32*k)*x[32+8*p+m];
			}
		}
	}

	for(int k=0; k<8; k++){
		for(int m=0; m<8; m++){
			for(int p=0; p<4; p++){
				d[8*k+m]+=W64(8*p*k)*s[32*(k%2)+8*p+m];
			}
		}
	}

 	for(int k=0; k<64; k++){
 		for(int m=0; m<8; m++){
			y[k]+=W64(m*k)*d[8*(k%8)+m];
 		}
 	}
//-------- rounding -----------------------
	for(int i=0; i<64; i++){
		dst[i].re=floor(y[i].re+0.5);
		dst[i].im=floor(y[i].im+0.5);
	}
}
*/

void nmppsFFT64FwdRef2x4x8(nm32sc*	src, nm32sc*	dst)
{
	//--------------------- 
	int SHR1=16;
	int SHR2=7;
	int MAX1=1<<SHR1;
	int MAX2=1<<SHR2;

	//---------------------
	vec<cmplx<int> > x((cmplx<int>*)src,64);
	vec<cmplx<int> > y((cmplx<int>*)dst,64);
	vec<cmplx<int> > sLo(32);
	vec<cmplx<int> > sHi(32);
	vec<cmplx<int> > d(64);
	vec<cmplx<int> > n(64);

	for(int i=0; i<64; i++){
		y[i].re=0;
		y[i].im=0;
		d[i].re=0;
		d[i].im=0;
	}
	//-------- stage 0. ------------------------ 2*rep32= 64 ticks
	for(int i=0; i<32; i++){
		sLo[i]=x[i]+x[32+i];
	}
	for(int i=0; i<32; i++){
		sHi[i]=x[i]-x[32+i];
	}

	//-------- stage 1.0 ---------------------- 8*rep4*2  =64 ticks + 32Tics(conjg)
	//for(int k=0; k<8; k++){
	//	for(int m=0; m<8; m++){
	//		for(int p=0; p<4; p++){
	//			d[8*k+m]+=W64(8*p*k)*s[32*(k%2)+8*p+m];
	//		}
	//	}
	//}
	// [1.0.0]
	for(int k=0; k<8; k+=2){
		for(int m=0; m<8; m++){
			for(int p=0; p<4; p++){
				d[8*k+m]+=toFix(W64(8*p*k),MAX1)*sLo[8*p+m];
			}
		}
	}
	// [1.0.1]
	for(int k=1; k<8; k+=2){
		for(int m=0; m<8; m++){
			for(int p=0; p<4; p++){
				d[8*k+m]+=toFix(W64(8*p*k),MAX1)*sHi[8*p+m];
			}
		}
	}

	//-------- stage 1.1 (norm) -------------- 2*rep32 = 64Ticks
	for(int i=0; i<64; i++){
		d[i].re  =(d[i].re + MAX1/2);
		d[i].im  =(d[i].im + MAX1/2);
	}
	// stage 1.2
	for(int i=0; i<64; i++){
		n[i].re  =(d[i].re)>>SHR1;
		n[i].im  =(d[i].im)>>SHR1;
	}
	//-------- stage 2.0 --------------------- 8*rep8*2 = 128 Ticks + 64Ticks(conjg)
	//  	for(int k=0; k<64; k++){
	//  		for(int m=0; m<8; m++){
	//  			y[k]+=toFix(W64(m*k),MAX2)*n[8*(k%8)+m];
	//  		}
	//  	}
	//............
	//  Let k(0..63)==8*p+k, where k=0..7 p=0..7
	for(int p=0; p<8; p++){
		for(int k=0; k<8; k++){
			for(int m=0; m<8; m++){
				y[8*p+k]+=toFix(W64(m*(8*p+k)),MAX2)*n[8*k+m];
			}
		}
	}
	
	//-------- stage 2.2 -------------- 2*rep32 = 64Ticks
	for(int i=0; i<64; i++){
		y[i].re  =(y[i].re + MAX2/2);
		y[i].im  =(y[i].im + MAX2/2);
	}
	// stage 2.3
	for(int i=0; i<64; i++){
		y[i].re  =(y[i].re )>>SHR2;
		y[i].im  =(y[i].im )>>SHR2;
	}
	// TOTAL = 64+(64+32)+(64+32)+(64)+(128+64)+64= 576 Ticks
	// TABLE = 64+1024=1088 Coeff
}




// ======================================================
void nmppsFFT64FwdRef8x8_f( nm32sc* src, nm32sc* dst)
{
	vec<cmplx<double> > x(64);
	vec<cmplx<double> > y(64);
	vec<cmplx<double> > s(64);
	
	for(int i=0; i<64; i++){
		x[i].re=src[i].re;
		x[i].im=src[i].im;
		y[i].re=0;
		y[i].im=0;
	}

	//------ initial scheme -------------------------
// 	for(int k=0; k<64; k++){
// 		for(int p=0; p<8; p++){
// 			for(int n=0; n<8; n++){
// 				y[k]+=W64(p*k)*W64(8*n*k)*x[8*n+p];
// 			}
// 		}
// 	}
	//------ final scheme -------------------------
	// stage 1.0
	for(int k=0; k<8; k++){
		for(int p=0; p<8; p++){
			for(int n=0; n<8; n++){
				s[8*k+p]+=W64(8*n*k)*x[8*n+p];
			}
		}
	}
	
	// stage 2.0
	for(int k=0; k<64; k++){
		for(int p=0; p<8; p++){
			y[k]+=W64(p*k)*s[8*(k%8)+p];
		}
	}
	//-------- rounding -----------------------
	// stage 2.1
	for(int i=0; i<64; i++){
		dst[i].re=floor(y[i].re+0.5);
		dst[i].im=floor(y[i].im+0.5);
	}
}

void nmppsFFT64FwdRef8x8( nm32sc* src, nm32sc* dst)
{
	//---------------------
	int SHR1=16;
	int SHR2=7;
	int MAX1=1<<SHR1;
	int MAX2=1<<SHR2;

	//---------------------
	vec<cmplx<int> > x((cmplx<int>*)src,64);
	vec<cmplx<int> > y((cmplx<int>*)dst,64);
	vec<cmplx<int> > s(64);
	vec<cmplx<int> > d(64);

	for(int i=0; i<64; i++){
		y[i].re=0;
		y[i].im=0;
	}

	for(int i=0; i<64; i++){
		x[i].re=src[i].re;
		x[i].im=src[i].im;
		y[i].re=0;
		y[i].im=0;
		d[i].re=0;
		d[i].im=0;
	}

	//------ final scheme ------------------------- rep8*8*2+64= 128+64 Ticks
	for(int k=0; k<8; k++){
		for(int p=0; p<8; p++){
			for(int n=0; n<8; n++){
				s[8*k+p]+=toFix(W64(8*n*k),MAX1)*x[8*n+p];
			}
			//-------- rounding ----------------------- 64 Ticks
			s[8*k+p].re+=MAX1/2;
			s[8*k+p].im+=MAX1/2;
			s[8*k+p].re>>=SHR1;
			s[8*k+p].im>>=SHR1;
		}

	}

	//................................. rep8*8*2+64= 128+64 Ticks
	for(int k=0; k<64; k++){ 
		for(int p=0; p<8; p++){
			y[k]+=toFix(W64(p*k),MAX2)*s[8*(k%8)+p];
		}
	}
	//-------- rounding ----------------------- 64Ticks
	for(int i=0; i<64; i++){
		dst[i].re=(y[i].re+MAX2/2)>>SHR2;
		dst[i].im=(y[i].im+MAX2/2)>>SHR2;
	}
	// TOTAL  128+64+64+128+64+64=512 Ticks
	// TABLE  8*8*2+64*8*2=1152 Coeff(Bytes)
}	

