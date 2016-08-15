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
#include "fft2.h"
//#include "fftext.h"
#include "nmtl/tcmplx_spec.h"
#include <math.h>

#include "fftexp.h"
#ifndef PI
#define PI 3.14159265359
#endif

/*
cmplx<double> expFFT<8192>(int power)
{
	cmplx<double> z(0,-2.0*PI*power/8192.0);
	return exp(z);
}

cmplx<int > toFix(cmplx<double> X,double Ampl);*/
void load_wfifo(cmplx<int>* wcoef, int wstep, int size);
void vsum_data (nm8s* data,  cmplx<int>* afifo);


int nmppsDFT8192FwdRef_f(const nm32sc* src, nm32sc* dst)
{
	vec<cmplx<double> > x(8192);
	vec<cmplx<double> > y(8192);
	
	for(int i=0; i<8192; i++){
		x[i].re=src[i].re;
		x[i].im=src[i].im;
	}
	for(int k=0; k<8192; k++){
		y[k]=expFFT<8192>(0)*x[0];
		for(int n=1; n<8192; n++){
			y[k]+=expFFT<8192>(n*k)*x[n];
		}
	}
	for(int i=0; i<8192; i++){
		dst[i].re=floor(y[i].re+0.5);
		dst[i].im=floor(y[i].im+0.5);
	}
	return 0;
}


int nmppsFFT8192Fwd28888Ref_f(const nm32sc* src, nm32sc* dst)
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
	//----------------- 0 -----------------
	//for(int k=0; k<8192; k++){
	//	y[k]=expFFT<8192>(0)*x[0];
	//	for(int n=1; n<8192; n++){
	//		y[k]+=expFFT<8192>(n*k)*x[n];
	//	}
	//}
	//------------- 1 ---------------
	// n=8*n+i
	// 	for(int k=0; k<8192; k++)
	// 		for(int i=0; i<8; i++)
	// 			for(int n=0; n<8192/8; n++)
	// 				y[k]+=expFFT<8192>(8*n*k)*expFFT<8192>(k*i)*x[8*n+i];
	//------------- 2 ---------------
	// n=8*n+j
	//for(int k=0; k<8192; k++)
	//	for(int i=0; i<8; i++)
	//		for(int j=0; j<8; j++)
	//			for(int n=0; n<8192/8/8; n++)
	//				y[k]+=expFFT<8192>(8*(8*n+j)*k)*expFFT<8192>(k*i)*x[8*(8*n+j)+i];
	//------------- 3 ---------------
	// n=8*n+h
	//for(int k=0; k<8192; k++)
	//	for(int i=0; i<8; i++)
	//		for(int j=0; j<8; j++)
	//			for(int h=0; h<8; h++)
	//				for(int n=0; n<8192/8/8/8; n++)
	//					y[k]+=expFFT<8192>(8*(8*(8*n+h)+j)*k)*expFFT<8192>(k*i)*x[8*(8*(8*n+h)+j)+i];
	//------------- 4 ---------------
	// n=8*n+g
	//for(int k=0; k<8192; k++)
	//	for(int i=0; i<8; i++)
	//		for(int j=0; j<8; j++)
	//			for(int h=0; h<8; h++)
	//				for(int g=0; g<8; g++)
	//					for(int n=0; n<8192/8/8/8/8; n++)
	//						y[k]+=expFFT<8192>(8*(8*(8*(8*n+g)+h)+j)*k)*expFFT<8192>(k*i)*x[8*(8*(8*(8*n+g)+h)+j)+i];
	//------------- 5 ---------------
	//for(int k=0; k<8192; k++)
	//	for(int i=0; i<8; i++)
	//		for(int j=0; j<8; j++)
	//			for(int h=0; h<8; h++)
	//				for(int g=0; g<8; g++)
	//					for(int n=0; n<2; n++)
	//						y[k]+=	x[4096*n+512*g+64*h+8*j+i]*
	//								expFFT<8192>(4096*n*k)*
	//								expFFT<8192>(512*g*k)*
	//								expFFT<8192>(64*h*k)*
	//								expFFT<8192>(8*j*k)*
	//								expFFT<8192>(i*k);
	//------------- 6 ---------------
	//for(int k=0; k<8192; k++)
	//	for(int i=0; i<8; i++)
	//		for(int j=0; j<8; j++)
	//			for(int h=0; h<8; h++)
	//				for(int g=0; g<8; g++){
	//					cmplx<double> sumN;
	//					for(int n=0; n<2; n++)
	//						sumN+=	x[4096*n+512*g+64*h+8*j+i]*
	//								expFFT<8192>(4096*n*k);
	//					y[k]+=sumN*	expFFT<8192>(512*g*k)*
	//								expFFT<8192>(64*h*k)*
	//								expFFT<8192>(8*j*k)*
	//								expFFT<8192>(i*k);
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
	//								expFFT<8192>(4096*n*k);
	//					sumG+= sumN*expFFT<8192>(512*g*k);
	//				}
	//				y[k]+=sumG*		expFFT<8192>(64*h*k)*
	//								expFFT<8192>(8*j*k)*
	//								expFFT<8192>(i*k);
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
	//								expFFT<8192>(4096*n*k);
	//					sumG+= sumN*expFFT<8192>(512*g*k);
	//				}
	//				sumH+=sumG*		expFFT<8192>(64*h*k);
	//			}
	//			y[k]+=sumH*			expFFT<8192>(8*j*k)*
	//								expFFT<8192>(i*k);
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
	//								expFFT<8192>(4096*n*k);
	//					}
	//					sumG+= sumN*expFFT<8192>(512*g*k);
	//				}
	//				sumH+=sumG*		expFFT<8192>(64*h*k);
	//			}
	//			sumJ+=sumH*			expFFT<8192>(8*j*k);
	//		}
	//		y[k]+=sumJ*				expFFT<8192>(i*k);
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
	//								expFFT<8192>(4096*n*k);
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
	//					sumG+= N[4096*(k%2)+512*g+64*h+8*j+i]*expFFT<8192>(512*g*k);
	//				}
	//				sumH+=sumG*		expFFT<8192>(64*h*k);
	//			}
	//			sumJ+=sumH*			expFFT<8192>(8*j*k);
	//		}
	//		y[k]+=sumJ*				expFFT<8192>(i*k);
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
	//						sumN+=	x[4096*n+512*g+64*h+8*j+i]*expFFT<8192>(4096*n*k);
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
	//					sumG+= N[4096*(k%2)+512*g+64*h+8*j+i]*expFFT<8192>(512*g*k);
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
	//				sumH+=G[512*(k%16)+64*h+8*j+i]*expFFT<8192>(64*h*k);
	//			}
	//			sumJ+=sumH*			expFFT<8192>(8*j*k);
	//		}
	//		y[k]+=sumJ*				expFFT<8192>(i*k);
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
	//						sumN+=	x[4096*n+512*g+64*h+8*j+i]*expFFT<8192>(4096*n*k);
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
	//					sumG+= N[4096*(k%2)+512*g+64*h+8*j+i]*expFFT<8192>(512*g*k);
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
	//				sumH+=G[512*(k%16)+64*h+8*j+i]*expFFT<8192>(64*h*k);
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
	//			sumJ+=H[64*(k%128)+8*j+i]* expFFT<8192>(8*j*k);
	//		}
	//		y[k]+=sumJ*				expFFT<8192>(i*k);
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
	//						sumN+=	x[4096*n+512*g+64*h+8*j+i]*expFFT<8192>(4096*n*k);
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
	//					sumG+= N[4096*(k%2)+512*g+64*h+8*j+i]*expFFT<8192>(512*g*k);
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
	//				sumH+=G[512*(k%16)+64*h+8*j+i]*expFFT<8192>(64*h*k);
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
	//			sumJ+=H[64*(k%128)+8*j+i]* expFFT<8192>(8*j*k);
	//		}
	//		J[8*(k%1024)+i]=sumJ;
	//	}
	//}
	//
	//for(int k=0; k<8192; k++){
	//	for(int i=0; i<8; i++){
	//		y[k]+=J[8*(k%1024)+i]*		expFFT<8192>(i*k);
	//	}
	//}
	//------------- 13 ---------------
	//for(int k=0; k<2; k++){
	//	for(int i=0; i<8; i++){
	//		for(int j=0; j<8; j++){
	//			for(int h=0; h<8; h++){
	//				for(int g=0; g<8; g++){
	//					for(int n=0; n<2; n++){
	//						N[4096*k+512*g+64*h+8*j+i]+=	x[4096*n+512*g+64*h+8*j+i]*expFFT<8192>(4096*n*k);
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
	//					G[512*(k%16)+64*h+8*j+i]+= N[4096*(k%2)+512*g+64*h+8*j+i]*expFFT<8192>(512*g*k);
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
	//				H[64*(k%128)+8*j+i]+=G[512*(k%16)+64*h+8*j+i]*expFFT<8192>(64*h*k);
	//			}
	//		}
	//	}
	//}
	//
	//for(int k=0; k<1024; k++){
	//	for(int i=0; i<8; i++){
	//		for(int j=0; j<8; j++){
	//			J[8*(k%1024)+i]+=H[64*(k%128)+8*j+i]* expFFT<8192>(8*j*k);
	//		}
	//	}
	//}
	//
	//for(int k=0; k<8192; k++){
	//	for(int i=0; i<8; i++){
	//		y[k]+=J[8*(k%1024)+i]*		expFFT<8192>(i*k);
	//	}
	//}
	//------------- 14 ---------------
	// kk=512*g+64*h+8*j+i
	//for(int k=0; k<2; k++){
	//	for(int kk=0; kk<4096; kk++){
	//		for(int n=0; n<2; n++){
	//			N[4096*k+kk]+=	x[4096*n+kk]*				expFFT<8192>(4096*n*k);
	//		}
	//	}
	//}
	//for(int k=0; k<16; k++){
	//	for(int kk=0; kk<512; kk++){
	//		for(int g=0; g<8; g++){
	//			G[512*(k%16)+kk]+= N[4096*(k%2)+512*g+kk]*	expFFT<8192>(512*g*k);
	//		}
	//	}
	//}
	//
	//for(int k=0; k<128; k++){
	//	for(int kk=0; kk<64; kk++){
	//		for(int h=0; h<8; h++){
	//			H[64*(k%128)+kk]+=G[512*(k%16)+64*h+kk]*	expFFT<8192>(64*h*k);
	//		}
	//	}
	//}
	//
	//for(int k=0; k<1024; k++){
	//	for(int i=0; i<8; i++){
	//		for(int j=0; j<8; j++){
	//			J[8*(k%1024)+i]+=H[64*(k%128)+8*j+i]*		expFFT<8192>(8*j*k);
	//		}
	//	}
	//}
	//
	//for(int k=0; k<8192; k++){
	//	for(int i=0; i<8; i++){
	//		y[k]+=J[8*(k%1024)+i]*							expFFT<8192>(i*k);
	//	}
	//}
	//
	//------------- 15 ---------------
	for(int k=0; k<2; k++){
		for(int kk=0; kk<4096; kk++){
			N[4096*k+kk]+=X[kk]+X[4096+kk]*expFFT<8192>(4096*k);
		}
	}
	
	for(int k=0; k<16; k++){
		for(int kk=0; kk<512; kk++){
			for(int g=0; g<8; g++){
				G[512*(k%16)+kk]+= N[4096*(k%2)+512*g+kk]*	expFFT<8192>(512*g*k);
			}
		}
	}

	for(int k=0; k<128; k++){
		for(int kk=0; kk<64; kk++){
			for(int h=0; h<8; h++){
				H[64*(k%128)+kk]+=G[512*(k%16)+64*h+kk]*	expFFT<8192>(64*h*k);
			}
		}
	}

	for(int k=0; k<1024; k++){
		for(int i=0; i<8; i++){
			for(int j=0; j<8; j++){
				J[8*(k%1024)+i]+=H[64*(k%128)+8*j+i]*		expFFT<8192>(8*j*k);
			}
		}
	}

	for(int k=0; k<8192; k++){
		for(int i=0; i<8; i++){
			Y[k]+=J[8*(k%1024)+i]*							expFFT<8192>(i*k);
		}
	}

	for(int i=0; i<8192; i++){
		dst[i].re=floor(Y[i].re+0.5);
		dst[i].im=floor(Y[i].im+0.5);
	}
	return 0;
}





void nmppsFFT8192Fwd28888_RefFloat(const nm32sc* src, nm32sc* dst)
{
	vec<cmplx<double> > X(8192);
	vec<cmplx<double> > y(8192);

	vec<cmplx<double> > vH(8192);
	vec<cmplx<double> > vI(8192);
	vec<cmplx<double> > vJ(8192);

	for(int i=0; i<8192; i++){
		X[i].re=src[i].re;
		X[i].im=src[i].im;
	}

	y.reset();
	vH.reset();
	vI.reset();
	vJ.reset();

	//------------- 0 ---------------
	//for(int k=0; k<8192; k++)
	//	for(int n=0; n<8192; n++)
	//		y[k]+=expFFT<8192>(n*k)*x[n];
	//------------- 1 ---------------
	// n=8*n+i
// 	for(int k=0; k<8192; k++)
// 		for(int i=0; i<8; i++)
// 			for(int n=0; n<8192/8; n++)
// 				y[k]+=expFFT<8192>(8*n*k)*expFFT<8192>(k*i)*x[8*n+i];

	//------------- 2 ---------------
	// n=8*n+i
// 	for(int k=0; k<8192; k++)
// 		for(int i=0; i<8; i++){
// 			cmplx<double> sum;
// 			for(int n=0; n<8192/8; n++){
// 				sum+=expFFT<8192>(8*n*k)*x[8*n+i];
// 			}
// 			y[k]+=sum*expFFT<8192>(k*i);
// 		}

	//------------- 3 ---------------
	// n=8*n+j
// 	for(int k=0; k<8192; k++)
// 		for(int i=0; i<8; i++){
// 			cmplx<double> sum;
// 			//for(int n=0; n<8192/8; n++){
// 			for(int j=0; j<8; j++){
// 				for(int n=0; n<8192/8/8; n++){
// 					sum+=expFFT<8192>(64*n*k)*expFFT<8192>(8*j*k)*x[8*(8*n+j)+i];
// 				}
// 			}
// 			y[k]+=sum*expFFT<8192>(k*i);
// 		}

// 	//------------- 4 ---------------
// 	for(int k=0; k<8192; k++)
// 		for(int i=0; i<8; i++){
// 			cmplx<double> sum;
// 			for(int j=0; j<8; j++){
// 				cmplx<double> sumj;
// 				for(int n=0; n<8192/8/8; n++){
// 					sumj+=expFFT<8192>(64*n*k)*x[8*(8*n+j)+i];
// 				}
// 				sum+=sumj*expFFT<8192>(8*j*k);
// 			}
// 			y[k]+=sum*expFFT<8192>(k*i);
// 		}

// 	//------------- 5 ---------------
// 	// n = 8*n+h
// 	for(int k=0; k<8192; k++)
// 		for(int i=0; i<8; i++){
// 			cmplx<double> sum;
// 			for(int j=0; j<8; j++){
// 				cmplx<double> sumj;
// 				for(int h=0; h<8; h++){
// 					for(int n=0; n<8192/8/8/8; n++){
// 						sumj+=expFFT<8192>(8*8*(8*n+h)*k)*x[8*8*(8*n+h)+8*j+i];
// 					}
// 				}
// 				sum+=sumj*expFFT<8192>(8*j*k);
// 			}
// 			y[k]+=sum*expFFT<8192>(k*i);
// 		}

	//------------- 6 ---------------
// 	for(int k=0; k<8192; k++)
// 		for(int i=0; i<8; i++){
// 			cmplx<double> sumi;
// 			for(int j=0; j<8; j++){
// 				cmplx<double> sumj;
// 				for(int h=0; h<8; h++){
// 					cmplx<double> sumh;
// 					for(int n=0; n<8192/8/8/8; n++){
// 						sumh+=expFFT<8192>(8*8*8*n*k)*x[8*8*8*n+8*8*h+8*j+i];
// 					}
// 					sumj+=sumh*expFFT<8192>(8*8*h*k);
// 				}
// 				sumi+=sumj*expFFT<8192>(8*j*k);
// 			}
// 			y[k]+=sumi*expFFT<8192>(k*i);
// 		}

	//------------- 7 ---------------
	//
	//k=8192/8/8/8*k+kk;
// 	for(int kk=0; kk<8192/8/8/8; kk++)
// 		for(int i=0; i<8; i++){
// 			cmplx<double> sumi;
// 			for(int j=0; j<8; j++){
// 				cmplx<double> sumj;
// 				for(int h=0; h<8; h++){
// 					cmplx<double> sumh;
// 					for(int n=0; n<8192/8/8/8; n++){
// 						vH[8*8*8*kk+8*8*h+8*j+i]+=expFFT<8192>(8*8*8*n*kk)*x[8*8*8*n+8*8*h+8*j+i];
// 					}
// 				}
// 			}
// 		}
// 
// 		for(int k=0; k<8192; k++)
// 			for(int i=0; i<8; i++){
// 				cmplx<double> sumi;
// 				for(int j=0; j<8; j++){
// 					cmplx<double> sumj;
// 					for(int h=0; h<8; h++){
// 						sumj+=vH[8*8*8*(k%4)+8*8*h+8*j+i]*expFFT<8192>(8*8*h*k);
// 					}
// 					sumi+=sumj*expFFT<8192>(8*j*k);
// 				}
// 				y[k]+=sumi*expFFT<8192>(k*i);
// 			}
	//------------- 7 ---------------
	//
	//k=8192/8/8/8*k+kk;
// 	for(int kk=0; kk<8192/8/8/8; kk++)
// 		for(int i=0; i<8; i++){
// 			for(int j=0; j<8; j++){
// 				for(int h=0; h<8; h++){
// 					for(int n=0; n<8192/8/8/8; n++){
// 						vH[8*8*8*kk+8*8*h+8*j+i]+=expFFT<8192>(8*8*8*n*kk)*x[8*8*8*n+8*8*h+8*j+i];
// 					}
// 				}
// 			}
// 		}
// 	//k=8192/8*8*k+kk    k=0..64  k=0..8192/8*8
// 	for(int kk=0; kk<8192/8/8; kk++)
// 		for(int i=0; i<8; i++){
// 			for(int j=0; j<8; j++){
// 				for(int h=0; h<8; h++){
// 					vJ[8*8*kk+8*j+i]+=vH[8*8*8*(kk%(8192/8/8/8))+8*8*h+8*j+i]*expFFT<8192>(8*8*h*kk);
// 				}
// 			}
// 		}
// 
// 	for(int k=0; k<8192; k++){
// 		for(int i=0; i<8; i++){
// 			cmplx<double> sumi;
// 			for(int j=0; j<8; j++){
// 				sumi+=vJ[8*8*(k%(8192/8/8))+8*j+i]*expFFT<8192>(8*j*k);
// 			}
// 			y[k]+=sumi*expFFT<8192>(k*i);
// 		}
// 	}
		//------------- 8 ---------------
		//
// 		//k=8192/8/8/8*k+kk;
// 		for(int kk=0; kk<8192/8/8/8; kk++){
// 			for(int i=0; i<8; i++){
// 				for(int j=0; j<8; j++){
// 					for(int h=0; h<8; h++){
// 						for(int n=0; n<8192/8/8/8; n++){
// 							vH[8*8*8*kk+8*8*h+8*j+i]+=expFFT<8192>(8*8*8*n*kk)*x[8*8*8*n+8*8*h+8*j+i];
// 						}
// 					}
// 				}
// 			}
// 		}
// 		//k=8192/8*8*k+kk    k=0..64  k=0..8192/8*8
// 		for(int kk=0; kk<8192/8/8; kk++){
// 			for(int i=0; i<8; i++){
// 				for(int j=0; j<8; j++){
// 					for(int h=0; h<8; h++){
// 						vJ[8*8*kk+8*j+i]+=vH[8*8*8*(kk%(8192/8/8/8))+8*8*h+8*j+i]*expFFT<8192>(8*8*h*kk);
// 					}
// 				}
// 			}
// 		}
// 		// k=8192/8*k+kk
// 		for(int kk=0; kk<8192/8; kk++){
// 			for(int i=0; i<8; i++){
// 				for(int j=0; j<8; j++){
// 					vI[8*kk+i]+=vJ[8*8*(kk%(8192/8/8))+8*j+i]*expFFT<8192>(8*j*kk);
// 				}
// 			}
// 		}
// 
// 		for(int k=0; k<8192; k++){
// 			for(int i=0; i<8; i++){
// 				y[k]+=vI[8*(k%(8192/8))+i]*expFFT<8192>(k*i);
// 			}
// 		}
		//------------- 9 ---------------
		//
		//k=8192/8/8/8*k+kk;
		for(int kk=0; kk<4; kk++){
			for(int i=0; i<512; i++){
				for(int n=0; n<4; n++){
					vH[512*kk+i]+=X[512*n+i]*expFFT<8192>(512*n*kk);
				}
			}
		}
		//k=8192/8*8*k+kk    k=0..64  k=0..8192/8*8
		for(int kk=0; kk<32; kk++){
			for(int i=0; i<64; i++){
				for(int h=0; h<8; h++){
					vJ[64*kk+i]+=vH[512*(kk%4)+8*8*h+i]*expFFT<8192>(64*h*kk);
				}
			}
		}
		// k=8192/8*k+kk
		for(int kk=0; kk<256; kk++){
			for(int i=0; i<8; i++){
				for(int j=0; j<8; j++){
					vI[8*kk+i]+=vJ[64*(kk%32)+8*j+i]*expFFT<8192>(8*j*kk);
				}
			}
		}

		for(int k=0; k<8192; k++){
			for(int i=0; i<8; i++){
				y[k]+=vI[8*(k%256)+i]*expFFT<8192>(k*i);
			}
		}

	//------------- 2 ---------------

	for(int i=0; i<8192; i++){
		dst[i].re=floor(y[i].re+0.5);
		dst[i].im=floor(y[i].im+0.5);
	}
}



void nmppsFFT8192Fwd28888_RefInt(const nm32sc* src, nm32sc* dst)
{
	vec<cmplx<int> > vX(8192);
	vec<cmplx<int> > vY(8192);
	vec<cmplx<int> > vYRe(8192);
	vec<cmplx<int> > vYIm(8192);

	vec<cmplx<int> > vH(8192);
	vec<cmplx<int> > vHRe(8192);
	vec<cmplx<int> > vHIm(8192);
	vec<cmplx<int> > vI(8192);
	vec<cmplx<int> > vIRe(8192);
	vec<cmplx<int> > vIIm(8192);
	vec<cmplx<int> > vJ(8192);

	for(int i=0; i<8192; i++){
		vX[i].re=src[i].re;
		vX[i].im=src[i].im;
	}

	vY.reset();
	vH.reset();
	vI.reset();
	vJ.reset();

	vH.reset();

	cmplx<int> z;
	cmplx<int> x;

//---------------------------------- 0 -----------------------------------------
// 	for(int kk=0; kk<4; kk++){
// 		for(int i=0; i<512; i++){
// 			for(int n=0; n<4; n++){
// 				z=toFix(expFFT<8192>(512*n*kk),1);
// 				x=X[512*n+i];
// 				cmplx<int> h;
// 				h+=z*x;
// 				//vH[512*kk+i]+=X[512*n+i]*toFix(expFFT<8192>(512*n*kk),1);
// 				vH[512*kk+i]+=h;//X[512*n+i]*toFix(expFFT<8192>(512*n*kk),1);
// 			}
// 		}
// 	}

	nm8s* w0re=new nm8s[4*4];
	nm8s* w0im=new nm8s[4*4];

	nm8s* pwre=w0re;
	nm8s* pwim=w0im;

	
	for(int kk=0,ii=0; kk<4; kk++){
		for(int n=0; n<4; n++,ii++){
			z=expFFT<8192>(512*n*kk,1);
			w0re[ii]=z.re;
			w0im[ii]=z.im;
		}
	}


	for(int i=0; i<512; i++){
		load_wfifo(vX.addr(i),512,4);
		pwre=w0re;
		pwim=w0im;
		for(int kk=0; kk<4; kk++){
// 			for(int n=0; n<4; n++){
// 				z=toFix(expFFT<8192>(512*n*kk),1);
// 				w0re[n]=z.re;
// 				w0im[n]=z.im;
// 			}
			//vH[512*kk+i]+=X[512*n+i]*toFix(expFFT<8192>(512*n*kk),1);
			vsum_data(pwre,vHRe.addr(512*kk+i));
			vsum_data(pwim,vHIm.addr(512*kk+i));
			vH[512*kk+i].re=vHRe[512*kk+i].re-vHIm[512*kk+i].im;
			vH[512*kk+i].im=vHRe[512*kk+i].im+vHIm[512*kk+i].re;
			pwre+=4;
			pwim+=4;
		}
	}
	delete w0re;
	delete w0im;

	//512*4

//---------------------------------- 1 -----------------------------------------
// 	for(int kk=0; kk<32; kk++){
// 		for(int i=0; i<64; i++){
// 			for(int h=0; h<8; h++){
// 				vJ[64*kk+i]+=vH[512*(kk%4)+8*8*h+i]*toFix(expFFT<8192>(64*h*kk),64);
// 			}
// 		}
// 	}
// 	vJ>>=6;

	nm8s* w1re=new nm8s[4*8*8];
	nm8s* w1im=new nm8s[4*8*8];

	for(int kk=0,ii=0; kk<4; kk++){
		for(int k=0; k<8; k++){	
			for(int h=0; h<8; h++,ii++){
				expFFT127<8192>(64*h*(4*k+kk),64,&z);
				w1re[ii]=z.re;
				w1im[ii]=z.im;
			}
		}
	}

	for(int i=0,ii=0; i<64; i++){
		pwre=w1re;
		pwim=w1im;
		for(int kk=0; kk<4; kk++){
			load_wfifo(vH.addr(512*kk+i),64,8);	
			for(int k=0; k<8; k++,ii++){	
				vsum_data(pwre,vHRe.addr(ii));
				vsum_data(pwim,vHIm.addr(ii));
				pwre+=8;
				pwim+=8;

			}
		}
	}
	for(int i=0,ii=0; i<64; i++){
		for(int kk=0; kk<4; kk++){
			for(int k=0; k<8; k++,ii++){	
				vJ[64*(k*4+kk)+i].re=vHRe[ii].re-vHIm[ii].im;
				vJ[64*(k*4+kk)+i].im=vHRe[ii].im+vHIm[ii].re;
			}
		}
	}

	vJ>>=6;

	delete w1re;
	delete w1im;

//---------------------------------- 2 -----------------------------------------

	nm8s* w2re=new nm8s[32*8*8];
	nm8s* w2im=new nm8s[32*8*8];

	for(int kk=0,ii=0; kk<32; kk++){
		for(int k=0; k<8; k++){		
			for(int j=0; j<8; j++,ii++){
				expFFT127<8192>(8*j*(32*k+kk),64,&z);
				w2re[ii]=z.re;
				w2im[ii]=z.im;
			}
		}
	}

	for(int i=0,ii=0; i<8; i++){
		pwre=w2re;
		pwim=w2im;
		for(int kk=0; kk<32; kk++){
			load_wfifo(vJ.addr(64*kk+i),8,8);	// rep 8 wfifo = []
			for(int k=0; k<8; k++,ii++){		
				vsum_data(pwre,vIRe.addr(ii));	// rep 8 data=[ar0++gr0] with vsum ,data,0;
				vsum_data(pwim,vIIm.addr(ii));	// rep 8 data=[ar1++gr1] with vsum ,data,0;
				pwre+=8;
				pwim+=8;
			}
		}
	}
	for(int i=0,ii=0; i<8; i++){
		for(int kk=0; kk<32; kk++){
			for(int k=0; k<8; k++,ii++){		
				vI[8*(32*k+kk)+i].re=vIRe[ii].re-vIIm[ii].im;
				vI[8*(32*k+kk)+i].im=vIRe[ii].im+vIIm[ii].re;
			}
		}
	}

	vI>>=6;
	delete w2re;
	delete w2im;
	// 8*32*8

//---------------------------------- 3 -----------------------------------------
// 	for(int k=0; k<8192; k++){
// 		for(int i=0; i<8; i++){
// 			Y[k]+=vI[8*(k%256)+i]*toFix(expFFT<8192>(k*i),64);
// 		}
// 	}
//	Y>>=6;

	nm8s* w3re=new nm8s[256*8*8];
	nm8s* w3im=new nm8s[256*8*8];

	for(int kk=0,ii=0; kk<256; kk++){
		for(int k=0; k<8; k++){
			for(int i=0; i<8; i++,ii++){
				expFFT127<8192>((256*k+kk)*i,64,&z);
				w3re[ii]=z.re;
				w3im[ii]=z.im;
			}
		}
	}
	pwre=w3re;
	pwim=w3im;

	for(int kk=0,ii=0; kk<256; kk++){
		load_wfifo(vI.addr(8*kk),1,8);								// rep 8 wfifo=[ar0++gr0]
		for(int k=0; k<8; k++,ii++){
			vsum_data(pwre,vYRe.addr(ii));					// rep 8 data=[ar0++gr0]
			vsum_data(pwim,vYIm.addr(ii));					// rep 8 data=[ar1++gr1]
			pwre+=8;
			pwim+=8;
		}
	}
	
	for(int kk=0,ii=0; kk<256; kk++){
		for(int k=0; k<8; k++,ii++){
			vY[(256*k+kk)].re=vYRe[ii].re-vYIm[ii].im;	
			vY[(256*k+kk)].im=vYRe[ii].im+vYIm[ii].re;
		}
	}


	vY>>=6;
	delete w3re;
	delete w3im;

	//------------- 2 ---------------

	for(int i=0; i<8192; i++){
		dst[i].re=vY[i].re;
		dst[i].im=vY[i].im;
	}
}
//всего =  8192*2*2+8192*3=38912

