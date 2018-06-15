global _LastLayerFFT_32fcr: label;
begin "text"
<_LastLayerFFT_32fcr>
	ar5 = ar7 - 2;
	push ar3, gr3;
	push ar2, gr2;
	push ar1, gr1;
	push ar0, gr0;

	ar0 = [--ar5];		// src1
	ar1 = [--ar5];		// src2
	ar2 = [--ar5];		// dst
	ar3 = [--ar5];		// W
	gr1 = [--ar5];		// N

	ar5 = ar2 + 4096 with gr1--;

<LAST_LAYER>
	fpu 0 rep 32 vreg0 = [ar3++];
	fpu 1 rep 32 vreg0 = [ar3++];
	fpu 2 rep 32 vreg0 = [ar3++];
	fpu 3 rep 32 vreg0 = [ar3++];

	fpu 0 rep 32 vreg1 = [ar0++];
	fpu 0 rep 32 vreg2 = [ar1++]; // need mul W
	fpu 0 .complex vreg5 = vreg0 * vreg2 + vreg1;
	fpu 0 .complex vreg6 = -vreg0 * vreg2 + vreg1;

	fpu 1 rep 32 vreg1 = [ar0++];
	fpu 1 rep 32 vreg2 = [ar1++]; // need mul W
	fpu 1 .complex vreg5 = vreg0 * vreg2 + vreg1;
	fpu 1 .complex vreg6 = -vreg0 * vreg2 + vreg1;
	
	fpu 2 rep 32 vreg1 = [ar0++];
	fpu 2 rep 32 vreg2 = [ar1++]; // need mul W
	fpu 2 .complex vreg5 = vreg0 * vreg2 + vreg1;
	fpu 2 .complex vreg6 = -vreg0 * vreg2 + vreg1;
	
	fpu 3 rep 32 vreg1 = [ar0++];
	fpu 3 rep 32 vreg2 = [ar1++]; // need mul W
	fpu 3 .complex vreg5 = vreg0 * vreg2 + vreg1;
	fpu 3 .complex vreg6 = -vreg0 * vreg2 + vreg1;

	fpu 0 rep 32 [ar2++] = vreg5;
	fpu 1 rep 32 [ar2++] = vreg5;
	fpu 2 rep 32 [ar2++] = vreg5;
	fpu 3 rep 32 [ar2++] = vreg5;

	fpu 0 rep 32 [ar5++] = vreg6;
	fpu 1 rep 32 [ar5++] = vreg6;

	if > delayed goto LAST_LAYER with gr1--;
		fpu 2 rep 32 [ar5++] = vreg6;
		fpu 3 rep 32 [ar5++] = vreg6;

<exit_LastLayerFFT_32fcr>
	pop ar0, gr0;
	pop ar1, gr1;
	pop ar2, gr2;
	pop ar3, gr3;
	return;
end "text";