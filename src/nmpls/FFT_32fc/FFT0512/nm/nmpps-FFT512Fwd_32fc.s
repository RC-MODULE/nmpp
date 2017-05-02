global _nmppsFFT512Fwd_32fc: label;
data ".data_imu1"
AddrFor32DFT8: word[64]  = (
	0, 64, 32, 96, 16, 80, 48, 112, 8, 72, 40, 104, 24, 88, 56, 120,
	4, 68, 36, 100, 20, 84, 52, 116, 12, 76, 44, 108, 28, 92, 60, 124,
	2, 66, 34, 98, 18, 82, 50, 114, 10, 74, 42, 106, 26, 90, 58, 122,
	6, 70, 38, 102, 22, 86, 54, 118, 14, 78, 46, 110, 30, 94, 62, 126
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

macro INMEM(N512)
	fpu N512 rep 32 [ar2++] = vreg3;
	fpu N512 rep 32 [ar2++] = vreg2;
	fpu N512 rep 32 [ar2++] = vreg0;
	fpu N512 rep 32 [ar2++] = vreg1;
end INMEM;

begin ".text"
<_nmppsFFT512Fwd_32fc>
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
	ar4 = [ar5++];
	ar2 = [ar5++];
	gr1 = 128;
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

// COMPUTE 64 PART OF DFT8
	ar0 = [ar5++]; // buff_fft512
	ar6 = [ar5++]; // buff_fft512xW
	gr2 = ar0;
	gr7 = ar6;
	ar4 = AddrFor32DFT8;
	gr3 = [ar4++];
<COMP_64_8>
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
	if > delayed goto COMP_64_8;
	gr3 = [ar4++];
	nul;
// END COMPUTE 32 PART OF DFT16

// COMPUTE 32 PART OF FFT16
	ar5 = ar5 + 5;
	ar1 = [ar5++]; // W8_0
	ar2 = [ar5++]; // W8_1
	ar3 = ar1;
	ar4 = ar2;
	gr4 = gr1 >> 5;
	ar0 = gr2; // buff_fft512
	ar6 = gr7; // buff_fft512xW
	fpu 0 rep 8 vreg0 = [ar1++];
	fpu 1 rep 8 vreg0 = [ar2++];
	fpu 2 rep 8 vreg0 = [ar3++];
	fpu 3 rep 8 vreg0 = [ar4++];
	ar3 = ar0;
	ar4 = ar6;
<COMP_32_FFT16_512>
	COMPUTE_FFT16_32_64(0, 8);

	COMPUTE_FFT16_32_64(1, 8);

	COMPUTE_FFT16_32_64(2, 8);

	COMPUTE_FFT16_32_64(3, 8);

	SAVE_FFT16_32(0, 8);
	SAVE_FFT16_32(1, 8);
	SAVE_FFT16_32(2, 8);
	SAVE_FFT16_32(3, 8);
	gr4--;
	if > goto COMP_32_FFT16_512;
// END FFT16

//COMPUTE 16 PART OF FFT32
	ar0 = gr2; // buff_fft512
	ar6 = gr7; // buff_fft512xW
	gr0 = gr1 >> 6;
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
<COMP_16_FFT32_512>
	COMPUTE_FFT16_32_64(0, 16); // 2 FFT32

	COMPUTE_FFT16_32_64(1, 16); // 2 FFT32

	COMPUTE_FFT16_32_64(2, 16); // 2 FFT32

	COMPUTE_FFT16_32_64(3, 16); // 2 FFT32

	SAVE_FFT16_32(0, 16);
	SAVE_FFT16_32(1, 16);
	SAVE_FFT16_32(2, 16);
	SAVE_FFT16_32(3, 16);
	gr0--;
	if > goto COMP_16_FFT32_512;

// END FFT32

// COMPUTE 8 PART FFT64
	ar5 = ar5 + 5;
	ar1 = [ar5++]; // W256
	gr4 = ar1;
	gr1 >>= 3;
	ar0 = gr2; // buff_fft512
	ar6 = gr7; // buff_fft512xW
	fpu 0 rep 32 vreg0 = [ar1++gr1];
	fpu 1 vreg0 = fpu 0 vreg0;
	fpu 2 vreg0 = fpu 0 vreg0;
	fpu 3 vreg0 = fpu 0 vreg0;

	COMPUTE_FFT16_32_64(0, 32); // 2 FFT64

	COMPUTE_FFT16_32_64(1, 32); // 2 FFT64

	COMPUTE_FFT16_32_64(2, 32); // 2 FFT64

	COMPUTE_FFT16_32_64(3, 32); // 2 FFT64

// END FFT64

// COMPUTE 4 PART OF FFT128
	ar1 = gr4; // W256
	gr1 >>= 1;
	fpu 0 rep 32 vreg0 = [ar1++gr1];
	fpu 0 rep 32 vreg1 = [ar1++gr1];
	fpu 1 vreg0 = fpu 0 vreg0;
	fpu 1 vreg1 = fpu 0 vreg1;
	COMPUTE_FFT128(0); // 1 FFT128
	fpu 2 vreg0 = fpu 1 vreg0;
	fpu 2 vreg1 = fpu 1 vreg1;
	COMPUTE_FFT128(1); // 2 FFT128
	fpu 3 vreg0 = fpu 2 vreg0;
	fpu 3 vreg1 = fpu 2 vreg1;
	COMPUTE_FFT128(2); // 3 FFT128
	COMPUTE_FFT128(3); // 4 FFT128
	ar1 = gr4; // W256
	gr1 >>= 1;
	fpu 1 rep 32 vreg4 = [ar1++gr1]; // 32 elem of W128
	fpu 1 rep 32 vreg5 = [ar1++gr1]; // 32 elem of W128
	fpu 1 rep 32 vreg6 = [ar1++gr1]; // 32 elem of W128
	fpu 1 rep 32 vreg7 = [ar1++gr1]; // 32 elem of W128
	fpu 3 vreg4 = fpu 1 vreg4;
	fpu 3 vreg5 = fpu 1 vreg5;
	fpu 3 vreg6 = fpu 1 vreg6;
	fpu 3 vreg7 = fpu 1 vreg7;
	fpu 1 .complex vreg3 = vreg3 * vreg4; // W128 * FFT128
	fpu 3 .complex vreg3 = vreg3 * vreg4; // W128 * FFT128
	fpu 1 .complex vreg2 = vreg2 * vreg5; // W128 * FFT128
	fpu 3 .complex vreg2 = vreg2 * vreg5; // W128 * FFT128
	fpu 1 .complex vreg0 = vreg0 * vreg6; // W128 * FFT128
	fpu 3 .complex vreg0 = vreg0 * vreg6; // W128 * FFT128
	fpu 1 .complex vreg1 = vreg1 * vreg7; // W128 * FFT128
	fpu 3 .complex vreg1 = vreg1 * vreg7; // W128 * FFT128
// END FFT128

// COMPUTE 2 PART OF FFT256
	fpu 0 vreg4 = fpu 1 vreg3;
	fpu 0 vreg5 = fpu 1 vreg2;
	fpu 0 vreg6 = fpu 1 vreg0;
	fpu 0 vreg7 = fpu 1 vreg1;
	fpu 1 vreg4 = fpu 0 vreg3;
	fpu 1 vreg5 = fpu 0 vreg2;
	fpu 1 vreg6 = fpu 0 vreg0;
	fpu 1 vreg7 = fpu 0 vreg1;
	fpu 0 .float vreg3 = vreg3 + vreg4;
	fpu 1 .float vreg3 = vreg4 - vreg3;
	fpu 0 .float vreg2 = vreg2 + vreg5;
	fpu 1 .float vreg2 = vreg5 - vreg2;
	fpu 0 .float vreg0 = vreg0 + vreg6;
	fpu 1 .float vreg0 = vreg6 - vreg0;
	fpu 0 .float vreg1 = vreg1 + vreg7;
	fpu 1 .float vreg1 = vreg7 - vreg1;

	fpu 2 vreg4 = fpu 3 vreg3;
	fpu 2 vreg5 = fpu 3 vreg2;
	fpu 2 vreg6 = fpu 3 vreg0;
	fpu 2 vreg7 = fpu 3 vreg1;
	fpu 3 vreg4 = fpu 2 vreg3;
	fpu 3 vreg5 = fpu 2 vreg2;
	fpu 3 vreg6 = fpu 2 vreg0;
	fpu 3 vreg7 = fpu 2 vreg1;
	fpu 2 .float vreg3 = vreg3 + vreg4;
	fpu 3 .float vreg3 = vreg4 - vreg3;
	fpu 2 .float vreg2 = vreg2 + vreg5;
	fpu 3 .float vreg2 = vreg5 - vreg2;
	fpu 2 .float vreg0 = vreg0 + vreg6;
	fpu 3 .float vreg0 = vreg6 - vreg0;
	fpu 2 .float vreg1 = vreg1 + vreg7;
	fpu 3 .float vreg1 = vreg7 - vreg1;

	ar1 = gr4; // W256
	fpu 2 rep 32 vreg4 = [ar1++];
	fpu 2 rep 32 vreg5 = [ar1++];
	fpu 2 rep 32 vreg6 = [ar1++];
	fpu 2 rep 32 vreg7 = [ar1++];
	fpu 3 rep 32 vreg4 = [ar1++];
	fpu 3 rep 32 vreg5 = [ar1++];
	fpu 3 rep 32 vreg6 = [ar1++];
	fpu 3 rep 32 vreg7 = [ar1++];
	fpu 2 .complex vreg3 = vreg3 * vreg4; // W256 * FFT256
	fpu 3 .complex vreg3 = vreg3 * vreg4; // odd W256 * FFT256
	fpu 2 .complex vreg2 = vreg2 * vreg5; // W256 * FFT256
	fpu 3 .complex vreg2 = vreg2 * vreg5; // odd W256 * FFT256
	fpu 2 .complex vreg0 = vreg0 * vreg6; // W256 * FFT256
	fpu 3 .complex vreg0 = vreg0 * vreg6; // odd W256 * FFT256
	fpu 2 .complex vreg1 = vreg1 * vreg7; // W256 * FFT256
	fpu 3 .complex vreg1 = vreg1 * vreg7; // odd W256 * FFT256
// END FFT256

// COMPUTE FFT512
	fpu 0 vreg4 = fpu 2 vreg3;
	fpu 0 vreg5 = fpu 2 vreg2;
	fpu 0 vreg6 = fpu 2 vreg0;
	fpu 0 vreg7 = fpu 2 vreg1;
	fpu 2 vreg4 = fpu 0 vreg3;
	fpu 2 vreg5 = fpu 0 vreg2;
	fpu 2 vreg6 = fpu 0 vreg0;
	fpu 2 vreg7 = fpu 0 vreg1;
	fpu 0 .float vreg3 = vreg3 + vreg4; // 1 - FFT512
	fpu 0 .float vreg2 = vreg2 + vreg5;
	fpu 0 .float vreg0 = vreg0 + vreg6;
	fpu 0 .float vreg1 = vreg1 + vreg7;

	fpu 2 .float vreg3 = vreg4 - vreg3; // 3 - FFT512
	fpu 2 .float vreg2 = vreg5 - vreg2;
	fpu 2 .float vreg0 = vreg6 - vreg0;
	fpu 2 .float vreg1 = vreg7 - vreg1;

	fpu 1 vreg4 = fpu 3 vreg3;
	fpu 1 vreg5 = fpu 3 vreg2;
	fpu 1 vreg6 = fpu 3 vreg0;
	fpu 1 vreg7 = fpu 3 vreg1;
	fpu 3 vreg4 = fpu 1 vreg3;
	fpu 3 vreg5 = fpu 1 vreg2;
	fpu 3 vreg6 = fpu 1 vreg0;
	fpu 3 vreg7 = fpu 1 vreg1;
	fpu 1 .float vreg3 = vreg3 + vreg4; // 2 - FFT512
	fpu 1 .float vreg2 = vreg2 + vreg5;
	fpu 1 .float vreg0 = vreg0 + vreg6;
	fpu 1 .float vreg1 = vreg1 + vreg7;

	ar2 = gr6; // output X

	fpu 3 .float vreg3 = vreg4 - vreg3; // 4 - FFT512
	fpu 3 .float vreg2 = vreg5 - vreg2;
	fpu 3 .float vreg0 = vreg6 - vreg0;
	fpu 3 .float vreg1 = vreg7 - vreg1;
// END FFT512

// in mem
	INMEM(0);
	INMEM(1);
	INMEM(2);
	INMEM(3);
// end in mem

<exit_fft512>
	pop ar0, gr0;
	pop ar1, gr1;
	pop ar2, gr2;
	pop ar3, gr3;
	pop ar4, gr4;
	pop ar6, gr6;
	return;
end ".text";