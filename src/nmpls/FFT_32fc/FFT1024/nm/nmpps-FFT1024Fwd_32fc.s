global _nmppsFFT1024Fwd_32fc: label;
data ".data_imu1"
AddrFor64DFT8: word[128] = (
	0, 128, 64, 192, 32, 160, 96, 224, 16, 144, 80, 208, 48, 176, 112, 240, 8, 136, 72, 200, 40, 168, 104, 232, 24, 152, 88, 216, 56, 184, 120, 248, 4, 
	132, 68, 196, 36, 164, 100, 228, 20, 148, 84, 212, 52, 180, 116, 244, 12, 140, 76, 204, 44, 172, 108, 236, 28, 156, 92, 220, 60, 188, 124, 252, 2, 
	130, 66, 194, 34, 162, 98, 226, 18, 146, 82, 210, 50, 178, 114, 242, 10, 138, 74, 202, 42, 170, 106, 234, 26, 154, 90, 218, 58, 186, 122, 250, 6, 
	134, 70, 198, 38, 166, 102, 230, 22, 150, 86, 214, 54, 182, 118, 246, 14, 142, 78, 206, 46, 174, 110, 238, 30, 158, 94, 222, 62, 190, 126, 254
	);
end ".data_imu1";

macro COMPUTE_FFT16_32_64_1024(NMF, LEN)
	fpu NMF rep LEN vreg1 = [ar0++];
	fpu NMF rep LEN vreg2 = [ar6++]; // need mul W
	fpu NMF rep LEN vreg3 = [ar0++];
	fpu NMF rep LEN vreg4 = [ar6++]; // need mul W
	fpu NMF .complex vreg5 = vreg0 * vreg2 + vreg1; // 1 part of FFT64
	fpu NMF .complex vreg6 = -vreg0 * vreg2 + vreg1; // 2 part of FFT64
	fpu NMF .complex vreg7 = vreg0 * vreg4 + vreg3; // 1 part of FFT64
	fpu NMF .complex vreg4 = -vreg0 * vreg4 + vreg3; // 2 part of FFT64
end COMPUTE_FFT16_32_64_1024;

macro SAVE_FFT16_32_64_1024(FMN, ELN)
	fpu FMN rep ELN [ar3++] = vreg5;
	fpu FMN rep ELN [ar4++] = vreg7;
	fpu FMN rep ELN [ar3++] = vreg6;
	fpu FMN rep ELN [ar4++] = vreg4;
end SAVE_FFT16_32_64_1024;

macro COMPUTE_FFT128_1024(NN)
	fpu NN rep 32 vreg2 = [ar0++];
	fpu NN rep 32 vreg3 = [ar6++]; // need mul W128
	fpu NN rep 32 vreg4 = [ar0++];
	fpu NN rep 32 vreg5 = [ar6++]; // need mul W128
	fpu NN .complex vreg6 = vreg0 * vreg3 + vreg2;
	fpu NN .complex vreg7 = vreg1 * vreg5 + vreg4;
	fpu NN .complex vreg2 = -vreg0 * vreg3 + vreg2;
	fpu NN .complex vreg4 = -vreg1 * vreg5 + vreg4;
end COMPUTE_FFT128_1024;

macro SAVE_FFT128_1024(NNM, REG)
	fpu NNM rep 32 [REG++] = vreg6;
	fpu NNM rep 32 [REG++] = vreg7;
	fpu NNM rep 32 [REG++] = vreg2;
	fpu NNM rep 32 [REG++] = vreg4;
end SAVE_FFT128_1024;

macro FFT128xW256(MNN)
	fpu MNN rep 32 vreg0 = [ar1++gr1];
	fpu MNN rep 32 vreg1 = [ar1++gr1];
	fpu MNN rep 32 vreg3 = [ar1++gr1];
	fpu MNN rep 32 vreg5 = [ar1++gr1];
	fpu MNN .complex vreg6 = vreg6 * vreg0;
	fpu MNN .complex vreg7 = vreg7 * vreg1;
	fpu MNN .complex vreg2 = vreg2 * vreg3;
	fpu MNN .complex vreg4 = vreg4 * vreg5;
end FFT128xW256;

macro COMPUTE_FFT256_512_1024(MM)
	fpu MM rep 32 vreg0 = [ar0++];
	fpu MM rep 32 vreg1 = [ar6++];
	fpu MM rep 32 vreg2 = [ar0++];
	fpu MM rep 32 vreg3 = [ar6++];
	fpu MM .float vreg4 = vreg0 + vreg1;
	fpu MM .float vreg5 = vreg2 + vreg3;
	fpu MM .float vreg6 = vreg0 - vreg1;
	fpu MM .float vreg7 = vreg2 - vreg3;
end COMPUTE_FFT256_512_1024;

macro INMEM1024(REG0, REG1, REG2)
	fpu 0 rep 32 [REG0++] = REG1;
	fpu 0 rep 32 [REG0++] = REG2;
	fpu 1 rep 32 [REG0++] = REG1;
	fpu 1 rep 32 [REG0++] = REG2;
	fpu 2 rep 32 [REG0++] = REG1;
	fpu 2 rep 32 [REG0++] = REG2;
	fpu 3 rep 32 [REG0++] = REG1;
	fpu 3 rep 32 [REG0++] = REG2;
end INMEM1024;

begin ".text"
<_nmppsFFT1024Fwd_32fc>
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
	gr1 = 256;
	ar4 = [ar5++]; // SinCos0
	ar2 = [ar5++]; // SinCos1
	gr0 = gr1 >> 2; // cycles number

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

// COMPUTE 128 PART OF DFT8
	ar4 = AddrFor64DFT8;
	gr3 = [ar4++];
	ar0 = [ar5++]; // buff_fft1024
	ar6 = [ar5++]; // buff_fft1024xW
	gr2 = ar0;
	gr7 = ar6;
<COMP_128_DFT8>
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
	if > delayed goto COMP_128_DFT8;
	gr3 = [ar4++];
	nul;
// END 128 DFT8 

// COMPUTE 64 PART OF FFT16
	ar5 = ar5 + 5;
	ar1 = [ar5++]; // W8_0
	ar2 = [ar5++]; // W8_1
	ar3 = ar1;
	ar4 = ar2;
	gr0 = gr1 >> 5;
	ar0 = gr2; // buff_fft1024
	ar6 = gr7; // buff_fft1024xW
	fpu 0 rep 8 vreg0 = [ar1++];
	fpu 1 rep 8 vreg0 = [ar2++];
	fpu 2 rep 8 vreg0 = [ar3++];
	fpu 3 rep 8 vreg0 = [ar4++];
	ar3 = ar0;
	ar4 = ar6;
<COMP_64_FFT16_1024>
	COMPUTE_FFT16_32_64_1024(0, 8);

	COMPUTE_FFT16_32_64_1024(1, 8);

	COMPUTE_FFT16_32_64_1024(2, 8);

	COMPUTE_FFT16_32_64_1024(3, 8);

	SAVE_FFT16_32_64_1024(0, 8);
	SAVE_FFT16_32_64_1024(1, 8);
	SAVE_FFT16_32_64_1024(2, 8);
	SAVE_FFT16_32_64_1024(3, 8);
	gr0--;
	if > goto COMP_64_FFT16_1024;
// END FFT16

// COMPUTE 32 OF FFT32
	ar5 = ar5 + 8;
	ar0 = gr2;
	ar6 = gr7;
	gr1 >>= 2;
	ar1 = [ar5++]; // W512
	gr4 = ar1;
	ar3 = ar0; // for SAVE_FFT32
	ar4 = ar6; // for SAVE_FFT32
	gr0 = gr1 >> 4;
	fpu 0 rep 16 vreg0 = [ar1++gr1];
	fpu 1 vreg0 = fpu 0 vreg0;
	fpu 2 vreg0 = fpu 0 vreg0;
	fpu 3 vreg0 = fpu 0 vreg0;
<COMP_FFT32_1024>
	COMPUTE_FFT16_32_64_1024(0, 16);

	COMPUTE_FFT16_32_64_1024(1, 16);

	COMPUTE_FFT16_32_64_1024(2, 16);

	COMPUTE_FFT16_32_64_1024(3, 16);
	SAVE_FFT16_32_64_1024(0, 16);
	SAVE_FFT16_32_64_1024(1, 16);
	SAVE_FFT16_32_64_1024(2, 16);
	SAVE_FFT16_32_64_1024(3, 16);

	gr0--;
	if > goto COMP_FFT32_1024;
// END FFT32

// COMPUTE 16 OF FFT64
	ar0 = gr2; // buff_fft1024
	ar6 = gr7; // buff_fft1024xW
	ar1 = gr4; // W512
	gr1 >>= 1;
	gr0 = gr1 >> 4;
	ar3 = gr2; // for save FFT64
	ar4 = gr7; // for save FFT64

	fpu 0 rep 32 vreg0 = [ar1++gr1]; // W32
	fpu 1 vreg0 = fpu 0 vreg0;
	fpu 2 vreg0 = fpu 1 vreg0;
	fpu 3 vreg0 = fpu 2 vreg0;

<COMP_FFT64_1024>
	COMPUTE_FFT16_32_64_1024(0, 32);

	COMPUTE_FFT16_32_64_1024(1, 32);

	COMPUTE_FFT16_32_64_1024(2, 32);

	COMPUTE_FFT16_32_64_1024(3, 32);
	SAVE_FFT16_32_64_1024(0, 32);
	SAVE_FFT16_32_64_1024(1, 32);
	SAVE_FFT16_32_64_1024(2, 32);
	SAVE_FFT16_32_64_1024(3, 32);
	gr0--;
	if > goto COMP_FFT64_1024;
// END FFT64

// COMPUTE 8 OF FFT128
	ar0 = gr2; // buff_fft1024
	ar6 = gr7; // buff_fft1024xW
	ar1 = gr4;
	gr1 >>= 1;
	ar3 = ar0;
	ar4 = ar6;

	fpu 0 rep 32 vreg0 = [ar1++gr1]; // 1 - W64
	fpu 0 rep 32 vreg1 = [ar1++gr1]; // 2 - W64
	fpu 1 vreg0 = fpu 0 vreg0;
	fpu 1 vreg1 = fpu 0 vreg1;
	fpu 2 vreg0 = fpu 1 vreg0;
	fpu 2 vreg1 = fpu 1 vreg1;
	fpu 3 vreg0 = fpu 2 vreg0;
	fpu 3 vreg1 = fpu 2 vreg1;
	ar1 = gr4; // W512
	gr1 >>= 1;
	COMPUTE_FFT128_1024(0);
	COMPUTE_FFT128_1024(1);
	//FFT128xW256(1);
	COMPUTE_FFT128_1024(2);
	COMPUTE_FFT128_1024(3);
	FFT128xW256(1);
	ar1 = gr4;
	FFT128xW256(3);

	SAVE_FFT128_1024(0, ar3);
	SAVE_FFT128_1024(1, ar4);
	SAVE_FFT128_1024(2, ar3);
	SAVE_FFT128_1024(3, ar4);
	fpu 1 vreg0 = fpu 0 vreg0;
	fpu 1 vreg1 = fpu 0 vreg1;
	fpu 3 vreg0 = fpu 1 vreg0;
	fpu 3 vreg1 = fpu 1 vreg1;
	ar1 = gr4;
	COMPUTE_FFT128_1024(0);
	COMPUTE_FFT128_1024(1);
	//FFT128xW256(1);
	COMPUTE_FFT128_1024(2);
	COMPUTE_FFT128_1024(3);
	FFT128xW256(1);
	ar1 = gr4; // W512
	FFT128xW256(3);

	SAVE_FFT128_1024(0, ar3);
	SAVE_FFT128_1024(1, ar4);
	SAVE_FFT128_1024(2, ar3);
	SAVE_FFT128_1024(3, ar4);
// END FTT 128

// COMPUTE 4 OF FFT256
	ar0 = gr2;
	ar6 = gr7;
	ar3 = ar0;
	ar4 = ar6;
	ar1 = gr4;
	gr1 >>= 1;

	COMPUTE_FFT256_512_1024(0);
	COMPUTE_FFT256_512_1024(1);
	COMPUTE_FFT256_512_1024(2);
	COMPUTE_FFT256_512_1024(3);
	//ar5 = ar7 - 15;
	fpu 2 rep 32 vreg0 = [ar1++gr1];
	fpu 2 rep 32 vreg1 = [ar1++gr1];
	fpu 3 rep 32 vreg0 = [ar1++gr1];
	fpu 3 rep 32 vreg1 = [ar1++gr1];
	fpu 2 rep 32 vreg2 = [ar1++gr1];
	fpu 2 rep 32 vreg3 = [ar1++gr1];
	fpu 3 rep 32 vreg2 = [ar1++gr1];
	fpu 3 rep 32 vreg3 = [ar1++gr1];
	fpu 2 .complex vreg4 = vreg4 * vreg0;
	fpu 2 .complex vreg5 = vreg5 * vreg1;
	fpu 3 .complex vreg4 = vreg4 * vreg0;
	fpu 3 .complex vreg5 = vreg5 * vreg1;
	fpu 2 .complex vreg6 = vreg6 * vreg2;
	fpu 2 .complex vreg7 = vreg7 * vreg3;
	fpu 3 .complex vreg6 = vreg6 * vreg2;
	fpu 3 .complex vreg7 = vreg7 * vreg3;


	fpu 0 rep 32 [ar3++] = vreg4;
	fpu 0 rep 32 [ar3++] = vreg5;
	fpu 1 rep 32 [ar3++] = vreg4;
	fpu 1 rep 32 [ar3++] = vreg5;
	fpu 0 rep 32 [ar3++] = vreg6;
	fpu 0 rep 32 [ar3++] = vreg7;
	fpu 1 rep 32 [ar3++] = vreg6;
	fpu 1 rep 32 [ar3++] = vreg7;

	fpu 2 rep 32 [ar4++] = vreg4;
	fpu 2 rep 32 [ar4++] = vreg5;
	fpu 3 rep 32 [ar4++] = vreg4;
	fpu 3 rep 32 [ar4++] = vreg5;
	fpu 2 rep 32 [ar4++] = vreg6;
	fpu 2 rep 32 [ar4++] = vreg7;
	fpu 3 rep 32 [ar4++] = vreg6;
	fpu 3 rep 32 [ar4++] = vreg7;

	COMPUTE_FFT256_512_1024(0);
	COMPUTE_FFT256_512_1024(1);
	COMPUTE_FFT256_512_1024(2);
	COMPUTE_FFT256_512_1024(3);
	ar1 = gr4;

	fpu 2 rep 32 vreg0 = [ar1++gr1];
	fpu 2 rep 32 vreg1 = [ar1++gr1];
	fpu 3 rep 32 vreg0 = [ar1++gr1];
	fpu 3 rep 32 vreg1 = [ar1++gr1];
	fpu 2 rep 32 vreg2 = [ar1++gr1];
	fpu 2 rep 32 vreg3 = [ar1++gr1];
	fpu 3 rep 32 vreg2 = [ar1++gr1];
	fpu 3 rep 32 vreg3 = [ar1++gr1];
	fpu 2 .complex vreg4 = vreg4 * vreg0;
	fpu 2 .complex vreg5 = vreg5 * vreg1;
	fpu 3 .complex vreg4 = vreg4 * vreg0;
	fpu 3 .complex vreg5 = vreg5 * vreg1;
	fpu 2 .complex vreg6 = vreg6 * vreg2;
	fpu 2 .complex vreg7 = vreg7 * vreg3;
	fpu 3 .complex vreg6 = vreg6 * vreg2;
	fpu 3 .complex vreg7 = vreg7 * vreg3;


	fpu 0 rep 32 [ar3++] = vreg4;
	fpu 0 rep 32 [ar3++] = vreg5;
	fpu 1 rep 32 [ar3++] = vreg4;
	fpu 1 rep 32 [ar3++] = vreg5;
	fpu 0 rep 32 [ar3++] = vreg6;
	fpu 0 rep 32 [ar3++] = vreg7;
	fpu 1 rep 32 [ar3++] = vreg6;
	fpu 1 rep 32 [ar3++] = vreg7;

	fpu 2 rep 32 [ar4++] = vreg4;
	fpu 2 rep 32 [ar4++] = vreg5;
	fpu 3 rep 32 [ar4++] = vreg4;
	fpu 3 rep 32 [ar4++] = vreg5;
	fpu 2 rep 32 [ar4++] = vreg6;
	fpu 2 rep 32 [ar4++] = vreg7;
	fpu 3 rep 32 [ar4++] = vreg6;
	fpu 3 rep 32 [ar4++] = vreg7;
// END FFT256

// COMPUTE 2 OF FFT512
	ar5 = ar5 - 14;
	ar0 = gr2;
	ar6 = gr7;
	ar3 = [ar5++];
	gr0 = ar3;
	ar4 = ar6;
	ar1 = gr4; // W512

	COMPUTE_FFT256_512_1024(0);
	COMPUTE_FFT256_512_1024(1);
	COMPUTE_FFT256_512_1024(2);
	COMPUTE_FFT256_512_1024(3);

	INMEM1024(ar3, vreg4, vreg5);
	INMEM1024(ar3, vreg6, vreg7);

	COMPUTE_FFT256_512_1024(0);
	COMPUTE_FFT256_512_1024(1);
	COMPUTE_FFT256_512_1024(2);
	COMPUTE_FFT256_512_1024(3);
	ar2 = gr6; // output X
	fpu 0 rep 32 vreg0 = [ar1++];
	fpu 0 rep 32 vreg1 = [ar1++];
	fpu 1 rep 32 vreg0 = [ar1++];
	fpu 1 rep 32 vreg1 = [ar1++];
	fpu 2 rep 32 vreg0 = [ar1++];
	fpu 2 rep 32 vreg1 = [ar1++];
	fpu 3 rep 32 vreg0 = [ar1++];
	fpu 3 rep 32 vreg1 = [ar1++];

	fpu 0 rep 32 vreg2 = [ar1++];
	fpu 0 rep 32 vreg3 = [ar1++];
	fpu 1 rep 32 vreg2 = [ar1++];
	fpu 1 rep 32 vreg3 = [ar1++];
	fpu 2 rep 32 vreg2 = [ar1++];
	fpu 2 rep 32 vreg3 = [ar1++];
	fpu 3 rep 32 vreg2 = [ar1++];
	fpu 3 rep 32 vreg3 = [ar1++];

	fpu 0 .complex vreg4 = vreg4 * vreg0;
	fpu 0 .complex vreg5 = vreg5 * vreg1;
	fpu 1 .complex vreg4 = vreg4 * vreg0;
	fpu 1 .complex vreg5 = vreg5 * vreg1;
	fpu 2 .complex vreg4 = vreg4 * vreg0;
	fpu 2 .complex vreg5 = vreg5 * vreg1;
	fpu 3 .complex vreg4 = vreg4 * vreg0;
	fpu 3 .complex vreg5 = vreg5 * vreg1;

	fpu 0 .complex vreg6 = vreg6 * vreg2;
	fpu 0 .complex vreg7 = vreg7 * vreg3;
	fpu 1 .complex vreg6 = vreg6 * vreg2;
	fpu 1 .complex vreg7 = vreg7 * vreg3;
	fpu 2 .complex vreg6 = vreg6 * vreg2;
	fpu 2 .complex vreg7 = vreg7 * vreg3;
	fpu 3 .complex vreg6 = vreg6 * vreg2;
	fpu 3 .complex vreg7 = vreg7 * vreg3;

	INMEM1024(ar4, vreg4, vreg5);
	INMEM1024(ar4, vreg6, vreg7);

// END FFT512

// COMPUTE 1 OF FFT1024
	ar0 = gr0;
	ar6 = gr7;

	COMPUTE_FFT256_512_1024(0);
	COMPUTE_FFT256_512_1024(1);
	COMPUTE_FFT256_512_1024(2);
	COMPUTE_FFT256_512_1024(3);

	INMEM1024(ar2, vreg4, vreg5);

	ar2 = ar2 + 512;

	INMEM1024(ar2, vreg6, vreg7);

	COMPUTE_FFT256_512_1024(0);
	COMPUTE_FFT256_512_1024(1);
	COMPUTE_FFT256_512_1024(2);
	COMPUTE_FFT256_512_1024(3);

	INMEM1024(ar2, vreg6, vreg7);

	ar2 = ar2 - 1536;

	INMEM1024(ar2, vreg4, vreg5);

// END FFT1024
<exit_fft1024>
	pop ar0, gr0;
	pop ar1, gr1;
	pop ar2, gr2;
	pop ar3, gr3;
	pop ar4, gr4;
	pop ar6, gr6;
	return;
end ".text";