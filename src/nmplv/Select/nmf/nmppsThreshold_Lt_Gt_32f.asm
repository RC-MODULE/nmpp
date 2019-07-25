
//void nmppsThreshold_Lt_Gt_32f(nm32f* pSrcVec, nm32f* pDstVec, float min, float max,  int size);
global _nmppsThreshold_Lt_Gt_32f: label;

nobits ".data_nmplv"
	buffer_long_min: long;
	buffer_long_max: long;
end ".data_nmplv";

begin ".text_nmplv"
<_nmppsThreshold_Lt_Gt_32f>
	ar5 = ar7-2	;
	push ar0,gr0;
	push ar1,gr1;
	push ar5,gr5;
	push ar6,gr6;
	
	ar0 = [--ar5];

	ar1 = [--ar5];
	gr1 = ar1;
	gr0 = buffer_long_min;
	[gr0] = ar1,gr1;
	fpu 0 rep 32 vreg1 = [gr0];
	
	ar1 = [--ar5];
	gr1 = ar1;
	gr0 = buffer_long_max;
	[gr0] = ar1,gr1;
	fpu 1 rep 32 vreg1 = [gr0];
	
	ar6 = [--ar5];
	gr5 = [--ar5];
	gr5>>=1;
	gr7 = gr5<<27;
	gr7 >>= 27;
	gr7--;
	gr5>>=5;
	if =0 delayed goto After32;
		vlen = gr7;
		gr5--;
<Next32>
	fpu 0 rep 32 vreg0 = [ar0++];
	fpu 0 .float vreg0 - vreg1, set mask if <;		//mask if src < min
	fpu 0 .float vreg0 = mask ? vreg1 : vreg0;
	fpu 1 vreg0 = fpu 0 vreg0; 
	fpu 1 .float vreg0 - vreg1, set mask if >;		//mask if src > max
	if > delayed goto Next32 with gr5--;
		fpu 1 .float vreg0 = mask ? vreg1 : vreg0;
		fpu 1 rep 32 [ar6++] = vreg0;
<After32>
	gr0 = buffer_long_min	with gr7;
	if < delayed goto end_program;
		nul;
		nul;
	fpu 0 rep vlen vreg1 = [gr0];
	gr0 = buffer_long_max;
	fpu 1 rep vlen vreg1 = [gr0];
	
	fpu 0 rep vlen vreg0 = [ar0++];
	fpu 0 .float vreg0 - vreg1, set mask if <;		//mask if src < min
	fpu 0 .float vreg0 = mask ? vreg1 : vreg0;
	fpu 1 vreg0 = fpu 0 vreg0; 
	fpu 1 .float vreg0 - vreg1, set mask if >;		//mask if src > max
	fpu 1 .float vreg0 = mask ? vreg1 : vreg0;
	fpu 1 rep vlen [ar6++] = vreg0;
<end_program>
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar1,gr1;
	pop ar0,gr0;
	return;
end ".text_nmplv";
