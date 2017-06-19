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
//#include "fft.h"
#include "fft.h"
//#include "fftext.h"
#include "nmtl/tcmplx_spec.h"
#include <math.h>

#include "fftexp.h"
#ifndef PI
#define PI 3.14159265359
#endif

#include "nmpp.h"
static unsigned crc;

#define CRC32(addres,size) crc=nmppsCrc_32s((nm32s*)addres,size);
void vsum_data(nm16s* data,  cmplx<int>* afifo, int vr);
/*
cmplx<double> expFFT<2048>(int power)
{
	cmplx<double> z(0,-2.0*PI*power/2048.0);
	return exp(z);
}
*/
cmplx<int > toFix(cmplx<double> X,double Ampl);
cmplx<int > toFix127(cmplx<double> X,double Ampl);

void nmppsDFT2048Fwd_RefFloat(const nm32sc* src, nm32sc* dst)
{
	vec<cmplx<double> > x(2048);
	vec<cmplx<double> > y(2048);
	
	for(int i=0; i<2048; i++){
		x[i].re=src[i].re;
		x[i].im=src[i].im;
	}
	for(int k=0; k<2048; k++){
		y[k]=expFFT<2048>(0)*x[0];
		for(int n=1; n<2048; n++){
			y[k]+=expFFT<2048>(n*k)*x[n];
		}
	}
	for(int i=0; i<2048; i++){
		dst[i].re=floor(y[i].re+0.5);
		dst[i].im=floor(y[i].im+0.5);
	}
}



void nmppsFFT2048Fwd2x32x32_RefFloat(const nm32sc* src, nm32sc* dst)
{
	vec<cmplx<double> > x(2048);
	vec<cmplx<double> > y(2048);

	vec<cmplx<double> > N(2048);
	vec<cmplx<double> > vI(2048);

	for(int i=0; i<2048; i++){
		x[i].re=src[i].re;
		x[i].im=src[i].im;
	}

	y.reset();
	N.reset();
	vI.reset();

	//------------- 0 ---------------
	//for(int k=0; k<2048; k++)
	//	for(int n=0; n<2048; n++)
	//		y[k]+=expFFT<2048>(n*k)*x[n];
	//------------- 1 ---------------
	//------------- 2 ---------------
	// n=32*n+i
// 	for(int k=0; k<2048; k++){
// 		for(int i=0; i<32; i++){
// 			cmplx<double> sum;
// 			for(int n=0; n<2048/32; n++){
// 				sum+=expFFT<2048>(32*n*k)*x[32*n+i];
// 			}
// 			y[k]+=sum*expFFT<2048>(i*k);
// 		}
// 	}
	//------------- 3 ---------------
	//------------- 5 ---------------
	// n=32*n+j
// 	for(int k=0; k<2048; k++){
// 		for(int i=0; i<32; i++){
// 			cmplx<double> sum;
// 			for(int j=0; j<32; j++){
// 				for(int n=0; n<2048/32/32; n++){
// 					sum+=expFFT<2048>(32*(32*n+j)*k)*x[32*(32*n+j)+i];
// 				}
// 			}
// 			y[k]+=sum*expFFT<2048>(i*k);
// 		}
// 	}
	//------------- 6 ---------------
	// n=32*n+j
// 	for(int k=0; k<2048; k++){
// 		for(int i=0; i<32; i++){
// 			cmplx<double> sum;
// 			for(int j=0; j<32; j++){
// 				cmplx<double> sumj;
// 				for(int n=0; n<2048/32/32; n++){
// 					sumj+=expFFT<2048>(1024*n*k)*x[32*(32*n+j)+i];
// 				}
// 				sum+=sumj*expFFT<2048>(32*j*k);
// 			}
// 			y[k]+=sum*expFFT<2048>(i*k);
// 		}
// 	}
	//------------- 7 ---------------
// 		//k=2k+kk
// 	 	for(int k=0; k<1024; k++){ //for(int k=0; k<2048; k++){
// 		for(int kk=0; kk<2; kk++){ //for(int k=0; k<2048; k++){
// 	 		for(int i=0; i<32; i++){
// 	 			cmplx<double> sum;
// 	 			for(int j=0; j<32; j++){
// 	 				cmplx<double> sumj;
// 	 				for(int n=0; n<2048/32/32; n++){
// 	 					sumj+=expFFT<2048>(1024*n*(2*k+kk))*x[32*(32*n+j)+i];
// 	 				}
// 	 				sum+=sumj*expFFT<2048>(32*j*(2*k+kk));
// 	 			}
// 	 			y[2*k+kk]+=sum*expFFT<2048>(i*(2*k+kk));
// 	 		}
// 		}
// 		}
	//------------- 8 ---------------
	//k=2k+kk
// 	for(int k=0; k<1024; k++){ //for(int k=0; k<2048; k++){
// 		for(int kk=0; kk<2; kk++){ 
// 			for(int i=0; i<32; i++){
// 				cmplx<double> sum;
// 				for(int j=0; j<32; j++){
// 					cmplx<double> sumj;
// 					for(int n=0; n<2048/32/32; n++){
// 						sumj+=expFFT<2048>(1024*n*kk)*x[32*(32*n+j)+i]; // не завист от k
// 					}
// 					sum+=sumj*expFFT<2048>(32*j*(2*k+kk));
// 				}
// 				y[2*k+kk]+=sum*expFFT<2048>(i*(2*k+kk));
// 			}
// 		}
// 	}


	//------------- 8 ---------------
	//k=2k+kk
	//for(int k=0; k<1024; k++){ //for(int k=0; k<2048; k++){
// 		for(int kk=0; kk<2; kk++){ 
// 			for(int i=0; i<32; i++){
// 				//cmplx<double> sum;
// 				for(int j=0; j<32; j++){
// 					for(int n=0; n<2048/32/32; n++){
// 						N[1024*kk+32*j+i]+=expFFT<2048>(1024*n*kk)*x[1024*n+32*j+i]; // не завист от k
// 					}
// 					//sum+=N[1024*kk+32*j+i]*expFFT<2048>(32*j*(2*k+kk));
// 				}
// 				//y[2*k+kk]+=sum*expFFT<2048>(i*(2*k+kk));
// 			}
// 		}
// 	//}
// 
// 	for(int k=0; k<1024; k++){ //for(int k=0; k<2048; k++){
// 		for(int kk=0; kk<2; kk++){ 
// 			for(int i=0; i<32; i++){
// 				cmplx<double> sum;
// 				for(int j=0; j<32; j++){
// 					sum+=N[1024*kk+32*j+i]*expFFT<2048>(32*j*(2*k+kk));
// 				}
// 				y[2*k+kk]+=sum*expFFT<2048>(i*(2*k+kk));
// 			}
// 		}
// 	}

// 	//------------- 9 ---------------
// 	//k=2k+kk
// 	//for(int k=0; k<1024; k++){ //for(int k=0; k<2048; k++){
// 	for(int kk=0; kk<2; kk++){ 
// 		for(int i=0; i<32; i++){
// 			for(int j=0; j<32; j++){
// 				for(int n=0; n<2048/32/32; n++){
// 					N[1024*kk+32*j+i]+=expFFT<2048>(1024*n*kk)*x[1024*n+32*j+i]; // не завист от k
// 				}
// 			}
// 		}
// 	}
// 	//}
// 
// 	for(int k=0; k<2048; k++){ //for(int k=0; k<2048; k++){
// 		for(int i=0; i<32; i++){
// 			cmplx<double> sum;
// 			for(int j=0; j<32; j++){
// 				sum+=N[1024*(k%2)+32*j+i]*expFFT<2048>(32*j*k);
// 			}
// 			y[k]+=sum*expFFT<2048>(i*k);
// 		}
// 	}

// ------------- 10 ---------------
// k=2k+kk
// for(int k=0; k<1024; k++){ //for(int k=0; k<2048; k++){
// for(int kk=0; kk<2; kk++){ 
// 	for(int i=0; i<32; i++){
// 		for(int j=0; j<32; j++){
// 			for(int n=0; n<2048/32/32; n++){
// 				N[1024*kk+32*j+i]+=expFFT<2048>(1024*n*kk)*x[1024*n+32*j+i]; // не завист от k
// 			}
// 		}
// 	}
// }
// }
// k=64*k+kk
// for(int k=0; k<32; k++){ //for(int k=0; k<2048; k++){ //for(int k=0; k<2048; k++){
// 	for(int kk=0; kk<64; kk++){ 
// 		for(int i=0; i<32; i++){
// 			cmplx<double> sum;
// 			for(int j=0; j<32; j++){
// 				sum+=N[1024*(kk%2)+32*j+i]*expFFT<2048>(32*j*kk); // не завист от k
// 			}
// 			y[64*k+kk]+=sum*expFFT<2048>(i*(64*k+kk));
// 		}
// 	}
// }

//------------- 11 ---------------
// for(int kk=0; kk<2; kk++)
// 	for(int i=0; i<32; i++)
// 		for(int j=0; j<32; j++)
// 			for(int n=0; n<2048/32/32; n++)
// 				N[1024*kk+32*j+i]+=expFFT<2048>(1024*n*kk)*x[1024*n+32*j+i]; // не завист от k
// 
// 	for(int kk=0; kk<64; kk++){ 
// 		for(int i=0; i<32; i++){
// 			for(int j=0; j<32; j++){
// 				vI[32*kk+i]+=N[1024*(kk%2)+32*j+i]*expFFT<2048>(32*j*kk); // не завист от k
// 			}
// 		}
// 	}
// 
// 
// for(int k=0; k<32; k++){ //for(int k=0; k<2048; k++){ //for(int k=0; k<2048; k++){
// 	for(int kk=0; kk<64; kk++){ 
// 		for(int i=0; i<32; i++){
// 			y[64*k+kk]+=vI[32*kk+i]*expFFT<2048>(i*(64*k+kk));
// 		}
// 	}
// }
//------------- 12 ---------------

for(int kk=0; kk<2; kk++)
	for(int i=0; i<32; i++)
		for(int j=0; j<32; j++)
			for(int n=0; n<2048/32/32; n++)
				N[1024*kk+32*j+i]+=expFFT<2048>(1024*n*kk)*x[1024*n+32*j+i]; // не завист от k

for(int kk=0; kk<64; kk++) 
	for(int i=0; i<32; i++)
		for(int j=0; j<32; j++)
			vI[32*kk+i]+=N[1024*(kk%2)+32*j+i]*expFFT<2048>(32*j*kk); // не завист от k


for(int k=0; k<2048; k++)
	for(int i=0; i<32; i++)
		y[k]+=vI[32*(k%64)+i]*expFFT<2048>(i*k);


	for(int i=0; i<2048; i++){
		dst[i].re=floor(y[i].re+0.5);
		dst[i].im=floor(y[i].im+0.5);
	}
}


void nmppsFFT2048Fwd4888_RefFloat(const nm32sc* src, nm32sc* dst)
{
	vec<cmplx<double> > X(2048);
	vec<cmplx<double> > y(2048);

	vec<cmplx<double> > vH(2048);
	vec<cmplx<double> > vI(2048);
	vec<cmplx<double> > vJ(2048);

	for(int i=0; i<2048; i++){
		X[i].re=src[i].re;
		X[i].im=src[i].im;
	}

	y.reset();
	vH.reset();
	vI.reset();
	vJ.reset();

	//------------- 0 ---------------
	//for(int k=0; k<2048; k++)
	//	for(int n=0; n<2048; n++)
	//		y[k]+=expFFT<2048>(n*k)*x[n];
	//------------- 1 ---------------
	// n=8*n+i
// 	for(int k=0; k<2048; k++)
// 		for(int i=0; i<8; i++)
// 			for(int n=0; n<2048/8; n++)
// 				y[k]+=expFFT<2048>(8*n*k)*expFFT<2048>(k*i)*x[8*n+i];

	//------------- 2 ---------------
	// n=8*n+i
// 	for(int k=0; k<2048; k++)
// 		for(int i=0; i<8; i++){
// 			cmplx<double> sum;
// 			for(int n=0; n<2048/8; n++){
// 				sum+=expFFT<2048>(8*n*k)*x[8*n+i];
// 			}
// 			y[k]+=sum*expFFT<2048>(k*i);
// 		}

	//------------- 3 ---------------
	// n=8*n+j
// 	for(int k=0; k<2048; k++)
// 		for(int i=0; i<8; i++){
// 			cmplx<double> sum;
// 			//for(int n=0; n<2048/8; n++){
// 			for(int j=0; j<8; j++){
// 				for(int n=0; n<2048/8/8; n++){
// 					sum+=expFFT<2048>(64*n*k)*expFFT<2048>(8*j*k)*x[8*(8*n+j)+i];
// 				}
// 			}
// 			y[k]+=sum*expFFT<2048>(k*i);
// 		}

// 	//------------- 4 ---------------
// 	for(int k=0; k<2048; k++)
// 		for(int i=0; i<8; i++){
// 			cmplx<double> sum;
// 			for(int j=0; j<8; j++){
// 				cmplx<double> sumj;
// 				for(int n=0; n<2048/8/8; n++){
// 					sumj+=expFFT<2048>(64*n*k)*x[8*(8*n+j)+i];
// 				}
// 				sum+=sumj*expFFT<2048>(8*j*k);
// 			}
// 			y[k]+=sum*expFFT<2048>(k*i);
// 		}

// 	//------------- 5 ---------------
// 	// n = 8*n+h
// 	for(int k=0; k<2048; k++)
// 		for(int i=0; i<8; i++){
// 			cmplx<double> sum;
// 			for(int j=0; j<8; j++){
// 				cmplx<double> sumj;
// 				for(int h=0; h<8; h++){
// 					for(int n=0; n<2048/8/8/8; n++){
// 						sumj+=expFFT<2048>(8*8*(8*n+h)*k)*x[8*8*(8*n+h)+8*j+i];
// 					}
// 				}
// 				sum+=sumj*expFFT<2048>(8*j*k);
// 			}
// 			y[k]+=sum*expFFT<2048>(k*i);
// 		}

	//------------- 6 ---------------
// 	for(int k=0; k<2048; k++)
// 		for(int i=0; i<8; i++){
// 			cmplx<double> sumi;
// 			for(int j=0; j<8; j++){
// 				cmplx<double> sumj;
// 				for(int h=0; h<8; h++){
// 					cmplx<double> sumh;
// 					for(int n=0; n<2048/8/8/8; n++){
// 						sumh+=expFFT<2048>(8*8*8*n*k)*x[8*8*8*n+8*8*h+8*j+i];
// 					}
// 					sumj+=sumh*expFFT<2048>(8*8*h*k);
// 				}
// 				sumi+=sumj*expFFT<2048>(8*j*k);
// 			}
// 			y[k]+=sumi*expFFT<2048>(k*i);
// 		}

	//------------- 7 ---------------
	//
	//k=2048/8/8/8*k+kk;
// 	for(int kk=0; kk<2048/8/8/8; kk++)
// 		for(int i=0; i<8; i++){
// 			cmplx<double> sumi;
// 			for(int j=0; j<8; j++){
// 				cmplx<double> sumj;
// 				for(int h=0; h<8; h++){
// 					cmplx<double> sumh;
// 					for(int n=0; n<2048/8/8/8; n++){
// 						vH[8*8*8*kk+8*8*h+8*j+i]+=expFFT<2048>(8*8*8*n*kk)*x[8*8*8*n+8*8*h+8*j+i];
// 					}
// 				}
// 			}
// 		}
// 
// 		for(int k=0; k<2048; k++)
// 			for(int i=0; i<8; i++){
// 				cmplx<double> sumi;
// 				for(int j=0; j<8; j++){
// 					cmplx<double> sumj;
// 					for(int h=0; h<8; h++){
// 						sumj+=vH[8*8*8*(k%4)+8*8*h+8*j+i]*expFFT<2048>(8*8*h*k);
// 					}
// 					sumi+=sumj*expFFT<2048>(8*j*k);
// 				}
// 				y[k]+=sumi*expFFT<2048>(k*i);
// 			}
	//------------- 7 ---------------
	//
	//k=2048/8/8/8*k+kk;
// 	for(int kk=0; kk<2048/8/8/8; kk++)
// 		for(int i=0; i<8; i++){
// 			for(int j=0; j<8; j++){
// 				for(int h=0; h<8; h++){
// 					for(int n=0; n<2048/8/8/8; n++){
// 						vH[8*8*8*kk+8*8*h+8*j+i]+=expFFT<2048>(8*8*8*n*kk)*x[8*8*8*n+8*8*h+8*j+i];
// 					}
// 				}
// 			}
// 		}
// 	//k=2048/8*8*k+kk    k=0..64  k=0..2048/8*8
// 	for(int kk=0; kk<2048/8/8; kk++)
// 		for(int i=0; i<8; i++){
// 			for(int j=0; j<8; j++){
// 				for(int h=0; h<8; h++){
// 					vJ[8*8*kk+8*j+i]+=vH[8*8*8*(kk%(2048/8/8/8))+8*8*h+8*j+i]*expFFT<2048>(8*8*h*kk);
// 				}
// 			}
// 		}
// 
// 	for(int k=0; k<2048; k++){
// 		for(int i=0; i<8; i++){
// 			cmplx<double> sumi;
// 			for(int j=0; j<8; j++){
// 				sumi+=vJ[8*8*(k%(2048/8/8))+8*j+i]*expFFT<2048>(8*j*k);
// 			}
// 			y[k]+=sumi*expFFT<2048>(k*i);
// 		}
// 	}
		//------------- 8 ---------------
		//
// 		//k=2048/8/8/8*k+kk;
// 		for(int kk=0; kk<2048/8/8/8; kk++){
// 			for(int i=0; i<8; i++){
// 				for(int j=0; j<8; j++){
// 					for(int h=0; h<8; h++){
// 						for(int n=0; n<2048/8/8/8; n++){
// 							vH[8*8*8*kk+8*8*h+8*j+i]+=expFFT<2048>(8*8*8*n*kk)*x[8*8*8*n+8*8*h+8*j+i];
// 						}
// 					}
// 				}
// 			}
// 		}
// 		//k=2048/8*8*k+kk    k=0..64  k=0..2048/8*8
// 		for(int kk=0; kk<2048/8/8; kk++){
// 			for(int i=0; i<8; i++){
// 				for(int j=0; j<8; j++){
// 					for(int h=0; h<8; h++){
// 						vJ[8*8*kk+8*j+i]+=vH[8*8*8*(kk%(2048/8/8/8))+8*8*h+8*j+i]*expFFT<2048>(8*8*h*kk);
// 					}
// 				}
// 			}
// 		}
// 		// k=2048/8*k+kk
// 		for(int kk=0; kk<2048/8; kk++){
// 			for(int i=0; i<8; i++){
// 				for(int j=0; j<8; j++){
// 					vI[8*kk+i]+=vJ[8*8*(kk%(2048/8/8))+8*j+i]*expFFT<2048>(8*j*kk);
// 				}
// 			}
// 		}
// 
// 		for(int k=0; k<2048; k++){
// 			for(int i=0; i<8; i++){
// 				y[k]+=vI[8*(k%(2048/8))+i]*expFFT<2048>(k*i);
// 			}
// 		}
		//------------- 9 ---------------
		//
		//k=2048/8/8/8*k+kk;
		for(int kk=0; kk<4; kk++){
			for(int i=0; i<512; i++){
				for(int n=0; n<4; n++){
					vH[512*kk+i]+=X[512*n+i]*expFFT<2048>(512*n*kk);
				}
			}
		}
		//k=2048/8*8*k+kk    k=0..64  k=0..2048/8*8
		for(int kk=0; kk<32; kk++){
			for(int i=0; i<64; i++){
				for(int h=0; h<8; h++){
					vJ[64*kk+i]+=vH[512*(kk%4)+8*8*h+i]*expFFT<2048>(64*h*kk);
				}
			}
		}
		// k=2048/8*k+kk
		for(int kk=0; kk<256; kk++){
			for(int i=0; i<8; i++){
				for(int j=0; j<8; j++){
					vI[8*kk+i]+=vJ[64*(kk%32)+8*j+i]*expFFT<2048>(8*j*kk);
				}
			}
		}

		for(int k=0; k<2048; k++){
			for(int i=0; i<8; i++){
				y[k]+=vI[8*(k%256)+i]*expFFT<2048>(k*i);
			}
		}

	//------------- 2 ---------------

	for(int i=0; i<2048; i++){
		dst[i].re=floor(y[i].re+0.5);
		dst[i].im=floor(y[i].im+0.5);
	}
}



void nmppsFFT2048Fwd4888_RefInt(const nm32sc* src, nm32sc* dst)
{
	vec<cmplx<int> > vX(2048);
	vec<cmplx<int> > vY(2048);
	vec<cmplx<int> > vYRe(2048);
	vec<cmplx<int> > vYIm(2048);

	vec<cmplx<int> > vH(2048);
	vec<cmplx<int> > vHRe(2048);
	vec<cmplx<int> > vHIm(2048);
	vec<cmplx<int> > vI(2048);
	vec<cmplx<int> > vIRe(2048);
	vec<cmplx<int> > vIIm(2048);
	vec<cmplx<int> > vJ(2048);

	int shift[4]={0,7,7,7};
	int amp[4];
	int round[4];

	amp[0]=1;//<<shift[0];
	amp[1]=1<<shift[1];
	amp[2]=1<<shift[2];
	amp[3]=1<<shift[3];
	
	round[0]=0;//amp[0]>>1;
	round[1]=1<<(shift[1]-1);
	round[2]=1<<(shift[2]-1);
	round[3]=1<<(shift[3]-1);

	for(int i=0; i<2048; i++){
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
/*
	for(int kk=0; kk<4; kk++){
		for(int i=0; i<512; i++){
			for(int n=0; n<4; n++){
				vH[512*kk+i]+=vX[512*n+i]*toFix(expFFT<2048>(512*n*kk),amp[0]);
			}
		}
	}
	vH>>=shift[0];
*/

	nm16s* w0re=new nm16s[4*4];
	nm16s* w0im=new nm16s[4*4];

	nm16s* pwre16;
	nm16s* pwim16;

	
	for(int kk=0,ii=0; kk<4; kk++){
		for(int n=0; n<4; n++,ii++){
			z=expFFT<2048>(512*n*kk,1);
			w0re[ii]=z.re;
			w0im[ii]=z.im;
		}
	}


	for(int i=0; i<512; i++){
		load_wfifo(vX.addr(i),512,4);
		pwre16=w0re;
		pwim16=w0im;
		for(int kk=0; kk<4; kk++){
			vsum_data(pwre16,vHRe.addr(512*kk+i),0);
			vsum_data(pwim16,vHIm.addr(512*kk+i),0);
			vH[512*kk+i].re=vHRe[512*kk+i].re-vHIm[512*kk+i].im;
			vH[512*kk+i].im=vHRe[512*kk+i].im+vHIm[512*kk+i].re;
			pwre16+=4;
			pwim16+=4;
		}
	}
	delete w0re;
	delete w0im;

	//512*4
	//CRC32(vH.m_data,2048*2);
//---------------------------------- 1 -----------------------------------------
/*
	for(int kk=0; kk<32; kk++){
 		for(int i=0; i<64; i++){
 			for(int h=0; h<8; h++){
 				vJ[64*kk+i]+=vH[512*(kk%4)+8*8*h+i]*toFix127(expFFT<2048>(64*h*kk),amp[1]);
 			}
 		}
 	}
	vJ+=round[1];
	vJ>>=shift[1];

*/
 


	nm8s* pwre;
	nm8s* pwim;

	nm8s* w1re=new nm8s[4*8*8];
	nm8s* w1im=new nm8s[4*8*8];



	for(int kk=0,ii=0; kk<4; kk++){
		for(int k=0; k<8; k++){	
			for(int h=0; h<8; h++,ii++){
				expFFT127<2048>(64*h*(4*k+kk),amp[1],&z);
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
				vsum_data(pwre,vHRe.addr(ii),round[1]);
				vsum_data(pwim,vHIm.addr(ii),0);
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

	vJ>>=shift[1];

	delete w1re;
	delete w1im;
	//CRC32(vJ.m_data,2048*2);
//---------------------------------- 2 -----------------------------------------
	// k=2048/8*k+kk
/*
	for(int kk=0; kk<256; kk++){
		for(int i=0; i<8; i++){
			for(int j=0; j<8; j++){
				vI[8*kk+i]+=vJ[64*(kk%32)+8*j+i]*toFix127(expFFT<2048>(8*j*kk),amp[2]);
			}
		}
	}
	vI+=round[2];
	vI>>=shift[2];
	*/

	
	nm8s* w2re=new nm8s[32*8*8];
	nm8s* w2im=new nm8s[32*8*8];

	for(int kk=0,ii=0; kk<32; kk++){
		for(int k=0; k<8; k++){		
			for(int j=0; j<8; j++,ii++){
				expFFT127<2048>(8*j*(32*k+kk),amp[2],&z);
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
				vsum_data(pwre,vIRe.addr(ii),round[2]);	// rep 8 data=[ar0++gr0] with vsum ,data,0;
				vsum_data(pwim,vIIm.addr(ii),0);		// rep 8 data=[ar1++gr1] with vsum ,data,0;
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

	vI>>=shift[2];
	delete w2re;
	delete w2im;
	
	// 8*32*8

//---------------------------------- 3 -----------------------------------------
/* 	for(int k=0; k<2048; k++){
 		for(int i=0; i<8; i++){
 			vY[k]+=vI[8*(k%256)+i]*toFix127(expFFT<2048>(k*i),amp[3]);
 		}
 	}
	vY+=round[3];
	vY>>=shift[3];
*/
	nm8s* w3re=new nm8s[256*8*8];
	nm8s* w3im=new nm8s[256*8*8];

	for(int kk=0,ii=0; kk<256; kk++){
		for(int k=0; k<8; k++){
			for(int i=0; i<8; i++,ii++){
				expFFT127<2048>((256*k+kk)*i,amp[3],&z);
				w3re[ii]=z.re;
				w3im[ii]=z.im;
			}
		}
	}
	pwre=w3re;
	pwim=w3im;

	for(int kk=0,ii=0; kk<256; kk++){
		load_wfifo(vI.addr(8*kk),1,8);							// rep 8 wfifo=[ar0++gr0]
		for(int k=0; k<8; k++,ii++){
			vsum_data(pwre,vYRe.addr(ii),round[3]);				// rep 8 data=[ar0++gr0]
			vsum_data(pwim,vYIm.addr(ii),0);					// rep 8 data=[ar1++gr1]
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


	vY>>=shift[3];
	delete w3re;
	delete w3im;

	//------------- 2 ---------------

	for(int i=0; i<2048; i++){
		dst[i].re=vY[i].re;
		dst[i].im=vY[i].im;
	}
}
//всего =  8192*2*2+2048*3=38912

