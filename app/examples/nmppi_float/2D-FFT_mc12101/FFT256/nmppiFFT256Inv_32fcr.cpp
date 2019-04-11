//***************************************************************************************************************/
//*                     RC Module Inc., Moscow, Russia                                                          */
//*                     NeuroMatrix(r) NM640x Software                                                          */
//*                                                                                                             */
//*   Software design:  A.Brodyazhenko 																            */
//*   Year: 2018                                                                                                */
//*                                                                                                             */
//* Prototype: void nmppiFFTInv_32fcr(const nm32fcr* pSrc, nm32fcr* pDst,										*/
//*										 nm32fcr* bufferDDR, nm32fcr* bufferSRAMw, nm32fcr* bufferSRAMh,		*/						*/
//*										 NmppsFFTSpec_32fcr* spec, int width, int height); 						*/
//* 																								            */
//* pSrc   		 - input matrix in DDR (size = width * height),													*/
//* pDst   		 - output matrix in DDR (size = width * height),												*/
//* bufferDDR    - temporary matrix in DDR (size = width * height)												*/
//*	bufferSRAMw  - temporary vector for strings in SRAM (size = width)										    */
//*	bufferSRAMh  - temporary vector for columns in SRAM (size = height)										    */
//* spec		 - struct of coeffs for 1D-FFT                              									*/
//* Description: This function computes inverse 2D-FFT (floating point) from the intput matrix.					*/
//*     It works on mc12101 only. Before start this function necessary to call halOpenDMA()! See main.cpp       */
//***************************************************************************************************************/

#include "dma.h"
#include "nmpp.h"
#include "fft_32fcr.h"

void nmppiFFT256Inv_32fcr(
						const nm32fcr* pSrc,
						nm32fcr* pDst,
						nm32fcr* bufferDDR,
						nm32fcr* bufferSRAM,
						NmppsFFTSpec_32fcr* spec
						)
{
	for(int offset = 0; offset < 256 * 256; offset += 256) {
		halInitStatusSingleDMA((nm32fcr*)(pSrc + offset), (nm32fcr*)((int)bufferSRAM + 0x40000), 2 * 256);
		while(halStatusDMA());

		nmppsFFT256Inv_32fcr(bufferSRAM, bufferSRAM, spec);

		halInitStatusSingleDMA((nm32fcr*)((int)bufferSRAM + 0x40000), (nm32fcr*)(bufferDDR + offset), 2 * 256);
		while(halStatusDMA());
	}

	for(int h = 0, offs = 0; h < 256; h++, offs += 256) {
		halInitMatrixDMA((nm32fcr*)(bufferDDR + h), 2, 256, 2 * 256, (nm32fcr*)((int)bufferSRAM + 0x40000), 2);
		while(halStatusDMA());

		nmppsFFT256Inv_32fcr(bufferSRAM, bufferSRAM, spec);

		halInitStatusSingleDMA((nm32fcr*)((int)bufferSRAM + 0x40000), (nm32fcr*)(pDst + offs), 2 * 256);
		while(halStatusDMA());
	}
}
