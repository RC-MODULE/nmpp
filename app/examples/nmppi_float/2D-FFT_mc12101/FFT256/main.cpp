//***************************************************************************************************************/
//*                     RC Module Inc., Moscow, Russia                                                          */
//*                     NeuroMatrix(r) NM640x Software                                                          */
//*                                                                                                             */
//*   Software design:  A.Brodyazhenko 																            */
//*   Year: 2018                                                                                                */
//*   This file is the example for to work with 2D-FFT256Fwd/Inv												*/
//***************************************************************************************************************/

#include "dma.h"
#include "nmpp.h"
#include "time.h"
#include <stdio.h>
#include "fft_32fcr.h"
#include "fft_macro.h"

#define		WIDTH			256
#define		HEIGHT			256
#define		FFT_SIZE		WIDTH * HEIGHT

#ifdef __GNUC__
/**************************NMC-GCC************************/
__attribute__((section(".data_imu1"))) 	nm32fcr buffSRAM[WIDTH];

__attribute__((section(".data_DDR"))) nm32fcr srcFwd[FFT_SIZE];
__attribute__((section(".data_DDR"))) nm32fcr srcInv[FFT_SIZE];
__attribute__((section(".data_DDR"))) nm32fcr dstInv[FFT_SIZE];
__attribute__((section(".data_DDR"))) nm32fcr buffDDR[FFT_SIZE];

#else
/***************************NMCC*************************/
#pragma data_section ".data_imu1"
	nm32fcr buffSRAM[WIDTH];

#pragma data_section ".data_DDR"
	nm32fcr srcFwd[FFT_SIZE];
	nm32fcr srcInv[FFT_SIZE];
	nm32fcr dstInv[FFT_SIZE];
	nm32fcr buffDDR[FFT_SIZE];

#endif

/***************Interface of 2D-FFT256********************/
void nmppiFFT256Fwd_32fcr(const nm32fcr* pSrc, nm32fcr* pDst, nm32fcr* bufferDDR, nm32fcr* bufferSRAM, NmppsFFTSpec_32fcr* spec);
void nmppiFFT256Inv_32fcr(const nm32fcr* pSrc, nm32fcr* pDst, nm32fcr* bufferDDR, nm32fcr* bufferSRAM, NmppsFFTSpec_32fcr* spec);

int main()
{
	int status;
	NmppsFFTSpec_32fcr* specFwd;
	NmppsFFTSpec_32fcr* specInv;

	status = nmppsFFT256FwdInitAlloc_32fcr(&specFwd);				   // init struct of coeffs for FFTFwd
	if(status) return status;

	status = nmppsFFT256InvInitAlloc_32fcr(&specInv);				   // init struct of coeffs for FFTInv
	if(status) return status;

	for(int i = 0; i < FFT_SIZE; i++) {								   // init input array
		srcFwd[i].re = i;
		srcFwd[i].im = 0;
	}

	halOpenDMA();													  // init DMA

	// nmppiFFT256Inv_32fcr(srcInv, dstInv, buffDDR, buffSRAM, specInv); // computing 2D-FFT256Inv
	clock_t t1, t2;
	t1 = clock();
	FFT_FWD_2D(srcFwd, srcInv, buffDDR, buffSRAM, specFwd, 256);
	//nmppiFFT256Fwd_32fcr(srcFwd, srcInv, buffDDR, buffSRAM, specFwd); // computing 2D-FFT256Fwd
	t2 = clock();
	FFT_INV_2D(srcInv, dstInv, buffDDR, buffSRAM, specInv, 256);

	status = nmppsFFTFree_32fcr(specFwd);
	if(status) return status;

	status = nmppsFFTFree_32fcr(specInv);
	if(status) return status;

	float norm;
	nmppsNormDiff_L2_32fcr(srcFwd, dstInv, FFT_SIZE, &norm);
	printf("%.7f\n", norm);

	// for(int i = 0; i < FFT_SIZE; i++) {
	// 	printf("%.7f   %.7f\n", dstInv[i].re, dstInv[i].im);
	// }

	return t2 - t1;
}

// perfomance (DMA copies consistently by 1 line):
// 2D-FFT256 : ~2.08 * 10^6 ticks
