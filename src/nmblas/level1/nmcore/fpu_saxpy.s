///////////
// nmblas (neiro matrix Basic Linear Algebra Subroutines)
//  Copyright (c) RC Module Inc.

// Author : Alexandr Bolotnikov 
// Originaly developed at reserch center "Module" Moscow 
// Year 2017 
///////////

global _fpu_saxpy:label;

nobits "nobits"
  buff:long;
end "nobits";

begin "text"
<_fpu_saxpy>

  //test input parametrs
  ar5 = gr7;//save alpha
  gr7 = gr5>>31;
  if <>0 delayed goto END;//case N is nagative
  gr7 = gr0>>31;
  nop;
  if <>0 delayed goto END;//case inc_x is negative
  gr7 = gr1>>31;
  nop;
  if <>0 delayed goto END;//case inx_y is negative  
  gr7 = ar5;//assert alpha back
  gr7;
  if =0 delayed goto END;//case alpha eqs zero

 

  //upload alpha to put into fpu register
  ar5 = buff;
  [ar5++] = gr7;
  [ar5] = gr7;
  ar5--;
  //
  fpu 0 rep 1 vreg0 = [ar5];//alpha

  gr7 = gr5 << 26;//the reminder
  gr7 = gr7 >> 26;

  gr5 = gr5 >> 6;//the quotient
  if =0 delayed goto REMINDER; 

<LOOP>
  ar5 = ar1;
  gr5--;
  fpu 0 rep 32 vreg1 = [ar0++];//load x
  fpu 0 rep 32 vreg2 = [ar1++];//load y
  ar1 = ar5;
  if <>0 delayed goto LOOP;
  fpu 0 .float vreg1 = vreg1*.retrive(vreg0) + vreg2;//getting result y = y + alpha*x
  fpu 0 rep 32 [ar1++] = vreg1;//upload result into y

<REMINDER>
  gr5 = gr7>>1;
  if =0 delayed goto REMINDER_THE_LAST;
  gr5--;
  vlen = gr5;
  ar5 = ar1;
  fpu 0 rep vlen vreg1 = [ar0++];//load x
  fpu 0 rep vlen vreg2 = [ar1++];//load y
  ar1 = ar5;
  fpu 0 .float vreg1 = vreg1*.retrive(vreg0) + vreg2;//getting result y = y + alpha*x
  fpu 0 rep vlen [ar1++] = vreg1;   

<REMINDER_THE_LAST>  
  gr7 = gr7<<31;
  
  if =0 delayed goto END;

  ar5 = buff;
  fpu 0 rep 1 vreg1 = [ar0];//load x
  fpu 0 rep 1 vreg2 = [ar1];//load y 
  fpu 0 .float vreg1 = vreg1*.retrive(vreg0) + vreg2;//getting result y = y + alpha*x
  fpu 0 rep 1 [ar5] = vreg1;//upload result into buff

  gr7 = [ar5];//load the low part of double word
  [ar1] = gr7;//upload the last element of array y  
<END>
  return;
end "text";