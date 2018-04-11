global _nmppsFFT64Fwd_32fcr: label;
global _nmppsFFT64Inv_32fcr: label;
data ".data_imu1"
AddrForDFT8_64: word[8] = (0, 8, 4, 12, 2, 10, 6, 14);
end ".data_imu1";

begin ".data_imu7"
<_nmppsFFT64Fwd_32fcr>
<_nmppsFFT64Inv_32fcr>
	set fp_branch;
	ar5 = ar7 - 2;
	push ar6, gr6;
	push ar4, gr4;
	push ar3, gr3;
	push ar2, gr2;
	push ar1, gr1;
	push ar0, gr0;
	ar3 = [--ar5]; // input x
	ar0 = [--ar5]; // output X
	gr2 = ar0;
	gr1 = 16;
	gr0 = gr1 >> 2;
	ar5 = [--ar5];
	ar1 = [ar5++];
	ar2 = [ar5++];

// Read SinCos
	fpu 0 rep 8 vreg1 = [ar1++];
	fpu 1 rep 8 vreg1 = [ar2++];
	fpu 2 vreg1 = fpu 0 vreg1;
	fpu 3 vreg1 = fpu 1 vreg1;
	fpu 0 rep 8 vreg2 = [ar1++];
	fpu 1 rep 8 vreg2 = [ar2++];
	fpu 2 vreg2 = fpu 0 vreg2;
	fpu 3 vreg2 = fpu 1 vreg2;
	fpu 0 rep 8 vreg3 = [ar1++];
	fpu 1 rep 8 vreg3 = [ar2++];
	fpu 2 vreg3 = fpu 0 vreg3;
	fpu 3 vreg3 = fpu 1 vreg3;
	fpu 0 rep 8 vreg4 = [ar1++];
	fpu 1 rep 8 vreg4 = [ar2++];
	fpu 2 vreg4 = fpu 0 vreg4;
	fpu 3 vreg4 = fpu 1 vreg4;
// end read SinCos

// Compute 8 things of DFT8
	//ar5 = [--ar5];
	ar0 = [ar5++]; // buff_fft64
	ar6 = [ar5++]; // buff_fft64xW
	ar4 = AddrForDFT8_64;
	gr3 = [ar4++];
	gr5 = ar0;
	gr6 = ar6;
<COMP_8_8_64>
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
	if > delayed goto COMP_8_8_64;
	gr3 = [ar4++];
	nul;
// COMPUTE 4 things of FFT16
	//ar5 = ar5 + 5;
	ar1 = [ar5++]; // W8
	ar0 = gr5;
	ar6 = gr6;
	fpu 0 rep 8 vreg0 = [ar1++];
	fpu 1 vreg0 = fpu 0 vreg0;
	fpu 2 vreg0 = fpu 1 vreg0;
	fpu 3 vreg0 = fpu 2 vreg0;

	fpu 0 rep 8 vreg1 = [ar0++];
	fpu 0 rep 8 vreg2 = [ar6++];
	fpu 0 .complex vreg5 = vreg0 * vreg2 + vreg1;
	fpu 0 .complex vreg6 = -vreg0 * vreg2 + vreg1;
	
	fpu 1 rep 8 vreg1 = [ar0++];
	fpu 1 rep 8 vreg2 = [ar6++];
	fpu 1 .complex vreg5 = vreg0 * vreg2 + vreg1;
	fpu 1 .complex vreg6 = -vreg0 * vreg2 + vreg1;
	ar3 = gr5;
	ar4 = gr6;
	fpu 2 rep 8 vreg1 = [ar0++];
	fpu 2 rep 8 vreg2 = [ar6++];
	fpu 2 .complex vreg5 = vreg0 * vreg2 + vreg1;
	fpu 2 .complex vreg6 = -vreg0 * vreg2 + vreg1;

	fpu 3 rep 8 vreg1 = [ar0++];
	fpu 3 rep 8 vreg2 = [ar6++];
	fpu 3 .complex vreg5 = vreg0 * vreg2 + vreg1;
	fpu 3 .complex vreg6 = -vreg0 * vreg2 + vreg1;

	fpu 0 rep 8 [ar3++] = vreg5;
	fpu 1 rep 8 [ar4++] = vreg5;

	fpu 0 rep 8 [ar3++] = vreg6;
	fpu 1 rep 8 [ar4++] = vreg6;

	fpu 2 rep 8 [ar3++] = vreg5;
	fpu 3 rep 8 [ar4++] = vreg5;

	fpu 2 rep 8 [ar3++] = vreg6;
	fpu 3 rep 8 [ar4++] = vreg6;

// END COMPUTE 4 things of FFT16

// COMPUTE 2 things of FFT32
	ar2 = gr2; // output X
	//ar5++;
	ar1 = [ar5++]; // W16
	ar0 = gr5;
	ar6 = gr6;

	fpu 0 rep 16 vreg0 = [ar1++];
	fpu 1 vreg0 = fpu 0 vreg0;

	fpu 0 rep 16 vreg1 = [ar0++];
	fpu 0 rep 16 vreg2 = [ar6++];
	fpu 0 .complex vreg5 = vreg0 * vreg2 + vreg1;
	fpu 0 .complex vreg6 = -vreg0 * vreg2 + vreg1;
	ar3 = gr5;
	ar4 = gr6;
	fpu 1 rep 16 vreg1 = [ar0++];
	fpu 1 rep 16 vreg2 = [ar6++];
	fpu 1 .complex vreg5 = vreg0 * vreg2 + vreg1;
	fpu 1 .complex vreg6 = -vreg0 * vreg2 + vreg1;

	fpu 0 rep 16 [ar3++] = vreg5;
	fpu 1 rep 16 [ar4++] = vreg5;

	fpu 0 rep 16 [ar3++] = vreg6;
	fpu 1 rep 16 [ar4++] = vreg6;
// END COMPUTE 2 things of FFT32

// COMPUTE 1 FFT64
	//ar5++;
	ar1 = [ar5++]; // W32
	ar0 = gr5;
	ar6 = gr6;
	fpu 0 rep 32 vreg0 = [ar1++];
	fpu 0 rep 32 vreg1 = [ar0++];
	fpu 0 rep 32 vreg2 = [ar6++];
	fpu 0 .complex vreg3 = vreg2 * vreg0 + vreg1;
	fpu 0 .complex vreg4 = -vreg2 * vreg0 + vreg1;
// END COMPUTE FFT64

	fpu 0 rep 32 [ar2++] = vreg3;
	fpu 0 rep 32 [ar2++] = vreg4;
<exit_fft64>
	pop ar0, gr0;
	pop ar1, gr1;
	pop ar2, gr2;
	pop ar3, gr3;
	pop ar4, gr4;
	pop ar6, gr6;
	return;
end ".data_imu7";