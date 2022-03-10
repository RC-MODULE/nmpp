global _nmppsConvertRisc_32u8u: label;
begin ".text_nmplv"
<_nmppsConvertRisc_32u8u>
	ar5 = ar7 - 2;
	push ar6, gr6;
	push ar5, gr5;
	push ar4, gr4;
	push ar3, gr3;
	push ar2, gr2;
	push ar1, gr1;
	push ar0, gr0;

	ar0 = [--ar5]; // input
	ar1 = [--ar5]; // output
	gr6 = [--ar5]; // size N

	gr6 >>= 2;

<Convert32u8u>
	ar2, gr2 = [ar0++];
	ar3, gr3 = [ar0++];
	gr0 = ar2 with gr2 <<= 8;
	gr1 = ar3 with gr3 <<= 24;
	gr1 <<= 16;
	gr4 = gr0 or gr2;
	gr5 = gr1 or gr3;
	gr6--;
	if > delayed goto Convert32u8u;
		gr4 = gr4 or gr5;
		[ar1++] = gr4;

<exit_Conv32u8u>
	pop ar0, gr0;
	pop ar1, gr1;
	pop ar2, gr2;
	pop ar3, gr3;
	pop ar4, gr4;
	pop ar5, gr5;
	pop ar6, gr6;
	return;
end ".text_nmplv";
