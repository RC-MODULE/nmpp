///////////
// nmblas (neiro matrix Basic Linear Algebra Subroutines)
//  Copyright (c) RC Module Inc.

// Author : Alexandr Bolotnikov 
// Originaly developed at reserch center "Module" Moscow 
// Year 2017 
///////////

//the purpose of this function see in nmblas_sdot.s file 
global _fpu_sdot:label;

data "data"
  init : long = double(0);
end "data";

nobits "nobits"
  buff : long;  
end "nobits";

begin "text"
<_fpu_sdot>
  gr5;
  if <= delayed goto END;
  gr7 = false;//return in case n is nagative or 0
  nop;

  ar5 = init;
  fpu 0 rep 1 vreg4 = [ar5];//init for reminder 
  fpu 0 vreg2 = fpu 0 vreg4; 
  
  gr7 = gr5<<26;
  gr7 = gr7>>26;
  gr5 = gr5>>6;

  
  if =0 delayed goto REMAINDER;
  gr0 = gr0+gr0;
  gr1 = gr1+gr1;

  gr5--;
  fpu 0 rep 32 vreg0 = [ar0++gr0];//load x
  if =0 delayed goto WRAP_UP;
  fpu 0 rep 32 vreg1 = [ar1++gr1];//load y
  fpu 0 .float vreg2 = vreg1*vreg0;

<LOOP>
  gr5--;
  fpu 0 rep 32 vreg0 = [ar0++gr0]; 
  if <>0 delayed goto LOOP;
  fpu 0 rep 32 vreg1 = [ar1++gr1];
  fpu 0 .float vreg2 = vreg1*vreg0+vreg2;

<WRAP_UP>
  fpu 0 .packer = vreg2 with .fixed_64 <= .fixed_64;
  fpu 0 rep 16 vreg0 = .packer;
  fpu 0 rep 16 vreg1 = .packer;
  fpu 0 .float vreg2 = vreg0 + vreg1;

  fpu 0 .packer = vreg2 with .fixed_64 <= .fixed_64;
  fpu 0 rep 8 vreg0 = .packer;
  fpu 0 rep 8 vreg1 = .packer;
  fpu 0 .float vreg2 = vreg0 + vreg1;

  fpu 0 .packer = vreg2 with .fixed_64 <= .fixed_64;
  fpu 0 rep 4 vreg0 = .packer;
  fpu 0 rep 4 vreg1 = .packer;
  fpu 0 .float vreg2 = vreg0 + vreg1;

  fpu 0 .packer = vreg2 with .fixed_64 <= .fixed_64;
  fpu 0 rep 2 vreg0 = .packer;
  fpu 0 rep 2 vreg1 = .packer;
  fpu 0 .float vreg2 = vreg0 + vreg1;

  fpu 0 .packer = vreg2 with .fixed_64 <= .fixed_64;
  fpu 0 rep 1 vreg0 = .packer;
  fpu 0 rep 1 vreg1 = .packer;
  fpu 0 .float vreg2 = vreg0 + vreg1;
////
  fpu 0 .packer = vreg2 with .float .in_low <= .float .in_high;
  fpu 0 rep 1 vreg0 = .packer;
  fpu 0 .float vreg2 = vreg0 + vreg2;//resalt is in low part

<REMAINDER>
  gr7;
  if =0 delayed goto RESULT;
  gr5 = gr7>>1;
  nop;
  if =0 delayed goto CASE_N_IS_1;
  gr5--;
  vlen = gr5;
  fpu 0 rep vlen vreg0 = [ar0++gr0];
  fpu 0 rep vlen vreg1 = [ar1++gr1];
  fpu 0 .float vreg3 = vreg1*vreg0; 
 <LOOP_REMINDER>
  if <>0 delayed goto LOOP_REMINDER;
  fpu 0 .float vreg4 = vreg4 + .retrive(vreg3);
  gr5--;
////
  fpu 0 .packer = vreg4 with .float .in_low <= .float .in_high;
  fpu 0 rep 1 vreg0 = .packer;
  fpu 0 .float vreg4 = vreg0 + vreg4;//resalt is in low part
  fpu 0 .float vreg2 = vreg2 + vreg4;//
///
<CASE_N_IS_1>
  gr5 = gr7<<31;
  if =0 delayed goto RESULT;
  fpu 0 rep 1 vreg0 = [ar0++gr0];
  fpu 0 rep 1 vreg1 = [ar1++gr1];
  fpu 0 .float vreg1 = vreg1 * vreg0;
  fpu 0 .float vreg2 = vreg1 + vreg2;  
  

<RESULT>
  ar5 = buff;
  fpu 0 rep 1 [ar5] = vreg2;
  gr7 = [ar5];

<END>
  return;
end "text";