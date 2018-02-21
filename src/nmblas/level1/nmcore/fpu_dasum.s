///////////
// nmblas (neiro matrix Basic Linear Algebra Subroutines)
//  Copyright (c) RC Module Inc.

// Author : Alexandr Bolotnikov 
// Originaly developed at reserch center "Module" Moscow 
// Year 2017 
///////////

global _fpu_dasum:label;

data "data"
  .align;
  zero_: long = double(0);
end "data";
 
nobits "nobits"
  .align;
  buff : long;
end "nobits";

begin "text"
<_fpu_dasum>  
  //vreg0 is a accumulator
  //vreg1 is a pupm
  //vreg2 is a result of unroullig
  //vreg4 is a result of unroullig for reminder
  /////
  gr5;
  if <= delayed goto END;
  gr7 = false;
  gr6 = false;
  /////check case n is one
  gr7 = gr5<<27;//REMINDER
  gr7 = gr7>>27;
  gr0 = gr0<<1;
  gr5 = gr5>>5;//quotient

  ar5 = zero_;

  if =0 delayed goto REMINDER;
  fpu 0 rep 1 vreg2 = [ar5];//init for reminder loop
  gr5--;
  //init
  fpu 0 rep 32 vreg0 = [ar0++gr0];
  fpu 0 .double vreg0 = /vreg0/;
  if =0  goto WRAP_UP;

<LOOP>  
  gr5--;
  fpu 0 rep 32 vreg1 = [ar0++gr0];
  if <>0 delayed goto LOOP;
  fpu 0 .double vreg1 = /vreg1/;
  fpu 0 .double vreg0 = vreg1 + vreg0;

<WRAP_UP>  
  fpu 0 .packer = vreg0 with .fixed_64 <= .fixed_64;
  fpu 0 rep 16 vreg0 = .packer;
  fpu 0 rep 16 vreg1 = .packer;
  fpu 0 .double vreg2 = vreg0 + vreg1;

  fpu 0 .packer = vreg2 with .fixed_64 <= .fixed_64;
  fpu 0 rep 8 vreg0 = .packer;
  fpu 0 rep 8 vreg1 = .packer;
  fpu 0 .double vreg2 = vreg0 + vreg1;

  fpu 0 .packer = vreg2 with .fixed_64 <= .fixed_64;
  fpu 0 rep 4 vreg0 = .packer;
  fpu 0 rep 4 vreg1 = .packer;
  fpu 0 .double vreg2 = vreg0 + vreg1;

  fpu 0 .packer = vreg2 with .fixed_64 <= .fixed_64;
  fpu 0 rep 2 vreg0 = .packer;
  fpu 0 rep 2 vreg1 = .packer;
  fpu 0 .double vreg2 = vreg0 + vreg1;

  fpu 0 .packer = vreg2 with .fixed_64 <= .fixed_64;
  fpu 0 rep 1 vreg0 = .packer;
  fpu 0 rep 1 vreg1 = .packer;
  fpu 0 .double vreg2 = vreg0 + vreg1;

<REMINDER>
  gr7;
  if =0 delayed goto RESULT;
  gr7--;
  vlen = gr7;
  fpu 0 rep vlen vreg3 = [ar0++gr0];
  fpu 0 .double vreg3 = /vreg3/;
 <LOOP_REMINDER>
  if <>0 delayed goto LOOP_REMINDER;
  fpu 0 .double vreg2 = vreg2 + .retrive(vreg3);
  gr7--;
  

<RESULT>
  ar5 = buff;
  fpu 0 rep 1 [ar5] = vreg2;
  gr7 = [ar5++];
  gr6 = [ar5++];
<END>
  return;
end "text";