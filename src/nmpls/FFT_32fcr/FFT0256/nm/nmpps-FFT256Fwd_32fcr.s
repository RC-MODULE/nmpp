//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software                      */
//*                                                                         */
//*   Software design:  A.Brodyazhenko                                      */
//*                                                                         */
//*   File:             nmpps-FFT256Fwd_32fcr.s                             */
//*   Contents:         Routine for forward and inverse FFT 256             */
//*                     of complex array with 32 bit elements				*/
//*	  Max Speed:		1812 ticks											*/
//***************************************************************************/

global _nmppsFFT256Fwd_32fcr: label;
global _nmppsFFT256Inv_32fcr: label;

extern _FFTFwd16x32Core: label;

data ".data_imu2"
AddrForDFT16_256: word[16] = (
					0, 16, 8, 24,
					 4, 20, 12, 28,
					  2, 18, 10, 26,
					   6, 22, 14, 30
					);
end ".data_imu2";

begin ".text"
<_nmppsFFT256Fwd_32fcr>
<_nmppsFFT256Inv_32fcr>
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
	ar5 = [--ar5]; // struct with W
	gr1 = 32; // offset for reading x
	vlen = 7;

/**************Sort 16 things of FFT16**************/
	ar4 = AddrForDFT16_256;
	ar1 = [ar5++] with gr2 = gr1 >> 3;  // addr for 1.0 or 1/256
	ar0 = [ar5++]; 						// buff_fft256
	ar6 = [ar5++]; 						// buff_fft256xW
	
	fpu 0 rep 1 vreg1 = [ar1]; 			// 1/256 or 1.0
	fpu 1 vreg1 = fpu 0 vreg1;
	fpu 2 vreg1 = fpu 1 vreg1;
	fpu 3 vreg1 = fpu 2 vreg1;

	gr4 = ar0;
	gr7 = ar6;
<SORT_16_16_256>
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
	gr2--;
	if > goto SORT_16_16_256;
// end 16 FFT16

/**********************Computing of 16 part of FFT16**********************/
	delayed call _FFTFwd16x32Core;
		ar3 = gr4; // addr for input buff_fft256
		gr6 = ar3; // addr for output buff_fft256

	ar5 = ar5 - 7;
	
	delayed call _FFTFwd16x32Core;
		ar3 = gr7; // buff_fft256xW
		gr6 = ar3;
// END FFT16

/**********************Computing of 8 part of FFT32**********************/

	ar0 = gr4 with gr1 >>= 1; 		// buff_fft256
	ar6 = gr7 with 	gr2 = gr1 >> 3; // buff_fft256xW
	ar1 = [ar5++]; 					// W128
	ar3 = ar0;
	ar4 = ar6;
	gr3 = ar1;
	fpu 0 rep 16 vreg0 = [ar1++gr1];
	fpu 1 vreg0 = fpu 0 vreg0;
	fpu 2 vreg0 = fpu 1 vreg0;
	fpu 3 vreg0 = fpu 2 vreg0;

<COMP_8_FFT32>
	fpu 0 rep 16 vreg1 = [ar0++];
	fpu 0 rep 16 vreg2 = [ar6++];
	fpu 0 .complex vreg5 = vreg0 * vreg2 + vreg1; // 1 - FFT32

	fpu 1 rep 16 vreg1 = [ar0++];
	fpu 1 rep 16 vreg2 = [ar6++];
	fpu 1 .complex vreg5 = vreg0 * vreg2 + vreg1; // 1 - FFT32

	fpu 2 rep 16 vreg1 = [ar0++];
	fpu 2 rep 16 vreg2 = [ar6++];
	fpu 2 .complex vreg5 = vreg0 * vreg2 + vreg1; // 1 - FFT32

	fpu 3 rep 16 vreg1 = [ar0++];
	fpu 3 rep 16 vreg2 = [ar6++];
	fpu 3 .complex vreg5 = vreg0 * vreg2 + vreg1; // 1 - FFT32

	fpu 0 rep 16 [ar3++] = vreg5;
	fpu 1 rep 16 [ar4++] = vreg5;

	fpu 0 .complex vreg6 = -vreg0 * vreg2 + vreg1; // 2 - FFT32
	fpu 1 .complex vreg6 = -vreg0 * vreg2 + vreg1; // 2 - FFT32
	fpu 2 .complex vreg6 = -vreg0 * vreg2 + vreg1; // 2 - FFT32
	fpu 3 .complex vreg6 = -vreg0 * vreg2 + vreg1; // 2 - FFT32

	fpu 0 rep 16 [ar3++] = vreg6;
	fpu 1 rep 16 [ar4++] = vreg6;

	fpu 2 rep 16 [ar3++] = vreg5;
	fpu 3 rep 16 [ar4++] = vreg5;

	fpu 2 rep 16 [ar3++] = vreg6;
	fpu 3 rep 16 [ar4++] = vreg6;
	gr2--;
	if > goto COMP_8_FFT32;
// end 8 FFT32

/**********************Computing of 4 part of FFT64**********************/
	ar1 = gr3 with gr1 >>= 1; 	// gr1 = 8 // W128
	ar0 = gr4;				  	// buff_fft256
	ar6 = gr7; 				  	// buff_fft256xW
	fpu 0 rep 32 vreg0 = [ar1++gr1];
	fpu 1 vreg0 = fpu 0 vreg0;
	fpu 2 vreg0 = fpu 1 vreg0;
	fpu 3 vreg0 = fpu 2 vreg0;

	fpu 0 rep 32 vreg1 = [ar0++];
	fpu 0 rep 32 vreg2 = [ar6++];
	fpu 0 .complex vreg5 = vreg0 * vreg2 + vreg1; // 1 - FFT64

	fpu 1 rep 32 vreg1 = [ar0++];
	fpu 1 rep 32 vreg2 = [ar6++];
	fpu 1 .complex vreg5 = vreg0 * vreg2 + vreg1; // 1 - FFT64
	
	ar1 = [ar5++]; // W64_0
	ar2 = [ar5++]; // W64_1

	fpu 2 rep 32 vreg1 = [ar0++];
	fpu 2 rep 32 vreg2 = [ar6++];
	fpu 2 .complex vreg5 = vreg0 * vreg2 + vreg1; // 1 - FFT64

	fpu 3 rep 32 vreg1 = [ar0++];
	fpu 3 rep 32 vreg2 = [ar6++];
	fpu 3 .complex vreg5 = vreg0 * vreg2 + vreg1; // 1 - FFT64

	fpu 0 rep 32 vreg3 = [ar1++];
	fpu 1 rep 32 vreg3 = [ar1++];
	fpu 2 rep 32 vreg3 = [ar2++];
	fpu 3 rep 32 vreg3 = [ar2++];

	fpu 0 .complex vreg6 = -vreg0 * vreg2 + vreg1; // 2 - FFT64
	fpu 1 .complex vreg6 = -vreg0 * vreg2 + vreg1; // 2 - FFT64
	fpu 2 .complex vreg6 = -vreg0 * vreg2 + vreg1; // 2 - FFT64
	fpu 3 .complex vreg6 = -vreg0 * vreg2 + vreg1; // 2 - FFT64

// end 4 FFT64

/**********************Computing of 2 part of FFT128**********************/

	fpu 0 vreg4 = fpu 1 vreg5;
	fpu 2 vreg4 = fpu 3 vreg5;
	fpu 1 vreg4 = fpu 0 vreg6;
	fpu 3 vreg4 = fpu 2 vreg6;
	
	ar1 = gr3;
	
	fpu 0 .complex vreg1 = vreg4 * vreg3 + vreg5;
	fpu 1 .complex vreg1 = vreg6 * vreg3 + vreg4;
	fpu 2 .complex vreg1 = vreg4 * vreg3 + vreg5;
	fpu 3 .complex vreg1 = vreg6 * vreg3 + vreg4;

	fpu 0 rep 32 vreg7 = [ar1++];
	fpu 1 rep 32 vreg7 = [ar1++];
	fpu 2 rep 32 vreg7 = [ar1++];
	fpu 3 rep 32 vreg7 = [ar1++];
	
	fpu 0 .complex vreg2 = -vreg4 * vreg3 + vreg5;
	fpu 1 .complex vreg2 = -vreg6 * vreg3 + vreg4;
	fpu 2 .complex vreg2 = -vreg4 * vreg3 + vreg5;
	fpu 3 .complex vreg2 = -vreg6 * vreg3 + vreg4;


// end 2 FFT128
	
/**********************Computing of 1 part of FFT256**********************/

	fpu 0 vreg3 = fpu 2 vreg1;
	fpu 1 vreg3 = fpu 3 vreg1;
	fpu 2 vreg3 = fpu 0 vreg2;
	fpu 3 vreg3 = fpu 1 vreg2;

	ar2 = gr5; // output X

	fpu 0 .complex vreg4 = vreg3 * vreg7 + vreg1;
	fpu 1 .complex vreg4 = vreg3 * vreg7 + vreg1;
	fpu 2 .complex vreg4 = vreg2 * vreg7 + vreg3;
	fpu 3 .complex vreg4 = vreg2 * vreg7 + vreg3;

	fpu 0 rep 32 [ar2++] = vreg4;
	fpu 1 rep 32 [ar2++] = vreg4;
	fpu 2 rep 32 [ar2++] = vreg4;
	fpu 3 rep 32 [ar2++] = vreg4;

	fpu 0 .complex vreg5 = -vreg3 * vreg7 + vreg1;
	fpu 1 .complex vreg5 = -vreg3 * vreg7 + vreg1;
	fpu 2 .complex vreg5 = -vreg2 * vreg7 + vreg3;
	fpu 3 .complex vreg5 = -vreg2 * vreg7 + vreg3;

// end 1 FFT256

/**********************Uploding of FFT256 in the memory**********************/
	fpu 0 rep 32 [ar2++] = vreg5;
	fpu 1 rep 32 [ar2++] = vreg5;
	fpu 2 rep 32 [ar2++] = vreg5;
	fpu 3 rep 32 [ar2++] = vreg5;

<exit_FFTFwd256>
	pop ar0, gr0;
	pop ar1, gr1;
	pop ar2, gr2;
	pop ar3, gr3;
	pop ar4, gr4;
	pop ar5, gr5;
	pop ar6, gr6;
	return;
end ".text";