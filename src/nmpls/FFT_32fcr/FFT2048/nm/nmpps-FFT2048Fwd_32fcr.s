//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software                      */
//*                                                                         */
//*   Software design:  A.Brodyazhenko                                      */
//*                                                                         */
//*   File:             nmpps-FFT2048Fwd_32fcr.s                            */
//*   Contents:         Routine for forward (inverse) FFT 2048              */
//*                     of complex array with 32 bit elements               */
//***************************************************************************/

global _nmppsFFT2048Fwd_32fcr: label;
global _nmppsFFT2048Inv_32fcr: label;

extern _FFTFwd16x32Core: label;

data ".data_imu1"
.align;
AddrFor128xFFT16: word[128] = (
	0, 128, 64, 192, 32, 160, 96, 224, 16, 144, 80, 208, 48, 176, 112, 240, 8, 136, 72, 200, 40, 168, 104, 232, 24, 152, 88, 216, 56, 184, 120, 248, 
	4, 132, 68, 196, 36, 164, 100, 228, 20, 148, 84, 212, 52, 180, 116, 244, 12, 140, 76, 204, 44, 172, 108, 236, 28, 156, 92, 220, 60, 188, 124, 252,
	2, 130, 66, 194, 34, 162, 98, 226, 18, 146, 82, 210, 50, 178, 114, 242, 10, 138, 74, 202, 42, 170, 106, 234, 26, 154, 90, 218, 58, 186, 122, 250,
	6, 134, 70, 198, 38, 166, 102, 230, 22, 150, 86, 214, 54, 182, 118, 246, 14, 142, 78, 206, 46, 174, 110, 238, 30, 158, 94, 222, 62, 190, 126, 254);
end ".data_imu1";

begin ".data_2048"
<_nmppsFFT2048Fwd_32fcr>
<_nmppsFFT2048Inv_32fcr>
	ar5 = ar7 - 2;
	push ar6, gr6;
	push ar5, gr5;
	push ar4, gr4;
	push ar3, gr3;
	push ar2, gr2;
	push ar1, gr1;
	push ar0, gr0;
	ar3 = [--ar5];				// input x
	gr7 = [--ar5];				// output X
	ar5 = [--ar5];				// NmppsFFTSpec_32fcr struct
	gr1 = 256;
	vlen = 31;
	gr0 = gr1 >> 2;				// cycles number

// SORT 128 VECTORS FOR FFT16
	ar4 = AddrFor128xFFT16;
	ar2 = [ar5++];				// 1.0 or 1/2048
	ar0 = [ar5++]; 				// buff_fft2048
	ar6 = [ar5++]; 				// buff_fft2048xW
	fpu 0 rep 1 vreg1 = [ar2]; 	// 1.0 or 1/2048
	fpu 1 vreg1 = fpu 0 vreg1;

	gr4 = ar0;					// saving buff_fft2048 address
	gr5 = ar6;					// saving buff_fft2048xW address
	
<SORT_128_FFT16>
	gr3 = [ar4++];
	ar1 = ar3 + gr3;
	fpu 0 rep 16 vreg0 = [ar1++gr1];
	fpu 0 .complex vreg2 = vreg0 * .retrive(vreg1);
	gr3 = [ar4++];
	ar1 = ar3 + gr3;
	fpu 1 rep 16 vreg0 = [ar1++gr1];
	fpu 1 .complex vreg2 = vreg0 * .retrive(vreg1);

	fpu 0 rep 16 [ar0++] = vreg2;
	fpu 1 rep 16 [ar6++] = vreg2;
	gr0--;
	if > goto SORT_128_FFT16;
// END SORT

// COMPUTE 128 PART OF FFT16
	delayed call _FFTFwd16x32Core;
		ar3 = gr4 with gr1 >>= 3;	// step for FFT16 = 32 for input // addr for input buff_fft1024
		gr6 = ar3;					// addr for output buff_fft1024
	
	ar3 = gr4;
	ar3 += 1024;
	gr6 = ar3;
	delayed call _FFTFwd16x32Core;
		ar5 -= 7;
	
	ar3 = gr5;
	gr6 = ar3;
	delayed call _FFTFwd16x32Core;
		ar5 -= 7;

	ar3 = gr5;
	ar3 += 1024;
	gr6 = ar3;
	delayed call _FFTFwd16x32Core;
		ar5 -= 7;
// END FFT16

// COMPUTE 64 OF FFT32
	ar0 = gr4;
	ar6 = gr5 with gr1 <<= 2; 		// 128
	ar1 = [ar5++];					// W2048
	gr2 = ar1 with gr0 = gr1 >> 3; 	// 16 saving W2048 address
	fpu 0 rep 16 vreg0 = [ar1++gr1];
	fpu 1 vreg0 = fpu 0 vreg0;
	fpu 2 vreg0 = fpu 1 vreg0;
	fpu 3 vreg0 = fpu 2 vreg0;
	ar3 = gr7;
	ar4 = [ar5++]; 		// buff_additional (buff_fft2048mulW)
	gr6 = ar4;	   		// saving buff_additional address

<COMP_FFT32_2048>
	fpu 0 rep 16 vreg1 = [ar0++];
	fpu 0 rep 16 vreg2 = [ar6++]; // need mul W
	fpu 0 .complex vreg5 = vreg0 * vreg2 + vreg1; // 1 part of FFT32
	fpu 0 .complex vreg6 = -vreg0 * vreg2 + vreg1; // 2 part of FFT32

	fpu 1 rep 16 vreg1 = [ar0++];
	fpu 1 rep 16 vreg2 = [ar6++]; // need mul W
	fpu 1 .complex vreg5 = vreg0 * vreg2 + vreg1; // 1 part of FFT32
	fpu 1 .complex vreg6 = -vreg0 * vreg2 + vreg1; // 2 part of FFT32

	fpu 2 rep 16 vreg1 = [ar0++];
	fpu 2 rep 16 vreg2 = [ar6++]; // need mul W
	fpu 2 .complex vreg5 = vreg0 * vreg2 + vreg1; // 1 part of FFT32
	fpu 2 .complex vreg6 = -vreg0 * vreg2 + vreg1; // 2 part of FFT32

	fpu 3 rep 16 vreg1 = [ar0++];
	fpu 3 rep 16 vreg2 = [ar6++]; // need mul W
	fpu 3 .complex vreg5 = vreg0 * vreg2 + vreg1; // 1 part of FFT32
	fpu 3 .complex vreg6 = -vreg0 * vreg2 + vreg1; // 2 part of FFT32

	fpu 0 rep 16 [ar3++] = vreg5;
	fpu 1 rep 16 [ar4++] = vreg5;

	fpu 0 rep 16 [ar3++] = vreg6;
	fpu 1 rep 16 [ar4++] = vreg6;

	fpu 2 rep 16 [ar3++] = vreg5;
	fpu 3 rep 16 [ar4++] = vreg5;

	fpu 2 rep 16 [ar3++] = vreg6;
	fpu 3 rep 16 [ar4++] = vreg6;
	gr0--;
	if > goto COMP_FFT32_2048;
// END FFT32

// COMPUTE 32 OF FFT64
	ar0 = gr7;
	ar6 = gr6 with gr1 >>= 1; 			// 64
	ar1 = gr2 with gr0 = gr1 >> 3; 	// 8
	fpu 0 rep 32 vreg0 = [ar1++gr1]; 	// W32
	fpu 1 vreg0 = fpu 0 vreg0;
	fpu 2 vreg0 = fpu 1 vreg0;
	fpu 3 vreg0 = fpu 2 vreg0;
	ar3 = gr4;
	ar4 = gr5;
<COMP_FFT64_2048>
	fpu 0 rep 32 vreg1 = [ar0++];
	fpu 0 rep 32 vreg2 = [ar6++]; // need mul W
	fpu 0 .complex vreg5 = vreg0 * vreg2 + vreg1; // 1 part of FFT64
	fpu 0 .complex vreg6 = -vreg0 * vreg2 + vreg1; // 2 part of FFT64

	fpu 1 rep 32 vreg1 = [ar0++];
	fpu 1 rep 32 vreg2 = [ar6++]; // need mul W
	fpu 1 .complex vreg5 = vreg0 * vreg2 + vreg1; // 1 part of FFT64
	fpu 1 .complex vreg6 = -vreg0 * vreg2 + vreg1; // 2 part of FFT64

	fpu 2 rep 32 vreg1 = [ar0++];
	fpu 2 rep 32 vreg2 = [ar6++]; // need mul W
	fpu 2 .complex vreg5 = vreg0 * vreg2 + vreg1; // 1 part of FFT64
	fpu 2 .complex vreg6 = -vreg0 * vreg2 + vreg1; // 2 part of FFT64

	fpu 3 rep 32 vreg1 = [ar0++];
	fpu 3 rep 32 vreg2 = [ar6++]; // need mul W
	fpu 3 .complex vreg5 = vreg0 * vreg2 + vreg1; // 1 part of FFT64
	fpu 3 .complex vreg6 = -vreg0 * vreg2 + vreg1; // 2 part of FFT64

	fpu 0 rep 32 [ar3++] = vreg5;
	fpu 1 rep 32 [ar4++] = vreg5;

	fpu 0 rep 32 [ar3++] = vreg6;
	fpu 1 rep 32 [ar4++] = vreg6;

	fpu 2 rep 32 [ar3++] = vreg5;
	fpu 3 rep 32 [ar4++] = vreg5;

	fpu 2 rep 32 [ar3++] = vreg6;
	fpu 3 rep 32 [ar4++] = vreg6;
	gr0--;
	if > goto COMP_FFT64_2048;
// END FFT64

// COMPUTE 16 OF FFT128
	ar0 = gr4;
	ar6 = gr5 with gr1 >>= 1; 			// 32
	ar1 = gr2 with gr3 = gr1 >> 2; 		// 8
	ar3 = gr7;
	ar4 = gr6;
	fpu 0 rep 32 vreg0 = [ar1++gr1]; // 1 - W64
	fpu 1 rep 32 vreg0 = [ar1++gr1]; // 2 - W64
	fpu 2 vreg0 = fpu 0 vreg0;
	fpu 3 vreg0 = fpu 1 vreg0;

<COMP_FFT128_2048>
	fpu 0 rep 32 vreg2 = [ar0++];
	fpu 0 rep 32 vreg3 = [ar6++]; // need mul W128
	fpu 0 .complex vreg6 = vreg0 * vreg3 + vreg2;

	fpu 1 rep 32 vreg2 = [ar0++];
	fpu 1 rep 32 vreg3 = [ar6++]; // need mul W128
	fpu 1 .complex vreg6 = vreg0 * vreg3 + vreg2;

	fpu 2 rep 32 vreg2 = [ar0++];
	fpu 2 rep 32 vreg3 = [ar6++]; // need mul W128
	fpu 2 .complex vreg6 = vreg0 * vreg3 + vreg2;

	fpu 3 rep 32 vreg2 = [ar0++];
	fpu 3 rep 32 vreg3 = [ar6++]; // need mul W128
	fpu 3 .complex vreg6 = vreg0 * vreg3 + vreg2;
	
	fpu 0 rep 32 [ar3++] = vreg6;
	fpu 2 rep 32 [ar4++] = vreg6;

	fpu 1 rep 32 [ar3++] = vreg6;
	fpu 3 rep 32 [ar4++] = vreg6;

	fpu 0 .complex vreg7 = -vreg0 * vreg3 + vreg2;
	fpu 1 .complex vreg7 = -vreg0 * vreg3 + vreg2;
	fpu 2 .complex vreg7 = -vreg0 * vreg3 + vreg2;
	fpu 3 .complex vreg7 = -vreg0 * vreg3 + vreg2;
	
	fpu 0 rep 32 [ar3++] = vreg7;
	fpu 2 rep 32 [ar4++] = vreg7;

	fpu 1 rep 32 [ar3++] = vreg7;
	fpu 3 rep 32 [ar4++] = vreg7;
	gr3--;
	if > goto COMP_FFT128_2048;
// END FTT 128

// COMPUTE 8 OF FFT256
	ar0 = gr7 with gr1 >>= 1; 				// 16
	ar6 = gr6 with gr0 = gr1 >> 2; 			// 4
	ar1 = gr2;
	ar3 = gr4;
	ar4 = gr5;

	ar2 = ar0 + 256;
	ar5 = ar6 + 256;

	fpu 0 rep 32 vreg0 = [ar1++gr1]; // 1 - W128
	fpu 1 rep 32 vreg0 = [ar1++gr1]; // 2 - W128
	fpu 2 vreg1 = fpu 0 vreg0;
	fpu 3 vreg1 = fpu 1 vreg0;

	fpu 0 rep 32 vreg1 = [ar1++gr1]; // 3 - W128
	fpu 1 rep 32 vreg1 = [ar1++gr1]; // 4 - W128
	fpu 2 vreg0 = fpu 0 vreg1;
	fpu 3 vreg0 = fpu 1 vreg1;
	
<COMP_FFT256_2048>
	fpu 0 rep 32 vreg2 = [ar0++];
	fpu 0 rep 32 vreg3 = [ar6++]; // need mul W128
	fpu 0 .complex vreg6 = vreg0 * vreg3 + vreg2;

	fpu 1 rep 32 vreg2 = [ar0++];
	fpu 1 rep 32 vreg3 = [ar6++]; // need mul W128
	fpu 1 .complex vreg6 = vreg0 * vreg3 + vreg2;

	fpu 2 rep 32 vreg2 = [ar2++];
	fpu 2 rep 32 vreg3 = [ar5++]; // need mul W128
	fpu 2 .complex vreg6 = vreg1 * vreg3 + vreg2;

	fpu 3 rep 32 vreg2 = [ar2++];
	fpu 3 rep 32 vreg3 = [ar5++]; // need mul W128
	fpu 3 .complex vreg6 = vreg1 * vreg3 + vreg2;
	
	fpu 0 rep 32 [ar3++] = vreg6;
	fpu 2 rep 32 [ar4++] = vreg6;
	fpu 1 rep 32 [ar3++] = vreg6;
	fpu 3 rep 32 [ar4++] = vreg6;

	fpu 0 .complex vreg7 = -vreg0 * vreg3 + vreg2;
	fpu 1 .complex vreg7 = -vreg0 * vreg3 + vreg2;
	fpu 2 .complex vreg7 = -vreg1 * vreg3 + vreg2;
	fpu 3 .complex vreg7 = -vreg1 * vreg3 + vreg2;
	
	fpu 0 rep 32 vreg2 = [ar0++];
	fpu 0 rep 32 vreg3 = [ar6++]; // need mul W128
	fpu 0 .complex vreg6 = vreg1 * vreg3 + vreg2;

	fpu 1 rep 32 vreg2 = [ar0++];
	fpu 1 rep 32 vreg3 = [ar6++]; // need mul W128
	fpu 1 .complex vreg6 = vreg1 * vreg3 + vreg2;

	fpu 2 rep 32 vreg2 = [ar2++];
	fpu 2 rep 32 vreg3 = [ar5++]; // need mul W128
	fpu 2 .complex vreg6 = vreg0 * vreg3 + vreg2;

	fpu 3 rep 32 vreg2 = [ar2++];
	fpu 3 rep 32 vreg3 = [ar5++]; // need mul W128
	fpu 3 .complex vreg6 = vreg0 * vreg3 + vreg2;
	
	fpu 0 rep 32 [ar3++] = vreg6;
	fpu 2 rep 32 [ar4++] = vreg6;
	fpu 1 rep 32 [ar3++] = vreg6;
	fpu 3 rep 32 [ar4++] = vreg6;

	ar0 = ar2;
	ar6 = ar5;

	fpu 0 .complex vreg5 = -vreg1 * vreg3 + vreg2;
	fpu 1 .complex vreg5 = -vreg1 * vreg3 + vreg2;
	fpu 2 .complex vreg5 = -vreg0 * vreg3 + vreg2;
	fpu 3 .complex vreg5 = -vreg0 * vreg3 + vreg2;
	
	fpu 0 rep 32 [ar3++] = vreg7;
	fpu 2 rep 32 [ar4++] = vreg7;
	fpu 1 rep 32 [ar3++] = vreg7;
	fpu 3 rep 32 [ar4++] = vreg7;

	fpu 0 rep 32 [ar3++] = vreg5;
	fpu 2 rep 32 [ar4++] = vreg5;
	fpu 1 rep 32 [ar3++] = vreg5;
	fpu 3 rep 32 [ar4++] = vreg5;

	ar2 += 256;
	gr0--;
	if > delayed goto COMP_FFT256_2048;
		ar5 += 256;
// END FFT256

// COMPUTE 4 OF FFT512
	ar0 = gr4 with gr1 >>= 1; 			// 8
	ar6 = gr5 with gr0 = gr1 >> 2; 		// 2
	ar3 = gr7;
	ar4 = gr6;
	
	ar2 = ar0 + 512;
	ar5 = ar6 + 512;

<COMP_FFT512_2048>
	ar1 = gr2;
	fpu 0 rep 32 vreg0 = [ar1++gr1]; // 1 - W128
	fpu 1 rep 32 vreg0 = [ar1++gr1]; // 2 - W128
	fpu 2 vreg1 = fpu 0 vreg0;
	fpu 3 vreg1 = fpu 1 vreg0;

	fpu 0 rep 32 vreg2 = [ar0++];
	fpu 0 rep 32 vreg3 = [ar6++]; // need mul W128
	fpu 0 .complex vreg6 = vreg0 * vreg3 + vreg2;

	fpu 1 rep 32 vreg2 = [ar0++];
	fpu 1 rep 32 vreg3 = [ar6++]; // need mul W128
	fpu 1 .complex vreg6 = vreg0 * vreg3 + vreg2;

	fpu 2 rep 32 vreg2 = [ar2++];
	fpu 2 rep 32 vreg3 = [ar5++]; // need mul W128
	fpu 2 .complex vreg6 = vreg1 * vreg3 + vreg2;

	fpu 3 rep 32 vreg2 = [ar2++];
	fpu 3 rep 32 vreg3 = [ar5++]; // need mul W128
	fpu 3 .complex vreg6 = vreg1 * vreg3 + vreg2;

	fpu 0 rep 32 [ar3++] = vreg6;
	fpu 2 rep 32 [ar4++] = vreg6;
	fpu 1 rep 32 [ar3++] = vreg6;
	fpu 3 rep 32 [ar4++] = vreg6;

	fpu 0 rep 32 vreg1 = [ar1++gr1]; // 3 - W128
	fpu 1 rep 32 vreg1 = [ar1++gr1]; // 4 - W128
	fpu 2 vreg0 = fpu 0 vreg1;
	fpu 3 vreg0 = fpu 1 vreg1;

	fpu 0 .complex vreg7 = -vreg0 * vreg3 + vreg2;
	fpu 1 .complex vreg7 = -vreg0 * vreg3 + vreg2;
	fpu 2 .complex vreg7 = -vreg1 * vreg3 + vreg2;
	fpu 3 .complex vreg7 = -vreg1 * vreg3 + vreg2;

	fpu 0 rep 32 vreg2 = [ar0++];
	fpu 0 rep 32 vreg3 = [ar6++]; // need mul W128
	fpu 0 .complex vreg6 = vreg1 * vreg3 + vreg2;

	fpu 1 rep 32 vreg2 = [ar0++];
	fpu 1 rep 32 vreg3 = [ar6++]; // need mul W128
	fpu 1 .complex vreg6 = vreg1 * vreg3 + vreg2;

	fpu 2 rep 32 vreg2 = [ar2++];
	fpu 2 rep 32 vreg3 = [ar5++]; // need mul W128
	fpu 2 .complex vreg6 = vreg0 * vreg3 + vreg2;

	fpu 3 rep 32 vreg2 = [ar2++];
	fpu 3 rep 32 vreg3 = [ar5++]; // need mul W128
	fpu 3 .complex vreg6 = vreg0 * vreg3 + vreg2;

	fpu 0 rep 32 [ar3++] = vreg6;
	fpu 2 rep 32 [ar4++] = vreg6;
	fpu 1 rep 32 [ar3++] = vreg6;
	fpu 3 rep 32 [ar4++] = vreg6;

	fpu 0 rep 32 vreg4 = [ar1++gr1]; // 3 - W128
	fpu 1 rep 32 vreg4 = [ar1++gr1]; // 4 - W128
	fpu 2 vreg5 = fpu 0 vreg4;
	fpu 3 vreg5 = fpu 1 vreg4;

	fpu 0 .complex vreg5 = -vreg1 * vreg3 + vreg2;
	fpu 1 .complex vreg5 = -vreg1 * vreg3 + vreg2;
	fpu 2 .complex vreg4 = -vreg0 * vreg3 + vreg2;
	fpu 3 .complex vreg4 = -vreg0 * vreg3 + vreg2;

	fpu 0 rep 32 vreg2 = [ar0++];
	fpu 0 rep 32 vreg3 = [ar6++]; // need mul W128
	fpu 0 .complex vreg6 = vreg4 * vreg3 + vreg2;

	fpu 1 rep 32 vreg2 = [ar0++];
	fpu 1 rep 32 vreg3 = [ar6++]; // need mul W128
	fpu 1 .complex vreg6 = vreg4 * vreg3 + vreg2;

	fpu 2 rep 32 vreg2 = [ar2++];
	fpu 2 rep 32 vreg3 = [ar5++]; // need mul W128
	fpu 2 .complex vreg6 = vreg5 * vreg3 + vreg2;

	fpu 3 rep 32 vreg2 = [ar2++];
	fpu 3 rep 32 vreg3 = [ar5++]; // need mul W128
	fpu 3 .complex vreg6 = vreg5 * vreg3 + vreg2;

	fpu 0 rep 32 [ar3++] = vreg6;
	fpu 2 rep 32 [ar4++] = vreg6;
	fpu 1 rep 32 [ar3++] = vreg6;
	fpu 3 rep 32 [ar4++] = vreg6;

	fpu 0 .complex vreg0 = -vreg4 * vreg3 + vreg2;
	fpu 1 .complex vreg0 = -vreg4 * vreg3 + vreg2;
	fpu 2 .complex vreg0 = -vreg5 * vreg3 + vreg2;
	fpu 3 .complex vreg0 = -vreg5 * vreg3 + vreg2;

	fpu 0 rep 32 vreg1 = [ar1++gr1]; // 1 - W128
	fpu 1 rep 32 vreg1 = [ar1++gr1]; // 2 - W128
	fpu 2 vreg5 = fpu 0 vreg1;
	fpu 3 vreg5 = fpu 1 vreg1;

	fpu 0 rep 32 vreg2 = [ar0++];
	fpu 0 rep 32 vreg3 = [ar6++]; // need mul W128
	fpu 0 .complex vreg6 = vreg1 * vreg3 + vreg2;

	fpu 1 rep 32 vreg2 = [ar0++];
	fpu 1 rep 32 vreg3 = [ar6++]; // need mul W128
	fpu 1 .complex vreg6 = vreg1 * vreg3 + vreg2;

	fpu 2 rep 32 vreg2 = [ar2++];
	fpu 2 rep 32 vreg3 = [ar5++]; // need mul W128
	fpu 2 .complex vreg6 = vreg5 * vreg3 + vreg2;

	fpu 3 rep 32 vreg2 = [ar2++];
	fpu 3 rep 32 vreg3 = [ar5++]; // need mul W128
	fpu 3 .complex vreg6 = vreg5 * vreg3 + vreg2;

	fpu 0 rep 32 [ar3++] = vreg6;
	fpu 2 rep 32 [ar4++] = vreg6;
	fpu 1 rep 32 [ar3++] = vreg6;
	fpu 3 rep 32 [ar4++] = vreg6;

	fpu 0 .complex vreg1 = -vreg1 * vreg3 + vreg2;
	fpu 1 .complex vreg1 = -vreg1 * vreg3 + vreg2;
	fpu 2 .complex vreg1 = -vreg5 * vreg3 + vreg2;
	fpu 3 .complex vreg1 = -vreg5 * vreg3 + vreg2;

	fpu 0 rep 32 [ar3++] = vreg7;
	fpu 2 rep 32 [ar4++] = vreg7;
	fpu 1 rep 32 [ar3++] = vreg7;
	fpu 3 rep 32 [ar4++] = vreg7;

	fpu 0 rep 32 [ar3++] = vreg5;
	fpu 2 rep 32 [ar4++] = vreg4;
	fpu 1 rep 32 [ar3++] = vreg5;
	fpu 3 rep 32 [ar4++] = vreg4;
	
	ar0 = ar2;
	ar6 = ar5;

	fpu 0 rep 32 [ar3++] = vreg0;
	fpu 2 rep 32 [ar4++] = vreg0;
	fpu 1 rep 32 [ar3++] = vreg0;
	fpu 3 rep 32 [ar4++] = vreg0;

	fpu 0 rep 32 [ar3++] = vreg1;
	fpu 2 rep 32 [ar4++] = vreg1;
	fpu 1 rep 32 [ar3++] = vreg1;
	fpu 3 rep 32 [ar4++] = vreg1;

	ar2 += 512;
	gr0--;
	if > delayed goto COMP_FFT512_2048;
		ar5 += 512;
// END FFT512

// COMPUTE 2 OF FFT1024
	ar1 = gr2;
	ar0 = gr7 with gr1 >>= 1;			// 4
	ar6 = gr6;
	ar3 = gr4 with gr0 = gr1 >> 1;		// 2
	ar4 = gr5;
	ar2 = ar3 + 1024;
	ar5 = ar4 + 1024;

	fpu 0 rep 32 vreg0 = [ar1++gr1]; // 1 - W128
	fpu 1 rep 32 vreg0 = [ar1++gr1]; // 2 - W128
	fpu 2 rep 32 vreg0 = [ar1++gr1]; // 3 - W128
	fpu 3 rep 32 vreg0 = [ar1++gr1]; // 4 - W128

	fpu 0 rep 32 vreg1 = [ar1++gr1]; // 1 - W128
	fpu 1 rep 32 vreg1 = [ar1++gr1]; // 2 - W128
	fpu 2 rep 32 vreg1 = [ar1++gr1]; // 3 - W128
	fpu 3 rep 32 vreg1 = [ar1++gr1]; // 4 - W128

	fpu 0 rep 32 vreg2 = [ar1++gr1]; // 1 - W128
	fpu 1 rep 32 vreg2 = [ar1++gr1]; // 2 - W128
	fpu 2 rep 32 vreg2 = [ar1++gr1]; // 3 - W128
	fpu 3 rep 32 vreg2 = [ar1++gr1]; // 4 - W128

	fpu 0 rep 32 vreg3 = [ar1++gr1]; // 1 - W128
	fpu 1 rep 32 vreg3 = [ar1++gr1]; // 2 - W128
	fpu 2 rep 32 vreg3 = [ar1++gr1]; // 3 - W128
	fpu 3 rep 32 vreg3 = [ar1++gr1]; // 4 - W128

<COMP_FFT1024_2048>
	fpu 0 rep 32 vreg4 = [ar0++];
	fpu 0 rep 32 vreg5 = [ar6++]; // need mul W128
	fpu 0 .complex vreg6 = vreg0 * vreg5 + vreg4;

	fpu 1 rep 32 vreg4 = [ar0++];
	fpu 1 rep 32 vreg5 = [ar6++]; // need mul W128
	fpu 1 .complex vreg6 = vreg0 * vreg5 + vreg4;

	fpu 2 rep 32 vreg4 = [ar0++];
	fpu 2 rep 32 vreg5 = [ar6++]; // need mul W128
	fpu 2 .complex vreg6 = vreg0 * vreg5 + vreg4;

	fpu 3 rep 32 vreg4 = [ar0++];
	fpu 3 rep 32 vreg5 = [ar6++]; // need mul W128
	fpu 3 .complex vreg6 = vreg0 * vreg5 + vreg4;

	fpu 0 rep 32 [ar3++] = vreg6;
	fpu 1 rep 32 [ar3++] = vreg6;
	fpu 2 rep 32 [ar3++] = vreg6;
	fpu 3 rep 32 [ar3++] = vreg6;

	fpu 0 .complex vreg7 = -vreg0 * vreg5 + vreg4;
	fpu 1 .complex vreg7 = -vreg0 * vreg5 + vreg4;
	fpu 2 .complex vreg7 = -vreg0 * vreg5 + vreg4;
	fpu 3 .complex vreg7 = -vreg0 * vreg5 + vreg4;

	fpu 0 rep 32 vreg4 = [ar0++];
	fpu 0 rep 32 vreg5 = [ar6++]; // need mul W128
	fpu 0 .complex vreg6 = vreg1 * vreg5 + vreg4;

	fpu 1 rep 32 vreg4 = [ar0++];
	fpu 1 rep 32 vreg5 = [ar6++]; // need mul W128
	fpu 1 .complex vreg6 = vreg1 * vreg5 + vreg4;

	fpu 2 rep 32 vreg4 = [ar0++];
	fpu 2 rep 32 vreg5 = [ar6++]; // need mul W128
	fpu 2 .complex vreg6 = vreg1 * vreg5 + vreg4;

	fpu 3 rep 32 vreg4 = [ar0++];
	fpu 3 rep 32 vreg5 = [ar6++]; // need mul W128
	fpu 3 .complex vreg6 = vreg1 * vreg5 + vreg4;

	fpu 0 rep 32 [ar3++] = vreg6;
	fpu 1 rep 32 [ar3++] = vreg6;
	fpu 2 rep 32 [ar3++] = vreg6;
	fpu 3 rep 32 [ar3++] = vreg6;

	fpu 0 .complex vreg6 = -vreg1 * vreg5 + vreg4;
	fpu 1 .complex vreg6 = -vreg1 * vreg5 + vreg4;
	fpu 2 .complex vreg6 = -vreg1 * vreg5 + vreg4;
	fpu 3 .complex vreg6 = -vreg1 * vreg5 + vreg4;

	fpu 0 rep 32 [ar2++] = vreg7;
	fpu 1 rep 32 [ar2++] = vreg7;
	fpu 2 rep 32 [ar2++] = vreg7;
	fpu 3 rep 32 [ar2++] = vreg7;

	fpu 0 rep 32 vreg4 = [ar0++];
	fpu 0 rep 32 vreg5 = [ar6++]; // need mul W128
	fpu 0 .complex vreg7 = vreg2 * vreg5 + vreg4;

	fpu 1 rep 32 vreg4 = [ar0++];
	fpu 1 rep 32 vreg5 = [ar6++]; // need mul W128
	fpu 1 .complex vreg7 = vreg2 * vreg5 + vreg4;

	fpu 2 rep 32 vreg4 = [ar0++];
	fpu 2 rep 32 vreg5 = [ar6++]; // need mul W128
	fpu 2 .complex vreg7 = vreg2 * vreg5 + vreg4;

	fpu 3 rep 32 vreg4 = [ar0++];
	fpu 3 rep 32 vreg5 = [ar6++]; // need mul W128
	fpu 3 .complex vreg7 = vreg2 * vreg5 + vreg4;

	fpu 0 rep 32 [ar2++] = vreg6;
	fpu 1 rep 32 [ar2++] = vreg6;
	fpu 2 rep 32 [ar2++] = vreg6;
	fpu 3 rep 32 [ar2++] = vreg6;

	fpu 0 .complex vreg6 = -vreg2 * vreg5 + vreg4;
	fpu 1 .complex vreg6 = -vreg2 * vreg5 + vreg4;
	fpu 2 .complex vreg6 = -vreg2 * vreg5 + vreg4;
	fpu 3 .complex vreg6 = -vreg2 * vreg5 + vreg4;

	fpu 0 rep 32 [ar3++] = vreg7;
	fpu 1 rep 32 [ar3++] = vreg7;
	fpu 2 rep 32 [ar3++] = vreg7;
	fpu 3 rep 32 [ar3++] = vreg7;

	fpu 0 rep 32 vreg4 = [ar0++];
	fpu 0 rep 32 vreg5 = [ar6++]; // need mul W128
	fpu 0 .complex vreg7 = vreg3 * vreg5 + vreg4;

	fpu 1 rep 32 vreg4 = [ar0++];
	fpu 1 rep 32 vreg5 = [ar6++]; // need mul W128
	fpu 1 .complex vreg7 = vreg3 * vreg5 + vreg4;

	fpu 2 rep 32 vreg4 = [ar0++];
	fpu 2 rep 32 vreg5 = [ar6++]; // need mul W128
	fpu 2 .complex vreg7 = vreg3 * vreg5 + vreg4;

	fpu 3 rep 32 vreg4 = [ar0++];
	fpu 3 rep 32 vreg5 = [ar6++]; // need mul W128
	fpu 3 .complex vreg7 = vreg3 * vreg5 + vreg4;

	fpu 0 rep 32 [ar2++] = vreg6;
	fpu 1 rep 32 [ar2++] = vreg6;
	fpu 2 rep 32 [ar2++] = vreg6;
	fpu 3 rep 32 [ar2++] = vreg6;

	fpu 0 .complex vreg6 = -vreg3 * vreg5 + vreg4;
	fpu 1 .complex vreg6 = -vreg3 * vreg5 + vreg4;
	fpu 2 .complex vreg6 = -vreg3 * vreg5 + vreg4;
	fpu 3 .complex vreg6 = -vreg3 * vreg5 + vreg4;

	fpu 0 rep 32 [ar3++] = vreg7;
	fpu 1 rep 32 [ar3++] = vreg7;
	fpu 2 rep 32 [ar3++] = vreg7;
	fpu 3 rep 32 [ar3++] = vreg7;

	fpu 0 rep 32 [ar2++] = vreg6;
	fpu 1 rep 32 [ar2++] = vreg6;
	fpu 2 rep 32 [ar2++] = vreg6;
	fpu 3 rep 32 [ar2++] = vreg6;
	ar3 = ar4;
	ar2 = ar5;
	gr0--;
	if > goto COMP_FFT1024_2048;
// END FFT1024

// COMPUTE 1 FFT2048
	ar1 = gr2 with gr1 <<= 2;				// 8
	ar0 = gr4;
	ar6 = gr5;
	ar2 = gr7;
	ar3 = ar2 + 2048;

<LAST_LAYER_2048>
	fpu 0 rep 32 vreg0 = [ar1++];
	fpu 1 vreg0 = fpu 0 vreg0;

	fpu 2 rep 32 vreg0 = [ar1++];
	fpu 3 vreg0 = fpu 2 vreg0;

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

	fpu 0 rep 32 [ar2++] = vreg3;
	fpu 2 rep 32 [ar2++] = vreg3;

	fpu 1 rep 32 [ar3++] = vreg3;
	fpu 3 rep 32 [ar3++] = vreg3;
	gr1--;
	if > goto LAST_LAYER_2048;
// END FFT2048

<exit_fft2048>
	pop ar0, gr0;
	pop ar1, gr1;
	pop ar2, gr2;
	pop ar3, gr3;
	pop ar4, gr4;
	pop ar5, gr5;
	pop ar6, gr6;
	return;
end ".data_2048";