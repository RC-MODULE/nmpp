///////////
// nmblas (neiro matrix Basic Linear Algebra Subroutines)
//  Copyright (c) RC Module Inc.

// Author : Alexandr Bolotnikov 
// Originaly developed at reserch center "Module" Moscow 
// Year 2017 
///////////

global _fpu_snrm2:label;
extern _sqrt:label;

data "data"
  init : long = double(0);
end "data";

nobits "nobits"
  buff : long;  
end "nobits";

begin "text"
<_fpu_snrm2>
  gr5;
  if <= delayed goto END;
  gr7 = false;
  gr0 = gr0<<1;

  gr7 = gr5<<26;
  gr7 = gr7>>26;

  gr5 = gr5 >> 6;
  ar5 = init;
  if =0 delayed goto REMAINDER;
  fpu 0 rep 1 vreg4 = [ar5];//init for reminder 
  fpu 0 vreg2 = vreg4;
//////init;
  gr5--;
  if =0 delayed goto WRAP_UP;  
  fpu 0 rep 32 vreg0 = [ar0++gr0];
  fpu 0 .float vreg2 = vreg0*vreg0;
<LOOP>
  gr5--;
  if <>0 delayed goto LOOP;
  fpu 0 rep 32 vreg0 = [ar0++gr0];
  fpu 0 .float vreg2 = vreg0*vreg0 + vreg2;

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
  fpu 0 .float vreg3 = vreg0*vreg0; 
 <LOOP_REMAINDER>
  if <>0 delayed goto LOOP_REMAINDER;
  fpu 0 .float vreg4 = vreg4 + .retrive(vreg3);
  gr5--;
////
  fpu 0 .packer = vreg4 with .float .in_low <= .float .in_high;
  fpu 0 rep 1 vreg0 = .packer;
  fpu 0 .float vreg4 = vreg0 + vreg4;//resalt is in low part
  fpu 0 .float vreg2 = vreg2 + vreg4;//
////
<CASE_N_IS_1>
  gr5 = gr7<<31;
  if =0 delayed goto RESULT;
  fpu 0 rep 1 vreg0 = [ar0++gr0];
  fpu 0 .float vreg1 = vreg0 * vreg0;
  fpu 0 .float vreg2 = vreg1 + vreg2;  
  

<RESULT>
  fpu 0 .packer = vreg2 with .double <= .float .in_low;
  fpu 0 rep 1 vreg2 = .packer;
  fpu 0 rep 1 [ar7++] = vreg2;
  call _sqrt;
  ar5 = buff;
  [ar5++] = gr7;
  [ar5++] = gr6;
  ar5 = buff;
  fpu rep 1 .packer = [ar5] with .float .in_low <= .double;
  fpu rep 1 [ar5] = .packer;
  gr7 = [ar5];
  ar7 = ar7-2;  

<END>
  return;
end "text";