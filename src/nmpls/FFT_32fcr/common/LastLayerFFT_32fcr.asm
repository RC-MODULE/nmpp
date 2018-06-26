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

	ar5 = ar2 + 4096;

<LAST_LAYER>
	fpu 0 rep 32 vreg0 = [ar3++];
	fpu 1 vreg0 = fpu 0 vreg0;

	fpu 2 rep 32 vreg0 = [ar3++];
	fpu 3 vreg0 = fpu 2 vreg0;

	fpu 0 rep 32 vreg1 = [ar0++];
	fpu 1 rep 32 vreg1 = [ar1++]; // xW
	fpu 0 vreg2 = fpu 1 vreg1;    // xW
	fpu 1 vreg2 = fpu 0 vreg1;

	fpu 0 .complex vreg3 = vreg0 * vreg2 + vreg1;
	fpu 1 .complex vreg3 = -vreg0 * vreg1 + vreg2;

	fpu 2 rep 32 vreg1 = [ar0++];
	fpu 3 rep 32 vreg1 = [ar1++]; // xW
	fpu 2 vreg2 = fpu 3 vreg1;    // xW
	fpu 3 vreg2 = fpu 2 vreg1;

	fpu 2 .complex vreg3 = vreg0 * vreg2 + vreg1;
	fpu 3 .complex vreg3 = -vreg0 * vreg1 + vreg2;

	fpu 0 rep 32 [ar2++] = vreg3;
	fpu 2 rep 32 [ar2++] = vreg3;

	fpu 1 rep 32 [ar5++] = vreg3;
	fpu 3 rep 32 [ar5++] = vreg3;
	gr1--;
	if > goto LAST_LAYER;


<exit_LastLayerFFT_32fcr>
	pop ar0, gr0;
	pop ar1, gr1;
	pop ar2, gr2;
	pop ar3, gr3;
	return;
end "text";