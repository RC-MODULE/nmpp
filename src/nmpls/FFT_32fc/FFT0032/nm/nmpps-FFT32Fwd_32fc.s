global _nmppsFFT32Fwd_32fc: label;
global _nmppsFFT32Inv_32fc: label;
data ".data_imu1"
AddrForDFT8_32: word[4] = (0, 4, 2, 6);
end ".data_imu1";

begin ".text"
<_nmppsFFT32Fwd_32fc>
<_nmppsFFT32Inv_32fc>
	set fp_branch;
	ar5 = ar7 - 2;
	push ar6, gr6;
	push ar4, gr4;
	push ar3, gr3;
	push ar2, gr2;
	push ar1, gr1;
	push ar0, gr0;
/*
ar0 = [--ar5];
ar6 = [--ar5];
ar5 = [--ar5];
ar2 = [ar5++];
ar3 = [ar5++];

fpu 0 rep 8 vreg1 = [ar2++];
fpu 0 rep 8 vreg2 = [ar3++];
*/
	ar3 = [--ar5]; // input x
	ar0 = [--ar5]; // output X
	gr6 = ar0;
	gr1 = 8;
	gr0 = gr1 >> 2;
	ar5 = [--ar5];
	ar1 = [ar5++];
	ar2 = [ar5++];

// SinCos
/*	fpu 0 rep 8 vreg1 = [ar1++];
	fpu 1 rep 8 vreg1 = [ar1++];
	fpu 2 vreg1 = fpu 0 vreg1;
	fpu 3 vreg1 = fpu 1 vreg1;
	fpu 0 rep 8 vreg2 = [ar1++];
	fpu 1 rep 8 vreg2 = [ar1++];
	fpu 2 vreg2 = fpu 0 vreg2;
	fpu 3 vreg2 = fpu 1 vreg2;
	fpu 0 rep 8 vreg3 = [ar1++];
	fpu 1 rep 8 vreg3 = [ar1++];
	fpu 2 vreg3 = fpu 0 vreg3;
	fpu 3 vreg3 = fpu 1 vreg3;
	fpu 0 rep 8 vreg4 = [ar1++];
	fpu 1 rep 8 vreg4 = [ar1++];
	fpu 2 vreg4 = fpu 0 vreg4;
	fpu 3 vreg4 = fpu 1 vreg4;
*/
	fpu 0 rep 8 vreg1 = [ar1++];
	fpu 0 rep 8 vreg2 = [ar1++];
	fpu 0 rep 8 vreg3 = [ar1++];
	fpu 0 rep 8 vreg4 = [ar1++];
	
	fpu 1 rep 8 vreg1 = [ar2++];
	fpu 1 rep 8 vreg2 = [ar2++];
	fpu 1 rep 8 vreg3 = [ar2++];
	fpu 1 rep 8 vreg4 = [ar2++];

	fpu 2 vreg1 = fpu 0 vreg1;
	fpu 2 vreg2 = fpu 0 vreg2;
	fpu 2 vreg3 = fpu 0 vreg3;
	fpu 2 vreg4 = fpu 0 vreg4;

	fpu 3 vreg1 = fpu 1 vreg1;
	fpu 3 vreg2 = fpu 1 vreg2;
	fpu 3 vreg3 = fpu 1 vreg3;
	fpu 3 vreg4 = fpu 1 vreg4;
// Compute 4 things of DFT8
	//ar0 = buff_fft32;
	//ar6 = buff_fft32xW;
	//ar5 = [--ar5]; // read third param of func (addr of struct)
	ar0 = [ar5++]; // buff_fft32
	ar6 = [ar5++]; // buff_fft32xW
	gr2 = ar0;
	gr7 = ar6;
	ar4 = AddrForDFT8_32;
	gr3 = [ar4++]; // read first elem of array
<COMP_4_8_32>
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
	if > delayed goto COMP_4_8_32;
	gr3 = [ar4++];
	nul;
// END COMPUTE 4 things of DFT8

// COMPUTE 2 FFT16
	ar2 = gr6;
	//ar5 = ar5 + 5;
	ar1 = [ar5++]; // W8
	//ar1 = W8;
	ar0 = gr2;
	ar6 = gr7;
	fpu 0 rep 8 vreg0 = [ar1++];
	fpu 0 rep 8 vreg1 = [ar0++];
	fpu 0 rep 8 vreg2 = [ar6++];
	fpu 0 rep 8 vreg3 = [ar0++];
	fpu 0 rep 8 vreg4 = [ar6++];
	fpu 0 .complex vreg5 = vreg0 * vreg2 + vreg1;
	fpu 0 .complex vreg6 = -vreg0 * vreg2 + vreg1;
	fpu 0 .complex vreg7 = vreg4 * vreg0 + vreg3;
	fpu 0 .complex vreg4 = -vreg4 * vreg0 + vreg3;
// END FFT16

// COMPUTE 1 FFT32
	//ar5++;
	ar1 = [ar5++]; // W16
	fpu 0 rep 8 vreg0 = [ar1++];
	fpu 0 rep 8 vreg1 = [ar1++];
	fpu 0 .complex vreg2 = vreg0 * vreg7 + vreg5;
	fpu 0 .complex vreg3 = vreg1 * vreg4 + vreg6;
	fpu 0 .complex vreg0 = -vreg0 * vreg7 + vreg5;
	fpu 0 .complex vreg1 = -vreg1 * vreg4 + vreg6;
// END FFT32

	fpu 0 rep 8 [ar2++] = vreg2;
	fpu 0 rep 8 [ar2++] = vreg3;
	fpu 0 rep 8 [ar2++] = vreg0;
	fpu 0 rep 8 [ar2++] = vreg1;
	
<exit_fft32>
	pop ar0, gr0;
	pop ar1, gr1;
	pop ar2, gr2;
	pop ar3, gr3;
	pop ar4, gr4;
	pop ar6, gr6;
	return;
end ".text";