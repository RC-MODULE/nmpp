//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software                      */
//*                                                                         */
//*   Software design:  A.Brodyazhenko                                      */
//*                                                                         */
//*   File:             nmpps-FFT128Fwd_32fcr.s                             */
//*   Contents:         Routine for forward FFT 128                         */
//*                     of complex array with 32 bit elements               */
//***************************************************************************/

global _nmppsFFT128Fwd_32fcr: label;
global _nmppsFFT128Inv_32fcr: label;
data ".data_imu1"
AddrForDFT8_128: word[16] = (
						0, 16, 8, 24, 4, 20, 12, 28,
						 2, 18, 10, 26, 6, 22, 14, 30
						);
end ".data_imu1";

begin ".data_imu7"
<_nmppsFFT128Fwd_32fcr>
<_nmppsFFT128Inv_32fcr>
	ar5 = ar7 - 2;
	push ar6, gr6;
	push ar4, gr4;
	push ar3, gr3;
	push ar2, gr2;
	push ar1, gr1;
	push ar0, gr0;
	ar3 = [--ar5]; // input x
	gr6 = [--ar5]; // output X
	ar5 = [--ar5];
	gr1 = 32; // offset for reading x
	ar4 = [ar5++];
	ar2 = [ar5++];
	gr0 = gr1 >> 2;

// Read SinCos
	fpu 0 rep 8 vreg1 = [ar4++];
	fpu 1 rep 8 vreg1 = [ar2++];
	fpu 2 vreg1 = fpu 0 vreg1;
	fpu 3 vreg1 = fpu 1 vreg1;
	fpu 0 rep 8 vreg2 = [ar4++];
	fpu 1 rep 8 vreg2 = [ar2++];
	fpu 2 vreg2 = fpu 0 vreg2;
	fpu 3 vreg2 = fpu 1 vreg2;
	fpu 0 rep 8 vreg3 = [ar4++];
	fpu 1 rep 8 vreg3 = [ar2++];
	fpu 2 vreg3 = fpu 0 vreg3;
	fpu 3 vreg3 = fpu 1 vreg3;
	fpu 0 rep 8 vreg4 = [ar4++];
	fpu 1 rep 8 vreg4 = [ar2++];
	fpu 2 vreg4 = fpu 0 vreg4;
	fpu 3 vreg4 = fpu 1 vreg4;
// end read SinCos

// Compute 16 things of DFT8
	ar0 = [ar5++]; // buff_fft128
	ar6 = [ar5++]; // buff_fft128xW
	gr2 = ar0;
	gr4 = ar6;
	ar4 = AddrForDFT8_128;
	gr3 = [ar4++];
<COMP_16_8_128>
	ar1 = ar3 + gr3;
	fpu 0 rep 4 vreg0 = [ar1++gr1];
    fpu 1 rep 4 vreg0 = [ar1++gr1];
	fpu 0 .complex vreg5 = vreg1 * .retrive(vreg0);
	fpu 1 .complex vreg5 = vreg1 * .retrive(vreg0);
	fpu 0 .complex vreg6 = vreg2 * .retrive(vreg0) + vreg5;
	fpu 1 .complex vreg6 = vreg2 * .retrive(vreg0) + vreg5;
	fpu 0 .complex vreg7 = vreg3 * .retrive(vreg0) + vreg6;
	fpu 1 .complex vreg7 = vreg3 * .retrive(vreg0) + vreg6;
	fpu 0 .complex vreg6 = vreg4 * .retrive(vreg0) + vreg7;
	fpu 1 .complex vreg6 = vreg4 * .retrive(vreg0) + vreg7;
	fpu 1 vreg5 = fpu 0 vreg6;
	fpu 1 .float vreg7 = vreg6 + vreg5;
	fpu 1 rep 8 [ar0++] = vreg7; // save First DFT8

	gr3 = [ar4++];
	ar1 = ar3 + gr3;
	fpu 2 rep 4 vreg0 = [ar1++gr1];
    fpu 3 rep 4 vreg0 = [ar1++gr1];
    fpu 2 .complex vreg5 = vreg1 * .retrive(vreg0);
    fpu 3 .complex vreg5 = vreg1 * .retrive(vreg0);
	fpu 2 .complex vreg6 = vreg2 * .retrive(vreg0) + vreg5;
	fpu 3 .complex vreg6 = vreg2 * .retrive(vreg0) + vreg5;
	fpu 2 .complex vreg7 = vreg3 * .retrive(vreg0) + vreg6;
	fpu 3 .complex vreg7 = vreg3 * .retrive(vreg0) + vreg6;
	fpu 2 .complex vreg6 = vreg4 * .retrive(vreg0) + vreg7;
	fpu 3 .complex vreg6 = vreg4 * .retrive(vreg0) + vreg7;
	fpu 3 vreg5 = fpu 2 vreg6;
	fpu 3 .float vreg7 = vreg6 + vreg5;
	fpu 3 rep 8 [ar6++] = vreg7; // save Second DFT8
	gr0--;
	if > delayed goto COMP_16_8_128;
		gr3 = [ar4++];
		nul;
// END COMPUTE 16 things of DFT8

// COMPUTE 8 things of FFT16
	ar1 = [ar5++]; // W8_0
	ar2 = [ar5++]; // W8_1
	ar0 = gr2 with gr0 = gr1 >> 3;	// buff_fft128
	ar6 = gr4; 					  	// buff_fft128xW
	ar3 = gr2;
	ar4 = gr4;
	fpu 0 rep 8 vreg0 = [ar1++];
	fpu 1 rep 8 vreg0 = [ar2++];
	fpu 2 vreg0 = fpu 0 vreg0;
	fpu 3 vreg0 = fpu 1 vreg0;


<COMP_4_16_128>
	fpu 0 rep 8 vreg1 = [ar0++];
	fpu 1 rep 8 vreg1 = [ar6++]; // xW
	fpu 0 vreg2 = fpu 1 vreg1;   // xW
	fpu 1 vreg2 = fpu 0 vreg1;
	
	fpu 0 .complex vreg3 = vreg0 * vreg2 + vreg1;
	fpu 1 .complex vreg3 = -vreg0 * vreg1 + vreg2;

	fpu 2 rep 8 vreg1 = [ar0++];
	fpu 3 rep 8 vreg1 = [ar6++]; // xW
	fpu 2 vreg2 = fpu 3 vreg1;   // xW
	fpu 3 vreg2 = fpu 2 vreg1;
	
	fpu 2 .complex vreg3 = vreg0 * vreg2 + vreg1;
	fpu 3 .complex vreg3 = -vreg0 * vreg1 + vreg2;

	fpu 0 rep 8 [ar3++] = vreg3;
	fpu 2 rep 8 [ar4++] = vreg3;

	fpu 1 rep 8 [ar3++] = vreg3;
	fpu 3 rep 8 [ar4++] = vreg3;
	gr0--;
	if > goto COMP_4_16_128;
// END COMPUTE 8 things of FFT16

// COMPUTE 4 things FFT32
	ar1 = [ar5++]; // W16_0
	ar2 = [ar5++]; // W16_1
	ar0 = gr2; // buff_fft128
	ar6 = gr4; // buff_fft128xW
	ar3 = ar0 with gr0 = gr1 >> 4;
	ar4 = ar6;

	fpu 0 rep 16 vreg0 = [ar1++];
	fpu 1 rep 16 vreg0 = [ar2++];
	fpu 2 vreg0 = fpu 0 vreg0;
	fpu 3 vreg0 = fpu 1 vreg0;

<COMP_2_32_128>
	fpu 0 rep 16 vreg1 = [ar0++];
	fpu 1 rep 16 vreg1 = [ar6++]; // xW
	fpu 0 vreg2 = fpu 1 vreg1;    // xW
	fpu 1 vreg2 = fpu 0 vreg1;
	
	fpu 0 .complex vreg3 = vreg0 * vreg2 + vreg1;
	fpu 1 .complex vreg3 = -vreg0 * vreg1 + vreg2;

	fpu 2 rep 16 vreg1 = [ar0++];
	fpu 3 rep 16 vreg1 = [ar6++]; // xW
	fpu 2 vreg2 = fpu 3 vreg1;    // xW
	fpu 3 vreg2 = fpu 2 vreg1;
	
	fpu 2 .complex vreg3 = vreg0 * vreg2 + vreg1;
	fpu 3 .complex vreg3 = -vreg0 * vreg1 + vreg2;

	fpu 0 rep 16 [ar3++] = vreg3;
	fpu 2 rep 16 [ar4++] = vreg3;

	fpu 1 rep 16 [ar3++] = vreg3;
	fpu 3 rep 16 [ar4++] = vreg3;
	gr0--;
	if > goto COMP_2_32_128;
// END COMPUTE 4 things FFT32

// COMPUTE 2 things FFT64
	ar1 = [ar5++]; // W32_0
	ar2 = [ar5++]; // W32_1
	ar0 = gr2; // buff_fft128
	ar6 = gr4; // buff_fft128xW

	fpu 0 rep 32 vreg0 = [ar1++];
	fpu 1 rep 32 vreg0 = [ar2++];
	fpu 2 vreg0 = fpu 0 vreg0;
	fpu 3 vreg0 = fpu 1 vreg0;

	fpu 0 rep 32 vreg1 = [ar0++];
	fpu 1 rep 32 vreg1 = [ar6++]; // xW
	fpu 0 vreg2 = fpu 1 vreg1;    // xW
	fpu 1 vreg2 = fpu 0 vreg1;
	
	fpu 0 .complex vreg3 = vreg0 * vreg2 + vreg1;
	fpu 1 .complex vreg3 = -vreg0 * vreg1 + vreg2;

	fpu 2 rep 32 vreg1 = [ar0++];
	fpu 3 rep 32 vreg1 = [ar6++]; // xW
	fpu 2 vreg2 = fpu 3 vreg1;    // xW
	fpu 3 vreg2 = fpu 2 vreg1;
	
	fpu 2 .complex vreg3 = vreg0 * vreg2 + vreg1;
	fpu 3 .complex vreg3 = -vreg0 * vreg1 + vreg2;
// END FFT64

// COMPUTE FFT128
	ar1 = [ar5++];  // W64_0
	ar2 = gr6;		// output X

	fpu 0 rep 32 vreg0 = [ar1++];
	fpu 2 vreg0 = fpu 0 vreg0;

	fpu 1 rep 32 vreg0 = [ar1++];
	fpu 3 vreg0 = fpu 1 vreg0;

	fpu 0 vreg4 = fpu 2 vreg3; // xW
	fpu 2 vreg4 = fpu 0 vreg3;
	fpu 1 vreg4 = fpu 3 vreg3; // xW
	fpu 3 vreg4 = fpu 1 vreg3;

	fpu 0 .complex vreg5 = vreg0 * vreg4 + vreg3;
	fpu 2 .complex vreg5 = -vreg0 * vreg3 + vreg4;
	fpu 1 .complex vreg5 = vreg0 * vreg4 + vreg3;
	fpu 3 .complex vreg5 = -vreg0 * vreg3 + vreg4;
// END FFT128

	fpu 0 rep 32 [ar2++] = vreg5;
	fpu 1 rep 32 [ar2++] = vreg5;
	fpu 2 rep 32 [ar2++] = vreg5;
	fpu 3 rep 32 [ar2++] = vreg5;
	
<exit_fft128>
	pop ar0, gr0;
	pop ar1, gr1;
	pop ar2, gr2;
	pop ar3, gr3;
	pop ar4, gr4;
	pop ar6, gr6;	
	return;
end ".data_imu7";