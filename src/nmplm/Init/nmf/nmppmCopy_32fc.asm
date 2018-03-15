global _nmppmCopy_32fc : label;
global _nmppmCopy_64f  : label;
begin "text"
<_nmppmCopy_32fc>
<_nmppmCopy_64f>
	ar5 = ar7 -2;
	push ar0,gr0;
	push ar1,gr1;
	push ar2,gr2;
	push ar3,gr3;
	push ar4,gr4;
	push ar5,gr5;
	push ar6,gr6;

	ar0 = [--ar5];//src addr
	gr0 = [--ar5];//srs stride
	ar1 = [--ar5];//dst addr
	gr1 = [--ar5];//dst stride
	gr2 = [--ar5];//Height
	gr3 = [--ar5];//Width
	gr6 = 2;
	gr4 = gr6;

	gr7 = gr3-gr2;
	if < delayed goto COPY_COL2COL;
	ar4 = ar0 with gr0 = gr0 << 1;//saved addr of srs
	ar6 = ar1 with gr1 = gr1 << 1;//saved addr of dst
<COPY_ROW2ROW>
	gr7 = gr3 << 27;
	gr3 = gr3 >> 5;//quotient of row length
	if =0 delayed goto REMINDER_ROW;
	gr7 = gr7 >> 27;//reminder of row length
	ar5 = gr2;//saved row counter to reload it later
	
<LOOP_ROW2ROW>// also it is a label for loop collume 2 collume
	ar4 = ar0;
	ar6 = ar1 with gr2--;
	fpu 0 rep 32 vreg0 = [ar4++gr4];
	fpu 0 rep 32 [ar6++gr6] = vreg0;
	if <>0 delayed goto LOOP_ROW2ROW;
	ar0 = ar0+gr0;
	ar1 = ar1+gr1; 
	
	gr3--;
	gr2 = ar5;
	if <>0 delayed goto LOOP_ROW2ROW with gr7;	
	ar0 = ar2 with gr0 = -gr0 noflags;
	ar1 = ar3 with gr1 = -gr1 noflags;

<REMINDER_ROW>
	if =0 delayed goto END with gr7-- noflags;
	vlen = gr7;
	gr7++;
	gr7 = gr7 - gr2;
	gr7 = vlen;
	if < delayed goto COPY_COL2COL;
	gr7++;
	gr3 = gr7;
<LOOP_ROW2ROW_REMINDER>
	ar4 = ar0;
	ar6 = ar1 with gr2--;
	fpu 0 rep vlen vreg0 = [ar4++gr4];
	fpu 0 rep vlen [ar6++gr6] = vreg0;
	if <>0 delayed goto LOOP_ROW2ROW_REMINDER;
	ar0 = ar0+gr0;
	ar1 = ar1+gr1;
	delayed goto END; 

<COPY_COL2COL>
	// gr2 Height
	// gr3 Width
	gr7 = gr2 << 27;
	ar6 = ar1 with gr2 = gr2 >> 5;
	if =0 delayed goto REMINDER_COL;
	ar4 = ar0 with gr7 = gr7 >> 27;
	ar5 = gr3;

<LOOP_COL2COL>
	ar0 = ar4;
	ar1 = ar6 with gr3--;
	fpu 0 rep 32 vreg0 = [ar0++gr0];
	fpu 0 rep 32 [ar1++gr1] = vreg0;
	if <>0 delayed goto LOOP_COL2COL;
	ar4 = ar4+gr4;
	ar6 = ar6+gr6;

	gr2--;
	gr3 = ar5;
	if <>0 delayed goto LOOP_COL2COL with gr7; 
	ar4 = ar0 with gr4 = -gr4 noflags;
	ar6 = ar1 with gr6 = -gr6 noflags;

<REMINDER_COL>
	if =0 delayed goto END with gr7-- noflags;
	vlen = gr7;
	gr7++;
	gr7 = gr7 - gr3;
	gr7 = vlen;
	if < delayed goto COPY_ROW2ROW;
	gr7++;
	gr2  = gr7;
<LOOP_COL2COL_REM>
	ar0 = ar4;
	ar1 = ar6 with gr3--;
	fpu 0 rep vlen vreg0 = [ar0++gr0];
	fpu 0 rep vlen [ar1++gr1] = vreg0;
	if <>0 delayed goto LOOP_COL2COL_REM;
	ar4 = ar4+gr4;
	ar6 = ar6+gr6;

<END>
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar4,gr4;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;
	return;
end "text";