global _nmppsFFT128Fwd_32fc: label;
data ".data_imu1"
AddrForDFT8_128: word[16] = (
						0, 16, 8, 24, 4, 20, 12, 28,
						 2, 18, 10, 26, 6, 22, 14, 30
						);
end ".data_imu1";

macro COMPUTE_FFT16_32_64(NUM, LEN)
	fpu NUM rep LEN vreg1 = [ar0++];
	fpu NUM rep LEN vreg2 = [ar6++];
	fpu NUM rep LEN vreg3 = [ar0++];
	fpu NUM rep LEN vreg4 = [ar6++];
	fpu NUM .complex vreg5 = vreg0 * vreg2 + vreg1;
	fpu NUM .complex vreg6 = -vreg0 * vreg2 + vreg1;
	fpu NUM .complex vreg7 = vreg4 * vreg0 + vreg3;
	fpu NUM .complex vreg4 = -vreg4 * vreg0 + vreg3;
end COMPUTE_FFT16_32_64;

macro SAVE_FFT16_32(NUMFP, NEL)
	fpu NUMFP rep NEL [ar3++] = vreg5;
	fpu NUMFP rep NEL [ar4++] = vreg7;
	fpu NUMFP rep NEL [ar3++] = vreg6;
	fpu NUMFP rep NEL [ar4++] = vreg4;
end SAVE_FFT16_32;

macro COMPUTE_FFT128(N128)
	fpu N128 .complex vreg3 = vreg7 * vreg0 + vreg5;
	fpu N128 .complex vreg2 = vreg4 * vreg1 + vreg6;
	fpu N128 .complex vreg0 = -vreg7 * vreg0 + vreg5;
	fpu N128 .complex vreg1 = -vreg4 * vreg1 + vreg6;
end COMPUTE_FFT128;

macro SAVE_FFT128()
	fpu 0 rep 32 [ar2++] = vreg3;
	fpu 0 rep 32 [ar2++] = vreg2;
	fpu 0 rep 32 [ar2++] = vreg0;
	fpu 0 rep 32 [ar2++] = vreg1;
end SAVE_FFT128;

begin ".text128"
<_nmppsFFT128Fwd_32fc>
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
	ar5 = ar5 + 5;
	ar1 = [ar5++]; // W8_0
	ar2 = [ar5++]; // W8_1
	ar3 = ar1;
	ar4 = ar2;
	ar0 = gr2; // buff_fft128
	ar6 = gr4; // buff_fft128xW
	fpu 0 rep 8 vreg0 = [ar1++];
	fpu 1 rep 8 vreg0 = [ar2++];
	fpu 2 rep 8 vreg0 = [ar3++];
	fpu 3 rep 8 vreg0 = [ar4++];

	COMPUTE_FFT16_32_64(0, 8); // 2 FFT16
	COMPUTE_FFT16_32_64(1, 8); // 2 FFT16
	COMPUTE_FFT16_32_64(2, 8); // 2 FFT16
	COMPUTE_FFT16_32_64(3, 8); // 2 FFT16
	ar3 = gr2; // buff_fft128
	ar4 = gr4; // buff_fft128xW
	SAVE_FFT16_32(0, 8);
	SAVE_FFT16_32(1, 8);
	SAVE_FFT16_32(2, 8);
	SAVE_FFT16_32(3, 8);
// END COMPUTE 8 things of FFT16

// COMPUTE 4 things FFT32
	ar1 = [ar5++]; // W16_0
	ar2 = [ar5++]; // W16_1
	ar0 = gr2; // buff_fft128
	ar6 = gr4; // buff_fft128xW
	ar3 = ar0;
	ar4 = ar6;
	fpu 0 rep 16 vreg0 = [ar1++];
	fpu 1 rep 16 vreg0 = [ar2++];
	COMPUTE_FFT16_32_64(0, 16); // 2 FFT32
	COMPUTE_FFT16_32_64(1, 16); // 2 FFT32
	ar5 = ar5 - 9;
	ar0 = [ar5++]; // tmp_128
	ar6 = [ar5++]; // tmp_128xW
	gr0 = ar0;
	gr1 = ar6;
	fpu 0 rep 16 [ar3++] = vreg5;
	fpu 0 rep 16 [ar4++] = vreg7;
	fpu 0 rep 16 [ar3++] = vreg6;
	fpu 0 rep 16 [ar4++] = vreg4;

	fpu 1 rep 16 [ar0++] = vreg5;
	fpu 1 rep 16 [ar6++] = vreg7;
	fpu 1 rep 16 [ar0++] = vreg6;
	fpu 1 rep 16 [ar6++] = vreg4;

// END COMPUTE 4 things FFT32

// COMPUTE 2 things FFT64
	ar5 = ar5 + 7;
	ar1 = [ar5++]; // W32_0
	ar2 = [ar5++]; // W32_1
	ar0 = gr2; // buff_fft128
	ar6 = gr4; // buff_fft128xW
	ar3 = gr0; // tmp_128
	ar4 = gr1; // tmp_128xW
	fpu 0 rep 32 vreg0 = [ar1++];
	fpu 1 rep 32 vreg0 = [ar2++];

	fpu 0 rep 32 vreg1 = [ar0++];
	fpu 0 rep 32 vreg2 = [ar6++];
	fpu 1 rep 32 vreg3 = [ar3++];
	fpu 1 rep 32 vreg4 = [ar4++];
	fpu 0 .complex vreg5 = vreg0 * vreg2 + vreg1;
	fpu 0 .complex vreg6 = -vreg0 * vreg2 + vreg1;
	fpu 1 .complex vreg7 = vreg4 * vreg0 + vreg3;
	fpu 1 .complex vreg4 = -vreg4 * vreg0 + vreg3;
// END FFT64

// COMPUTE FFT128
	ar1 = [ar5++]; // W64_0
	ar2 = gr6; // output X
	fpu 0 rep 32 vreg0 = [ar1++];
	fpu 0 rep 32 vreg1 = [ar1++];
	fpu 0 vreg2 = fpu 1 vreg7;
	fpu 0 vreg3 = fpu 1 vreg4;
	fpu 0 .complex vreg7 = vreg0 * vreg2 + vreg5;
	fpu 0 .complex vreg2 = -vreg0 * vreg2 + vreg5;
	fpu 0 .complex vreg5 = vreg1 * vreg3 + vreg6;
	fpu 0 .complex vreg1 = -vreg1 * vreg3 + vreg6;
	fpu 0 rep 32 [ar2++] = vreg7;
	fpu 0 rep 32 [ar2++] = vreg5;
	fpu 0 rep 32 [ar2++] = vreg2;
	fpu 0 rep 32 [ar2++] = vreg1;
// END FFT128
	
<exit_fft128>
	pop ar0, gr0;
	pop ar1, gr1;
	pop ar2, gr2;
	pop ar3, gr3;
	pop ar4, gr4;
	pop ar6, gr6;	
	return;
end ".text128";