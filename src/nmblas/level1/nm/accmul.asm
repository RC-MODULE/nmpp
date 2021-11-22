global _accmul32_64f : label;

data ".data_nmblas"
	result: long ;
end ".data_nmblas";

begin ".text_nmblas"
<_accmul32_64f>
	
	ar5 = ar7-2;
	push ar0,gr0;
	push ar1,gr1;
	push ar2,gr2;
	push ar3,gr3;
	
	ar0 = [--ar5];	// a
	ar1 = [--ar5];	// b
	ar2 = [--ar5];	// c
	ar3 = [--ar5];	// d
	gr7 = [--ar5];	// size
	gr7>>=5; 		// size/32
	gr7--;			// loop counter --
	ar5 = ar3;		// store dst address
	<next_accmul32>
		fpu 0 rep 32 vreg0 = [ar0++]; 
		fpu 0 rep 32 vreg1 = [ar1++]; 
		fpu 0 rep 32 vreg2 = [ar2++]; 
		fpu 0 .double vreg3 = vreg0*vreg1+vreg2;
		fpu 0 rep 32 [ar3++] = vreg3;
	if <>0 goto next_accmul32 with gr7--;
	
	
	// read first product
	gr7 = [ar5++];
	gr6 = [ar5];
	
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;

	return;
end ".text_nmblas";
