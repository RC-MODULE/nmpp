//***************************************************************************/
//*                     RC Module Inc., Moscow, Russia                      */
//*                     NeuroMatrix(r) NM640x Software                      */
//*                                                                         */
//*   Software design:  A.Brodyazhenko                                      */
//*                                                                         */
//*   File:             nmpps-FFT1024Fwd_32fcr.s                            */
//*   Contents:         Routine for forward and inverse FFT 1024            */
//*                     of complex array with 32 bit elements               */
//***************************************************************************/

global _nmppsFFT1024Fwd_32fcr: label;
global _nmppsFFT1024Inv_32fcr: label;

extern _FFTFwd16x32Core: label;

data ".data_imu2"
AddrForFFT16: word[64] = (
	0, 64, 32, 96, 16, 80, 48, 112, 8, 72, 40, 104, 24, 88, 56, 120,
	4, 68, 36, 100, 20, 84, 52, 116, 12, 76, 44, 108, 28, 92, 60, 124,
	2, 66, 34, 98, 18, 82, 50, 114, 10, 74, 42, 106, 26, 90, 58, 122,
	6, 70, 38, 102, 22, 86, 54, 118, 14, 78, 46, 110, 30, 94, 62, 126
	);
end ".data_imu2";

begin ".text"
<_nmppsFFT1024Fwd_32fcr>
<_nmppsFFT1024Inv_32fcr>
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
	ar5 = [--ar5]; // adress of the struct with W 
	gr1 = 128;
	vlen = 31;

// SORT 64 VECTORS FOR FFT16	
	ar4 = AddrForFFT16;
	ar2 = [ar5++]; 					// 1.0 or 1/1024
	ar0 = [ar5++]; 					// buff_fft1024
	ar6 = [ar5++]; 					// buff_fft1024_mulW
	fpu 0 rep 1 vreg1 = [ar2]; 		// 1.0 or 1/1024
	fpu 1 vreg1 = fpu 0 vreg1;
	gr4 = ar0 with gr0 = gr1 >> 2;  // cycles number;
	gr7 = ar6;
<SORT_64_FFT16>
	gr3 = [ar4++];
	ar1 = ar3 + gr3;
	fpu 0 rep 16 vreg0 = [ar1++gr1];
	fpu 0 .complex vreg0 = vreg0 * .retrive(vreg1);
	gr3 = [ar4++];
	ar1 = ar3 + gr3;
	fpu 1 rep 16 vreg0 = [ar1++gr1];
	fpu 1 .complex vreg0 = vreg0 * .retrive(vreg1);

	fpu 0 rep 16 [ar0++] = vreg0;
	fpu 1 rep 16 [ar6++] = vreg0;
	gr0--;
	if > goto SORT_64_FFT16;
// END SORT

// COMPUTE 64 PART OF FFT16
	
	delayed call _FFTFwd16x32Core;
		ar3 = gr4 with gr1 >>= 2; // step for FFT16 = 32 for input // addr for input buff_fft1024
		gr6 = gr5; 				  // addr for output buff_fft1024
	
	ar5 = ar5 - 7;
	
	delayed call _FFTFwd16x32Core;
		gr6 = [ar5]; 			 // buff_fft1024xW
		ar3 = gr7;
// END FFT16

// COMPUTE 32 OF FFT32
	ar5++ with gr1 <<= 1;
	ar0 = gr5 with gr2 = gr1 >> 3;      // output X
	ar1 = [ar5++];  					// W1024
	ar6 = gr6;      					// buff_fft1024xW
	gr0 = ar1;							// saving of W1024 addr
	ar3 = gr4;      					// buff_fft1024
	ar4 = gr7;      					// buff_fft1024_mulW
	
	fpu 0 rep 16 vreg0 = [ar1++gr1];
	fpu 1 vreg0 = fpu 0 vreg0;
	fpu 2 vreg0 = fpu 1 vreg0;
	fpu 3 vreg0 = fpu 2 vreg0;

<COMP_FFT32_1024>
	fpu 0 rep 16 vreg1 = [ar0++];
	fpu 0 rep 16 vreg2 = [ar6++]; // need mul W
	fpu 0 .complex vreg5 = vreg0 * vreg2 + vreg1;

	fpu 1 rep 16 vreg1 = [ar0++];
	fpu 1 rep 16 vreg2 = [ar6++]; // need mul W
	fpu 1 .complex vreg5 = vreg0 * vreg2 + vreg1;

	fpu 2 rep 16 vreg1 = [ar0++];
	fpu 2 rep 16 vreg2 = [ar6++]; // need mul W
	fpu 2 .complex vreg5 = vreg0 * vreg2 + vreg1;

	fpu 3 rep 16 vreg1 = [ar0++];
	fpu 3 rep 16 vreg2 = [ar6++]; // need mul W
	fpu 3 .complex vreg5 = vreg0 * vreg2 + vreg1;

	fpu 0 rep 16 [ar3++] = vreg5;
	fpu 1 rep 16 [ar4++] = vreg5;

	fpu 0 .complex vreg6 = -vreg0 * vreg2 + vreg1;
	fpu 1 .complex vreg6 = -vreg0 * vreg2 + vreg1;
	fpu 2 .complex vreg6 = -vreg0 * vreg2 + vreg1;
	fpu 3 .complex vreg6 = -vreg0 * vreg2 + vreg1;

	fpu 0 rep 16 [ar3++] = vreg6;
	fpu 1 rep 16 [ar4++] = vreg6;

	fpu 2 rep 16 [ar3++] = vreg5;
	fpu 3 rep 16 [ar4++] = vreg5;
	fpu 2 rep 16 [ar3++] = vreg6;
	fpu 3 rep 16 [ar4++] = vreg6;
	gr2--;
	if > goto COMP_FFT32_1024 ;
// END FFT32

// COMPUTE 16 OF FFT64
	ar1 = gr0;
	ar0 = gr4 with gr1 >>= 1; 				// buff_fft1024
	ar6 = gr7; 								// buff_fft1024_mulW
	ar3 = gr5; 								// output X
	ar4 = gr6 with gr2 = gr1 >> 3;			// buff_fft1024xW
	fpu 0 rep 32 vreg0 = [ar1++gr1]; 		// W32
	fpu 1 vreg0 = fpu 0 vreg0;
	fpu 2 vreg0 = fpu 1 vreg0;
	fpu 3 vreg0 = fpu 2 vreg0;

<COMP_FFT64_1024>
	fpu 0 rep 32 vreg1 = [ar0++];
	fpu 0 rep 32 vreg2 = [ar6++]; // need mul W
	fpu 0 .complex vreg5 = vreg0 * vreg2 + vreg1;

	fpu 1 rep 32 vreg1 = [ar0++];
	fpu 1 rep 32 vreg2 = [ar6++]; // need mul W
	fpu 1 .complex vreg5 = vreg0 * vreg2 + vreg1;

	fpu 2 rep 32 vreg1 = [ar0++];
	fpu 2 rep 32 vreg2 = [ar6++]; // need mul W
	fpu 2 .complex vreg5 = vreg0 * vreg2 + vreg1;

	fpu 3 rep 32 vreg1 = [ar0++];
	fpu 3 rep 32 vreg2 = [ar6++]; // need mul W
	fpu 3 .complex vreg5 = vreg0 * vreg2 + vreg1;

	fpu 0 rep 32 [ar3++] = vreg5;
	fpu 1 rep 32 [ar4++] = vreg5;

	fpu 0 .complex vreg6 = -vreg0 * vreg2 + vreg1;
	fpu 1 .complex vreg6 = -vreg0 * vreg2 + vreg1;
	fpu 2 .complex vreg6 = -vreg0 * vreg2 + vreg1;
	fpu 3 .complex vreg6 = -vreg0 * vreg2 + vreg1;

	fpu 0 rep 32 [ar3++] = vreg6;
	fpu 1 rep 32 [ar4++] = vreg6;

	fpu 2 rep 32 [ar3++] = vreg5;
	fpu 3 rep 32 [ar4++] = vreg5;
	fpu 2 rep 32 [ar3++] = vreg6;
	fpu 3 rep 32 [ar4++] = vreg6;
	gr2--;
	if > goto COMP_FFT64_1024;
// END FFT64

// COMPUTE 8 OF FFT128
	ar0 = gr5; 								// output X
	ar6 = gr6; 								// buff_fft1024xW
	ar1 = gr0 with gr1 >>= 1; // gr1 = 16 	// W1024
	ar3 = gr4 with gr3 = gr1 >> 2; 			// buff_fft1024
	ar4 = gr7; 								// buff_fft1024_mulW

	fpu 0 rep 32 vreg0 = [ar1++gr1]; 		// 1 - W64
	fpu 1 rep 32 vreg0 = [ar1++gr1]; 		// 2 - W64
	fpu 2 vreg0 = fpu 0 vreg0;
	fpu 3 vreg0 = fpu 1 vreg0;

<COMP_FFT128_1024>
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
	if > goto COMP_FFT128_1024;
// END FFT 128

// COMPUTE 4 OF FFT256
	ar0 = gr4; 								// buff_fft1024
	ar6 = gr7; 							   // buff_fft1024_mulW
	ar1 = gr0 with gr1 >>= 1; // gr1 = 8  // W1024
	ar3 = gr5; 							 // output X
	ar4 = gr6 with gr2 = gr1 >> 2; 		// buff_fft1024xW

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
	
<COMP_FFT256_1024>
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
	gr2--;
	if > delayed goto COMP_FFT256_1024;
		ar5 += 256;
// END FFT256

// COMPUTE 2 OF FFT512
	ar0 = gr5; // output X
	ar6 = gr6; // buff_fft1024xW
	ar1 = gr0 with gr1 >>= 1; // W1024
	ar3 = gr4; // buff_fft1024
	ar4 = gr7; // buff_fft1024_mulW

	ar2 = ar0 + 512;
	ar5 = ar6 + 512;

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

	fpu 0 rep 32 [ar3++] = vreg0;
	fpu 2 rep 32 [ar4++] = vreg0;
	fpu 1 rep 32 [ar3++] = vreg0;
	fpu 3 rep 32 [ar4++] = vreg0;

	fpu 0 rep 32 [ar3++] = vreg1;
	fpu 2 rep 32 [ar4++] = vreg1;
	fpu 1 rep 32 [ar3++] = vreg1;
	fpu 3 rep 32 [ar4++] = vreg1;

// END FFT512

// COMPUTE 1 OF FFT1024

	ar0 = gr4; 							// buff_fft1024
	ar6 = gr7; 							// buff_fft1024_mulW
	ar1 = gr0; 							// W1024
	ar2 = gr5; 							// output X
	ar3 = ar2 + 1024 with gr1 <<= 1;

<LAST_LAYER_1024>
	fpu 0 rep 32 vreg0 = [ar1++];
	fpu 1 vreg0 = fpu 0 vreg0;

	fpu 2 rep 32 vreg0 = [ar1++];
	fpu 3 vreg0 = fpu 2 vreg0;

	fpu 0 rep 32 vreg1 = [ar0++];
	fpu 1 rep 32 vreg1 = [ar6++]; // xW
	fpu 0 vreg2 = fpu 1 vreg1;    // xW
	fpu 1 vreg2 = fpu 0 vreg1;

	fpu 0 .complex vreg3 = vreg0 * vreg2 + vreg1; // 1 - FFT32
	fpu 1 .complex vreg3 = -vreg0 * vreg1 + vreg2; // 2 - FFT32

	fpu 2 rep 32 vreg1 = [ar0++];
	fpu 3 rep 32 vreg1 = [ar6++]; // xW
	fpu 2 vreg2 = fpu 3 vreg1;    // xW
	fpu 3 vreg2 = fpu 2 vreg1;

	fpu 2 .complex vreg3 = vreg0 * vreg2 + vreg1; // 1 - FFT32
	fpu 3 .complex vreg3 = -vreg0 * vreg1 + vreg2; // 2 - FFT32

	fpu 0 rep 32 [ar2++] = vreg3;
	fpu 2 rep 32 [ar2++] = vreg3;

	fpu 1 rep 32 [ar3++] = vreg3;
	fpu 3 rep 32 [ar3++] = vreg3;
	gr1--;
	if > goto LAST_LAYER_1024;
	
// END FFT1024

<exit_fft1024>
	pop ar0, gr0;
	pop ar1, gr1;
	pop ar2, gr2;
	pop ar3, gr3;
	pop ar4, gr4;
	pop ar5, gr5;
	pop ar6, gr6;
	return;
end ".text";