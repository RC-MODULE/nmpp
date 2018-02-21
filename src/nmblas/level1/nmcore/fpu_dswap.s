global _fpu_dswap : label;

begin "text"
<_fpu_dswap>
push ar3,gr3; 
push ar4,gr4; 

  //gr5 = [--ar5];//ammount of elements//N
  //ar0 = [--ar5];//address of x array//X
  //gr0 = [--ar5];//offset of x array//INCX
  //ar1 = [--ar5];//address of y array//Y
  //gr1 = [--ar5];//offset of y array//INCY

  gr0 = gr0<<1;
  gr1 = gr1<<1;

  gr7 = gr5<<26;
  gr7 = gr7>>26;
  gr5 = gr5>>6;
  
  if =0 delayed goto REMINDER with gr7;
  ar3 = ar0;//x bank 
  ar5 = ar1;//y bank
	fpu 0 rep 32 vreg0 = [ar0++gr0];//load x0
	fpu 0 rep 32 vreg1 = [ar1++gr1];//load y0

<LOOP>
	//2
	//load x1	
	fpu 0 rep 32 vreg2 = [ar0++gr0];
	gr4 = ar0;
	//upload y0
	ar1 = ar5;
	fpu 0 rep 32 [ar1++gr1] = vreg0;//upload x0 2 y0
	ar5 = ar1;

	//3
	//upload x0
	ar0 = ar3;
	fpu 0 rep 32 [ar0++gr0] = vreg1;
	ar3 = ar0;
	ar0 = gr4;
	//load y1
	fpu 0 rep 32 vreg3 = [ar1++gr1];
	
	//4
	//load x2
	fpu 0 rep 32 vreg0 = [ar0++gr0];//load x2
	gr4 = ar0;
	//upload y1
	ar1 = ar5;
	fpu 0 rep 32 [ar1++gr1] = vreg2;
	ar5 = ar1;

	//5
	//load y2
	fpu 0 rep 32 vreg1 = [ar1++gr1];
	//upload x1
	ar0 = ar3;
	fpu 0 rep 32 [ar0++gr0] = vreg3;
	gr5--;
	if <>0 delayed goto LOOP with gr7;
  ar3 = ar0;
	ar0 = gr4;


<REMINDER>
	if =0 delayed goto END;
	ar0 = ar3;
	ar1 = ar5;
	gr5 = gr7>>5;
	nop;
	if =0 delayed goto OVER_JUMP;
	gr7 = gr7<<27;
	gr7 = gr7>>27;
	fpu 0 rep 32 vreg0 = [ar0++gr0];//load x 
	fpu 0 rep 32 vreg1 = [ar1++gr1];//load y
	ar0 = ar3;
	ar1 = ar5;
	fpu 0 rep 32 [ar0++gr0] = vreg1;
	fpu 0 rep 32 [ar1++gr1] = vreg0;
	
<OVER_JUMP>
	gr7;
	if =0 delayed goto END;
	gr7--;
	vlen = gr7;
	ar3 = ar0;
	ar5 = ar1;
	fpu 0 rep vlen vreg0 = [ar0++gr0];//load x 
	fpu 0 rep vlen vreg1 = [ar1++gr1];//load y
	ar0 = ar3;
	ar1 = ar5;
	fpu 0 rep vlen [ar0++gr0] = vreg1;
	fpu 0 rep vlen [ar1++gr1] = vreg0;

<END>
pop ar4,gr4;
pop ar3,gr3;
return;
end "text";
