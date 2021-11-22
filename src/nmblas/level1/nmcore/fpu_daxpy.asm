///////////
// nmblas (neiro matrix Basic Linear Algebra Subroutines)
//  Copyright (c) RC Module Inc.

// Author : Alexandr Bolotnikov 
// Originaly developed at reserch center "Module" Moscow 
// Year 2017 
///////////

////perpose of the function see in nmblas_daxpy.s file 

global _fpu_daxpy:label;

nobits "nobits"
  buff :long;
end "nobits";

begin "text"
<_fpu_daxpy>

  //test input parametrs
  gr5;
  if <= goto END;//case N is nagative
  gr7 = gr5 << 27;//the reminder
  gr7 = gr7 >> 27;
  gr0 = gr0 <<1;
  gr1 = gr1 <<1;
  gr5 = gr5 >> 5;//the quotient
  if =0 delayed goto REMAINDER with gr7; 

<LOOP>
  ar5 = ar1;
  gr5--;
  fpu 0 rep 32 vreg1 = [ar0++gr0];//load x
  fpu 0 rep 32 vreg2 = [ar1++gr1];//load y
  ar1 = ar5;
  if <>0 delayed goto LOOP with gr7;
  fpu 0 .double vreg1 = vreg1*.retrive(vreg0) + vreg2;//getting result y = y + alpha*x
  fpu 0 rep 32 [ar1++gr1] = vreg1;//upload result into y

<REMAINDER>
  if =0 delayed goto END;
  gr7--;
  vlen = gr7;
  ar5 = ar1;
  fpu 0 rep vlen vreg1 = [ar0++gr0];//load x
  fpu 0 rep vlen vreg2 = [ar1++gr1];//load y
  ar1 = ar5;
  fpu 0 .double vreg1 = vreg1*.retrive(vreg0) + vreg2;//getting result y = y + alpha*x
  fpu 0 rep vlen [ar1++gr1] = vreg1;   

<END>
  return;
end "text";