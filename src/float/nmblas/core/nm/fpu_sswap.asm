///////////
// nmblas (neiro matrix Basic Linear Algebra Subroutines)
//  Copyright (c) RC Module Inc.

// Author : Alexandr Bolotnikov 
// Originaly developed at reserch center "Module" Moscow 
// Year 2017 
///////////

global _fpu_sswap:label;

begin "text"
<_fpu_sswap>
  push ar4,gr4;
  gr5;
  if <= delayed goto END;//case inc_y is negative
  gr7 = gr5 << 26;//reminder
  gr7 = gr7 >> 26;
  gr5 = gr5 >> 6;//there is a quotient there
  if =0 delayed goto REMAINDER; 
<LOOP>
  ar5 = ar0;
  ar4 = ar1;
  gr5--;
  fpu 0 rep 32 vreg0 = [ar0++];//load x into fpu
  fpu 0 rep 32 vreg1 = [ar1++];//load y into fpu 
  ar0 = ar5;
  ar1 = ar4;
  if <>0 delayed goto LOOP;  
  fpu 0 rep 32 [ar0++] = vreg1;//upload y into x plase
  fpu 0 rep 32 [ar1++] = vreg0;//upload x intp y plase

<REMAINDER>
  gr5 = gr7>>1;
  if =0 delayed goto REMAINDER_THE_LAST; 
  gr5--;
  vlen = gr5;
  ar5 = ar0;
  ar4 = ar1;
  fpu 0 rep vlen vreg0 = [ar0++];//load x into fpu
  fpu 0 rep vlen vreg1 = [ar1++];//load y into fpu 
  ar0 = ar5;
  ar1 = ar4;
  fpu 0 rep vlen [ar0++] = vreg1; 
  fpu 0 rep vlen [ar1++] = vreg0;
<REMAINDER_THE_LAST>
 
  gr7 = gr7<<31;
  if =0 delayed goto END;
  
  gr7 = [ar0];//load the last x
  gr5 = [ar1];//load the last y
  [ar0] = gr5;//upload the last y into x
  [ar1] = gr7;//upload the last x into y
<END>  
  pop ar4,gr4;
  return;
end "text";