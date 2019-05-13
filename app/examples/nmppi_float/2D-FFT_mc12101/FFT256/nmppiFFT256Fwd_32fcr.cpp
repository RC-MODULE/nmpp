//***************************************************************************************************************/
//*                     RC Module Inc., Moscow, Russia                                                          */
//*                     NeuroMatrix(r) NM640x Software                                                          */
//*                                                                                                             */
//*   Software design:  A.Brodyazhenko 																            */
//*   Year: 2018                                                                                                */
//*                                                                                                             */
//* Prototype: void nmppiFFT256Fwd_32fcr(const nm32fcr* pSrc, nm32fcr* pDst,									*/
//*										 nm32fcr* bufferDDR, nm32fcr* bufferSRAM, NmppsFFTSpec_32fcr* spec) 	*/
//* 																								            */
//* pSrc   		- input matrix in DDR (size = 256 * 256),														*/
//* pDst   		- output matrix in DDR (size = 256 * 256),														*/
//* bufferDDR   - temporary matrix in DDR (size = 256 * 256)													*/
//*	bufferSRAM  - temporary vector in SRAM (size = 256)										            		*/
//* spec		- struct of coeffs for 1D-FFT                              										*/
//* Description: This function computes forward 2D-FFT256 (floating point) from the intput matrix.				*/
//*     It works on mc12101 only. Before start this function necessary to call halOpenDMA()! See main.cpp       */
//***************************************************************************************************************/

#include "dma.h"
#include "nmpp.h"
#include "fft_32fcr.h"

void nmppiFFT256Fwd_32fcr(const nm32fcr* pSrc, nm32fcr* pDst, nm32fcr* bufferDDR, nm32fcr* bufferSRAM, NmppsFFTSpec_32fcr* spec)
{
	for(int offset = 0; offset < 256 * 256; offset += 256) {
		halInitStatusSingleDMA((nm32fcr*)(pSrc + offset), (nm32fcr*)((int)bufferSRAM + 0x40000), 2 * 256);
		while(halStatusDMA());

		nmppsFFT256Fwd_32fcr(bufferSRAM, bufferSRAM, spec);

		halInitStatusSingleDMA((nm32fcr*)((int)bufferSRAM + 0x40000), (nm32fcr*)(bufferDDR + offset), 2 * 256);
		while(halStatusDMA());
	}

	for(int height = 0, offs = 0; height < 256; height++, offs += 256) {
		halInitMatrixDMA((nm32fcr*)(bufferDDR + height), 2, 256, 2 * 256, (nm32fcr*)((int)bufferSRAM + 0x40000), 2);
		while(halStatusDMA());

		nmppsFFT256Fwd_32fcr(bufferSRAM, bufferSRAM, spec);

		halInitStatusSingleDMA((nm32fcr*)((int)bufferSRAM + 0x40000), (nm32fcr*)(pDst + offs), 2 * 256);
		while(halStatusDMA());
	}
}