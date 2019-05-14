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
#define DISABLE_PRINTX
//#include "internal.h"
//#include "fft.h"
#include "fft.h"
#include "fftref.h"
//#include "fftext.h"
#include "nmtl/tcmplx_spec.h"
#include <math.h>
#include "printx.h"
#include "fftexp.h"
#ifndef PI
#define PI 3.14159265359
#endif




#include "nmpp.h"
extern "C" {

	void nmppsFFT16Fwd242Raw(const nm32sc* src, nm32sc* dst, NmppsFFTSpec* spec )
	{

		const nm32sc* X = src;

		//for (int i = 0; i < 16; i++) {
		//	X[i].re = src[i].re;
		//	X[i].im = src[i].im;
		//}

		//Y.reset();
		//A.reset();
		//B.reset();

		int shift = spec->norm[0].shift;
		//int amplitude = spec->amp[0];
		int round = spec->norm[0].round;
		//round.im = amplitude >> 1;


		//nm32sc ARe[8];
		//nm32sc AIm[8];
		nm32sc* ARe = spec->buffer[0];
		nm32sc* AIm = spec->buffer[0]+8;
		nm32sc C[8];
		nm32sc D[8];
		nm32sc* Y=dst;
		nm32sc A[8];
		nm32sc* BRe = spec->buffer[1];
		nm32sc* BIm = spec->buffer[1]+8;
		nm32sc B[8];

		nm16s* pwRe = (nm16s*)spec->fftTable[0];
		nm16s* pwIm = (nm16s*)spec->fftTable[1];



		//------------- 0 ---------------
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

		//------------- 1.0 ---------------
		//for (int i = 0; i < 4; i++)
		//	for (int j = 0; j < 4; j++) {
		//		A[2 * i] += C[2 * j]	 * expFFT<8>(2 * i*j, amplitude);
		//		B[2 * i] += C[2 * j + 1] * expFFT<8>(2 * i*j + i, amplitude);
		//	}

		PRINT_MATRIX_32S("[pC]", C, 8, 2);
		PRINT_MATRIX_32S("[pD]", D, 8, 2);
		
		load_wfifo(C, 2, 4);
		PRINT_MATRIX_16S("[pWRe]", pwRe, 4, 4);
		PRINT_MATRIX_16S("[pWIm]", pwIm, 4, 4);
		

		for (int i = 0; i < 4; i++) {
			vsum_data(pwRe, ARe + 2 * i, round);
			vsum_data(pwIm, AIm + 2 * i, 0);
			pwRe += 4;
			pwIm += 4;
		}
		//[8]
		PRINT_MATRIX_32X("[pARe]", ARe, 8, 2);
		PRINT_MATRIX_32X("[pAIm]", AIm, 8, 2);
		//------------- 1.1 ---------------

		load_wfifo(C + 1, 2, 4);
		for (int i = 0; i < 4; i++) {
			vsum_data(pwRe, BRe + 2 * i, 0);
			vsum_data(pwIm, BIm + 2 * i, 0);
			pwRe += 4;
			pwIm += 4;
		}
		//[8]

		PRINT_MATRIX_32X("[pBRe]", BRe, 8, 2);
		PRINT_MATRIX_32X("[pBIm]", BIm, 8, 2);

		//------------- 1.2 ---------------
		//for (int i = 0; i < 4; i++)
		//	for (int j = 0; j < 4; j++) {
		//		A[2 * i + 1] += D[2 * j] * expFFT<8>(2 * i*j + j, amplitude);
		//		B[2 * i + 1] += D[2 * j + 1] * expFFT<16>(2 * (2 * i*j + j + i) + 1, amplitude);
		//	}

		load_wfifo(D, 2, 4);
		for (int i = 0; i < 4; i++) {
			vsum_data(pwRe, ARe + 2 * i + 1, round);
			vsum_data(pwIm, AIm + 2 * i + 1, 0);
			pwRe += 4;
			pwIm += 4;
		}
		PRINT_MATRIX_32X("[pARe]", ARe, 8, 2);
		PRINT_MATRIX_32X("[pAIm]", AIm, 8, 2);

		//[8]
		//------------- 1.3 ---------------
		load_wfifo(D + 1, 2, 4);
		for (int i = 0; i < 4; i++) {
			vsum_data(pwRe, BRe + 2 * i + 1, 0);
			vsum_data(pwIm, BIm + 2 * i + 1, 0);
			pwRe += 4;
			pwIm += 4;
		}
		PRINT_MATRIX_32X("[pBRe]", BRe, 8, 2);
		PRINT_MATRIX_32X("[pBIm]", BIm, 8, 2);

		//[8]

		//------------2.0
		for (int i = 0; i < 8; i++) {
			A[i].re = ARe[i].re - AIm[i].im;
			A[i].im = ARe[i].im + AIm[i].re;
			B[i].re = BRe[i].re - BIm[i].im;
			B[i].im = BRe[i].im + BIm[i].re;
		}
		//[16]

		PRINT_MATRIX_32X("[pA]", A, 8, 2);
		PRINT_MATRIX_32X("[pB]", B, 8, 2);


		//------------3.0
		for (int i = 0; i < 8; i++) {
			Y[i].re = A[i].re + B[i].re;
			Y[i].im = A[i].im + B[i].im;
			Y[i + 8].re = A[i].re - B[i].re;
			Y[i + 8].im = A[i].im - B[i].im;
		}
		PRINT_MATRIX_32X("[pY]", Y, 16, 2);
		//[16]

		//for (int i = 0; i < 16; i++) {
		//	dst[i].re = Y[i].re >> shift;
		//	dst[i].im = Y[i].im >> shift;
		//}
		//[16]
		//: 32+4*8+2*16+16 = 112 tick (peak performance)
	}
	// [242]	16-bit scheme: 32+4*8+2*16+16 = 112 tick (peak performance)
	// [16]		16-bit scheme: 256/4*2+16+16 = 160
	// [16]		8-bit  scheme: 256/8*2+16+16 = 96
	// [2x8]	8-bit  scheme: 32+2*16+16+16 = 96
	// [8x2]	8-bit  scheme: 2*16+16+16+16 = 80 ?

	void nmppsFFT16Fwd242(const nm32sc* src, nm32sc* dst, NmppsFFTSpec* spec) {
		int shift = spec->norm[0].shift;

		nm32sc* raw = spec->buffer[1];
		spec->buffer[1] = dst;
		//dst = raw;
		nmppsFFT16Fwd242Raw(src, raw, spec);

		PRINT_MATRIX_32X("raw", raw, 16, 2);

		for (int i = 0; i < 16; i++) {
			dst[i].re = raw[i].re >> shift;
			dst[i].im = raw[i].im >> shift;
		}
		spec->buffer[1] = raw;
	}

};