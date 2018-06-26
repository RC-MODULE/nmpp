//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software                      */
//*                                                                         */
//*   Software design:  A.Brodyazhenko                                      */
//*                                                                         */
//*   File:             nmpps-FFT512Fwd_32fcr.s                             */
//*   Contents:         Routine for forward and inverse FFT 512             */
//*                     of complex array with 32 bit elements               */
//***************************************************************************/

global _nmppsFFT512Fwd_32fcr: label;
global _nmppsFFT512Inv_32fcr: label;

extern _FFTFwd16x32Core: label;

data ".data_imu1"
AddrFor32FFT16_512: word[32] = (0, 32, 16, 48, 8, 40, 24, 56,
							 	 4, 36, 20, 52, 12, 44, 28, 60,
							 	  2, 34, 18, 50, 10, 42, 26, 58,
							 	   6, 38, 22, 54, 14, 46, 30, 62);
end ".data_imu1";

begin ".text"
<_nmppsFFT512Fwd_32fcr>
<_nmppsFFT512Inv_32fcr>
	ar5 = ar7 - 2;
	push ar6, gr6;
	push ar5, gr5;
	push ar4, gr4;
	push ar3, gr3;
	push ar2, gr2;
	push ar1, gr1;
	push ar0, gr0;
	ar3 = [--ar5]; // input x
	gr5 = [--ar5]; // output X
	ar5 = [--ar5]; // address of the struct with W-coefficients
	gr1 = 64;
	vlen = 15;
	gr0 = gr1 >> 3;

	ar4 = AddrFor32FFT16_512;
	ar1 = [ar5++]; // 1.0
	ar0 = [ar5++]; // buff_fft512
	ar6 = [ar5++]; // buff_fft512xW
	fpu 0 rep 1 vreg1 = [ar1];
	fpu 1 vreg1 = fpu 0 vreg1;
	fpu 2 vreg1 = fpu 1 vreg1;
	fpu 3 vreg1 = fpu 2 vreg1;
	gr4 = ar0;
	gr7 = ar6;
<SORT_32_16>
	gr3 = [ar4++];
	ar1 = ar3 + gr3;
	fpu 0 rep 16 vreg0 = [ar1++gr1];
	fpu 0 .complex vreg0 = vreg0 * .retrive(vreg1);
	gr3 = [ar4++];
	ar1 = ar3 + gr3;
	fpu 1 rep 16 vreg0 = [ar1++gr1];
	fpu 1 .complex vreg0 = vreg0 * .retrive(vreg1);
	gr3 = [ar4++];
	ar1 = ar3 + gr3;
	fpu 2 rep 16 vreg0 = [ar1++gr1];
	fpu 2 .complex vreg0 = vreg0 * .retrive(vreg1);
	gr3 = [ar4++];
	ar1 = ar3 + gr3;
	fpu 3 rep 16 vreg0 = [ar1++gr1];
	fpu 3 .complex vreg0 = vreg0 * .retrive(vreg1);

	fpu 0 rep 16 [ar0++] = vreg0;
	fpu 1 rep 16 [ar6++] = vreg0;
	fpu 2 rep 16 [ar0++] = vreg0;
	fpu 3 rep 16 [ar6++] = vreg0;
	gr0--;
	if > goto SORT_32_16;

// COMPUTE 32 PART OF FFT16
	gr1 >>= 1; // step for FFT16 = 32 for input

	delayed call _FFTFwd16x32Core;
		ar3 = gr4; // addr for input buff_fft1024
		gr6 = ar3; // addr for output buff_fft1024
	
	ar5 = ar5 - 7;

	delayed call _FFTFwd16x32Core;
		ar3 = gr7;
		gr6 = ar3;
// END FFT16

//COMPUTE 16 PART OF FFT32
	ar0 = gr4;
	ar6 = gr7;
	gr2 = gr1 >> 3;
	ar1 = [ar5++]; // W256
	gr0 = ar1; // saving W256
	ar3 = ar0;
	ar4 = ar6;
	fpu 0 rep 16 vreg0 = [ar1++gr1];
	fpu 1 vreg0 = fpu 0 vreg0;
	fpu 2 vreg0 = fpu 1 vreg0;
	fpu 3 vreg0 = fpu 2 vreg0;
<COMP_16_FFT32_512>
	fpu 0 rep 16 vreg1 = [ar0++];
	fpu 0 rep 16 vreg2 = [ar6++];
	fpu 0 .complex vreg5 = vreg0 * vreg2 + vreg1; // 1 - FFT32
	fpu 0 .complex vreg6 = -vreg0 * vreg2 + vreg1; // 2 - FFT32

	fpu 1 rep 16 vreg1 = [ar0++];
	fpu 1 rep 16 vreg2 = [ar6++];
	fpu 1 .complex vreg5 = vreg0 * vreg2 + vreg1; // 1 - FFT32
	fpu 1 .complex vreg6 = -vreg0 * vreg2 + vreg1; // 2 - FFT32

	fpu 2 rep 16 vreg1 = [ar0++];
	fpu 2 rep 16 vreg2 = [ar6++];
	fpu 2 .complex vreg5 = vreg0 * vreg2 + vreg1; // 1 - FFT32
	fpu 2 .complex vreg6 = -vreg0 * vreg2 + vreg1; // 2 - FFT32

	fpu 3 rep 16 vreg1 = [ar0++];
	fpu 3 rep 16 vreg2 = [ar6++];
	fpu 3 .complex vreg5 = vreg0 * vreg2 + vreg1; // 1 - FFT32
	fpu 3 .complex vreg6 = -vreg0 * vreg2 + vreg1; // 2 - FFT32

	fpu 0 rep 16 [ar3++] = vreg5;
	fpu 1 rep 16 [ar4++] = vreg5;
	fpu 0 rep 16 [ar3++] = vreg6;
	fpu 1 rep 16 [ar4++] = vreg6;

	fpu 2 rep 16 [ar3++] = vreg5;
	fpu 3 rep 16 [ar4++] = vreg5;
	fpu 2 rep 16 [ar3++] = vreg6;
	fpu 3 rep 16 [ar4++] = vreg6;
	gr2--;
	if > goto COMP_16_FFT32_512;
// END FFT32

// COMPUTE 8 PART FFT64
	ar1 = gr0;
	gr1 >>= 1;
	ar0 = gr4;
	ar6 = gr7;
	fpu 0 rep 32 vreg0 = [ar1++gr1];
	fpu 1 vreg0 = fpu 0 vreg0;
	fpu 2 vreg0 = fpu 1 vreg0;
	fpu 3 vreg0 = fpu 2 vreg0;

	fpu 0 rep 32 vreg1 = [ar0++];
	fpu 0 rep 32 vreg2 = [ar6++];
	fpu 0 rep 32 vreg3 = [ar0++];
	fpu 0 rep 32 vreg4 = [ar6++];
	fpu 0 .complex vreg5 = vreg0 * vreg2 + vreg1; // 1 - FFT64
	fpu 0 .complex vreg6 = -vreg0 * vreg2 + vreg1; // 2 - FFT64

	fpu 0 .complex vreg7 = vreg4 * vreg0 + vreg3; // need * W 1 - FFT64
	fpu 0 .complex vreg4 = -vreg4 * vreg0 + vreg3; // need * W 2 - FFT64

	fpu 1 rep 32 vreg1 = [ar0++];
	fpu 1 rep 32 vreg2 = [ar6++];
	fpu 1 rep 32 vreg3 = [ar0++];
	fpu 1 rep 32 vreg4 = [ar6++];
	fpu 1 .complex vreg5 = vreg0 * vreg2 + vreg1; // 1 - FFT64
	fpu 1 .complex vreg6 = -vreg0 * vreg2 + vreg1; // 2 - FFT64

	fpu 1 .complex vreg7 = vreg4 * vreg0 + vreg3; // need * W 1 - FFT64
	fpu 1 .complex vreg4 = -vreg4 * vreg0 + vreg3; // need * W 2 - FFT64

	fpu 2 rep 32 vreg1 = [ar0++];
	fpu 2 rep 32 vreg2 = [ar6++];
	fpu 2 rep 32 vreg3 = [ar0++];
	fpu 2 rep 32 vreg4 = [ar6++];
	fpu 2 .complex vreg5 = vreg0 * vreg2 + vreg1; // 1 - FFT64
	fpu 2 .complex vreg6 = -vreg0 * vreg2 + vreg1; // 2 - FFT64

	fpu 2 .complex vreg7 = vreg4 * vreg0 + vreg3; // need * W 1 - FFT64
	fpu 2 .complex vreg4 = -vreg4 * vreg0 + vreg3; // need * W 2 - FFT64

	fpu 3 rep 32 vreg1 = [ar0++];
	fpu 3 rep 32 vreg2 = [ar6++];
	fpu 3 rep 32 vreg3 = [ar0++];
	fpu 3 rep 32 vreg4 = [ar6++];
	fpu 3 .complex vreg5 = vreg0 * vreg2 + vreg1; // 1 - FFT64
	fpu 3 .complex vreg6 = -vreg0 * vreg2 + vreg1; // 2 - FFT64

	fpu 3 .complex vreg7 = vreg4 * vreg0 + vreg3; // need * W 1 - FFT64
	fpu 3 .complex vreg4 = -vreg4 * vreg0 + vreg3; // need * W 2 - FFT64
// END FFT64

// COMPUTE 4 PART OF FFT128
	ar1 = gr0;
	gr1 >>= 1;

	fpu 0 rep 32 vreg0 = [ar1++gr1];
	fpu 1 vreg0 = fpu 0 vreg0;
	fpu 2 vreg0 = fpu 1 vreg0;
	fpu 3 vreg0 = fpu 2 vreg0;

	fpu 0 rep 32 vreg1 = [ar1++gr1];
	fpu 1 vreg1 = fpu 0 vreg1;
	fpu 2 vreg1 = fpu 1 vreg1;
	fpu 3 vreg1 = fpu 2 vreg1;

	fpu 0 .complex vreg3 = vreg7 * vreg0 + vreg5;
	fpu 1 .complex vreg3 = vreg7 * vreg0 + vreg5;
	fpu 2 .complex vreg3 = vreg7 * vreg0 + vreg5;
	fpu 3 .complex vreg3 = vreg7 * vreg0 + vreg5;

	fpu 0 .complex vreg2 = vreg4 * vreg1 + vreg6;
	fpu 1 .complex vreg2 = vreg4 * vreg1 + vreg6;
	fpu 2 .complex vreg2 = vreg4 * vreg1 + vreg6;
	fpu 3 .complex vreg2 = vreg4 * vreg1 + vreg6;
	
	fpu 0 .complex vreg0 = -vreg7 * vreg0 + vreg5;
	fpu 1 .complex vreg0 = -vreg7 * vreg0 + vreg5;
	fpu 2 .complex vreg0 = -vreg7 * vreg0 + vreg5;
	fpu 3 .complex vreg0 = -vreg7 * vreg0 + vreg5;
	
	fpu 0 .complex vreg1 = -vreg4 * vreg1 + vreg6;
	fpu 1 .complex vreg1 = -vreg4 * vreg1 + vreg6;
	fpu 2 .complex vreg1 = -vreg4 * vreg1 + vreg6;
	fpu 3 .complex vreg1 = -vreg4 * vreg1 + vreg6;
// END FFT128

// COMPUTE 2 PART OF FFT256
	ar1 = gr0;
	gr1 >>= 1;
	fpu 0 rep 32 vreg4 = [ar1++gr1]; // 1 - W128
	fpu 0 rep 32 vreg5 = [ar1++gr1]; // 2 - W128
	fpu 1 rep 32 vreg4 = [ar1++gr1]; // 3 - W128
	fpu 1 rep 32 vreg5 = [ar1++gr1]; // 4 - W128

	fpu 0 vreg6 = fpu 1 vreg3;
	fpu 1 vreg6 = fpu 0 vreg0;
	fpu 2 vreg6 = fpu 3 vreg3;
	fpu 3 vreg6 = fpu 2 vreg0;
	
	fpu 2 vreg4 = fpu 0 vreg4; // copy 1 - W128
	fpu 3 vreg4 = fpu 1 vreg4; // copy 3 - W128
	fpu 2 vreg5 = fpu 0 vreg5; // copy 2 - W128
	fpu 3 vreg5 = fpu 1 vreg5; // copy 4 - W128
	
	fpu 0 .complex vreg0 = vreg6 * vreg4 + vreg3;
	fpu 1 .complex vreg3 = vreg0 * vreg4 + vreg6;
	fpu 2 .complex vreg0 = vreg6 * vreg4 + vreg3;
	fpu 3 .complex vreg3 = vreg0 * vreg4 + vreg6;
	
	fpu 0 vreg7 = fpu 1 vreg2;
	fpu 1 vreg7 = fpu 0 vreg1;
	fpu 2 vreg7 = fpu 3 vreg2;
	fpu 3 vreg7 = fpu 2 vreg1;

	fpu 0 .complex vreg1 = vreg7 * vreg5 + vreg2;
	fpu 1 .complex vreg2 = vreg1 * vreg5 + vreg7;
	fpu 2 .complex vreg1 = vreg7 * vreg5 + vreg2;
	fpu 3 .complex vreg2 = vreg1 * vreg5 + vreg7;
	
	fpu 0 .complex vreg6 = -vreg6 * vreg4 + vreg3;
	fpu 1 .complex vreg6 = -vreg0 * vreg4 + vreg6;
	fpu 2 .complex vreg6 = -vreg6 * vreg4 + vreg3;
	fpu 3 .complex vreg6 = -vreg0 * vreg4 + vreg6;

	fpu 0 .complex vreg7 = -vreg7 * vreg5 + vreg2;
	fpu 1 .complex vreg7 = -vreg1 * vreg5 + vreg7;
	fpu 2 .complex vreg7 = -vreg7 * vreg5 + vreg2;
	fpu 3 .complex vreg7 = -vreg1 * vreg5 + vreg7;
// END FFT256

// COMPUTE FFT512
	ar1 = gr0;
	ar2 = gr5;
	
	fpu 0 rep 32 vreg4 = [ar1++];
	fpu 0 rep 32 vreg5 = [ar1++];

	fpu 0 vreg2 = fpu 2 vreg0;
	fpu 2 vreg2 = fpu 0 vreg6;
	fpu 1 vreg0 = fpu 3 vreg3;
	fpu 3 vreg0 = fpu 1 vreg6;

	fpu 0 vreg3 = fpu 2 vreg1;
	fpu 2 vreg3 = fpu 0 vreg7;
	fpu 1 vreg1 = fpu 3 vreg2;
	fpu 3 vreg1 = fpu 1 vreg7;
	
	fpu 1 rep 32 vreg4 = [ar1++];
	fpu 1 rep 32 vreg5 = [ar1++];
	
	fpu 2 rep 32 vreg4 = [ar1++];
	fpu 2 rep 32 vreg5 = [ar1++];

	fpu 3 rep 32 vreg4 = [ar1++];
	fpu 3 rep 32 vreg5 = [ar1++];

	fpu 0 .complex vreg6 = vreg2 * vreg4 + vreg0;
	fpu 1 .complex vreg6 = vreg0 * vreg4 + vreg3;
	fpu 2 .complex vreg0 = vreg6 * vreg4 + vreg2;
	fpu 3 .complex vreg2 = vreg6 * vreg4 + vreg0;
	
	fpu 0 rep 32 [ar2++] = vreg6;
	
	fpu 0 .complex vreg7 = vreg3 * vreg5 + vreg1;
	fpu 1 .complex vreg7 = vreg1 * vreg5 + vreg2;
	fpu 2 .complex vreg1 = vreg7 * vreg5 + vreg3;
	fpu 3 .complex vreg3 = vreg7 * vreg5 + vreg1;

	fpu 0 rep 32 [ar2++] = vreg7;
	fpu 1 rep 32 [ar2++] = vreg6;
	fpu 1 rep 32 [ar2++] = vreg7;
	fpu 2 rep 32 [ar2++] = vreg0;
	fpu 2 rep 32 [ar2++] = vreg1;
	fpu 3 rep 32 [ar2++] = vreg2;
	fpu 3 rep 32 [ar2++] = vreg3;

	fpu 0 .complex vreg2 = -vreg2 * vreg4 + vreg0;
	fpu 1 .complex vreg0 = -vreg0 * vreg4 + vreg3;
	fpu 2 .complex vreg2 = -vreg6 * vreg4 + vreg2;
	fpu 3 .complex vreg0 = -vreg6 * vreg4 + vreg0;

	fpu 0 rep 32 [ar2++] = vreg2;

	fpu 0 .complex vreg3 = -vreg3 * vreg5 + vreg1;
	fpu 1 .complex vreg1 = -vreg1 * vreg5 + vreg2;
	fpu 2 .complex vreg3 = -vreg7 * vreg5 + vreg3;
	fpu 3 .complex vreg1 = -vreg7 * vreg5 + vreg1;
// END FFT512

// in mem

	fpu 0 rep 32 [ar2++] = vreg3;
	fpu 1 rep 32 [ar2++] = vreg0;
	fpu 1 rep 32 [ar2++] = vreg1;
	fpu 2 rep 32 [ar2++] = vreg2;
	fpu 2 rep 32 [ar2++] = vreg3;
	fpu 3 rep 32 [ar2++] = vreg0;
	fpu 3 rep 32 [ar2++] = vreg1;
// end in mem

<exit_fft512>
	pop ar0, gr0;
	pop ar1, gr1;
	pop ar2, gr2;
	pop ar3, gr3;
	pop ar4, gr4;
	pop ar5, gr5;
	pop ar6, gr6;
	return;
end ".text";