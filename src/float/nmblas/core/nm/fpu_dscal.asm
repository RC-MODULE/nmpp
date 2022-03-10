///////////
// nmblas (neiro matrix Basic Linear Algebra Subroutines)
//  Copyright (c) RC Module Inc.

// Author : Alexandr Bolotnikov 
// Originaly developed at reserch center "Module" Moscow 
// Year 2017 
///////////
//the purpose of thise function see in nmblas_dscal.s file
global _fpu_dscal:label;

begin "text"
<_fpu_dscal>
  gr5;
  if <= delayed goto END;
  gr7 = gr5<<27;//reminder
  gr7 = gr7>>27;
  gr5 = gr5>>5;
  if =0 delayed goto REMAINDER with gr7;
  gr0 = gr0<<1;

<LOOP>  
  ar5 = ar0;//save address of x to upload later
  fpu 0 rep 32 vreg1 = [ar0++gr0];//load x
  ar0 = ar5;
  gr5--;
  if <>0 delayed goto LOOP with gr7;
  fpu 0 .double vreg1 = vreg1 * .retrive(vreg0);//alpha*x
  fpu 0 rep 32 [ar0++gr0] = vreg1;

<REMAINDER>
  if =0 delayed goto END;
  gr7--;
  vlen = gr7;    
  ar5 = ar0;//save address of x to upload later
  fpu 0 rep vlen vreg1 = [ar0++gr0];//load x
  ar0 = ar5;
  fpu 0 .double vreg1 = vreg1 * .retrive(vreg0);//alpha*x
  fpu 0 rep vlen [ar0++gr0] = vreg1;  

<END>
  return;
end "text";