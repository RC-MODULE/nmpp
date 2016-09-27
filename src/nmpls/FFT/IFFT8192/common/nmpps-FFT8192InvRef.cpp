//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM6403 Software                      */
//*                                                                         */
//*   Fast Fourie Transform Library                                         */
//*                                                                         */
//*   File:             pcFFT256.cpp                                        */
//*   Contents:         C++ Equivalent function of the FFT_Inv256.          */
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
#include "fft2.h"
//#include "fftext.h"
#include "nmtl/tcmplx_spec.h"
#include <math.h>

#include "fftexp.h"
#ifndef PI
#define PI 3.14159265359
#endif

/*
cmplx<double> expIFFT<8192>(int power)
{
	cmplx<double> z(0,-2.0*PI*power/8192.0);
	return exp(z);
}

cmplx<int > toFix(cmplx<double> X,double Ampl);*/
void load_wfifo(cmplx<int>* wcoef, int wstep, int size);
void vsum_data (nm8s* data,  cmplx<int>* afifo);


int nmppsDFT8192InvRef_f(const nm32sc* src, nm32sc* dst)
{
	vec<cmplx<double> > x(8192);
	vec<cmplx<double> > y(8192);
	
	for(int i=0; i<8192; i++){
		x[i].re=src[i].re;
		x[i].im=src[i].im;
	}
	for(int k=0; k<8192; k++){
		y[k]=expIFFT<8192>(0)*x[0];
		for(int n=1; n<8192; n++){
			y[k]+=expIFFT<8192>(n*k)*x[n];
		}
	}
	for(int i=0; i<8192; i++){
		dst[i].re=floor(y[i].re/8192+0.5);
		dst[i].im=floor(y[i].im/8192+0.5);
	}
	return 0;
}


int nmppsFFT8192Inv28888Ref_f(const nm32sc* src, nm32sc* dst)
{
	vec<cmplx<double> > X(8192);
	vec<cmplx<double> > Y(8192);
	vec<cmplx<double> > G(8192);
	vec<cmplx<double> > N(8192);
	vec<cmplx<double> > H(8192);
	vec<cmplx<double> > J(8192);
	cmplx<double> z;
	cmplx<double> t;
	for(int i=0; i<8192; i++){
		X[i].re=src[i].re;
		X[i].im=src[i].im;
	}
	// Вывод:
	//----------------- 0 -----------------
	//for(int k=0; k<8192; k++){
	//	y[k]=expIFFT<8192>(0)*x[0];
	//	for(int n=1; n<8192; n++){
	//		y[k]+=expIFFT<8192>(n*k)*x[n];
	//	}
	//}
	//------------- 1 ---------------
	// n=8*n+i
	// 	for(int k=0; k<8192; k++)
	// 		for(int i=0; i<8; i++)
	// 			for(int n=0; n<8192/8; n++)
	// 				y[k]+=expIFFT<8192>(8*n*k)*expIFFT<8192>(k*i)*x[8*n+i];
	//------------- 2 ---------------
	// n=8*n+j
	//for(int k=0; k<8192; k++)
	//	for(int i=0; i<8; i++)
	//		for(int j=0; j<8; j++)
	//			for(int n=0; n<8192/8/8; n++)
	//				y[k]+=expIFFT<8192>(8*(8*n+j)*k)*expIFFT<8192>(k*i)*x[8*(8*n+j)+i];
	//------------- 3 ---------------
	// n=8*n+h
	//for(int k=0; k<8192; k++)
	//	for(int i=0; i<8; i++)
	//		for(int j=0; j<8; j++)
	//			for(int h=0; h<8; h++)
	//				for(int n=0; n<8192/8/8/8; n++)
	//					y[k]+=expIFFT<8192>(8*(8*(8*n+h)+j)*k)*expIFFT<8192>(k*i)*x[8*(8*(8*n+h)+j)+i];
	//------------- 4 ---------------
	// n=8*n+g
	//for(int k=0; k<8192; k++)
	//	for(int i=0; i<8; i++)
	//		for(int j=0; j<8; j++)
	//			for(int h=0; h<8; h++)
	//				for(int g=0; g<8; g++)
	//					for(int n=0; n<8192/8/8/8/8; n++)
	//						y[k]+=expIFFT<8192>(8*(8*(8*(8*n+g)+h)+j)*k)*expIFFT<8192>(k*i)*x[8*(8*(8*(8*n+g)+h)+j)+i];
	//------------- 5 ---------------
	//for(int k=0; k<8192; k++)
	//	for(int i=0; i<8; i++)
	//		for(int j=0; j<8; j++)
	//			for(int h=0; h<8; h++)
	//				for(int g=0; g<8; g++)
	//					for(int n=0; n<2; n++)
	//						y[k]+=	x[4096*n+512*g+64*h+8*j+i]*
	//								expIFFT<8192>(4096*n*k)*
	//								expIFFT<8192>(512*g*k)*
	//								expIFFT<8192>(64*h*k)*
	//								expIFFT<8192>(8*j*k)*
	//								expIFFT<8192>(i*k);
	//------------- 6 ---------------
	//for(int k=0; k<8192; k++)
	//	for(int i=0; i<8; i++)
	//		for(int j=0; j<8; j++)
	//			for(int h=0; h<8; h++)
	//				for(int g=0; g<8; g++){
	//					cmplx<double> sumN;
	//					for(int n=0; n<2; n++)
	//						sumN+=	x[4096*n+512*g+64*h+8*j+i]*
	//								expIFFT<8192>(4096*n*k);
	//					y[k]+=sumN*	expIFFT<8192>(512*g*k)*
	//								expIFFT<8192>(64*h*k)*
	//								expIFFT<8192>(8*j*k)*
	//								expIFFT<8192>(i*k);
	//				}
	//------------- 7 ---------------
	//for(int k=0; k<8192; k++)
	//	for(int i=0; i<8; i++)
	//		for(int j=0; j<8; j++)
	//			for(int h=0; h<8; h++){
	//				cmplx<double> sumG;
	//				for(int g=0; g<8; g++){
	//					cmplx<double> sumN;
	//					for(int n=0; n<2; n++)
	//						sumN+=	x[4096*n+512*g+64*h+8*j+i]*
	//								expIFFT<8192>(4096*n*k);
	//					sumG+= sumN*expIFFT<8192>(512*g*k);
	//				}
	//				y[k]+=sumG*		expIFFT<8192>(64*h*k)*
	//								expIFFT<8192>(8*j*k)*
	//								expIFFT<8192>(i*k);
	//			}
	//------------- 8 ---------------
	//for(int k=0; k<8192; k++)
	//	for(int i=0; i<8; i++)
	//		for(int j=0; j<8; j++){
	//			cmplx<double> sumH;
	//			for(int h=0; h<8; h++){
	//				cmplx<double> sumG;
	//				for(int g=0; g<8; g++){
	//					cmplx<double> sumN;
	//					for(int n=0; n<2; n++)
	//						sumN+=	x[4096*n+512*g+64*h+8*j+i]*
	//								expIFFT<8192>(4096*n*k);
	//					sumG+= sumN*expIFFT<8192>(512*g*k);
	//				}
	//				sumH+=sumG*		expIFFT<8192>(64*h*k);
	//			}
	//			y[k]+=sumH*			expIFFT<8192>(8*j*k)*
	//								expIFFT<8192>(i*k);
	//		}
	//------------- 9 ---------------
	//for(int k=0; k<8192; k++){
	//	for(int i=0; i<8; i++){
	//		cmplx<double> sumJ;
	//		for(int j=0; j<8; j++){
	//			cmplx<double> sumH;
	//			for(int h=0; h<8; h++){
	//				cmplx<double> sumG;
	//				for(int g=0; g<8; g++){
	//					cmplx<double> sumN;
	//					for(int n=0; n<2; n++){
	//						sumN+=	x[4096*n+512*g+64*h+8*j+i]*
	//								expIFFT<8192>(4096*n*k);
	//					}
	//					sumG+= sumN*expIFFT<8192>(512*g*k);
	//				}
	//				sumH+=sumG*		expIFFT<8192>(64*h*k);
	//			}
	//			sumJ+=sumH*			expIFFT<8192>(8*j*k);
	//		}
	//		y[k]+=sumJ*				expIFFT<8192>(i*k);
	//	}
	//}
	//------------- 10 ---------------
	//for(int k=0; k<2; k++){
	//	for(int i=0; i<8; i++){
	//		for(int j=0; j<8; j++){
	//			for(int h=0; h<8; h++){
	//				for(int g=0; g<8; g++){
	//					cmplx<double> sumN;
	//					for(int n=0; n<2; n++){
	//						sumN+=	x[4096*n+512*g+64*h+8*j+i]*
	//								expIFFT<8192>(4096*n*k);
	//					}
	//					N[4096*k+512*g+64*h+8*j+i]=sumN;
	//				}
	//			}
	//		}
	//	}
	//}
	//for(int k=0; k<8192; k++){
	//	for(int i=0; i<8; i++){
	//		cmplx<double> sumJ;
	//		for(int j=0; j<8; j++){
	//			cmplx<double> sumH;
	//			for(int h=0; h<8; h++){
	//				cmplx<double> sumG;
	//				for(int g=0; g<8; g++){
	//					sumG+= N[4096*(k%2)+512*g+64*h+8*j+i]*expIFFT<8192>(512*g*k);
	//				}
	//				sumH+=sumG*		expIFFT<8192>(64*h*k);
	//			}
	//			sumJ+=sumH*			expIFFT<8192>(8*j*k);
	//		}
	//		y[k]+=sumJ*				expIFFT<8192>(i*k);
	//	}
	//}
	//------------- 11 ---------------
	//for(int k=0; k<2; k++){
	//	for(int i=0; i<8; i++){
	//		for(int j=0; j<8; j++){
	//			for(int h=0; h<8; h++){
	//				for(int g=0; g<8; g++){
	//					cmplx<double> sumN;
	//					for(int n=0; n<2; n++){
	//						sumN+=	x[4096*n+512*g+64*h+8*j+i]*expIFFT<8192>(4096*n*k);
	//					}
	//					N[4096*k+512*g+64*h+8*j+i]=sumN;
	//				}
	//			}
	//		}
	//	}
	//}
	//for(int k=0; k<16; k++){
	//	for(int i=0; i<8; i++){
	//		for(int j=0; j<8; j++){
	//			for(int h=0; h<8; h++){
	//				cmplx<double> sumG;
	//				for(int g=0; g<8; g++){
	//					sumG+= N[4096*(k%2)+512*g+64*h+8*j+i]*expIFFT<8192>(512*g*k);
	//				}
	//				G[512*(k%16)+64*h+8*j+i]=sumG;
	//			}
	//		}
	//	}
	//}
	//
	//for(int k=0; k<8192; k++){
	//	for(int i=0; i<8; i++){
	//		cmplx<double> sumJ;
	//		for(int j=0; j<8; j++){
	//			cmplx<double> sumH;
	//			for(int h=0; h<8; h++){
	//				sumH+=G[512*(k%16)+64*h+8*j+i]*expIFFT<8192>(64*h*k);
	//			}
	//			sumJ+=sumH*			expIFFT<8192>(8*j*k);
	//		}
	//		y[k]+=sumJ*				expIFFT<8192>(i*k);
	//	}
	//}
	//------------- 12 ---------------
	//for(int k=0; k<2; k++){
	//	for(int i=0; i<8; i++){
	//		for(int j=0; j<8; j++){
	//			for(int h=0; h<8; h++){
	//				for(int g=0; g<8; g++){
	//					cmplx<double> sumN;
	//					for(int n=0; n<2; n++){
	//						sumN+=	x[4096*n+512*g+64*h+8*j+i]*expIFFT<8192>(4096*n*k);
	//					}
	//					N[4096*k+512*g+64*h+8*j+i]=sumN;
	//				}
	//			}
	//		}
	//	}
	//}
	//for(int k=0; k<16; k++){
	//	for(int i=0; i<8; i++){
	//		for(int j=0; j<8; j++){
	//			for(int h=0; h<8; h++){
	//				cmplx<double> sumG;
	//				for(int g=0; g<8; g++){
	//					sumG+= N[4096*(k%2)+512*g+64*h+8*j+i]*expIFFT<8192>(512*g*k);
	//				}
	//				G[512*(k%16)+64*h+8*j+i]=sumG;
	//			}
	//		}
	//	}
	//}
	//
	//for(int k=0; k<128; k++){
	//	for(int i=0; i<8; i++){
	//		for(int j=0; j<8; j++){
	//			cmplx<double> sumH;
	//			for(int h=0; h<8; h++){
	//				sumH+=G[512*(k%16)+64*h+8*j+i]*expIFFT<8192>(64*h*k);
	//			}
	//			H[64*(k%128)+8*j+i]=sumH;
	//		}
	//	}
	//}
	//
	//for(int k=0; k<8192; k++){
	//	for(int i=0; i<8; i++){
	//		cmplx<double> sumJ;
	//		for(int j=0; j<8; j++){
	//			sumJ+=H[64*(k%128)+8*j+i]* expIFFT<8192>(8*j*k);
	//		}
	//		y[k]+=sumJ*				expIFFT<8192>(i*k);
	//	}
	//}
	//------------- 13 ---------------
	//for(int k=0; k<2; k++){
	//	for(int i=0; i<8; i++){
	//		for(int j=0; j<8; j++){
	//			for(int h=0; h<8; h++){
	//				for(int g=0; g<8; g++){
	//					cmplx<double> sumN;
	//					for(int n=0; n<2; n++){
	//						sumN+=	x[4096*n+512*g+64*h+8*j+i]*expIFFT<8192>(4096*n*k);
	//					}
	//					N[4096*k+512*g+64*h+8*j+i]=sumN;
	//				}
	//			}
	//		}
	//	}
	//}
	//for(int k=0; k<16; k++){
	//	for(int i=0; i<8; i++){
	//		for(int j=0; j<8; j++){
	//			for(int h=0; h<8; h++){
	//				cmplx<double> sumG;
	//				for(int g=0; g<8; g++){
	//					sumG+= N[4096*(k%2)+512*g+64*h+8*j+i]*expIFFT<8192>(512*g*k);
	//				}
	//				G[512*(k%16)+64*h+8*j+i]=sumG;
	//			}
	//		}
	//	}
	//}
	//
	//for(int k=0; k<128; k++){
	//	for(int i=0; i<8; i++){
	//		for(int j=0; j<8; j++){
	//			cmplx<double> sumH;
	//			for(int h=0; h<8; h++){
	//				sumH+=G[512*(k%16)+64*h+8*j+i]*expIFFT<8192>(64*h*k);
	//			}
	//			H[64*(k%128)+8*j+i]=sumH;
	//		}
	//	}
	//}
	//
	//for(int k=0; k<1024; k++){
	//	for(int i=0; i<8; i++){
	//		cmplx<double> sumJ;
	//		for(int j=0; j<8; j++){
	//			sumJ+=H[64*(k%128)+8*j+i]* expIFFT<8192>(8*j*k);
	//		}
	//		J[8*(k%1024)+i]=sumJ;
	//	}
	//}
	//
	//for(int k=0; k<8192; k++){
	//	for(int i=0; i<8; i++){
	//		y[k]+=J[8*(k%1024)+i]*		expIFFT<8192>(i*k);
	//	}
	//}
	//------------- 13 ---------------
	//for(int k=0; k<2; k++){
	//	for(int i=0; i<8; i++){
	//		for(int j=0; j<8; j++){
	//			for(int h=0; h<8; h++){
	//				for(int g=0; g<8; g++){
	//					for(int n=0; n<2; n++){
	//						N[4096*k+512*g+64*h+8*j+i]+=	x[4096*n+512*g+64*h+8*j+i]*expIFFT<8192>(4096*n*k);
	//					}
	//				}
	//			}
	//		}
	//	}
	//}
	//for(int k=0; k<16; k++){
	//	for(int i=0; i<8; i++){
	//		for(int j=0; j<8; j++){
	//			for(int h=0; h<8; h++){
	//				for(int g=0; g<8; g++){
	//					G[512*(k%16)+64*h+8*j+i]+= N[4096*(k%2)+512*g+64*h+8*j+i]*expIFFT<8192>(512*g*k);
	//				}
	//			}
	//		}
	//	}
	//}
	//
	//for(int k=0; k<128; k++){
	//	for(int i=0; i<8; i++){
	//		for(int j=0; j<8; j++){
	//			for(int h=0; h<8; h++){
	//				H[64*(k%128)+8*j+i]+=G[512*(k%16)+64*h+8*j+i]*expIFFT<8192>(64*h*k);
	//			}
	//		}
	//	}
	//}
	//
	//for(int k=0; k<1024; k++){
	//	for(int i=0; i<8; i++){
	//		for(int j=0; j<8; j++){
	//			J[8*(k%1024)+i]+=H[64*(k%128)+8*j+i]* expIFFT<8192>(8*j*k);
	//		}
	//	}
	//}
	//
	//for(int k=0; k<8192; k++){
	//	for(int i=0; i<8; i++){
	//		y[k]+=J[8*(k%1024)+i]*		expIFFT<8192>(i*k);
	//	}
	//}
	//------------- 14 ---------------
	// kk=512*g+64*h+8*j+i
	//for(int k=0; k<2; k++){
	//	for(int kk=0; kk<4096; kk++){
	//		for(int n=0; n<2; n++){
	//			N[4096*k+kk]+=	x[4096*n+kk]*				expIFFT<8192>(4096*n*k);
	//		}
	//	}
	//}
	//for(int k=0; k<16; k++){
	//	for(int kk=0; kk<512; kk++){
	//		for(int g=0; g<8; g++){
	//			G[512*(k%16)+kk]+= N[4096*(k%2)+512*g+kk]*	expIFFT<8192>(512*g*k);
	//		}
	//	}
	//}
	//
	//for(int k=0; k<128; k++){
	//	for(int kk=0; kk<64; kk++){
	//		for(int h=0; h<8; h++){
	//			H[64*(k%128)+kk]+=G[512*(k%16)+64*h+kk]*	expIFFT<8192>(64*h*k);
	//		}
	//	}
	//}
	//
	//for(int k=0; k<1024; k++){
	//	for(int i=0; i<8; i++){
	//		for(int j=0; j<8; j++){
	//			J[8*(k%1024)+i]+=H[64*(k%128)+8*j+i]*		expIFFT<8192>(8*j*k);
	//		}
	//	}
	//}
	//
	//for(int k=0; k<8192; k++){
	//	for(int i=0; i<8; i++){
	//		y[k]+=J[8*(k%1024)+i]*							expIFFT<8192>(i*k);
	//	}
	//}
	//
	//------------- 15 ---------------
	//for(int k=0; k<2; k++){
	//	for(int kk=0; kk<4096; kk++){
	//		N[4096*k+kk]+=X[kk]+X[4096+kk]*expIFFT<8192>(4096*k);
	//	}
	//}
	//
	//for(int k=0; k<16; k++){
	//	for(int kk=0; kk<512; kk++){
	//		for(int g=0; g<8; g++){
	//			G[512*(k%16)+kk]+= N[4096*(k%2)+512*g+kk]*	expIFFT<8192>(512*g*k);
	//		}
	//	}
	//}
    //
	//for(int k=0; k<128; k++){
	//	for(int kk=0; kk<64; kk++){
	//		for(int h=0; h<8; h++){
	//			H[64*(k%128)+kk]+=G[512*(k%16)+64*h+kk]*	expIFFT<8192>(64*h*k);
	//		}
	//	}
	//}
    //
	//for(int k=0; k<1024; k++){
	//	for(int i=0; i<8; i++){
	//		for(int j=0; j<8; j++){
	//			J[8*(k%1024)+i]+=H[64*(k%128)+8*j+i]*		expIFFT<8192>(8*j*k);
	//		}
	//	}
	//}
    //
	//for(int k=0; k<8192; k++){
	//	for(int i=0; i<8; i++){
	//		Y[k]+=J[8*(k%1024)+i]*							expIFFT<8192>(i*k);
	//	}
	//}
	//=========== Final FFT algorithm: =========================
	// ---------------- 0.0 --------------------
	for(int k=0; k<2; k++){
		for(int kk=0; kk<4096; kk++){
			N[4096*k+kk]+=X[kk]+X[4096+kk]*expIFFT<8192>(4096*k);
		}
	}
	// ---------------- 1.0 --------------------
	for(int kk=0; kk<512; kk++){
		for(int k2=0; k2<2; k2++){ 		
			for(int k1=0; k1<8; k1++){	// rep 8
				int k=k1*2+k2;			// for(int k=0; k<16; k++)
				for(int g=0; g<8; g++){	// vsum
					G[1024*k1+512*k2+kk]+= N[4096*k2+512*g+kk]*	expIFFT<8192>(512*g*k);
				}
			}
		}
	}
	// ---------------- 2.0 --------------------
    for(int kk=0; kk<64; kk++){
		for(int k2=0; k2<16; k2++){ 		
			for(int k1=0; k1<8; k1++){	// rep 8
				int k=k1*16+k2;			// for(int k=0; k<128; k++){
				for(int h=0; h<8; h++){	// vsum
					H[1024*k1+64*k2+kk]+=G[512*k2+64*h+kk]*	expIFFT<8192>(64*h*k);
				}
			}
		}
	}
    // ---------------- 3.0 --------------------
	for(int k2=0; k2<128; k2++){ 		
		for(int k1=0; k1<8; k1++){
			for(int i=0; i<8; i++){		// rep 8
				int k=k1*128+k2;		// for(int k=0; k<1024; k++){
				for(int j=0; j<8; j++){	// vsum
					J[1024*k1+8*k2+i]+=H[64*k2+8*j+i]*expIFFT<8192>(8*j*k);
				}
			}
		}
	}
    // ---------------- 4.0 --------------------
	
	for(int k2=0; k2<1024; k2++){ 		
		for(int k1=0; k1<8; k1++){		// rep 8
			int k=1024*k1+k2;			// for(int k=0; k<8192; k++){ 
			for(int i=0; i<8; i++){		// vsum
				Y[1024*k1+k2]+=J[8*k2+i]*expIFFT<8192>(i*k);
			}
		}
	}
    
	for(int i=0; i<8192; i++){
		dst[i].re=floor(Y[i].re+0.5);
		dst[i].im=floor(Y[i].im+0.5);
	}
	return 0;
}





