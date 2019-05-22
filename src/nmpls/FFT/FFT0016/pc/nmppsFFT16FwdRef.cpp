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
#include "fftref.h"
//#include "fftext.h"
#include "nmtl/tcmplx_spec.h"
#include <math.h>

#include "fftexp.h"
#ifndef PI
#define PI 3.14159265359
#endif

#include "nmpp.h"

cmplx<int > toFix(cmplx<double> X, double Ampl);
cmplx<int > toFix127(cmplx<double> X, double Ampl);


	static unsigned crc;

#define CRC32(addres,size) crc=nmppsCrc_32s((nm32s*)addres,size);
void vsum_data(nm16s* data, cmplx<int>* afifo, int vr);
/*
cmplx<double> expFFT<2048>(int power)
{
	cmplx<double> z(0,-2.0*PI*power/2048.0);
	return exp(z);
}
*/

void nmppsDFT16Fwd_RefFloat(const nm32sc* src, nm32sc* dst)
{
	vec<cmplx<double> > x(16);
	vec<cmplx<double> > y(16);

	for (int i = 0; i < 16; i++) {
		x[i].re = src[i].re;
		x[i].im = src[i].im;
	}
	for (int i = 0; i < 16; i++) {
		y[i] = expFFT<16>(0)*x[0];
		for (int j = 1; j < 16; j++) {
			y[i] += expFFT<16>(i*j)*x[j];
		}
	}
	for (int i = 0; i < 16; i++) {
		dst[i].re = floor(y[i].re + 0.5);
		dst[i].im = floor(y[i].im + 0.5);
	}
}


// разделение по частоте 
void nmppsFFT16Fwd2x8_RefFloat(const nm32sc* src, nm32sc* dst)
{
	vec<cmplx<double> > X(16);
	vec<cmplx<double> > Y(16);

	vec<cmplx<double> > A(16);


	for (int i = 0; i < 16; i++) {
		X[i].re = src[i].re;
		X[i].im = src[i].im;
	}

	Y.reset();
	A.reset();
	
	//------------- 0 ---------------
	//for (int i = 0; i < 16; i++)
	//	for (int j = 0; j < 16; j++)
	//		Y[i] += expFFT<16>(i*j)*X[j];
	//------------- 1.0 ---------------
	// j:= j+8*k j=[0..7], k=[0,1]
	//for (int i = 0; i < 16; i++)
	//	for (int j = 0; j < 8; j++)
	//		for (int k = 0; k < 2; k++)
	//			Y[i] += expFFT<16>(i*(j+8*k))*X[j+8*k]; // разделение по частоте : бабочки через 8 отсчетов 
	//------------- 1.1 ---------------
	//for (int i = 0; i < 16; i++)
	//	for (int j = 0; j < 8; j++)
	//		for (int k = 0; k < 2; k++)
	//			Y[i] += expFFT<16>(i*j)*expFFT<16>(8*i*k)*X[j+8*k];
	//------------- 1.2 ---------------
	//for (int i = 0; i < 16; i++) {
	//	for (int j = 0; j < 8; j++){
	//		cmplx<double> sum;
	//		for (int k = 0; k < 2; k++) {
	//			sum += expFFT<16>(8*i*k)*X[j+8*k]; 
	//		}
	//		Y[i] += sum*expFFT<16>(i*j);
	//	}
	//}
	//------------- 1.3 ---------------
	//for (int i = 0; i < 2; i++) {
	//	for (int j = 0; j < 8; j++){
	//		for (int k = 0; k < 2; k++) {
	//			A[j+8*i] += expFFT<16>(8*i*k)*X[j+8*k]; 
	//		}
	//	}
	//}
	//for (int i = 0; i < 16; i++) {
	//	for (int j = 0; j < 8; j++){
	//		Y[i] += expFFT<16>(i*j)*A[j+8*(i%2)];
	//	}
	//}
	//------------- 1.4 ---------------
	//for (int i = 0; i < 2; i++) {
	//	for (int j = 0; j < 8; j++){
	//		for (int k = 0; k < 2; k++) {
	//			A[j+8*i] += expFFT<16>(8*i*k)*X[j+8*k];
	//		}
	//	}
	//}
	//// i:=2*i+ii
	//for (int ii = 0; ii < 2; ii++) {
	//	for (int i = 0; i < 8; i++) {
	//		for (int j = 0; j < 8; j++){
	//			Y[2 * i + ii] +=expFFT<16>((2 * i + ii)*j)* A[j + 8 * ii] ;
	//		}
	//	}
	//}
	//------------- 1.5 ---------------
	// i:=0
	for (int j = 0; j < 8; j++) {
		A[j] = X[j]+X[j+8];
	}
	// i:=1
	for (int j = 0; j < 8; j++){
		A[j+8] += X[j]- X[j + 8];
	}

	for (int ii = 0; ii < 2; ii++) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				Y[2 * i + ii] += expFFT<16>((2 * i + ii)*j)* A[j + 8 * ii];
			}
		}
	}
	for(int i=0; i<16; i++){
		dst[i].re=floor(Y[i].re+0.5);
		dst[i].im=floor(Y[i].im+0.5);
	}
}




void nmppsFFT16Fwd2x8_RefInt(const nm32sc* src, nm32sc* dst)
{
	const nm32sc* pX  = src;
	nm32sc* pY  = dst;
	nm32sc* pA	= nmppsMalloc_32sc(16);
	nm32sc* pB = nmppsMalloc_32sc(16);
	nm32sc* pBRe = nmppsMalloc_32sc(16);
	nm32sc* pBIm = nmppsMalloc_32sc(16);
	
	int round[2];
	int shift[2];
	int ampl[2];
	ampl[1] = 128;
	shift[1] = 7;
	round[1] = 64;
	//---------------------------------- 0 -----------------------------------------
	//for (int j = 0; j < 8; j++) {
	//	A[j] = X[j] + X[j + 8];
	//}
	//// i:=1
	//for (int j = 0; j < 8; j++) {
	//	A[j + 8] += X[j] - X[j + 8];
	//}
	for (int j = 0; j < 8; j++) {
		pA[j].re = pX[j].re + pX[j+8].re;
		pA[j].im = pX[j].im + pX[j+8].im;
	}
	
	for (int j = 0; j < 8; j++) {
		pA[j+8].re = pX[j].re - pX[j+8].re;
		pA[j+8].im = pX[j].im - pX[j+8].im;
	}

	//--------------------------------- 1-------------------
	//for (int ii = 0; ii < 2; ii++) {
	//	for (int i = 0; i < 8; i++) {
	//		for (int j = 0; j < 8; j++) {
	//			Y[2 * i + ii] += expFFT<16>((2 * i + ii)*j)* A[j + 8 * ii];
	//		}
	//	}
	//}

	nm8s* cosTbl = nmppsMalloc_8s(2* 8 * 8);
	nm8s* sinTbl = nmppsMalloc_8s(2* 8 * 8);

	cmplx<int> w;
	int idx = 0;
	for (int ii = 0; ii < 2; ii++) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++,idx++) {
				w = expFFT127<16>((2 * i + ii)*j, ampl[1]);
				nmppsPut_8s(cosTbl, idx, w.re);
				nmppsPut_8s(sinTbl, idx, w.im);
			}
		}
	}


	nm8s* v8cos = cosTbl;
	nm8s* v8sin = sinTbl;

	// asm("vr = %1" : "+r"dummy_vr : "r"(round[1]));

	for (int ii = 0; ii < 2; ii++) {
		load_wfifo(pA + 8*ii, 1, 8);
		for (int i = 0; i < 8; i++) {
			vsum_data(v8cos, pBRe + 2*i + ii, round[1]);	v8cos += 8; 
																		//	asm( 
																		//  rep 1 data=[%0] with vsum ,data,vr;  
																		//  rep 1 [%2] = afifo;
																		//  %0 += 8;
																		//  : "+a" v8cos, "=m" *(pBRe + 2*i) : "a" (pBRe + 2*i), "r"(dummy_vr) )
			vsum_data(v8sin, pBIm + 2*i + ii, 0);			v8sin += 8;
			pB[2 * i + ii].re = pBRe[2 * i + ii].re - pBIm[2 * i + ii].im;
			pB[2 * i + ii].im = pBRe[2 * i + ii].im + pBIm[2 * i + ii].re;
		}
	}

	for (int i = 0; i < 16; i++) {
		pY[i].re = pB[i].re >> shift[1];
		pY[i].im = pB[i].im >> shift[1];
	}

	nmppsFree(cosTbl);
	nmppsFree(sinTbl);


}




// http://ru.dsplib.org/content/fft_dec_in_time/fft_dec_in_time.html
// алогритм БПФ с прореживанием по времени
void nmppsFFT16Fwd2x8Time_RefFloat(const nm32sc* src, nm32sc* dst)
{
	vec<cmplx<double> > X(16);
	vec<cmplx<double> > Y(16);

	vec<cmplx<double> > A(8);
	vec<cmplx<double> > B(8);


	for (int i = 0; i < 16; i++) {
		X[i].re = src[i].re; 
		X[i].im = src[i].im;
	}

	Y.reset();
	A.reset();
	B.reset();

	//------------- 0 ---------------
	//for (int i = 0; i < 16; i++)
	//	for (int j = 0; j < 16; j++)
	//		Y[i] += expFFT<16>(i*j)*X[j];
	//------------- 1.0 ---------------
	// j:= 2*j+k j=[0..7], k=[0,1]		// разделение по времени: бабочки через 2 отсчета
	//for (int i = 0; i < 16; i++)
	//	for (int j = 0; j < 8; j++)
	//		for (int k = 0; k < 2; k++)
	//			Y[i] += expFFT<16>(i*(2 * j + k))*X[2 * j + k];  // разделение по времени: бабочки через 2 отсчета
	//------------- 1.1 ---------------
	//for (int i = 0; i < 16; i++)
	//	for (int j = 0; j < 8; j++)
	//		for (int k = 0; k < 2; k++)
	//			Y[i] += expFFT<16>(2*i*j)*expFFT<16>(i*k)*X[2 * j + k];
	//------------- 1.1 ---------------
	//for (int i = 0; i < 16; i++)
	//	for (int j = 0; j < 8; j++)
	//		Y[i] += expFFT<16>(2*i*j)*(X[2 * j] + expFFT<16>(i)*X[2 * j+1];

	//------------- 1.1 ---------------
	//for (int i = 0; i < 8; i++)
	//	for (int j = 0; j < 8; j++)
	//		Y[i] += expFFT<8>(i*j)*(X[2 * j] + expFFT<16>(i)*X[2 * j + 1]);
	//
	//for (int i = 8; i < 16; i++)
	//	for (int j = 0; j < 8; j++)
	//		Y[i] += expFFT<8>(i*j)*(X[2 * j] + expFFT<16>(i)*X[2 * j + 1]);
	//------------- 1.1 ---------------
	//for (int i = 0; i < 8; i++)
	//	for (int j = 0; j < 8; j++)
	//		Y[i] += expFFT<8>(i*j)*(X[2 * j] + expFFT<16>(i)*X[2 * j + 1]);
	//
	//for (int i = 0; i < 8; i++)
	//	for (int j = 0; j < 8; j++)
	//		Y[i+8] += expFFT<8>(i*j)*(X[2 * j] + expFFT<16>(8+i)*X[2 * j + 1]);

	//------------- 1.1 ---------------
	//for (int i = 0; i < 8; i++)
	//	for (int j = 0; j < 8; j++)
	//		Y[i]   += expFFT<8>(i*j)*(X[2 * j] + expFFT<16>(i)*X[2 * j + 1]);
	//
	//for (int i = 0; i < 8; i++)
	//	for (int j = 0; j < 8; j++)
	//		Y[i+8] += expFFT<8>(i*j)*(X[2 * j] - expFFT<16>(i)*X[2 * j + 1]);
	//------------- 1.1 ---------------
	//for (int i = 0; i < 8; i++)
	//	for (int j = 0; j < 8; j++)
	//		A[i]   += expFFT<8>(i*j)*X[2 * j];
	//
	//for (int i = 0; i < 8; i++) {
	//	for (int j = 0; j < 8; j++)
	//		B[i] += expFFT<8>(i*j)*X[2 * j + 1];
	//}
	//
	//for (int i = 0; i < 8; i++) {
	//	Y[i] = A[i] + expFFT<16>(i)*B[i];
	//}
	//
	//A.reset();
	//B.reset();
	//for (int i = 0; i < 8; i++)
	//	for (int j = 0; j < 8; j++)
	//		A[i] += expFFT<8>(i*j)*X[2 * j];
	//
	//for (int i = 0; i < 8; i++)
	//	for (int j = 0; j < 8; j++)
	//		B[i] += expFFT<8>(i*j)*X[2 * j + 1];
	//
	//for (int i = 0; i < 8; i++)
	//	Y[i+8] = A[i]-expFFT<16>(i)*B[i];
	//
	//------------- 1.1 ---------------
	//for (int i = 0; i < 8; i++)
	//	for (int j = 0; j < 8; j++)
	//		A[i] += expFFT<8>(i*j)*X[2 * j];
	//
	//for (int i = 0; i < 8; i++) {
	//	for (int j = 0; j < 8; j++)
	//		B[i] += expFFT<8>(i*j)*X[2 * j + 1];
	//}
	//
	//for (int i = 0; i < 8; i++) {
	//	Y[i] = A[i] + expFFT<16>(i)*B[i];
	//	Y[i + 8] = A[i] - expFFT<16>(i)*B[i];
	//}

	//------------- 1.1 ---------------
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			A[i] += expFFT<8>(i*j)*X[2 * j];

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++)
			B[i] += expFFT<16>(i)*expFFT<8>(i*j)*X[2 * j + 1];
	}

	for (int i = 0; i < 8; i++) {
		Y[i] = A[i] + B[i];
		Y[i + 8] = A[i] - B[i];
	}

	for (int i = 0; i<16; i++) {
		dst[i].re = floor(Y[i].re + 0.5);
		dst[i].im = floor(Y[i].im + 0.5);
	}
}


// алогритм БПФ с прореживанием по времени и частоте

void nmppsFFT16Fwd242_RefFloat(const nm32sc* src, nm32fc* dst)
{
	vec<cmplx<double> > X(16);
	vec<cmplx<double> > Y(16);

	vec<cmplx<double> > A(8);
	vec<cmplx<double> > B(8);
	vec<cmplx<double> > C(8);
	vec<cmplx<double> > D(8);


	for (int i = 0; i < 16; i++) {
		X[i].re = src[i].re;
		X[i].im = src[i].im;
	}

	Y.reset();
	A.reset();
	B.reset();

	// предыдущий вывод в предыдущей функции
	//------------- 10 ---------------
	//for (int i = 0; i < 8; i++)
	//	for (int j = 0; j < 8; j++)
	//		A[i] += expFFT<8>(i*j)*X[2 * j];
	//
	//for (int i = 0; i < 8; i++) {
	//	for (int j = 0; j < 8; j++)
	//		B[i] += expFFT<8>(i*j)*X[2 * j + 1];
	//}
	//
	//for (int i = 0; i < 8; i++) {
	//	B[i] *= expFFT<16>(i);
	//}
	//for (int i = 0; i < 8; i++) {
	//	Y[i] = A[i] + B[i];
	//	Y[i + 8] = A[i] - B[i];
	//}

	////------------- 11 ---------------
	//// j:= j+4*k j=[0..4], k=[0,1]
	//for (int i = 0; i < 8; i++)
	//	for (int j = 0; j < 4; j++)
	//		for (int k = 0; k < 2; k++)
	//			A[i] += expFFT<8>(i*(j+4*k))*X[2 * (j + 4 * k)];
	//// j:= j+4*k j=[0..4], k=[0,1]
	//for (int i = 0; i < 8; i++) {
	//	for (int j = 0; j < 4; j++)
	//		for (int k = 0; k < 2; k++)
	//			B[i] += expFFT<8>(i*(j + 4 * k))*X[2 * (j + 4 * k) + 1];
	//}
	//
	//for (int i = 0; i < 8; i++) {
	//	B[i] *= expFFT<16>(i);
	//}
	//for (int i = 0; i < 8; i++) {
	//	Y[i] = A[i] + B[i];
	//	Y[i + 8] = A[i] - B[i];
	//}

	//------------- 12 ---------------
	// j:= j+4*k j=[0..4], k=[0,1]
	//for (int i = 0; i < 8; i++)
	//	for (int j = 0; j < 4; j++)
	//		for (int k = 0; k < 2; k++) {
	//			A[i] += X[2 * (j + 4 * k)]     * expFFT<8>(i*j) * expFFT<8>(4*i*k);
	//			B[i] += X[2 * (j + 4 * k) + 1] * expFFT<8>(i*j) * expFFT<8>(4*i*k);
	//		}
	//for (int i = 0; i < 8; i++) 
	//	B[i] *= expFFT<16>(i);
	//
	//for (int i = 0; i < 8; i++) {
	//	Y[i] = A[i] + B[i];
	//	Y[i + 8] = A[i] - B[i];
	//}

	////------------- 13 ---------------
	//// j:= j+4*k j=[0..4], k=[0,1]
	//for (int i = 0; i < 8; i++)
	//	for (int j = 0; j < 4; j++){
	//			A[i] += X[2 * j]     * expFFT<8>(i*j) + X[2 * (j + 4 * 1)] * expFFT<8>(i*j) * expFFT<8>(4 * i);
	//			B[i] += X[2 * j + 1] * expFFT<8>(i*j) + X[2 * (j + 4 * 1) + 1] * expFFT<8>(i*j) * expFFT<8>(4 * i);
	//		}
	//for (int i = 0; i < 8; i++)
	//	B[i] *= expFFT<16>(i);
	//
	//for (int i = 0; i < 8; i++) {
	//	Y[i] = A[i] + B[i];
	//	Y[i + 8] = A[i] - B[i];
	//}
	//------------- 14 ---------------
	//i:=2*i+ii i=[0..4] ii=[0,1]
	//for(int ii=0; ii<2; ii++)
	//	for (int i = 0; i < 4; i++)
	//		for (int j = 0; j < 4; j++) {
	//			A[2 * i + ii] += X[2 * j] * expFFT<8>((2 * i + ii)*j)		+ X[2 * (j + 4 * 1)]	* expFFT<8>((2 * i + ii)*j) * expFFT<8>(4 * (2 * i + ii));
	//			B[2 * i + ii] +=(X[2 * j + 1] * expFFT<8>((2 * i + ii)*j)	+ X[2 * (j + 4 * 1) + 1]* expFFT<8>((2 * i + ii)*j) * expFFT<8>(4 * (2 * i + ii)))* expFFT<16>(2 * i + ii);
	//		}
	//for (int i = 0; i < 8; i++) {
	//	Y[i] = A[i] + B[i];
	//	Y[i + 8] = A[i] - B[i];
	//}
	//------------- 15 ---------------
	//for (int ii = 0; ii<2; ii++)
	//	for (int i = 0; i < 4; i++)
	//		for (int j = 0; j < 4; j++) {
	//			A[2 * i + ii] += X[2 * j]		* expFFT<8>(2 * i *j)* expFFT<8>(ii*j) + X[2 * (j + 4 * 1)]		* expFFT<8>(2 * i *j) * expFFT<8>(ii*j) *expFFT<8>(4 * ii);
	//			B[2 * i + ii] +=(X[2 * j + 1]	* expFFT<8>(2 * i *j)* expFFT<8>(ii*j) + X[2 * (j + 4 * 1) + 1]	* expFFT<8>(2 * i *j) * expFFT<8>(ii*j) *expFFT<8>(4 * ii))*expFFT<8>(i)*expFFT<16>(ii);
	//		}
	//
	//for (int i = 0; i < 8; i++) {
	//	Y[i] = A[i] + B[i];
	//	Y[i + 8] = A[i] - B[i];
	//}

	////------------- 16 ---------------
	////ii:=0; 
	//for (int i = 0; i < 4; i++)
	//	for (int j = 0; j < 4; j++) {
	//		A[2 * i] += X[2 * j]		* expFFT<8>(2 * i *j)	+ X[2 * (j + 4 * 1)]		* expFFT<8>(2 * i *j);
	//		B[2 * i] += (X[2 * j + 1]	* expFFT<8>(2 * i *j)	+ X[2 * (j + 4 * 1) + 1]	* expFFT<8>(2 * i *j))*expFFT<8>(i);
	//	}
	////ii:=1
	//for (int i = 0; i < 4; i++)
	//	for (int j = 0; j < 4; j++) {
	//		A[2 * i + 1] += X[2*j]		* expFFT<8>(2 * i *j)* expFFT<8>(j) + X[2 * (j + 4 * 1)] * expFFT<8>(2 * i *j) * expFFT<8>(j) *expFFT<8>(4 );
	//		B[2 * i + 1] +=(X[2*j+1]	* expFFT<8>(2 * i *j)* expFFT<8>(j) + X[2 * (j + 4 * 1) + 1] * expFFT<8>(2 * i *j) * expFFT<8>(j) *expFFT<8>(4))*expFFT<8>(i)*expFFT<16>(1);
	//	}
	//
	//for (int i = 0; i < 8; i++) {
	//	Y[i] = A[i] + B[i];
	//	Y[i + 8] = A[i] - B[i];
	//}

	//------------- 17 ---------------
	//for (int i = 0; i < 4; i++)
	//	for (int j = 0; j < 4; j++) {
	//		A[2*i] += (X[2*j]		+ X[2*j+8]  )	* expFFT<8>(2*i*j);
	//		B[2*i] += (X[2*j+1]		+ X[2*j+8+1])	* expFFT<8>(2*i*j+i);
	//	}
	//
	//for (int i = 0; i < 4; i++)
	//	for (int j = 0; j < 4; j++) {
	//		A[2*i+1] +=(X[2*j]		- X[2*j+8]  )	* expFFT<8>(2*i*j+j) ;
	//		B[2*i+1] +=(X[2*j+1]	- X[2*j+8+1])	* expFFT<8>(2*i*j+j+i)*expFFT<16>(1);
	//	}
	//
	//for (int i = 0; i < 8; i++) {
	//	Y[i]	= A[i] + B[i];
	//	Y[i + 8]= A[i] - B[i];
	//}
	//------------- 17 ---------------
	for (int j = 0; j < 8; j++) {
		//C[2 * j]   = X[2 * j] + X[2 * j + 8];
		//C[2 * j+1] = X[2 * j + 1] + X[2 * j + 8 + 1];
		C[j] = X[j] + X[j + 8];

		//D[2 * j ]    = X[2 * j] - X[2 * j + 8];
		//D[2 * j + 1] = X[2 * j + 1] - X[2 * j + 8 + 1];
		D[j] = X[j] - X[j + 8];
	}


	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			//A[2 * i] += (X[2 * j] + X[2 * j + 8])	* expFFT<8>(2 * i*j);
			//B[2 * i] += (X[2 * j + 1] + X[2 * j + 8 + 1])	* expFFT<8>(2 * i*j + i);
			A[2 * i] += C[2 * j] * expFFT<8>(2 * i*j);
			B[2 * i] += C[2 * j + 1] * expFFT<8>(2 * i*j + i);
		}

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			A[2 * i + 1] += D[2 * j] * expFFT<8>(2 * i*j + j);
			B[2 * i + 1] += D[2 * j + 1] * expFFT<16>(2 * (2 * i*j + j + i) + 1);
		}

	for (int i = 0; i < 8; i++) {
		Y[i] = A[i] + B[i];
		Y[i + 8] = A[i] - B[i];
	}

	for (int i = 0; i<16; i++) {
		dst[i].re =Y[i].re;
		dst[i].im =Y[i].im;
	}
}

void nmppsFFT16Fwd242_RefFloat(const nm32sc* src, nm32sc* dst)
{
	nm32fc Y[32];
	nmppsFFT16Fwd242_RefFloat(src, Y);

	for (int i = 0; i<16; i++) {
		dst[i].re = floor(Y[i].re + 0.5);
		dst[i].im = floor(Y[i].im + 0.5);
	}
}



void nmppsFFT16Fwd242_RefInt(const nm32sc* src, nm32sc* dst)
{
	vec<cmplx<int> > X(16);
	vec<cmplx<int> > Y(16);
			  
	vec<cmplx<int> > A(8);
	vec<cmplx<int> > B(8);
	vec<cmplx<int> > C(8);
	vec<cmplx<int> > D(8);


	for (int i = 0; i < 16; i++) {
		X[i].re = src[i].re;
		X[i].im = src[i].im;
	}

	Y.reset();
	A.reset();
	B.reset();

	int shift = 8;
	int amplitude = 1 << shift;
	cmplx<int> round;
	round.re =  amplitude >> 1;
	round.im =  amplitude >> 1;
	//------------- 17 ---------------
	for (int j = 0; j < 8; j++) {
		C[j] = X[j] + X[j + 8];
		D[j] = X[j] - X[j + 8];
	}


	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			
			A[2 * i] += C[2 * j]		* expFFT<8>(2 * i*j, amplitude);
			B[2 * i] += C[2 * j + 1]	* expFFT<8>(2 * i*j + i, amplitude);
		}

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			A[2 * i + 1] += D[2 * j]	* expFFT<8>(2 * i*j + j, amplitude);
			B[2 * i + 1] += D[2 * j + 1]* expFFT<16>(2*(2 * i*j + j + i)+1, amplitude);
		}

	for (int i = 0; i < 8; i++) {
		A[i] += round;
		Y[i] = A[i] + B[i] ;
		Y[i + 8] = A[i] - B[i] ;
	}

	for (int i = 0; i<16; i++) {
		dst[i].re = Y[i].re  >> shift;
		dst[i].im = Y[i].im  >> shift;
	}
}


void nmppsFFT16Fwd242_RefNmc(const nm32sc* src, nm32sc* dst)
{

	const nm32sc* X = src;
	
	//for (int i = 0; i < 16; i++) {
	//	X[i].re = src[i].re;
	//	X[i].im = src[i].im;
	//}

	//Y.reset();
	//A.reset();
	//B.reset();

	int shift = 8;
	int amplitude = 1 << shift;
	//cmplx<int> round;
	int round = amplitude >> 1;
	//round.im = amplitude >> 1;
	


	nm16s wRe[16*4];
	nm16s wIm[16*4];
	nm32sc ARe[8];
	nm32sc AIm[8];
	nm32sc C[8];
	nm32sc D[8];
	nm32sc Y[16];
	nm32sc A[8];
	nm32sc BRe[8];
	nm32sc BIm[8];
	nm32sc B[8];

	nm16s* pwRe=wRe;
	nm16s* pwIm=wIm;
	
	int k = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++, k++) {
			cmplx<int> w = expFFT<8>(2 * i*j, amplitude);
			nmppsPut_16s(wRe, k, w.re);
			nmppsPut_16s(wIm, k, w.im);
		}

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++,k++) {
			cmplx<int> w = expFFT<8>(2 * i*j + i, amplitude);
			nmppsPut_16s(wRe, k, w.re);
			nmppsPut_16s(wIm, k, w.im);
		}
	
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++, k++) {
			cmplx<int> w = expFFT<8>(2 * i*j + j, amplitude);
			nmppsPut_16s(wRe, k, w.re);
			nmppsPut_16s(wIm, k, w.im);
		}

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++, k++) {
			cmplx<int> w = expFFT<16>(2 * (2 * i*j + j + i) + 1, amplitude);
			nmppsPut_16s(wRe, k, w.re);
			nmppsPut_16s(wIm, k, w.im);
		}


	//------------- 17 ---------------
	//for (int j = 0; j < 8; j++) {
	//	C[j] = X[j] + X[j + 8];
	//	D[j] = X[j] - X[j + 8];
	//}

	for (int j = 0; j < 8; j++) {
		C[j].re = X[j].re + X[j + 8].re;
		C[j].im = X[j].im + X[j + 8].im;
		D[j].re = X[j].re - X[j + 8].re;
		D[j].im = X[j].im - X[j + 8].im;
	}
	//[32]

	//for (int i = 0; i < 4; i++)
	//	for (int j = 0; j < 4; j++) {
	//		A[2 * i] += C[2 * j]	 * expFFT<8>(2 * i*j, amplitude);
	//		B[2 * i] += C[2 * j + 1] * expFFT<8>(2 * i*j + i, amplitude);
	//	}

	load_wfifo(C,2,4);
	for (int i = 0; i < 4; i++) {
		vsum_data(pwRe, ARe +2*i, round);
		vsum_data(pwIm, AIm +2*i, 0);
		pwRe += 4;
		pwIm += 4;
	}
	//[8]
	
	load_wfifo(C+1, 2, 4);
	for (int i = 0; i < 4; i++) {
		vsum_data(pwRe, BRe+2*i, 0);
		vsum_data(pwIm, BIm+2*i, 0);
		pwRe += 4;
		pwIm += 4;
	}
	//[8]
		

	//for (int i = 0; i < 4; i++)
	//	for (int j = 0; j < 4; j++) {
	//		A[2 * i + 1] += D[2 * j] * expFFT<8>(2 * i*j + j, amplitude);
	//		B[2 * i + 1] += D[2 * j + 1] * expFFT<16>(2 * (2 * i*j + j + i) + 1, amplitude);
	//	}

	load_wfifo(D, 2, 4);
	for (int i = 0; i < 4; i++) {
		vsum_data(pwRe, ARe + 2 * i+1, round);
		vsum_data(pwIm, AIm + 2 * i+1, 0);
		pwRe += 4;
		pwIm += 4;
	}
	//[8]

	load_wfifo(D + 1, 2, 4);
	for (int i = 0; i < 4; i++) {
		vsum_data(pwRe, BRe + 2 * i+1, 0);
		vsum_data(pwIm, BIm + 2 * i+1, 0);
		pwRe += 4;
		pwIm += 4;
	}
	//[8]

	//------------
	for (int i = 0; i<8; i++) {
		A[i].re = ARe[i].re - AIm[i].im;
		A[i].im = ARe[i].im + AIm[i].re;
		B[i].re = BRe[i].re - BIm[i].im;
		B[i].im = BRe[i].im + BIm[i].re;
	}
	//[16]

	for (int i = 0; i < 8; i++) {
		Y[i].re = A[i].re + B[i].re;
		Y[i].im = A[i].im + B[i].im;
		Y[i + 8].re = A[i].re - B[i].re;
		Y[i + 8].im = A[i].im - B[i].im;
	}
	//[16]

	for (int i = 0; i<16; i++) {
		dst[i].re = Y[i].re >> shift;
		dst[i].im = Y[i].im >> shift;
	}
	//[16]
	//: 32+4*8+2*16+16 = 112 tick (peak performance)
}
// [242]	16-bit scheme: 32+4*8+2*16+16 = 112 tick (peak performance)
// [16]		16-bit scheme: 256/4*2+16+16 = 160
// [16]		8-bit  scheme: 256/8*2+16+16 = 96
// [2x8]	8-bit  scheme: 32+2*16+16+16 = 96
// [8x2]	8-bit  scheme: 2*16+16+16+16 = 80 ?

// http://ru.dsplib.org/content/fft_dec_in_freq/fft_dec_in_freq.html
// алогритм бпф с прореживанием по частоте 
void nmppsFFT16Fwd2x8Freq_RefFloat(const nm32sc* src, nm32sc* dst)
{
	vec<cmplx<double> > X(16);
	vec<cmplx<double> > Y(16);

	vec<cmplx<double> > A(8);
	vec<cmplx<double> > B(8);


	for (int i = 0; i < 16; i++) {
		X[i].re = src[i].re;
		X[i].im = src[i].im;
	}

	Y.reset();
	A.reset();
	B.reset();

	//------------- 0 ---------------
	//for (int i = 0; i < 16; i++)
	//	for (int j = 0; j < 16; j++)
	//		Y[i] += expFFT<16>(i*j)*X[j];
	//-------------------------------
	// j:= j+8*k j=[0..7], k=[0,1]
	//for (int i = 0; i < 16; i++)
	//	for (int j = 0; j < 8; j++)
	//		for (int k = 0; k < 2; k++)
	//			Y[i] += expFFT<16>(i*j)*expFFT<16>(i* 8 * k)*X[j+8*k]; // разделение по частоте : бабочки через 8 отсчетов
	//																  
	//-------------------------------
	//i:=2*i+ii i=[0..7] ii=[0,1]
	//for(int ii=0; ii<2; ii++)
	//	for (int i = 0; i < 8; i++)
	//		for (int j = 0; j < 8; j++)
	//			for (int k = 0; k < 2; k++)
	//				Y[2 * i + ii] += expFFT<16>((2 * i + ii)*j)*expFFT<16>((2 * i + ii) * 8 * k)*X[j + 8 * k];
	//----------------------------------
	//for (int ii = 0; ii<2; ii++)
	//	for (int i = 0; i < 8; i++)
	//		for (int j = 0; j < 8; j++)
	//			for (int k = 0; k < 2; k++)
	//				Y[2 * i + ii] += expFFT<16>(2 * i *j)*expFFT<16>(ii*j)*expFFT<16>(2 * i * 8 * k)*expFFT<16>(ii * 8 * k)*X[j + 8 * k];
	//
	//----------------------------------
	// for (int ii = 0; ii<2; ii++)
	//	  for (int i = 0; i < 8; i++)
	//		  for (int j = 0; j < 8; j++)
	//			  for (int k = 0; k < 2; k++)
	//				  Y[2 * i + ii] += expFFT<16>(2 * i *j)*expFFT<16>(ii*j)*expFFT<16>(ii * 8 * k)*X[j + 8 * k];
	//---------
	//// ii:= 0;
	//  for (int i = 0; i < 8; i++)
	//	  for (int j = 0; j < 8; j++)
	//		  for (int k = 0; k < 2; k++)
	//			  Y[2 * i] += expFFT<16>(2 * i *j)*X[j + 8 * k];
	//  //ii: = 1;
	//	for (int i = 0; i < 8; i++)
	//		  for (int j = 0; j < 8; j++)
	//			  for (int k = 0; k < 2; k++)
	//				  Y[2 * i + 1] += expFFT<16>(2 * i *j)*expFFT<16>(j)*expFFT<16>(8 * k)*X[j + 8 * k];
	//
	//----------
	//	//ii = 0;
	//	for (int i = 0; i < 8; i++)
	//		for (int j = 0; j < 8; j++)
	//				Y[2 * i] += expFFT<8>(i *j)*(X[j ] + X[j + 8 ]);
	//	//ii = 1;
	//	for (int i = 0; i < 8; i++)
	//		for (int j = 0; j < 8; j++)
	//			Y[2 * i + 1] += expFFT<16>(j*(2*i+1))*(X[j]- X[j + 8]);
	//----------
	//	//ii = 0;
	//	for (int i = 0; i < 8; i++)
	//		for (int j = 0; j < 8; j++)
	//				Y[2 * i] += expFFT<8>(i *j)*(X[j ] + X[j + 8 ]);
	//	//ii = 1;
	//	for (int i = 0; i < 8; i++)
	//		for (int j = 0; j < 8; j++)
	//			Y[2 * i + 1] += expFFT<8>(j*i)*expFFT<16>(j)*(X[j]- X[j + 8]);
	//----------
	//for (int j = 0; j < 8; j++) {
	//	A[j] = (X[j] + X[j + 8]);
	//	B[j] = (X[j] - X[j + 8])*expFFT<16>(j);
	//}
	//for (int i = 0; i < 8; i++)
	//	for (int j = 0; j < 8; j++)
	//		Y[2 * i] += expFFT<8>(i *j)*A[j];
	//
	//for (int i = 0; i < 8; i++)
	//	for (int j = 0; j < 8; j++)
	//		Y[2 * i + 1] += expFFT<8>(i*j)*B[j];
	//----------
	for (int j = 0; j < 8; j++) {
		A[j] = (X[j] + X[j + 8]);
		B[j] = (X[j] - X[j + 8]);
	}
	//[32]
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			Y[2*i] += A[j] * expFFT<8>(i *j);
	//[16]
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			Y[2*i+1] += B[j] * expFFT<8>(i*j)* expFFT<16>(j);
	//[16]
	//[16]
	for (int i = 0; i<16; i++) {
		dst[i].re = floor(Y[i].re + 0.5);
		dst[i].im = floor(Y[i].im + 0.5);
	}
	//[16]
	//: 32+16*4=96
}