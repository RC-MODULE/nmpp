global _Split_32fcr: label;
begin "text"
<_Split_32fcr>
	ar5 = ar7 - 2;
	push ar3, gr3;
	push ar2, gr2;
	push ar1, gr1;
	push ar0, gr0;

	ar0 = [--ar5];			// input
	ar1 = [--ar5];			// output1
	ar2 = [--ar5];			// output2
	gr7 = [--ar5];			// size N

	gr0 = 4;
	ar3 = ar0 + 2 with gr3 = gr0;

	gr1 = gr7 >> 6;			// count of the iterations
	if =0 delayed goto Split_32fcr_less64;
		gr7 <<= 26;
		gr7 >>= 26;

<Loop_Split_32fcr>
	fpu 0 rep 32 vreg0 = [ar0++gr0];
	fpu 1 rep 32 vreg0 = [ar3++gr3];
	gr1--;
	if > delayed goto Loop_Split_32fcr;
		fpu 0 rep 32 [ar1++] = vreg0;
		fpu 1 rep 32 [ar2++] = vreg0;

	gr7 >>= 1;
	if =0 delayed goto exit_Split_32fcr;
<Split_32fcr_less64>
	gr7--;
	vlen = gr7;
	fpu 0 rep vlen vreg0 = [ar0++gr0];
	fpu 1 rep vlen vreg0 = [ar3++gr3];
	fpu 0 rep vlen [ar1++] = vreg0;
	fpu 1 rep vlen [ar2++] = vreg0;

<exit_Split_32fcr>
	pop ar0, gr0;
	pop ar1, gr1;
	pop ar2, gr2;
	pop ar3, gr3;
	return;
end "text";