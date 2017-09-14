//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software                      */
//*                                                                         */
//*   Software design:  A.Brodyazhenko                                      */
//*                                                                         */
//*   File:             nmpps-FFT256Fwd_32fc.s                             	*/
//*   Contents:         Routine for forward and inverse FFT 256             */
//*                     of complex array with 32 bit elements               */                                                        */
//***************************************************************************/

global _nmppsFFT256Fwd_32fc: label;
global _nmppsFFT256Inv_32fc: label;
data ".data_imu1"
AddrForDFT16_256: word[32] = (
						0, 32, 16, 48, 8, 40, 24, 56,
						 4, 36, 20, 52, 12, 44, 28, 60,
						  2, 34, 18, 50, 10, 42, 26, 58,
						   6, 38, 22, 54, 14, 46, 30, 62
						);
end ".data_imu1";

macro COMPUTE_FFT16_32_64(NUM, LEN)
	fpu NUM rep LEN vreg1 = [ar0++];
	fpu NUM rep LEN vreg2 = [ar6++];
	fpu NUM rep LEN vreg3 = [ar0++];
	fpu NUM rep LEN vreg4 = [ar6++];
	fpu NUM .complex vreg5 = vreg0 * vreg2 + vreg1; // 1 - FFT32
	fpu NUM .complex vreg6 = -vreg0 * vreg2 + vreg1; // 2 - FFT32
	fpu NUM .complex vreg7 = vreg4 * vreg0 + vreg3; // need * W 1 - FFT32
	fpu NUM .complex vreg4 = -vreg4 * vreg0 + vreg3; // need * W 2 - FFT32
end COMPUTE_FFT16_32_64;

macro SAVE_FFT16_32(NUMFP, NEL)
	fpu NUMFP rep NEL [ar3++] = vreg5; // save 16 elem of FFT32
	fpu NUMFP rep NEL [ar4++] = vreg7; // save 16 elem of FFT32
	fpu NUMFP rep NEL [ar3++] = vreg6; // save 16 elem of FFT32
	fpu NUMFP rep NEL [ar4++] = vreg4; // save 16 elem of FFT32
end SAVE_FFT16_32;

macro COMPUTE_FFT128(N128)
	fpu N128 .complex vreg3 = vreg7 * vreg0 + vreg5;
	fpu N128 .complex vreg2 = vreg4 * vreg1 + vreg6;
	fpu N128 .complex vreg0 = -vreg7 * vreg0 + vreg5;
	fpu N128 .complex vreg1 = -vreg4 * vreg1 + vreg6;
end COMPUTE_FFT128;

begin ".text"
<_nmppsFFT256Fwd_32fc>
<_nmppsFFT256Inv_32fc>
	set fp_branch;
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
	gr1 = 64; // offset for reading x
	ar2 = [ar5++];
	ar6 = [ar5++];
	gr0 = gr1 >> 2;

// Read SinCos
	fpu 0 rep 8 vreg1 = [ar2++];
	fpu 1 rep 8 vreg1 = [ar6++];
	fpu 2 vreg1 = fpu 0 vreg1;
	fpu 3 vreg1 = fpu 1 vreg1;
	fpu 0 rep 8 vreg2 = [ar2++];
	fpu 1 rep 8 vreg2 = [ar6++];
	fpu 2 vreg2 = fpu 0 vreg2;
	fpu 3 vreg2 = fpu 1 vreg2;
	fpu 0 rep 8 vreg3 = [ar2++];
	fpu 1 rep 8 vreg3 = [ar6++];
	fpu 2 vreg3 = fpu 0 vreg3;
	fpu 3 vreg3 = fpu 1 vreg3;
	fpu 0 rep 8 vreg4 = [ar2++];
	fpu 1 rep 8 vreg4 = [ar6++];
	fpu 2 vreg4 = fpu 0 vreg4;
	fpu 3 vreg4 = fpu 1 vreg4;
// end read SinCos

// Compute 32 things of DFT8
	ar4 = AddrForDFT16_256;
	gr3 = [ar4++];
	ar0 = [ar5++]; // buff_fft256
	ar6 = [ar5++]; // buff_fft256xW
	gr2 = ar0;
	gr7 = ar6;
<COMP_64_8_256>
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
	if > delayed goto COMP_64_8_256;
	gr3 = [ar4++];
	nul;
// end 32 DFT8

// COMPUTE 16 PART OF FFT16
	ar0 = gr2; // buff_fft256
	ar6 = gr7; // buff_fft256xW
	gr4 = gr1 >> 5;
	//ar5 = ar5 + 5;
	ar1 = [ar5++]; // W8_0
	ar2 = [ar5++]; // W8_1
	ar3 = ar1;
	ar4 = ar2;
	fpu 0 rep 8 vreg0 = [ar1++];
	fpu 1 rep 8 vreg0 = [ar2++];
	fpu 2 rep 8 vreg0 = [ar3++];
	fpu 3 rep 8 vreg0 = [ar4++];
	ar3 = ar0;
	ar4 = ar6;
<COMP_16_FFT16_256>
	COMPUTE_FFT16_32_64(0, 8); // 2 FFT16
	COMPUTE_FFT16_32_64(1, 8); // 2 FFT16
	COMPUTE_FFT16_32_64(2, 8); // 2 FFT16
	COMPUTE_FFT16_32_64(3, 8); // 2 FFT16

	SAVE_FFT16_32(0, 8);
	SAVE_FFT16_32(1, 8);
	SAVE_FFT16_32(2, 8);
	SAVE_FFT16_32(3, 8);
	gr4--;
	if > goto COMP_16_FFT16_256;
// END FFT16

// Compute 8 things of FFT32
	ar0 = gr2;
	ar6 = gr7;
	ar1 = [ar5++]; // W16_0
	ar2 = [ar5++]; // W16_1
	ar3 = ar1;
	ar4 = ar2;
	fpu 0 rep 16 vreg0 = [ar1++];
	fpu 1 rep 16 vreg0 = [ar2++];
	fpu 2 rep 16 vreg0 = [ar3++];
	fpu 3 rep 16 vreg0 = [ar4++];
	ar3 = ar0;
	ar4 = ar6;
	COMPUTE_FFT16_32_64(0, 16); // 2 FFT32

	COMPUTE_FFT16_32_64(1, 16); // 2 FFT32

	COMPUTE_FFT16_32_64(2, 16); // 2 FFT32

	COMPUTE_FFT16_32_64(3, 16); // 2 FFT32

	SAVE_FFT16_32(0, 16);
	SAVE_FFT16_32(1, 16);
	SAVE_FFT16_32(2, 16);
	SAVE_FFT16_32(3, 16);
// end 8 FFT32

// Compute 4 things of FFT64
	ar1 = [ar5++]; // W32_0
	ar2 = [ar5++]; // W32_1
	ar0 = gr2;
	ar6 = gr7;
	fpu 0 rep 32 vreg0 = [ar1++];
	fpu 1 rep 32 vreg0 = [ar2++];
	COMPUTE_FFT16_32_64(0, 32); // 2 FFT64
	COMPUTE_FFT16_32_64(1, 32); // 2 FFT64
// end 4 FFT64

// Compute 2 things of FFT128
	ar1 = [ar5++]; // W64_0
	ar2 = [ar5++]; // W64_1
	//gr1 >>= 1;
	fpu 0 rep 32 vreg0 = [ar1++];
	fpu 2 rep 32 vreg0 = [ar1++];
	fpu 1 rep 32 vreg0 = [ar2++];
	fpu 3 rep 32 vreg0 = [ar2++];

	fpu 2 vreg6 = fpu 0 vreg6;
	fpu 2 vreg4 = fpu 0 vreg4;
	fpu 3 vreg6 = fpu 1 vreg6;
	fpu 3 vreg4 = fpu 1 vreg4;

	fpu 0 .complex vreg1 = vreg0 * vreg7 + vreg5;
	fpu 0 .complex vreg2 = -vreg0 * vreg7 + vreg5;

	fpu 1 .complex vreg1 = vreg0 * vreg7 + vreg5;
	fpu 1 .complex vreg2 = -vreg0 * vreg7 + vreg5;

	fpu 2 .complex vreg1 = vreg0 * vreg4 + vreg6;
	fpu 2 .complex vreg2 = -vreg0 * vreg4 + vreg6;

	fpu 3 .complex vreg1 = vreg0 * vreg4 + vreg6;
	fpu 3 .complex vreg2 = -vreg0 * vreg4 + vreg6;

	fpu 0 vreg3 = fpu 1 vreg1;
	fpu 2 vreg3 = fpu 3 vreg1;
	fpu 1 vreg3 = fpu 0 vreg2;
	fpu 3 vreg3 = fpu 2 vreg2;

// end 2 FFT128

// Compute 1 things of FFT256
	ar1 = [ar5++]; // W128
	fpu 0 rep 32 vreg5 = [ar1++];
	fpu 2 rep 32 vreg5 = [ar1++];
	fpu 1 rep 32 vreg5 = [ar1++];
	fpu 3 rep 32 vreg5 = [ar1++];
	ar2 = gr6; // need for output X

	fpu 0 .complex vreg6 = vreg5 * vreg3 + vreg1;
	fpu 0 .complex vreg7 = -vreg5 * vreg3 + vreg1;

	fpu 1 .complex vreg6 = vreg5 * vreg2 + vreg3;
	fpu 1 .complex vreg7 = -vreg5 * vreg2 + vreg3;

	fpu 2 .complex vreg6 = vreg5 * vreg3 + vreg1;
	fpu 2 .complex vreg7 = -vreg5 * vreg3 + vreg1;

	fpu 3 .complex vreg6 = vreg5 * vreg2 + vreg3;
	fpu 3 .complex vreg7 = -vreg5 * vreg2 + vreg3;

// end 1 FFT256

// in mem
	fpu 0 rep 32 [ar2++] = vreg6;
	fpu 2 rep 32 [ar2++] = vreg6;
	fpu 1 rep 32 [ar2++] = vreg6;
	fpu 3 rep 32 [ar2++] = vreg6;

	fpu 0 rep 32 [ar2++] = vreg7;
	fpu 2 rep 32 [ar2++] = vreg7;
	fpu 1 rep 32 [ar2++] = vreg7;
	fpu 3 rep 32 [ar2++] = vreg7;
// end mem
<exit_fft256>
	pop ar0, gr0;
	pop ar1, gr1;
	pop ar2, gr2;
	pop ar3, gr3;
	pop ar4, gr4;
	pop ar6, gr6;
	return;
end ".text";