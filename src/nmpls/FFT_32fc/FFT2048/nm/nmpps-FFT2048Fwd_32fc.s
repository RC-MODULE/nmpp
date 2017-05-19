global _nmppsFFT2048Fwd_32fc: label;
data ".data_imu1"
AddrFor256DFT8: word[256] = (
	0, 256, 128, 384, 64, 320, 192, 448, 32, 288, 160, 416, 96, 352, 224, 480, 16, 272, 144, 400, 80, 336, 208, 464, 48, 304, 176, 432, 112, 368, 240, 496, 8, 
	264, 136, 392, 72, 328, 200, 456, 40, 296, 168, 424, 104, 360, 232, 488, 24, 280, 152, 408, 88, 344, 216, 472, 56, 312, 184, 440, 120, 376, 248, 504, 4, 
	260, 132, 388, 68, 324, 196, 452, 36, 292, 164, 420, 100, 356, 228, 484, 20, 276, 148, 404, 84, 340, 212, 468, 52, 308, 180, 436, 116, 372, 244, 500, 12, 
	268, 140, 396, 76, 332, 204, 460, 44, 300, 172, 428, 108, 364, 236, 492, 28, 284, 156, 412, 92, 348, 220, 476, 60, 316, 188, 444, 124, 380, 252, 508, 2, 
	258, 130, 386, 66, 322, 194, 450, 34, 290, 162, 418, 98, 354, 226, 482, 18, 274, 146, 402, 82, 338, 210, 466, 50, 306, 178, 434, 114, 370, 242, 498, 10, 
	266, 138, 394, 74, 330, 202, 458, 42, 298, 170, 426, 106, 362, 234, 490, 26, 282, 154, 410, 90, 346, 218, 474, 58, 314, 186, 442, 122, 378, 250, 506, 6, 
	262, 134, 390, 70, 326, 198, 454, 38, 294, 166, 422, 102, 358, 230, 486, 22, 278, 150, 406, 86, 342, 214, 470, 54, 310, 182, 438, 118, 374, 246, 502, 14, 
	270, 142, 398, 78, 334, 206, 462, 46, 302, 174, 430, 110, 366, 238, 494, 30, 286, 158, 414, 94, 350, 222, 478, 62, 318, 190, 446, 126, 382, 254, 510
);
end ".data_imu1";

macro COMPUTE_FFT16_32_64_2048(NMF, LEN)
	fpu NMF rep LEN vreg1 = [ar0++];
	fpu NMF rep LEN vreg2 = [ar6++]; // need mul W
	fpu NMF rep LEN vreg3 = [ar0++];
	fpu NMF rep LEN vreg4 = [ar6++]; // need mul W
	fpu NMF .complex vreg5 = vreg0 * vreg2 + vreg1; // 1 part of FFT64
	fpu NMF .complex vreg6 = -vreg0 * vreg2 + vreg1; // 2 part of FFT64
	fpu NMF .complex vreg7 = vreg0 * vreg4 + vreg3; // 1 part of FFT64
	fpu NMF .complex vreg4 = -vreg0 * vreg4 + vreg3; // 2 part of FFT64
end COMPUTE_FFT16_32_64_2048;

macro SAVE_FFT16_32_64_2048(FMN, ELN)
	fpu FMN rep ELN [ar3++] = vreg5;
	fpu FMN rep ELN [ar4++] = vreg7;
	fpu FMN rep ELN [ar3++] = vreg6;
	fpu FMN rep ELN [ar4++] = vreg4;
end SAVE_FFT16_32_64_2048;

macro COMPUTE_FFT128_2048(NN)
	fpu NN rep 32 vreg2 = [ar0++];
	fpu NN rep 32 vreg3 = [ar6++]; // need mul W128
	fpu NN rep 32 vreg4 = [ar0++];
	fpu NN rep 32 vreg5 = [ar6++]; // need mul W128
	fpu NN .complex vreg6 = vreg0 * vreg3 + vreg2;
	fpu NN .complex vreg7 = vreg1 * vreg5 + vreg4;
	fpu NN .complex vreg2 = -vreg0 * vreg3 + vreg2;
	fpu NN .complex vreg4 = -vreg1 * vreg5 + vreg4;
end COMPUTE_FFT128_2048;

macro SAVE_FFT128_2048(NNM, REG)
	fpu NNM rep 32 [REG++] = vreg6;
	fpu NNM rep 32 [REG++] = vreg7;
	fpu NNM rep 32 [REG++] = vreg2;
	fpu NNM rep 32 [REG++] = vreg4;
end SAVE_FFT128_2048;

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

macro INMEM2048(REG0, REG1, REG2)
	fpu 0 rep 32 [REG0++] = REG1;
	fpu 0 rep 32 [REG0++] = REG2;
	fpu 1 rep 32 [REG0++] = REG1;
	fpu 1 rep 32 [REG0++] = REG2;
	fpu 2 rep 32 [REG0++] = REG1;
	fpu 2 rep 32 [REG0++] = REG2;
	fpu 3 rep 32 [REG0++] = REG1;
	fpu 3 rep 32 [REG0++] = REG2;
end INMEM2048;

begin ".text"
<_nmppsFFT2048Fwd_32fc>
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
	gr1 = 512;
	ar2 = [ar5++]; // SinCos0
	ar6 = [ar5++]; // SinCos1
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

// COMPUTE 256 PART OF DFT8
	ar4 = AddrFor256DFT8;
	gr3 = [ar4++];
	ar0 = [ar5++]; // buff_fft2048
	ar6 = [ar5++]; // buff_fft2048xW
	gr2 = ar0;
	gr7 = ar6;
<COMP_256_DFT8>
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
	if > delayed goto COMP_256_DFT8;
	gr3 = [ar4++];
	nul;
// END 256 DFT8

// COMPUTE 128 PART OF FFT16
	//ar5 = ar5 + 16;
	gr1 >>= 1; // 256
	gr0 = gr1 >> 4; // 16
	ar1 = [ar5++]; // W1024
	gr4 = ar1;
	ar0 = gr2; // buff_fft2048
	ar6 = gr7; // buff_fft2048xW
	fpu 0 rep 8 vreg0 = [ar1++gr1];
	fpu 1 vreg0 = fpu 0 vreg0;
	fpu 2 vreg0 = fpu 1 vreg0;
	fpu 3 vreg0 = fpu 2 vreg0;
	ar3 = ar0;
	ar4 = ar6;
<COMP_128_FFT16_2048>
	COMPUTE_FFT16_32_64_2048(0, 8);

	COMPUTE_FFT16_32_64_2048(1, 8);

	COMPUTE_FFT16_32_64_2048(2, 8);

	COMPUTE_FFT16_32_64_2048(3, 8);
	SAVE_FFT16_32_64_2048(0, 8);
	SAVE_FFT16_32_64_2048(1, 8);
	SAVE_FFT16_32_64_2048(2, 8);
	SAVE_FFT16_32_64_2048(3, 8);
	gr0--;
	if > goto COMP_128_FFT16_2048;
// END FFT16

// COMPUTE 64 OF FFT32
	ar0 = gr2; // buff_fft2048
	ar6 = gr7; // buff_fft2048xW
	gr1 >>= 1; // 128
	ar1 = gr4; // W1024
	gr0 = gr1 >> 4; // 8 
	fpu 0 rep 16 vreg0 = [ar1++gr1];
	fpu 1 vreg0 = fpu 0 vreg0;
	fpu 2 vreg0 = fpu 1 vreg0;
	fpu 3 vreg0 = fpu 2 vreg0;
	ar3 = ar0; // for SAVE_FFT32
	ar4 = ar6; // for SAVE_FFT32
<COMP_FFT32_2048>
	COMPUTE_FFT16_32_64_2048(0, 16);

	COMPUTE_FFT16_32_64_2048(1, 16);

	COMPUTE_FFT16_32_64_2048(2, 16);

	COMPUTE_FFT16_32_64_2048(3, 16);
	SAVE_FFT16_32_64_2048(0, 16);
	SAVE_FFT16_32_64_2048(1, 16);
	SAVE_FFT16_32_64_2048(2, 16);
	SAVE_FFT16_32_64_2048(3, 16);
	gr0--;
	if > goto COMP_FFT32_2048;
// END FFT32

// COMPUTE 32 OF FFT64
	ar0 = gr2; // buff_fft2048
	ar6 = gr7; // buff_fft2048xW
	ar1 = gr4; // W1024
	gr1 >>= 1; // 64
	gr0 = gr1 >> 4; // 4
	fpu 0 rep 32 vreg0 = [ar1++gr1]; // W32
	fpu 1 vreg0 = fpu 0 vreg0;
	fpu 2 vreg0 = fpu 1 vreg0;
	fpu 3 vreg0 = fpu 2 vreg0;
	ar3 = ar0; // for save FFT64
	ar4 = ar6; // for save FFT64
<COMP_FFT64_2048>
	COMPUTE_FFT16_32_64_2048(0, 32);

	COMPUTE_FFT16_32_64_2048(1, 32);

	COMPUTE_FFT16_32_64_2048(2, 32);

	COMPUTE_FFT16_32_64_2048(3, 32);
	SAVE_FFT16_32_64_2048(0, 32);
	SAVE_FFT16_32_64_2048(1, 32);
	SAVE_FFT16_32_64_2048(2, 32);
	SAVE_FFT16_32_64_2048(3,32);
	gr0--;
	if > goto COMP_FFT64_2048;
// END FFT64

// COMPUTE 16 OF FFT128
	ar0 = gr2; // buff_fft2048
	ar6 = gr7; // buff_fft2048xW
	ar1 = gr4; // W1024
	gr1 >>= 1; // 32
	gr0 = gr1 >> 3; // 4
	fpu 0 rep 32 vreg0 = [ar1++gr1]; // 1 - W64
	fpu 0 rep 32 vreg1 = [ar1++gr1]; // 2 - W64
	fpu 1 vreg0 = fpu 0 vreg0;
	fpu 1 vreg1 = fpu 0 vreg1;
	fpu 2 vreg0 = fpu 1 vreg0;
	fpu 2 vreg1 = fpu 1 vreg1;
	fpu 3 vreg0 = fpu 2 vreg0;
	fpu 3 vreg1 = fpu 2 vreg1;
	gr1 >>= 1; // 16
	ar3 = ar0;
	ar4 = ar6;
<COMP_FFT128_16>
	ar1 = gr4; // W1024
	COMPUTE_FFT128_2048(0);
	COMPUTE_FFT128_2048(1);
	FFT128xW256(1);
	COMPUTE_FFT128_2048(2);
	COMPUTE_FFT128_2048(3);
	ar1 = gr4; // W1024
	FFT128xW256(3);

	SAVE_FFT128_2048(0, ar3);
	SAVE_FFT128_2048(1, ar4);
	SAVE_FFT128_2048(2, ar3);
	SAVE_FFT128_2048(3, ar4);
	fpu 1 vreg0 = fpu 0 vreg0;
	fpu 1 vreg1 = fpu 0 vreg1;
	gr0--;
	if > delayed goto COMP_FFT128_16;
	fpu 3 vreg0 = fpu 0 vreg0;
	fpu 3 vreg1 = fpu 0 vreg1;
// END FTT 128


// COMPUTE 8 OF FFT256
	gr1 >>= 1; // 8
	ar0 = gr2; // buff_fft2048
	ar6 = gr7; // buff_fft2048xW
	gr0 = gr1 >> 1; // 4
	ar3 = ar0;
	ar4 = ar6;
<COMP_FFT256_8>
	ar1 = gr4; // W1024
	COMPUTE_FFT256_512_1024(0);
	COMPUTE_FFT256_512_1024(1);
	COMPUTE_FFT256_512_1024(2);
	COMPUTE_FFT256_512_1024(3);

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
	gr0--;
	if > goto COMP_FFT256_8;
// END FFT256

// COMPUTE 4 OF FFT512
	//ar5 = ar5 - 13;
	gr1 >>= 1; // 4
	ar0 = gr2; // buff_fft2048
	ar6 = gr7; // buff_fft2048xW
	ar3 = [ar5++]; // buff2048_0
	gr3 = ar3;
	gr0 = gr1 >> 1;
	ar4 = ar6;
<COMP_FFT512_4>
	ar1 = gr4; // W1024
	COMPUTE_FFT256_512_1024(0);
	COMPUTE_FFT256_512_1024(1);
	COMPUTE_FFT256_512_1024(2);
	COMPUTE_FFT256_512_1024(3);

	INMEM2048(ar3, vreg4, vreg5);
	INMEM2048(ar3, vreg6, vreg7);

	COMPUTE_FFT256_512_1024(0);
	COMPUTE_FFT256_512_1024(1);
	COMPUTE_FFT256_512_1024(2);
	COMPUTE_FFT256_512_1024(3);

	fpu 0 rep 32 vreg0 = [ar1++gr1];
	fpu 0 rep 32 vreg1 = [ar1++gr1];
	fpu 1 rep 32 vreg0 = [ar1++gr1];
	fpu 1 rep 32 vreg1 = [ar1++gr1];
	fpu 2 rep 32 vreg0 = [ar1++gr1];
	fpu 2 rep 32 vreg1 = [ar1++gr1];
	fpu 3 rep 32 vreg0 = [ar1++gr1];
	fpu 3 rep 32 vreg1 = [ar1++gr1];

	fpu 0 rep 32 vreg2 = [ar1++gr1];
	fpu 0 rep 32 vreg3 = [ar1++gr1];
	fpu 1 rep 32 vreg2 = [ar1++gr1];
	fpu 1 rep 32 vreg3 = [ar1++gr1];
	fpu 2 rep 32 vreg2 = [ar1++gr1];
	fpu 2 rep 32 vreg3 = [ar1++gr1];
	fpu 3 rep 32 vreg2 = [ar1++gr1];
	fpu 3 rep 32 vreg3 = [ar1++gr1];
	ar3 = gr2;
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

	INMEM2048(ar4, vreg4, vreg5);
	INMEM2048(ar4, vreg6, vreg7);
	gr0--;
	if > goto COMP_FFT512_4;
// END FFT512

// COMPUTE 2 OF FFT1024
	ar0 = gr3; // buff2048_0
	ar6 = gr7; // buff_fft2048xW
	ar4 = ar0;
	ar3 = [ar5++]; // buff2048_1
	gr0 = ar3;
	ar1 = gr4; // W1024
	COMPUTE_FFT256_512_1024(0);
	COMPUTE_FFT256_512_1024(1);
	COMPUTE_FFT256_512_1024(2);
	COMPUTE_FFT256_512_1024(3);

	INMEM2048(ar3, vreg4, vreg5);

	INMEM2048(ar4, vreg6, vreg7);

	COMPUTE_FFT256_512_1024(0);
	COMPUTE_FFT256_512_1024(1);
	COMPUTE_FFT256_512_1024(2);
	COMPUTE_FFT256_512_1024(3);

	INMEM2048(ar4, vreg6, vreg7);

	INMEM2048(ar3, vreg4, vreg5);

	ar0 = gr2; // buff_fft2048
	ar3 = ar0;
	ar4 = ar6 - 1024;

	COMPUTE_FFT256_512_1024(0);
	COMPUTE_FFT256_512_1024(1);
	COMPUTE_FFT256_512_1024(2);
	COMPUTE_FFT256_512_1024(3);

	fpu 0 rep 32 vreg0 = [ar1++];
	fpu 0 rep 32 vreg1 = [ar1++];
	fpu 1 rep 32 vreg0 = [ar1++];
	fpu 1 rep 32 vreg1 = [ar1++];
	fpu 2 rep 32 vreg0 = [ar1++];
	fpu 2 rep 32 vreg1 = [ar1++];
	fpu 3 rep 32 vreg0 = [ar1++];
	fpu 3 rep 32 vreg1 = [ar1++];
	fpu 0 .complex vreg4 = vreg4 * vreg0;
	fpu 0 .complex vreg5 = vreg5 * vreg1;
	fpu 1 .complex vreg4 = vreg4 * vreg0;
	fpu 1 .complex vreg5 = vreg5 * vreg1;
	fpu 2 .complex vreg4 = vreg4 * vreg0;
	fpu 2 .complex vreg5 = vreg5 * vreg1;
	fpu 3 .complex vreg4 = vreg4 * vreg0;
	fpu 3 .complex vreg5 = vreg5 * vreg1;

	ar1 = ar1 + 512; 
	fpu 0 rep 32 vreg2 = [ar1++];
	fpu 0 rep 32 vreg3 = [ar1++];
	fpu 1 rep 32 vreg2 = [ar1++];
	fpu 1 rep 32 vreg3 = [ar1++];
	fpu 2 rep 32 vreg2 = [ar1++];
	fpu 2 rep 32 vreg3 = [ar1++];
	fpu 3 rep 32 vreg2 = [ar1++];
	fpu 3 rep 32 vreg3 = [ar1++];
	fpu 0 .complex vreg6 = vreg6 * vreg2;
	fpu 0 .complex vreg7 = vreg7 * vreg3;
	fpu 1 .complex vreg6 = vreg6 * vreg2;
	fpu 1 .complex vreg7 = vreg7 * vreg3;
	fpu 2 .complex vreg6 = vreg6 * vreg2;
	fpu 2 .complex vreg7 = vreg7 * vreg3;
	fpu 3 .complex vreg6 = vreg6 * vreg2;
	fpu 3 .complex vreg7 = vreg7 * vreg3;

	ar2 = gr6; // output X
	INMEM2048(ar4, vreg4, vreg5);

	INMEM2048(ar3, vreg6, vreg7);

	COMPUTE_FFT256_512_1024(0);
	COMPUTE_FFT256_512_1024(1);
	COMPUTE_FFT256_512_1024(2);
	COMPUTE_FFT256_512_1024(3);

	fpu 0 rep 32 vreg2 = [ar1++];
	fpu 0 rep 32 vreg3 = [ar1++];
	fpu 1 rep 32 vreg2 = [ar1++];
	fpu 1 rep 32 vreg3 = [ar1++];
	fpu 2 rep 32 vreg2 = [ar1++];
	fpu 2 rep 32 vreg3 = [ar1++];
	fpu 3 rep 32 vreg2 = [ar1++];
	fpu 3 rep 32 vreg3 = [ar1++];
	fpu 0 .complex vreg6 = vreg6 * vreg2;
	fpu 0 .complex vreg7 = vreg7 * vreg3;
	fpu 1 .complex vreg6 = vreg6 * vreg2;
	fpu 1 .complex vreg7 = vreg7 * vreg3;
	fpu 2 .complex vreg6 = vreg6 * vreg2;
	fpu 2 .complex vreg7 = vreg7 * vreg3;
	fpu 3 .complex vreg6 = vreg6 * vreg2;
	fpu 3 .complex vreg7 = vreg7 * vreg3;

	ar1 = ar1 - 1536;
	fpu 0 rep 32 vreg0 = [ar1++];
	fpu 0 rep 32 vreg1 = [ar1++];
	fpu 1 rep 32 vreg0 = [ar1++];
	fpu 1 rep 32 vreg1 = [ar1++];
	fpu 2 rep 32 vreg0 = [ar1++];
	fpu 2 rep 32 vreg1 = [ar1++];
	fpu 3 rep 32 vreg0 = [ar1++];
	fpu 3 rep 32 vreg1 = [ar1++];
	fpu 0 .complex vreg4 = vreg4 * vreg0;
	fpu 0 .complex vreg5 = vreg5 * vreg1;
	fpu 1 .complex vreg4 = vreg4 * vreg0;
	fpu 1 .complex vreg5 = vreg5 * vreg1;
	fpu 2 .complex vreg4 = vreg4 * vreg0;
	fpu 2 .complex vreg5 = vreg5 * vreg1;
	fpu 3 .complex vreg4 = vreg4 * vreg0;
	fpu 3 .complex vreg5 = vreg5 * vreg1;

	INMEM2048(ar4, vreg4, vreg5);

	INMEM2048(ar3, vreg6, vreg7);
// END FFT1024

// COMPUTE 1 FFT2048
	ar0 = gr0; // buff2048_1
	ar6 = gr7; // buff_fft2048xW

	COMPUTE_FFT256_512_1024(0);
	COMPUTE_FFT256_512_1024(1);
	COMPUTE_FFT256_512_1024(2);
	COMPUTE_FFT256_512_1024(3);

	INMEM2048(ar2, vreg4, vreg5);
	ar2 = ar2 + 1536;
	INMEM2048(ar2, vreg6, vreg7);

	COMPUTE_FFT256_512_1024(0);
	COMPUTE_FFT256_512_1024(1);
	COMPUTE_FFT256_512_1024(2);
	COMPUTE_FFT256_512_1024(3);

	INMEM2048(ar2, vreg6, vreg7);

	ar2 = ar2 - 2560;

	INMEM2048(ar2, vreg4, vreg5);

	ar0 = gr3; // buff2048_0
	ar6 = gr2; // buff_fft2048

	COMPUTE_FFT256_512_1024(0);
	COMPUTE_FFT256_512_1024(1);
	COMPUTE_FFT256_512_1024(2);
	COMPUTE_FFT256_512_1024(3);

	INMEM2048(ar2, vreg4, vreg5);

	ar2 = ar2 + 1536;

	INMEM2048(ar2, vreg6, vreg7);

	COMPUTE_FFT256_512_1024(0);
	COMPUTE_FFT256_512_1024(1);
	COMPUTE_FFT256_512_1024(2);
	COMPUTE_FFT256_512_1024(3);

	INMEM2048(ar2, vreg6, vreg7);

	ar2 = ar2 - 2560;

	INMEM2048(ar2, vreg4, vreg5);
	
// END FFT2048
<exit_fft2048>
	pop ar0, gr0;
	pop ar1, gr1;
	pop ar2, gr2;
	pop ar3, gr3;
	pop ar4, gr4;
	pop ar6, gr6;
	return;
end ".text";