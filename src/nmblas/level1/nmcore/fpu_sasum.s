///////////
// nmblas (neiro matrix Basic Linear Algebra Subroutines)
//  Copyright (c) RC Module Inc.

// Author : Alexandr Bolotnikov 
// Originaly developed at reserch center "Module" Moscow 
// Year 2017 
///////////

//the purpose of this function see in nmblas_sasum.s file
global _fpu_sasum:label;

data "data"
  .align;
  zero_: long = double(0);
end "data"; 
nobits "nobits"
  .align;
  buff : long;
end "nobits";
begin "text"
<_fpu_sasum>  

  //vreg0 is a accumulator
  //vreg1 is a pupm
  //vreg2 is a result of unroullig
  //vreg4 is a result of unroullig for reminder
  /////
  gr5;//test is N negative or not
  if <= delayed goto END;
  gr7 = false;
  gr0 = gr0<<1;//multiply the increment of array 

  gr7 = gr5>>1;//test is N greater then 1 or not 
  if =0 delayed goto CASE_N_IS_ONE_OR_ZERO;

  gr7 = gr5<<26;//REMAINDER
  gr7 = gr7>>26;
  gr5 = gr5>>6;//quotient

  ar5 = zero_;
  fpu 0 rep 1 vreg4 = [ar5];//init for reminder loop

  if =0 delayed goto REMINDER;
  fpu 0 vreg2 = vreg4;//init to avoid accumulator of result with next function call in case only reminder is counted
  gr5--;
  //init
  fpu 0 rep 32 vreg0 = [ar0++gr0];
  fpu 0 .float vreg0 = /vreg0/;
  if =0  goto WRAP_UP;

<LOOP>  
  gr5--;
  fpu 0 rep 32 vreg1 = [ar0++gr0];
  if <>0 delayed goto LOOP;
  fpu 0 .float vreg1 = /vreg1/;
  fpu 0 .float vreg0 = vreg1 + vreg0;

<WRAP_UP>  
  fpu 0 .packer = vreg0 with .fixed_64 <= .fixed_64;
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
  if =0 delayed goto CASE_REMAINDER_EQ_ONE;
  gr5--;
  vlen = gr5;
  fpu 0 rep vlen vreg3 = [ar0++gr0];
  fpu 0 .float vreg3 = /vreg3/;
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
<CASE_REMAINDER_EQ_ONE>
  gr5 = gr7<<31;
  if =0 delayed goto RESULT;
  fpu 0 rep 1 vreg1 = [ar0++gr0];
  fpu 0 .float vreg1 = /vreg1/;  
  fpu 0 .float vreg2 = vreg1 + vreg2;  
  

<RESULT>
  ar5 = buff;
  fpu 0 rep 1 [ar5] = vreg2;
  gr7 = [ar5];
<END>
  return;
<CASE_N_IS_ONE_OR_ZERO>
  gr5;
  if =0 goto END;//case n is 0
  gr7 = [ar0];
  .align;
  delayed return;
  gr7 = gr7<<1;
  gr7 = gr7>>1;

end "text";